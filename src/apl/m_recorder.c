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
* File Name    : m_recorder.c
* Version      : 1.0
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Source file of Recorder.
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "m_common.h"
#include "m_recorder.h"
#include "m_interpreter.h"



/******************************************************************************
Global variables
******************************************************************************/
t_trace trace;

t_motor *traceMotor;
short traceCode0;
short traceCode1;
short traceCode2;
short traceCode3;

void *tracePtr0;
void *tracePtr1;
void *tracePtr2;
void *tracePtr3;
float traceData[TRACE_BUFFER_SIZE * 4];
unsigned short traceIdx;
unsigned short traceCntr;
unsigned short cntrBegin, cntrEnd;

/* exported variables */
extern t_motor g_st_m[MOTOR_NUM];
extern short   g_counter;

/******************************************************************************
Static variables and functions
******************************************************************************/
/* prototype definitions of static functions */

/* static variables */
/* RZ/T2 add */
t_decode mDecodePtrTbl[32] = {
    { sizeof(volatile long), (void *)(&g_st_m[0].crnt_pos), (void *)&(g_st_m[1].crnt_pos), (void *)&(g_st_m[2].crnt_pos), (void *)&(g_st_m[3].crnt_pos), (void *)&(g_st_m[4].crnt_pos), (void *)&(g_st_m[5].crnt_pos), (void *)&(g_st_m[6].crnt_pos), (void *)&(g_st_m[7].crnt_pos), (void *)&(g_st_m[8].crnt_pos) }, // 0:position
    { sizeof(long), (void *)&(g_st_m[0].crnt_vel), (void *)&(g_st_m[1].crnt_vel), (void *)&(g_st_m[2].crnt_vel), (void *)&(g_st_m[3].crnt_vel), (void *)&(g_st_m[4].crnt_vel), (void *)&(g_st_m[5].crnt_vel), (void *)&(g_st_m[6].crnt_vel), (void *)&(g_st_m[7].crnt_vel), (void *)&(g_st_m[8].crnt_vel) }, // 1:Commanded velocity
    { sizeof(long), &(g_st_m[0].crnt_acc), &(g_st_m[1].crnt_acc), &(g_st_m[2].crnt_acc), &(g_st_m[3].crnt_acc), &(g_st_m[4].crnt_acc), &(g_st_m[5].crnt_acc), &(g_st_m[6].crnt_acc), &(g_st_m[7].crnt_acc), &(g_st_m[8].crnt_acc) }, // 2:Commanded acceleration
    { sizeof(long), &(g_st_m[0].I2t_integral), &(g_st_m[1].I2t_integral), &(g_st_m[2].I2t_integral), &(g_st_m[3].I2t_integral), &(g_st_m[4].I2t_integral), &(g_st_m[5].I2t_integral), &(g_st_m[6].I2t_integral), &(g_st_m[7].I2t_integral), &(g_st_m[8].I2t_integral) }, // 3:
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 4:None
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 5:None
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 6:None
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 7:None
    { sizeof(short), &(g_st_m[0].pos_error), &(g_st_m[1].pos_error), &(g_st_m[2].pos_error), &(g_st_m[3].pos_error), &(g_st_m[4].pos_error), &(g_st_m[5].pos_error), &(g_st_m[6].pos_error), &(g_st_m[7].pos_error), &(g_st_m[8].pos_error) }, // 8:Error
    { sizeof(short), &(g_st_m[0].output_q), &(g_st_m[1].output_q), &(g_st_m[2].output_q), &(g_st_m[3].output_q), &(g_st_m[4].output_q), &(g_st_m[5].output_q), &(g_st_m[6].output_q), &(g_st_m[7].output_q), &(g_st_m[8].output_q) }, // 9:PID Output
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //10:None
    { sizeof(long), &(g_st_m[0].foc_id), &(g_st_m[1].foc_id), &(g_st_m[2].foc_id), &(g_st_m[3].foc_id), &(g_st_m[4].foc_id), &(g_st_m[5].foc_id), &(g_st_m[6].foc_id), &(g_st_m[7].foc_id), &(g_st_m[8].foc_id) }, //11:Direct Current
    { sizeof(long), &(g_st_m[0].foc_iq), &(g_st_m[1].foc_iq), &(g_st_m[2].foc_iq), &(g_st_m[3].foc_iq), &(g_st_m[4].foc_iq), &(g_st_m[5].foc_iq), &(g_st_m[6].foc_iq), &(g_st_m[7].foc_iq), &(g_st_m[8].foc_iq) }, //12:Quadrature Current
    { sizeof(long), (void *)&(g_st_m[0].foc_id_err), (void *)&(g_st_m[1].foc_id_err), (void *)&(g_st_m[2].foc_id_err), (void *)&(g_st_m[3].foc_id_err), (void *)&(g_st_m[4].foc_id_err), (void *)&(g_st_m[5].foc_id_err), (void *)&(g_st_m[6].foc_id_err), (void *)&(g_st_m[7].foc_id_err), (void *)&(g_st_m[8].foc_id_err) }, //13:Direct Current Error
    { sizeof(long), &(g_st_m[0].foc_iq_err), &(g_st_m[1].foc_iq_err), &(g_st_m[2].foc_iq_err), &(g_st_m[3].foc_iq_err), &(g_st_m[4].foc_iq_err), &(g_st_m[5].foc_iq_err), &(g_st_m[6].foc_iq_err), &(g_st_m[7].foc_iq_err), &(g_st_m[8].foc_iq_err) }, //14:Quadrature Current Error
    { sizeof(short), &(g_st_m[0].adc1_raw), &(g_st_m[1].adc1_raw), &(g_st_m[2].adc1_raw), &(g_st_m[3].adc1_raw), &(g_st_m[4].adc1_raw), &(g_st_m[5].adc1_raw), &(g_st_m[6].adc1_raw), &(g_st_m[7].adc1_raw), &(g_st_m[8].adc1_raw) }, //15:Current A
    { sizeof(short), &(g_st_m[0].adc2_raw), &(g_st_m[1].adc2_raw), &(g_st_m[2].adc2_raw), &(g_st_m[3].adc2_raw), &(g_st_m[4].adc2_raw), &(g_st_m[5].adc2_raw), &(g_st_m[6].adc2_raw), &(g_st_m[7].adc2_raw), &(g_st_m[8].adc2_raw) }, //16:Current B
    { sizeof(volatile short), (void *)&(g_st_m[0].pvt_points), (void *)&(g_st_m[1].pvt_points), (void *)&(g_st_m[2].pvt_points), (void *)&(g_st_m[3].pvt_points), (void *)&(g_st_m[4].pvt_points), (void *)&(g_st_m[5].pvt_points), (void *)&(g_st_m[6].pvt_points), (void *)&(g_st_m[7].pvt_points), (void *)&(g_st_m[8].pvt_points) }, //17:PVT FIFO buffer depth
    { sizeof(short), &(g_st_m[0].foc_vd), &(g_st_m[1].foc_vd), &(g_st_m[2].foc_vd), &(g_st_m[3].foc_vd), &(g_st_m[4].foc_vd), &(g_st_m[5].foc_vd), &(g_st_m[6].foc_vd), &(g_st_m[7].foc_vd), &(g_st_m[8].foc_vd) }, //18:FOC Voltage Output - D
    { sizeof(short), &(g_st_m[0].foc_vq), &(g_st_m[1].foc_vq), &(g_st_m[2].foc_vq), &(g_st_m[3].foc_vq), &(g_st_m[4].foc_vq), &(g_st_m[5].foc_vq), &(g_st_m[6].foc_vq), &(g_st_m[7].foc_vq), &(g_st_m[8].foc_vq) }, //19:FOC Voltage Output - Q
    { sizeof(short), &(g_counter), &(g_counter), &(g_counter), &(g_counter), &(g_counter), &(g_counter), &(g_counter), &(g_counter), &(g_counter) }, //20:RealTime task timing
    { sizeof(short), &(g_st_m[0].phase_angle), &(g_st_m[1].phase_angle), &(g_st_m[2].phase_angle), &(g_st_m[3].phase_angle), &(g_st_m[4].phase_angle), &(g_st_m[5].phase_angle), &(g_st_m[6].phase_angle), &(g_st_m[7].phase_angle), &(g_st_m[8].phase_angle) }, //21:Phase Angle
    { sizeof(short), &(g_st_m[0].adc3_raw), &(g_st_m[1].adc3_raw), &(g_st_m[2].adc3_raw), &(g_st_m[3].adc3_raw), &(g_st_m[4].adc3_raw), &(g_st_m[5].adc3_raw), &(g_st_m[6].adc3_raw), &(g_st_m[7].adc3_raw), &(g_st_m[8].adc3_raw) }, //22:Current C
    { sizeof(volatile TReg32), (void *)&(g_st_m[0].captured_pos), (void *)&(g_st_m[1].captured_pos), (void *)&(g_st_m[2].captured_pos), (void *)&(g_st_m[3].captured_pos), (void *)&(g_st_m[4].captured_pos), (void *)&(g_st_m[5].captured_pos), (void *)&(g_st_m[6].captured_pos), (void *)&(g_st_m[7].captured_pos), (void *)&(g_st_m[8].captured_pos) }, //23:Input Capture p
    { sizeof(long), &(g_st_m[0].pos_error2), &(g_st_m[1].pos_error2), &(g_st_m[2].pos_error2), &(g_st_m[3].pos_error2), &(g_st_m[4].pos_error2), &(g_st_m[5].pos_error2), &(g_st_m[6].pos_error2), &(g_st_m[7].pos_error2), &(g_st_m[8].pos_error2) }, //24:Position Err
    { sizeof(long long), &(g_st_m[0].integral_err2), &(g_st_m[1].integral_err2), &(g_st_m[2].integral_err2), &(g_st_m[3].integral_err2), &(g_st_m[4].integral_err2), &(g_st_m[5].integral_err2), &(g_st_m[6].integral_err2), &(g_st_m[7].integral_err2), &(g_st_m[8].integral_err2) }, //25:Pos Control Integral
    { sizeof(long long), &(g_st_m[0].vel_error2), &(g_st_m[1].vel_error2), &(g_st_m[2].vel_error2), &(g_st_m[3].vel_error2), &(g_st_m[4].vel_error2), &(g_st_m[5].vel_error2), &(g_st_m[6].vel_error2), &(g_st_m[7].vel_error2), &(g_st_m[8].vel_error2) }, //26:Velocity Err
    { sizeof(long long), &(g_st_m[0].integral_err2_vel), &(g_st_m[1].integral_err2_vel), &(g_st_m[2].integral_err2_vel), &(g_st_m[3].integral_err2_vel), &(g_st_m[4].integral_err2_vel), &(g_st_m[5].integral_err2_vel), &(g_st_m[6].integral_err2_vel), &(g_st_m[7].integral_err2_vel), &(g_st_m[8].integral_err2_vel) }, //27:Vel Control Integral
    { sizeof(long), &(g_st_m[0].foc_id_err_int), &(g_st_m[1].foc_id_err_int), &(g_st_m[2].foc_id_err_int), &(g_st_m[3].foc_id_err_int), &(g_st_m[4].foc_id_err_int), &(g_st_m[5].foc_id_err_int), &(g_st_m[6].foc_id_err_int), &(g_st_m[7].foc_id_err_int), &(g_st_m[8].foc_id_err_int) }, //28:Id Control Integral
    { sizeof(long), &(g_st_m[0].foc_iq_err_int), &(g_st_m[1].foc_iq_err_int), &(g_st_m[2].foc_iq_err_int), &(g_st_m[3].foc_iq_err_int), &(g_st_m[4].foc_iq_err_int), &(g_st_m[5].foc_iq_err_int), &(g_st_m[6].foc_iq_err_int), &(g_st_m[7].foc_iq_err_int), &(g_st_m[8].foc_iq_err_int) }, //29:Iq Control Integral
    { sizeof(short), &(g_st_m[0].est_trq), &(g_st_m[1].est_trq), &(g_st_m[2].est_trq), &(g_st_m[3].est_trq), &(g_st_m[4].est_trq), &(g_st_m[5].est_trq), &(g_st_m[6].est_trq), &(g_st_m[7].est_trq), &(g_st_m[8].est_trq) }, //30:Torque Estimate
    { sizeof(float), &(g_st_m[0].angle_rad), &(g_st_m[1].angle_rad), &(g_st_m[2].angle_rad), &(g_st_m[3].angle_rad), &(g_st_m[4].angle_rad), &(g_st_m[5].angle_rad), &(g_st_m[6].angle_rad), &(g_st_m[7].angle_rad), &(g_st_m[8].angle_rad) }, //31:Motor Electric Angle
};


