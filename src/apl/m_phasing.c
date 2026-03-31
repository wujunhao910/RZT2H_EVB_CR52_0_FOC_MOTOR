/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* System Name  : RZ/T2H Motor Solution Kit
* File Name    : m_phasing.c
* Version      : 1.0
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Algorithms to implement different modes of rotor phasing
*******************************************************************************/

#include <math.h>
#include "m_common.h"

void forced_phasing(t_motor *pm)
{
    if (pm->phasing_timer == 0)
    {
        return;
    }
    if(SW12_4 == 0) /* SW12_4 : ON */
    {
	    /* Check if this is the first entry into the wait state */
	    if (pm->phasing_timer == pm->phasing_time)
	    {
	        /* Apply Phase Voltage*/
	        pm->output_q = pm->phasing_power;
	        pm->phase_vector = 1;
	        commutate_set(pm);
	        update_pwm(pm);
	    }
	    
	    if (pm->phasing_timer == (pm->phasing_time / 2))
	    {
	        /* Apply Phase Voltage*/
	        pm->output_q = pm->phasing_power;
	        pm->phase_vector = 0;
	        commutate_set(pm);
	        update_pwm(pm);
	    }
    }
	else
	{
	    /* Check if this is the first entry into the wait state */
	    if (pm->phasing_timer == pm->phasing_time)
	    {
	        /* Apply Phase Voltage*/
	        pm->output_q = pm->phasing_power;
	        pm->phase_vector = 0;
	        commutate_set(pm);
	        update_pwm(pm);
	    }
	}

    /* Waits motor to settle for X time slices */
    pm->phasing_timer--;
    if (pm->phasing_timer > 0)
    {
        return;
    }
    
    /* Set the phase origin to the current position */
    pm->phase_origin = pm->crnt_pos; 
    
    /* Set the current positoin equal to the command position to avoid position error (in case servo is on) */
    pm->cmd_pos = pm->crnt_pos;
    
    /* Indicate the phasing is completed */
    pm->aligning = 0;
    pm->act_state |= ACT_Aligned;
    
    /* Remove Phase Voltage */
    pm->output_q = 0;
    commutate_set(pm);
    update_pwm(pm);
}

void hall_phasing(t_motor *pm)
{
    long angle;
    
    /* Check for hall sensors transition */
    if (pm->hall_state_1 == pm->hall_state)
    {
        return;
    }
    
    /* Validate the transition by comparing the position to 1/6 ecpr value */
    
    /* Determine the angle of the rotor */
    switch (pm->hall_state_1)
    {
    case 2:     /* 0 - 60 deg sector */
        if (pm->hall_state == 6)
        {
            angle = 60;
        }
        else if (pm->hall_state == 3)
        {
            angle = 0;
        }
        else
        {
            return;     
        }
        break;
    case 6:     /* 60 - 120 deg sector */
        if (pm->hall_state == 4)
        {
            angle = 120;
        }
        else if (pm->hall_state == 2)
        {
            angle = 60;
        }
        else
        {
            return;     
        }
        break;
    case 4:     /* 120 - 180 deg sector */
        if (pm->hall_state == 5)
        {
            angle = 180;
        }
        else if (pm->hall_state == 6)
        {
            angle = 120;
        }
        else
        {
            return;     
        }
        break;
    case 5:     /* 180 - 240 deg sector */
        if (pm->hall_state == 1)
        {
            angle = 240;
        }
        else if (pm->hall_state == 4)
        {
            angle = 180;
        }
        else
        {
            return;     
        }
        break;
    case 1:     /* 240 - 300 deg sector */
        if (pm->hall_state == 3)
        {
            angle = 300;
        }
        else if (pm->hall_state == 5)
        {
            angle = 240;
        }
        else
        {
            return;     
        }
        break;
    case 3:     /* 300 - 360 deg sector */
        if (pm->hall_state == 2)
        {
            angle = 0;
        }
        else if (pm->hall_state == 1)
        {
            angle = 300;
        }
        else
        {
            return;     
        }
        break;
    }
    
    /* Set the desired flux orientation 90 deg away from the current position */
    pm->phase_origin = pm->crnt_pos - (long)(((float)(angle - 30) * pm->ec_per_ecycle) / 360.0);
    
    /* Indicate the phasing is completed */
    pm->aligning = 0;
    pm->act_state |= ACT_Aligned;
}

void dither_phasing(t_motor *pm)
{
    if (pm->phasing_timer == 0)
    {
        return;
    }
    
    /* Scale the output from +/-32767 to +/-1*/  
    float pwm_out_q =  pm->phasing_power * (1/32768.0);  
    float pwm_out_d =  0;
    
    float angle = (double)(pm->crnt_pos - pm->phase_origin) * pm->counts2rad;
    __sincosf(angle, &pm->angle_sin, &pm->angle_cos);
    
    /* Inverse Park Transformation */
    pm->calc_alpha= pwm_out_d * pm->angle_cos - pwm_out_q * pm->angle_sin;
    pm->calc_beta = pwm_out_q * pm->angle_cos + pwm_out_d * pm->angle_sin;

    /* Space Vector Modulation. Result is +/-0.5 in pm->out_u/v/w */
    commutate_svm(pm, pm->calc_alpha, pm->calc_beta);
    update_pwm(pm);    
    
    pm->dither_timer--;
    /* Wait for dither time */
    if (pm->dither_timer > 0)			
    {
        return;
    }
    
    pm->dither_timer = pm->phasing_time >> 7;
    if (pm->dither_timer < 2)
    {
        pm->dither_timer = 2;
    }
    
    /* Calculate velocity */
    pm->dither_vel = pm->crnt_pos - pm->dither_last_pos;
    pm->dither_last_pos = pm->crnt_pos;
    
    /* Calculate Acceleration */
    pm->dither_acc = pm->dither_vel - pm->dither_last_vel; 
    pm->dither_last_vel = pm->dither_vel;

    /* Wait two dithering cycles */
    pm->dither_cycles++;
    if (pm->dither_cycles < 2)
    {
        return;
    }
    
    pm->dither_cycles = 0;
    
    /* Change flux angle estimate */
    if (pm->dither_acc >= 0)
    {
        pm->phase_origin += pm->dither_delta;
    } 
    else
    { 
        pm->phase_origin -= pm->dither_delta;
    }
    
    /* Reduce dither delta by 25% */
    pm->dither_delta -= pm->dither_delta >> 2;
    if (pm->dither_delta > 10)                  /* phasing accuracy [encoder counts] */
    {
        return;
    }
    
    /* Wait another 1/16th of the phasing time */
    pm->phasing_timer -= pm->phasing_time >> 4;
    if (pm->phasing_timer > 0)
    {
       return;
    }
    
    /* Shift the phase origin at 90 deg from the current position */
    pm->phase_origin += pm->crnt_pos - pm->ec_per_ecycle >> 2;
    
    /* Stop the phasing procedure */
    pm->phasing_timer = 0;
    servo_off(pm);
    
    /* Indicate the phasing is completed */
    pm->aligning = 0;
    pm->act_state |= ACT_Aligned;
}
