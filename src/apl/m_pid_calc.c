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
* File Name    : m_pid_calc.c
* Version      : 1.0
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Source file of PID Calculation.
*******************************************************************************/



#include "m_common.h"

long pid_calc(t_motor *pm, long posErr)
{
    long pidOut;
    short err16;
    
    /* Clip position error to signed short integer */
    if (posErr > 32767)
    {
        posErr = 32767;
    }
    else if (posErr < -32767)
    {
        posErr = -32767;
    }
    else
    {
        /* Do Nothing */
    }

    /* Calculate the position error derivative */
    err16 = pm->pos_error;
    pm->pos_error = (short)posErr;
    pm->derivative_err = pm->pos_error - err16;

    /* Integrate the position error */
    pm->integral_err += posErr;
    
    /* Clip integral within the Integral Limit parameter */
    if (pm->integral_err > pm->integral_limit)
    {
        pm->integral_err = pm->integral_limit;
    }
    else if (pm->integral_err < -pm->integral_limit)
    {
        pm->integral_err = -pm->integral_limit;
    }
    else
    {
        /* Do Nothing */
    }

    /* Add proportional, derivative and intergral terms */
    pidOut = ((long)(pm->integral_err) * (long)(pm->crnt_ki)) >> 8;
    pidOut += pm->derivative_err * pm->crnt_kd;
    pidOut += (long)(pm->pos_error) * (long)(pm->crnt_kp);

    /* Add velocity and acceleration feed forward */ 
    pidOut += (pm->crnt_kvff * (pm->cmd_vel >> 8)) >> 8;
    pidOut += (pm->crnt_kaff * (pm->cmd_acc >> 8)) >> 8;

    /* Add output bias */
    pidOut += pm->crnt_bias;

    /* Clip PID regulator output within the Motor Limit paraqmeter */
    if (pidOut > (long)pm->pos_loop_limit)
    {
        pidOut = pm->pos_loop_limit;
    }
    else if (pidOut < -(long)pm->pos_loop_limit)
    {
        pidOut = -(long)pm->pos_loop_limit;
    }
    else
    {
        /* Do Nothing */
    }



	return pidOut;
}

long long pid_calc_pos64(t_motor *pm, long long posErr)
{
    long long pidOut;
    long err32;
    long long integral_limit;
    long long pidOut_limit;
    
    /* Clip position error within the Position Error Limit parameter */
    if (posErr > PID_POS_INPUT_LIMIT)
    {
        posErr = PID_POS_INPUT_LIMIT;
    }
    else if (posErr < -PID_POS_INPUT_LIMIT)
    {
        posErr = -PID_POS_INPUT_LIMIT;
    }
    else
    {
        /* Do Nothing */
    }

    /* Calculate the position error derivative */
    err32 = pm->pos_error2;
    pm->pos_error2 = (long)posErr;
    pm->derivative_err2 = pm->pos_error2 - err32;

    /* Integrate the position error */
    pm->integral_err2 += posErr;

    /* Clip integral within the Integral Limit parameter */
    integral_limit = (long long)pm->integral_limit << 16;
    if (pm->integral_err2 > integral_limit)
    {
        pm->integral_err2 = integral_limit;
    }
    else if (pm->integral_err2 < -integral_limit)
    {
        pm->integral_err2 = -integral_limit;
    }
    else
    {
        /* Do Nothing */
    }


    /* Add proportional, derivative and intergral terms */
    pidOut = ((long long)pm->integral_err2 * (long long)pm->crnt_ki) >> PID_POS_KI_SHIFT;
    pidOut += ((long long)pm->derivative_err2 * (long long)pm->crnt_kd) >> PID_POS_KD_SHIFT;
    pidOut += ((long long)pm->pos_error2 * (long long)pm->crnt_kp) >> PID_POS_KP_SHIFT;

    /* Add velocity and acceleration feed forward */ 
    pidOut += ((long long)(pm->crnt_kvff * (pm->cmd_vel >> 8)) >> PID_POS_KVFF_SHIFT) << 16;
    pidOut += ((long long)(pm->crnt_kaff * (pm->cmd_acc >> 8)) >> PID_POS_KAFF_SHIFT) << 16;

    /* Add output bias */
    pidOut += (long long)pm->crnt_bias << 16;

    /* Clip PID regulator output within the Motor Limit paraqmeter */
    pidOut_limit = (long long)pm->pos_loop_limit << 16;
    if (pidOut > pidOut_limit)
    {
        pidOut = pidOut_limit;
    }
    else if (pidOut < -pidOut_limit)
    {
        pidOut = -pidOut_limit;
    }
    else
    {
        /* Do Nothing */
    }


    /* Update original variable */
    pm->pos_error = (short)(pm->pos_error2 >> 16);
    pm->integral_err = (long)(pm->integral_err2 >> 16);
    pm->derivative_err = (short)(pm->derivative_err2 >> 16);

    return pidOut;
}