/******************************************************************************
Global functions
******************************************************************************/


void m_TraceSetup(void)
{
    trace.buff_size = TRACE_BUFFER_SIZE;
    trace.Count = 0;
    trace.Mode = 0;
    traceIdx = 0;
    traceCntr = 0;
}

void m_Trace(t_console *pc, t_motor *pm) 
{
    // Configure data tracing
    if (pc->set) 
    {
        trace.Trigger = (short)pc->arg;
        if (!trace.Trigger) 
        {
            trace.Mode = 0; // Stop data recording
            return;
        }
        traceCntr = traceIdx = trace.Count = 0;
        switch (trace.Trigger) 
        {
        case 1:     // Start now continuous recording
            trace.Mode = 3;
            break;   
        case 2:     // Start now, Stop on buffer full
            trace.Mode = 2;
            break;   
        case 3:     // Start on begin of motion, Stop on end of motion
            trace.Mode = 1; // Armed
            break;
        case 5:     // Start now, Stop on value0 > threshold
        case 6:     // Start now, Stop on value0 < threshold
            trace.Mode = 3;
            break;   
        case 7:     // Start on begin of motion (when servo is on) or PWM output change (when servo is off)
            trace.Mode = 1; // Armed
            break;
        case 9:     // Start on value0 > threshold, Stop on buffer full
        case 10:    // Start on value0 < threshold, Stop on buffer full
            trace.Mode = 1; // Armed
            break;
        }
    } 
    else 
    {
        print_dec (pc, trace.Trigger);
    }
}

