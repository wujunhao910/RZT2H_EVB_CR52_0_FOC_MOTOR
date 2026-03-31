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
* File Name    : m_vpg_trap.c
* Version      : 1.0
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Source file of vpg.
*******************************************************************************/


#include "m_common.h"

/* Trapezoidal velocity Profile Generator - startup */
t_vpg_state  vpg_trap_start(t_motor *pm, short jogging)
{
    pm->prfl_push_1 = &pm->profileFIFO[0];
    pm->prfl_push_1->position = pm->cmd_pos;
    pm->prfl_push_1->velocity = 0;
    pm->prfl_push_1->acceleration = 0;
    pm->prfl_push_1->stop_dist = 0;
    pm->prfl_push_1->vpg_state = VPG_MotionCompleted;

    pm->prfl_push = pm->prfl_push_1 + 1;
    pm->prfl_pull = pm->prfl_push;
    pm->delta_pos = 0;
    if (jogging) 
    {
        pm->direction = pm->trgtMotion.dir_sign;
    } 
    else 
    {
        pm->direction = pm->trgtMotion.position >= pm->prfl_push_1->position ? 1 : -1;
    }
    vpg_trap_next(pm, pm->prfl_push_1, pm->prfl_push, jogging);
    pm->prfl_push_1 = pm->prfl_push;
    pm->prfl_push++;
    pm->prfl_points = 1;
    return pm->prfl_push_1->vpg_state;
}

/* Trapezoidal velocity Profile Generator - next position set point */
void  vpg_trap_next(t_motor *pm, TMotionProfile *crntPars, TMotionProfile *cmdPars, short jogging)
{
long dist2target;
long temp32;
short temp16, dir_sign;

    if (jogging) 
    {
        dir_sign = pm->trgtMotion.dir_sign;
        dist2target = 0x7fffffff;
        if (pm->trgtMotion.velocity == 0 && crntPars->velocity < pm->trgtMotion.deceleration) 
        {
            cmdPars->velocity = 0;
            cmdPars->acceleration = 0;
            cmdPars->position = crntPars->position;
            cmdPars->vpg_state = VPG_MotionCompleted;
            return;
        }
    } 
    else 
    {
        dist2target = pm->trgtMotion.position - crntPars->position;
        if (dist2target < 0) 
        {
            dir_sign = -1;
            dist2target = -dist2target;
        } 
        else 
        {
            dir_sign = 1;
        }
        temp16 = pm->trgtMotion.deceleration >> 16;
        if (temp16 < 1)
            temp16 = 1;
        if (dist2target <= (long) temp16) 
        {
             cmdPars->velocity = 0;
             cmdPars->acceleration = 0;
             cmdPars->position = pm->trgtMotion.position;
             cmdPars->vpg_state = VPG_MotionCompleted;
             return;
        }
    }
    if (((crntPars->stop_dist >= dist2target) ||
        (crntPars->velocity > pm->trgtMotion.velocity) ||
        (pm->direction != dir_sign))) 
    {
        /* deceleration Phase */
        temp32 = crntPars->velocity - pm->trgtMotion.deceleration;
        if (temp32 < pm->trgtMotion.deceleration) {
            pm->direction = dir_sign;
            if (pm->trgtMotion.velocity < pm->trgtMotion.deceleration) 
            {
                cmdPars->velocity = pm->trgtMotion.velocity;
            } 
            else 
            {
                cmdPars->velocity = pm->trgtMotion.deceleration;
            }
        } 
        else 
        {
            cmdPars->velocity = temp32;
        }
        if (crntPars->velocity > pm->trgtMotion.velocity)
            cmdPars->velocity = temp32 < pm->trgtMotion.velocity ? pm->trgtMotion.velocity : temp32;

        cmdPars->acceleration = pm->trgtMotion.deceleration;
        cmdPars->vpg_state = VPG_Deceleration;
    } 
    else if (crntPars->velocity < pm->trgtMotion.velocity) 
    {
        /* acceleration Phase */
        temp32 = crntPars->velocity + pm->trgtMotion.acceleration;
        cmdPars->velocity = temp32 > pm->trgtMotion.velocity ? pm->trgtMotion.velocity : temp32;
        cmdPars->acceleration = pm->trgtMotion.acceleration;
        cmdPars->vpg_state = VPG_Acceleration;
    } 
    else  
    {
        /* Plateau */
        cmdPars->velocity = crntPars->velocity;
        cmdPars->acceleration = 0;
        cmdPars->vpg_state = VPG_Plateau;
    }

    /* Calculate stopping distance = (velocity * velocity) / deceleration */
    cmdPars->stop_dist = (long)(((double)cmdPars->velocity * (double)cmdPars->velocity) / (double)(pm->trgtMotion.deceleration<<1)) >> 16;
      
    /* Calculate commanded position via trapezoidal integration of the velocity */
    pm->delta_pos += (crntPars->velocity + cmdPars->velocity) >> 1;
    temp32 = (pm->delta_pos >> 16);
    if (pm->direction < 0)
        temp32 = -temp32;
    cmdPars->position = crntPars->position + temp32;
    pm->delta_pos &= 0x0000ffff;
    return;
}

