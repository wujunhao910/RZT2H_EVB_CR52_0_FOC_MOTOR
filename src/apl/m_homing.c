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
* File Name    : m_homing.c
* Version      : 1.0
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Source file of Homing.
*******************************************************************************/

#include "m_common.h"

void fsm_homing(t_motor *pm) 
{
    switch (pm->fsm_home) {
    case HS_IDLE:
        break;
    case HS_FINDING_LIMIT:
        pm->home_switch = pm->dinputs & pm->home_mask;
        /* Check if home switch is triggered */
        if (pm->home_switch != (pm->dinputs_1 & pm->home_mask)) 
        {
            /* Stop Motion */
            pm->stop_request = SM_SMOOTH;
            update_ctrl(pm);
            pm->fsm_home = HS_WAIT_STOP;
        }
        break;
    case HS_WAIT_STOP:
        /* Wait for motion complete */
        if (pm->act_state & ACT_MotionComplete) 
        {
            /* Initiate position capture upon index */
         	pm->act_state &= ~ACT_PosCaptured;
            /* Start motion in positive direction */
            pm->buffMotion.position = 50000;
            update_ctrl(pm);
            pm->fsm_home = HS_FINDING_INDEX;
         }
         break;
    case HS_FINDING_INDEX:
         /* If position is captured (index latched) */
         if (pm->act_state & ACT_PosCaptured) 
         {
             /* Get Captured position */
             if (pm->pos_inv_mode)
             {
                 pm->home_idx_pos = -pm->captured_pos.Reg32;
             }
             else
             {
                 pm->home_idx_pos =  pm->captured_pos.Reg32;
             }
#if 1	// EtherCAT
         	pm->act_state |= ACT_Homed;
#else // ethercat
         	//pm->act_state |= ACT_Homed;
#endif // ethercat
            /* Stop Motion */
            pm->stop_request = SM_SMOOTH;
            update_ctrl(pm);
            pm->fsm_home = HS_WAIT_STOP2;
         }
         break;
    case HS_WAIT_STOP2:
        if (pm->act_state & ACT_MotionComplete) 
        {
            /* Sets current position based on the index position and the home offset */
            set_position (pm, pm->crnt_pos - pm->home_idx_pos - pm->home_offset);
            pm->buffMotion.position = 0;
            update_ctrl(pm);
            pm->fsm_home = HS_WAIT_STOP3;
        }
        break;
    case HS_FINDING_HARDSTOP:
        if (pm->pos_error > 100 || pm->pos_error < -100) 
        {
            set_position (pm, -pm->home_offset);
            pm->buffMotion.position = 0;
            update_ctrl(pm);
#if 1	// EtherCAT
         	pm->act_state |= ACT_Homed;
#else // ethercat
         	//pm->act_state |= ACT_Homed;
#endif // ethercat
            pm->fsm_home = HS_WAIT_STOP3;
        }
        if (pm->act_state & ACT_MotionComplete) 
        {
            pm->buffMotion.position =  pm->crnt_pos - 5500;
            update_ctrl(pm);
            pm->fsm_home = HS_WAIT_STOP3;
        }
        break;
    case HS_WAIT_STOP3:
        if (pm->act_state & ACT_MotionComplete) 
        {
            pm->fsm_home = HS_IDLE;
            pm->act_state &= ~ACT_Busy;
        }
        break;
    case HS_WAIT_ALIGN_0:    
        if (--pm->phasing_timer > 3)
            break;
        pm->phasing_timer = pm->phasing_time;
        pm->phase_vector++;
        pm->fsm_home = HS_WAIT_ALIGN_1;
        pm->dither_last_pos = pm->crnt_pos;
        /* Determine if the Hall sensors have to be inverted 
           If the Halls combination is 2 - proceed to the next state. 
           If the result is 1 or 4 - change the mapping to get 2 and then proceed.
           else - the sensors need to be inverted and the result to be set to 2.
        */
        if (pm->hall_state == 3 || pm->hall_state == 5 || pm->hall_state == 6) 
        {
            pm->hall_inverted |= 0x10;
        }
        while (pm->hall_state != 2 && (pm->hall_inverted & 7) < 8)
        {
            pm->hall_inverted++;
        }
        break;
    case HS_WAIT_ALIGN_1:    
        if (--pm->phasing_timer > 3)
            break;
        /* Handle invalid direction of motion - change phase mapping */
        if (pm->dither_last_pos >= pm->crnt_pos)
        {
            if (pm->phase_config == 1)
            {
                pm->output_q = 0;
                pm->fsm_home = HS_IDLE;
                pm->phasing_timer = 0;
                pm->aligning = 0;
                pm->phase_config = 0;
                map_phases(pm);
                break;
            }
            pm->phase_config = 1;
            map_phases(pm);
            pm->phasing_timer = pm->phasing_time;
            pm->phase_vector = 0;
            pm->hall_inverted = 0;
            pm->fsm_home = HS_WAIT_ALIGN_0;
            break;
        }
        /* Hanlde halls mapping. Expected hall combination is 6 */
        if (pm->hall_state != 6)
        {
            pm->hall_inverted &= 0x10;
            while (pm->hall_state != 2 && (pm->hall_inverted & 7) < 8)
            {
                pm->hall_inverted++;
            }
        }
        pm->fsm_home = HS_IDLE;
        pm->phasing_timer = 0;
        pm->act_state &= ~ACT_Busy;
        break;
    default:
        pm->fsm_home = HS_IDLE;
        break;
    }
}

void m_StartHoming(t_console *pc, t_motor *pm) 
{
    /* Check if it is OK to start the homing procedure */
    if (pm->servo_on == 0 || (pm->act_state & ACT_Busy) != 0 || pm->vpg_state != VPG_MotionCompleted)
    {
        pc->err = PE_INVALID_STATE;    /* Invalid State */
        return;
    }

    /* If the home switch mask is not zero - search for the home switch trigger */
    if (pm->home_mask == 3) {
        pm->buffMotion.position = pm->crnt_pos + 5500;
        pm->fsm_home = HS_FINDING_HARDSTOP;
    } else if (pm->home_mask != 0) {
        pm->buffMotion.position = 1000000;
        /* Check Limit (Home) Sensor State, determine jog direction */
        if (pm->dinputs & pm->home_mask) 
        {
            pm->buffMotion.position = -pm->buffMotion.position;
        }
        pm->fsm_home = HS_FINDING_LIMIT;
    } 
    else 
    {
        pm->buffMotion.position = -50000;
        pm->act_state &= ~ACT_PosCaptured;
        pm->fsm_home = HS_FINDING_INDEX;
    }
    /* Start Motion and activate Homing procedure */
    update_ctrl(pm);
#if 1	// EtherCAT
    pm->act_state &= ~ACT_Homed;
#else // ethercat
    //pm->act_state &= ~ACT_Homed;
#endif // ethercat
    pm->act_state |= ACT_Busy;
}