static void flush_buffer(t_console *pc)
{
    print_buff(pc);
    while (pc->tx_count != 0)
    {
        for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
        {
            vpg_update(&g_st_m[idx]);
        }
    }
    pc->ptx = pc->tx_buf;
}

void m_Play(t_console *pc, t_motor *pm) 
{
int idx;
short save, traceOffs = 0;
unsigned char cs = 0;
unsigned char b0, b1, b2, b3;
long lval;

    save = trace.Mode;
    trace.Mode = 0;
    if (trace.Count < TRACE_BUFFER_SIZE)
        traceIdx = 0;
    
    if (pc->cmd_req == PTR_PACKET)
    {
        //pc->rx_buf[0] - buffer code / data format
        

        /* RZ/T2 change start */
        /* Send status */
        pc->pSCI0->TDR_b.TDAT = pc->tx_buf[0];   
        pc->pSCI0->CCR0_b.TE = 1U;

        /* Send number of samples */
        pc->tx_buf[1] = (unsigned char)trace.Count;
        pc->tx_buf[2] = (unsigned char)(trace.Count >> 8);
        pc->pSCI0->TDR_b.TDAT = pc->tx_buf[1];
        pc->pSCI0->TDR_b.TDAT = pc->tx_buf[2];
        
        /* Send number of bytes per sample */
        pc->tx_buf[3] = sizeof(float);
    	pc->pSCI0->TDR_b.TDAT = pc->tx_buf[3];
        
        // Calc check sum
        cs += pc->tx_buf[0];
        cs += pc->tx_buf[1];
        cs += pc->tx_buf[2];
        cs += pc->tx_buf[3];
        
        switch(pc->rx_buf[0])
        {
        case 0:
            traceOffs = TRACE_BUFFER_SIZE*0;
            break;
        case 1:
            traceOffs = TRACE_BUFFER_SIZE*1;
            break;
        case 2:
            traceOffs = TRACE_BUFFER_SIZE*2;
            break;
        case 3:
            traceOffs = TRACE_BUFFER_SIZE*3;
            break;
        default:
            break;
        }
    }
    
    /* Display trace buffers */
    for (idx = 0; idx < trace.Count; idx++) 
    {
        if (pc->cmd_req == PTR_PACKET)
        {
            while (pc->pSCI0->FTSR_b.T > 8)
            {
                for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
                {
                    vpg_update(&g_st_m[idx]);
                }
            }
            
            lval = (long)(*((long*)(&traceData[traceIdx + traceOffs])));
            b0 = lval >>  0;
            b1 = lval >>  8;
            b2 = lval >> 16;
            b3 = lval >> 24;
            cs += b0;
            cs += b1;
            cs += b2;
            cs += b3;
            pc->pSCI0->TDR_b.TDAT = b0;
            pc->pSCI0->TDR_b.TDAT = b1;
            pc->pSCI0->TDR_b.TDAT = b2;
            pc->pSCI0->TDR_b.TDAT = b3;
         }
        else
        { 
            // Print idx, data0, data1, data2, data3 CR/LF
            
            // Channel-1
            lval = (long)(*((long*)(&traceData[traceIdx + TRACE_BUFFER_SIZE * 0])));
            print_dec(pc, lval);
            *(pc->ptx++) = ',';

            // Channel-2
            lval = (long)(*((long*)(&traceData[traceIdx + TRACE_BUFFER_SIZE * 1])));
            print_dec(pc, lval);
            *(pc->ptx++) = ',';

            // Channel-3
            lval = (long)(*((long*)(&traceData[traceIdx + TRACE_BUFFER_SIZE * 2])));
            print_dec(pc, lval);
            *(pc->ptx++) = ',';

            // Channel-4
            lval = (long)(*((long*)(&traceData[traceIdx + TRACE_BUFFER_SIZE * 3])));
            print_dec(pc, lval);

            *(pc->ptx++) = 13;
            *(pc->ptx++) = 10;
            pc->tx_count += 5;   // Comma x 3 + CR + LF
            flush_buffer(pc);
        }

        if (++traceIdx >= TRACE_BUFFER_SIZE)
        {
            traceIdx = 0;
        }
    }
    trace.Mode = save;
    
    if (pc->cmd_req == PTR_PACKET)
    {
        /* Send checksum */
        pc->pSCI0->TDR_b.TDAT = cs;
        
        /* Wait for end of transmission */
        while (1U != pc->pSCI0->CSR_b.TEND)
          ;
        pc->pSCI0->CCR0_b.TE = 0U;
    /* RZ/T2 change end */
    }
}