long pi_calc_vel(t_motor *pm, long bias)
{
    long pidOut;
    long err16;
    
    /* Calculate the velocity error derivative */
    err16 = pm->vel_error;
    pm->vel_error = bias;
    pm->derivative_err_vel = pm->vel_error - err16;

    /* Integrate the velocity error */
    pm->integral_err_vel += bias;
    
    /* Clip integral within the Integral Limit parameter */
    if (pm->integral_err_vel > pm->integral_limit_vel)
    {
        pm->integral_err_vel = pm->integral_limit_vel;
    }
    else if (pm->integral_err_vel < -pm->integral_limit_vel)
    {
        pm->integral_err_vel = -pm->integral_limit_vel;
    }
    else
    {
        /* Do Nothing */
    }


    /* Add proportional, derivative and intergral terms */
	pidOut = ( ( pm->integral_err_vel * (long)(pm->crnt_ki_vel) ) >> 16 );
    pidOut += ( ( pm->vel_error * (long)(pm->crnt_kp_vel) ) >> 12 ) ;
    pidOut += pm->derivative_err_vel * pm->crnt_kd_vel;

    /* Clip PID regulator output within the Motor Limit paraqmeter */
    if (pidOut > (long)pm->PiOut_limit_vel)
    {
        pidOut = pm->PiOut_limit_vel;
    }
    else if (pidOut < -(long)pm->PiOut_limit_vel)
    {
        pidOut = -(long)pm->PiOut_limit_vel;
    }
    else
    {
        /* Do Nothing */
    }

    return pidOut;
}


short pid_calc_vel64(t_motor *pm, long long velErr)
{
    long long pidOut;
    long long err64;
    long long integral_limit;
    
    /* Clip velocity error within the Velocity Error Limit parameter */
    if (velErr > PID_VEL_INPUT_LIMIT)
    {
        velErr = PID_VEL_INPUT_LIMIT;
    }
    else if (velErr < -PID_VEL_INPUT_LIMIT)
    {
        velErr = -PID_VEL_INPUT_LIMIT;
    }
    else
    {
        /* Do Nothing */
    }


    /* Calculate the velocity error derivative */
    err64 = pm->vel_error2;
    pm->vel_error2 = velErr;
    pm->derivative_err2_vel = pm->vel_error2 - err64;

    /* Integrate the velocity error */
    pm->integral_err2_vel += velErr;
    
    /* Clip integral within the Integral Limit parameter */
    integral_limit = (long long)pm->integral_limit_vel << 16;
    if (pm->integral_err2_vel > integral_limit)
    {
        pm->integral_err2_vel = integral_limit;
    }
    else if (pm->integral_err2_vel < -integral_limit)
    {
        pm->integral_err2_vel = -integral_limit;
    }
    else
    {
        /* Do Nothing */
    }


    /* Add proportional, derivative and intergral terms */
    pidOut = ((long long)pm->integral_err2_vel * (long long)pm->crnt_ki_vel) >> PID_VEL_KI_SHIFT;
    pidOut += ((long long)pm->vel_error2 * (long long)pm->crnt_kp_vel) >> PID_VEL_KP_SHIFT;

    /* RZ/T2 add */
    /* Judgment to add a derivative term */
    if(((pm->ctrl_mode != CTRM_VELOCITY)&&(pm->ctrl_mode != CTRM_TORQUE)) || pm->in_vel64 == pm->in_vel64_old)
    {
        pidOut += ((long long)pm->derivative_err2_vel * (long long)pm->crnt_kd_vel) >> PID_VEL_KD_SHIFT;
    }
    else
    {
        /* Do nothing */
    }
    pm->in_vel64_old = pm->in_vel64;

    /* Clip PID regulator output within the Motor Limit paraqmeter */
    if (pidOut > (long long)pm->PiOut_limit_vel)
    {
    	pidOut = (long long)pm->PiOut_limit_vel;
    }
    else if (pidOut < -(long long)pm->PiOut_limit_vel)
    {
        pidOut = -(long long)pm->PiOut_limit_vel;
    }
    else
    {
        /* Do Nothing */
    }


    /* Update original variable */
    pm->vel_error = (long)(pm->vel_error2 >> 16);
    pm->integral_err_vel = (long)(pm->integral_err2_vel >> 16);
    pm->derivative_err_vel = (long)(pm->derivative_err2_vel >> 16);

    return (short)pidOut;
}
