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
* File Name    : m_interlocks.c
* Version      : 1.0
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Source file of Interlocks.
*******************************************************************************/

#include <stdlib.h>
#include "m_common.h"


/* 
Processing of all protections and interlocks:

- I2t protection - thermal dissipation. 
    The flag ACT_MtOverTemp is raised 
- Current limit exceeded for longer than time defined. Servo is turned off
    The flag ACT_OverCurrent is raised.
- Position error limit exceeded. Servo may or may not be turned off depending on a configuration setting.
    The flag ACT_PosError is raised 
- Amplifier fault digital input. Indicates either overcurrent, short or other amplifier specific condition
    The flag ACT_AmpFault is raised
- Digital input interlock
    The flag ACT_Inhibit is raised


    !!! The function shdould be invoked once every millisecond !!!
*/
void interlocks(t_motor *pm) 
{
    long crnt_sq, diff_sq;

    /* Fast Protection - triggers in pm->tc_limit_time of exceeding tc_limit current */
    if (pm->tc_limit && pm->tc_limit_time)
    {
        if (pm->total_current > pm->tc_limit)
        {
            if ((short)--pm->tc_limit_timer <= 0)
            {     
                pm->tc_limit_timer = pm->tc_limit_time;
                /* Indicate current overload */
                pm->act_state |= ACT_OverCurrent;
                /* Stop Motion by turning off servo */
                servo_off(pm);
                pm->ErrSts |= ERRBIT_26;
            }
        }
        else 
        {
            pm->tc_limit_timer = pm->tc_limit_time;
        }
    }

    /* Check for exceeding position error */
    if (pm->servo_on && pm->pos_error_limit)
    {
        if (abs(pm->pos_error) > pm->pos_error_limit)
        {
            if ((short)--pm->pos_error_timer <= 0)
            {
                pm->act_state |= ACT_PosError;
                pm->mecmd_pos = pm->cmd_pos;
                pm->mecmd_vel = pm->cmd_vel;
                pm->mecrnt_pos = pm->crnt_pos;
                pm->mecmd_output = pm->output_q;
                pm->ErrSts |= ERRBIT_17;
                if (pm->auto_stop_mode)
                {
                    servo_off(pm);
                    if (pm->auto_stop_mode == 1)
                    {
                        pm->servo_on = 1;
                    }
                }
            }
        }
        else
        {
            pm->pos_error_timer = pm->pos_error_time;
        }
    }
#if 0
    /* Check Low Volt */
    if( pm->crnt_volt <= pm->Lvolt_Val )
    {
        pm->ErrSts |= ERRBIT_28;
    }
#endif

#if 0
    /* Check High Volt */
    if( pm->crnt_volt >= pm->Hvolt_Val )
    {
        pm->ErrSts |= ERRBIT_27;
    }
#endif
    /* Check POE */
    if( ChkPOE() == 1 )
    {
        pm->ErrSts |= ERRBIT_25;
    }
    /* Check Over Load */
    if( (pm->total_current != 0) && (pm->total_current >= pm->Ovc_Val) )
    {
        pm->ErrSts |= ERRBIT_21;
    }
    /* Check Over Speed Limit*/
    if( (pm->act_state & ACT_MotionComplete ) == 0 && ( abs(pm->crnt_vel) >= pm->Ovs_Val) )
    {
        pm->ErrSts |= ERRBIT_20;
    }
    /* Check Over Speed Warning*/
    if(  (pm->act_state & ACT_MotionComplete ) == 0 && ( abs(pm->vel_error) >= pm->WOvs_Val) )
    {
        pm->WOvs_time++;
        if( pm->WOvs_time >= WOVS_TIME )
        {
            pm->ErrSts |= ERRBIT_19;
            pm->WOvs_time = WOVS_TIME;
        }
    }
    else
    {
        pm->WOvs_time = 0;
    }

    /* Check Over position Warning */
    if( pm->crnt_pos >= pm->WPosMax_Val )
    {
          pm->ErrSts |= ERRBIT_15;
    }

    /* Check Under position Warning */
    if( pm->crnt_pos <= pm->WPosMin_Val )
    {
          pm->ErrSts |= ERRBIT_13;
    }

    /* Check if new velocity / position EMPTY */
    if( pm->vpg_overrun >= pm->WEmp_Val )
    {
        pm->ErrSts |= ERRBIT_07;
    }

    /* Motor Stop Check */
    if( ( pm->ErrSts & pm->ErrMsk ) != 0 )
    {
        m_PowerOff(0, pm); /* PowerOFF & Servo_off */
        pm->act_state |= ACT_MotionComplete;
    }
    ErrLedDsp(); /* LED Disp */
}