void * DecodePtr (t_motor *pm, long code)
{
        /* RZ/T2 change */
    if ( mDecodePtrTbl[code].size == 0 )
    {
       return (void *)&(pm->pos_error);
    }
    else
    {
        if (pm->motor_idx == 0)
        {
        	return mDecodePtrTbl[code].ptr1;
        }
        else if(pm->motor_idx == 1)
        {
        	return mDecodePtrTbl[code].ptr2;
        }
        else if(pm->motor_idx == 2)
        {
        	return mDecodePtrTbl[code].ptr3;
        }
        else if(pm->motor_idx == 3)
        {
        	return mDecodePtrTbl[code].ptr4;
        }
        else if(pm->motor_idx == 4)
        {
        	return mDecodePtrTbl[code].ptr5;
        }
        else if(pm->motor_idx == 5)
        {
        	return mDecodePtrTbl[code].ptr6;
        }
        else if(pm->motor_idx == 6)
        {
        	return mDecodePtrTbl[code].ptr7;
        }
        else if(pm->motor_idx == 7)
        {
        	return mDecodePtrTbl[code].ptr8;
        }
        else if(pm->motor_idx == 8)
        {
        	return mDecodePtrTbl[code].ptr9;
        }
        else
        {
            return mDecodePtrTbl[code].ptr1;
        }
    }
}

