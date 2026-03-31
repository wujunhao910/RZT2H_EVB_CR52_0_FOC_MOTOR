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
* File Name    : m_pos_read.c
* Version      : 1.0
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Source file of Position.
*******************************************************************************/


#include "m_common.h"

void pos_read(t_motor *pm)
{
short pos_old, pos_new;
long long pos_wk;

#if defined(__ICCARM__)
    /* Do nothing */
#elif defined(__GNUC__)
    if(SW12_4 == 1) /* SW12_4 : OFF */
    {
        pm->pos_read_timer--;
        if(pm->pos_read_timer > 0)
        {
            return;
        }
        pm->pos_read_timer = 2;
    }
#endif

    
    if (pm->simulated_mode)
    {
        pm->crnt_pos = pm->cmd_pos;
        pm->crnt_pos64 = SetSignBit48( (long long)pm->crnt_pos << 16 );
        return;
    }
    /* Waiting for the bootstrap circuit charge *//* RZ/T2 add */
    if (pm->charge_state == BS_CHARGEING)
    {
        return;
    }
    if (pm->encoder_type == ETYPE_INCREMENTAL)
    {
      	pos_old = (short)(pm->real_pos.Reg16.Low & 0xc000);

        /* Check if positon was captured */
		if (capture_position(pm) != 0) 
        {
			pos_new = pm->captured_pos.Reg16.Low;
			pm->captured_pos.Reg16.High = pm->real_pos.Reg16.High;
            
            /* Expand 16-bit position to 32-bit */
			if (pos_old == 0 && pos_new < 0) 
            {
				pm->captured_pos.Reg16.High--;
			} 
            else if (pos_old == (short)(0xc000) && pos_new >= 0) 
            { 
				pm->captured_pos.Reg16.High++;
			}
            else
            {
                /* Do Nothing */
            }
            
            /* Apply position Offset parameter */
			pm->captured_pos.Reg32 += pm->pos_offset;
            
            /* Update Activity Status */
			pm->act_state |= ACT_PosCaptured;
            
			/* Save captured position */
            if ((pm->act_state & ACT_PosCaptured) == 0) 
            {
                pm->index_pos = pm->captured_pos.Reg32;
                pm->act_state |= ACT_PosCaptured;
            }
		}
		/* Read quadrature encoder counter */
		pos_new = pm->real_pos.Reg16.Low = *(pm->regPosCounter);
        
        /* Expand 16-bit position to 32-bit */
        if (pos_old == 0 && pos_new < 0) 
        {
            if (pm->real_pos.Reg16.High == (short)0x8000) 
            {
                pm->act_state |= ACT_WrapAround;
            }
            pm->real_pos.Reg16.High--;
        } 
        else if (pos_old == (short)(0xc000) && pos_new >= 0) 
        { 
            if (pm->real_pos.Reg16.High == 0x7fff) 
            {
                pm->act_state |= ACT_WrapAround;
            }
            pm->real_pos.Reg16.High++;
        }
        else
        {
            /* Do Nothing */
        }

    } 
    else
    {
        if (pm->enc_open)      
        {
            switch (pm->encoder_type)
            {
            case ETYPE_APE_FACODER:
                fac_pos(pm);
                break;
            case ETYPE_APE_AFORMAT:
#if 0 /* A-format is not supported. */
                a_as_pos(pm);
#endif
                pm->crnt_pos = pm->cmd_pos;
                break;
            case ETYPE_APE_ENDAT:
#if 0 /* EnDat is not supported. */
                endat_pos(pm);
#endif
                pm->crnt_pos = pm->cmd_pos;
                break;
            case ETYPE_APE_BISS:
#if 0 /* BiSS is not supported. */
                bissc_get_pos(pm);
#endif
                pm->crnt_pos = pm->cmd_pos;
                break;
            case ETYPE_APE_HIPERFACE_DSL:
#if 0 /* HIPERFACE DSL is not supported. */
                hfdsl_pos(pm);
#endif
                pm->crnt_pos = pm->cmd_pos;
                break;
            default:                /* If the encoder type is not known - simulate the position feedback */
                pm->crnt_pos = pm->cmd_pos;
                return;
            }
            pm->real_pos.Reg32 = (int32_t)((( (uint32_t)pm->real_rot << 16 ) & 0xffff0000) | (( (uint32_t)pm->real_res >> 16 ) & 0x0000ffff));
           // pm->real_pos.Reg32 = (int32_t)((( (uint32_t)pm->real_rot << 16 ) & 0x00000000) | (( (uint32_t)pm->real_res >> 16 ) & 0x0000ffff));
            // 假设需要完整的32位单圈位置
           // pm->real_pos.Reg32 = ((uint32_t)pm->real_res);
        }
    }
    /* Add the posion offset and position invertion */
    if (pm->pos_inv_mode)
    {
        pm->crnt_pos = -(pm->real_pos.Reg32 + pm->pos_offset);
        if(pm->encoder_type == ETYPE_INCREMENTAL)
        {
            pm->crnt_pos64 = SetSignBit48( (long long)pm->crnt_pos << 16 );
        }
        else
        {
            pos_wk = (long long)( (((unsigned long long)pm->real_rot << 32) & 0xffffffff00000000) | (((unsigned long long)pm->real_res) & 0x00000000ffffffff) );
                        pos_wk = -( pos_wk + ((long long)pm->pos_offset << 16) );
                        pm->crnt_pos64 = SetSignBit48(pos_wk);
        }
    }
    else
    {
        pm->crnt_pos = pm->real_pos.Reg32 + pm->pos_offset;
        if(pm->encoder_type == ETYPE_INCREMENTAL)
        {
            pm->crnt_pos64 = SetSignBit48( (long long)pm->crnt_pos << 16 );
        }
        else
        {
            pos_wk = (long long)( (((unsigned long long)pm->real_rot << 32) & 0xffffffff00000000) | (((unsigned long long)pm->real_res) & 0x00000000ffffffff) );
                        pos_wk = pos_wk + ((long long)pm->pos_offset << 16);
                        pm->crnt_pos64 = SetSignBit48(pos_wk);
        }
    }
}