static void LogChannel (t_console *pc, t_motor *pm, short ch)
{
   traceMotor = pm;
   if (pc->set) 
   {
      void * ptr = DecodePtr (pm, pc->arg);
      switch (ch) {
      case 1:
         tracePtr1 = ptr;
         traceCode1 = (short)pc->arg;
         break;
      case 2:
         tracePtr2 = ptr;
         traceCode2 = (short)pc->arg;
         break;
      case 3:
         tracePtr3 = ptr;
         traceCode3 = (short)pc->arg;
         break;
      default:
         tracePtr0 = ptr;
         traceCode0 = (short)pc->arg;
      }
   } 
   else 
   {
      switch (ch) {
      case 1:   print_dec (pc, traceCode1);   break;
      case 2:   print_dec (pc, traceCode2);   break;
      case 3:   print_dec (pc, traceCode3);   break;
      default:  print_dec (pc, traceCode0);   break;
      }
   }
}


void m_LogChannel0(t_console *pc, t_motor *pm) 
{
   LogChannel (pc, pm, 0);
}

void m_LogChannel1(t_console *pc, t_motor *pm) 
{
   LogChannel (pc, pm, 1);
}

void m_LogChannel2(t_console *pc, t_motor *pm)
{
   LogChannel (pc, pm, 2);
}

void m_LogChannel3(t_console *pc, t_motor *pm)
{
   LogChannel (pc, pm, 3);
}


void m_recorder(void)
{
    if (trace.Mode > 1) {
        if ((short)--traceCntr <= 0) 
        {
            /* RZ/T2 change start */
            float clevel;
            float * dp = &traceData[traceIdx];
            traceCntr = trace.RateMult;

            // Channel 1
            if (traceCode0 == 31 )    /* 31:Motor Electric Angle */
            {
                *(dp + TRACE_BUFFER_SIZE * 0) = (float)*((float*)tracePtr0);
            }
            else {
                if ( mDecodePtrTbl[traceCode0].size > sizeof(long) ) 
                {
                    *(dp + TRACE_BUFFER_SIZE * 0)  = (float)*((long*)tracePtr0);
                } 
                else 
                {
                    *(dp + TRACE_BUFFER_SIZE * 0)  = (float)*((short*)tracePtr0);
                }
            }
            clevel = *(dp + TRACE_BUFFER_SIZE * 0);

            // Channel 2
            if (traceCode1 == 31 )    /* 31:Motor Electric Angle */
            {
                *(dp + TRACE_BUFFER_SIZE * 1) = (float)*((float*)tracePtr1);
            }
            else {
                if ( mDecodePtrTbl[traceCode1].size > sizeof(long) ) 
                {
                    *(dp + TRACE_BUFFER_SIZE * 1)  = (float)*((long*)tracePtr1);
                } 
                else 
                {
                    *(dp + TRACE_BUFFER_SIZE * 1)  = (float)*((short*)tracePtr1);
                }
            }

            // Channel 3
            if (traceCode2 == 31 )    /* 31:Motor Electric Angle */
            {
                *(dp + TRACE_BUFFER_SIZE * 2) = (float)*((float*)tracePtr2);
            }
            else {
                if ( mDecodePtrTbl[traceCode2].size > sizeof(long) ) 
                {
                    *(dp + TRACE_BUFFER_SIZE * 2)  = (float)*((long*)tracePtr2);
                } 
                else 
                {
                    *(dp + TRACE_BUFFER_SIZE * 2)  = (float)*((short*)tracePtr2);
                }
            }

            // Channel 4
            if (traceCode3 == 31 )    /* 31:Motor Electric Angle */
            {
                *(dp + TRACE_BUFFER_SIZE * 3) = (float)*((float*)tracePtr3);
            }
            else {
                if ( mDecodePtrTbl[traceCode3].size > sizeof(long) ) 
                {
                    *(dp + TRACE_BUFFER_SIZE * 3)  = (float)*((long*)tracePtr3);
                } 
                else 
                {
                    *(dp + TRACE_BUFFER_SIZE * 3)  = (float)*((short*)tracePtr3);
                }
            }
            /* RZ/T2 change end */

            if (trace.Count < TRACE_BUFFER_SIZE)
                trace.Count++;

            if (trace.Mode == 2) 
            {   /* Trace until buffer is full */
                if (trace.Count >= TRACE_BUFFER_SIZE)
                   trace.Mode = 0;
            } 
            else 
            {
                /* Check for stop trigger */
                switch (trace.Trigger) 
                {
                case 3:  /* Stop on Motion End */
                    if (traceMotor->vpg_state == VPG_MotionCompleted) 
                    {
                        trace.Mode = 0;
                    }
                    break;
                case 5:  /* Value > Threshold */
                    if (clevel > trace.Level) 
                    {
                        trace.Mode = 0;
                    }
                    break;
                case 6:  /* Value < Threshold */
                    if (clevel < trace.Level) 
                    {
                        trace.Mode = 0;
                    }
                    break;   
                }
            }
            traceIdx++;
            traceIdx &= TRACE_BUFFER_SIZE-1;
        }
    }   
}

void    m_rec_begin(void)
{
    if (trace.Mode == 1) 
    {
        /* RZ/T2 change */
        float clevel;
        
        if (traceCode0 == 31 )    /* 31:Motor Electric Angle */
        {
            clevel = (float)*((float*)tracePtr0);
        }
        else {
            if ( mDecodePtrTbl[traceCode0].size > sizeof(long) ) 
            {
                clevel  = (float)*((long*)tracePtr0);
            } 
            else 
            {
                clevel  = (float)*((short*)tracePtr0);
            }
        }
//      float clevel = (float)*((float*)tracePtr0);
        
        switch (trace.Trigger) 
        {
        case 3:         /* Start on begin of motion, Stop on End of motion */
            if (traceMotor->servo_on != 0) 
            {
                if (!(traceMotor->act_state & ACT_MotionComplete))
                    trace.Mode = 3;      /* Start now, Stop on end of motion */
            } else {
                if (traceMotor->pos_loop_cmd != 0)
                    trace.Mode = 3; 
            }
            break;
        case 7:         /* Start on begin of motion (when servo is on) or PWM output change (when servo is off) */
            if (traceMotor->servo_on != 0) 
            {
                if (!(traceMotor->act_state & ACT_MotionComplete))
                    trace.Mode = 2;      /* Start now, Stop on buffer full */
            } else {
                if (traceMotor->pos_loop_cmd != 0 || traceMotor->output_d != 0)
                    trace.Mode = 2; 
            }
            break;
        case 9:         /* Start on value2 > threshold, Stop on buffer full */
            if (clevel > trace.Level) 
            {
                trace.Mode = 2;
            }
            break;
        case 10:        /* Start on value2 < threshold, Stop on buffer full */
            if (clevel < trace.Level) 
            {
                trace.Mode = 2;
            }
            break;
        }
  }
}
