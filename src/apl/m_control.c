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
* File Name    : m_control.c
* Version      : 1.0
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Source file of Control.
*******************************************************************************/

#include <math.h>
#include "m_common.h"
#if 1	// EtherCAT
#include "r_cg_macrodriver.h"
#include "r_dsmif.h"
#ifdef ETHERCAT_EN
extern void shared_mem_access( void );
#endif // ethercat
#endif // ethercat

volatile long    g_tick = 0;
long    g_tick_1 = 0;

static short timer_1ms = 0;

extern t_console con2;
extern t_motor g_st_m[MOTOR_NUM];
extern short g_suspend;

/* RZ/T2 add */
unsigned short DSM_wait_state = 0;
long           DSM_wait_count = 0;

unsigned char run_status;
static void vel_loop(t_motor *pm);
/* RZ/T2 add */
static short torque_to_current(t_motor *pm);
static short torque_limit(t_motor *pm, short cmd_cur, short limit);
static void bootstrap_charge (t_motor *pm);


static void adj_phase_origin(t_motor *pm)
{
    /* Safety check */
    if (pm->ec_per_ecycle == 0)
    {
        return;
    }
    /* Normalize the phase origin */
    if (pm->crnt_pos - pm->phase_origin > pm->ec_per_ecycle)
    {
        pm->phase_origin += pm->ec_per_ecycle;
        pm->phase_corr_cntr++;
    }

    if (pm->crnt_pos - pm->phase_origin < -pm->ec_per_ecycle)
    {
        pm->phase_origin -= pm->ec_per_ecycle;
        pm->phase_corr_cntr--;
    }

    if (pm->phase_corr_cntr >= pm->pole_pairs) {
        pm->phase_corr_cntr = 0;
        pm->phase_origin += pm->phase_corr;
    }
    else if (pm->phase_corr_cntr <= -pm->pole_pairs)
    {
        pm->phase_corr_cntr = 0;
        pm->phase_origin -= pm->phase_corr;
    }
    else
    {
        /* Do Nothing */
    }
}


void update_pwm(t_motor *pm)
{
    float _u, _v, _w;
    
    if (pm->simulated_mode != 0)
    {
      return;
    }
    
    if (pm->charge_state == BS_CHARGE_END)
    {
        /* Scale PWM values from +/-0.5 to +/-32767 (for reporting only) */
        pm->PhaseU = (short)(pm->out_u * 65535);
        pm->PhaseV = (short)(pm->out_v * 65535);
        pm->PhaseW = (short)(pm->out_w * 65535);
        
        /* Scale PWM values from +/-0.5 to +/-pwm_period */
        _u = pm->out_u * (float)pm->pwm_period;
        _v = pm->out_v * (float)pm->pwm_period;
        _w = pm->out_w * (float)pm->pwm_period;
        
        /* Update PWM timers */
        *pm->mapPhaseU = (unsigned short)(pm->pwm_period_half - (short)_u);
        *pm->mapPhaseV = (unsigned short)(pm->pwm_period_half - (short)_v);
        *pm->mapPhaseW = (unsigned short)(pm->pwm_period_half - (short)_w);
    }
    else
    {
        /* Lower arm ON *//* RZ/T2 add */
        *pm->mapPhaseU = *pm->regPWMPeriod;
        *pm->mapPhaseV = *pm->regPWMPeriod;
        *pm->mapPhaseW = *pm->regPWMPeriod;
    }
}

void update_pwm2(t_motor *pm)
{
    float _u, _v;
    
    if (pm->simulated_mode != 0)
    {
        return;
    }
    
    /* Scale PWM values from +/-0.5 to +/-pwm_period */
    _u = pm->out_u * (float)pm->pwm_period;
    _v = -_u;
    
    /* Update PWM timers */
    *pm->mapPhaseU = (unsigned short)(pm->pwm_period_half - (short)_u);
    *pm->mapPhaseV = (unsigned short)(pm->pwm_period_half - (short)_v);
}

static void crnt_loop(t_motor *pm)
{
    /* Waiting for the bootstrap circuit charge *//* RZ/T2 add */
    if (pm->charge_state == BS_CHARGEING)
    {
        return;
    }

    /* Check for Brushed DC / Voice Coil motor*/
    if (pm->motor_type == 2)
    {
        pm->out_u = 0.5 * (float)pm->output_q * (1/32768.0);
        update_pwm2(pm);
        return;
    }

    /* Process BLDC or PMSM motor*/
    short cm = pm->commutation_mode;

    /* Check for Aligning (Phasing) Process */
    if (pm->aligning)
    {
        switch (pm->phasing_mode_crnt)
        {
        case PIM_FORCED:    
            forced_phasing(pm);
            return;
            
        case PIM_HALLS_BASED:    
            /* Make sure the hall sensors are connected */
            if (pm->hall_state > 0 && pm->hall_state < 7)
            {
                cm = CM_HALLS;
                hall_phasing(pm);
                break;
            }
            forced_phasing(pm);
            return;
            
        case PIM_DITHERING:  
            dither_phasing(pm);
            return;
        }
    }
    
    /* Update phase origin angle - to stay within the counts of one electrical cycle */
    adj_phase_origin(pm);
    pm->phase_angle = pm->crnt_pos - pm->phase_origin;
    pm->angle_rad = (double)pm->phase_angle * pm->counts2rad;
    
    __sincosf(pm->angle_rad, &pm->angle_sin, &pm->angle_cos);

    /* Check for hall sensors transition */
    if (pm->hall_state_1 != pm->hall_state)
    {
        pm->hall_change_pos = pm->crnt_pos;
        pm->hall_state_1 = pm->hall_state;
    }
    
    /* No phasing - then use hall based commutation */
    if ((pm->act_state & ACT_Aligned) == 0 || cm == CM_HALLS)
    {
        commutate_hall(pm);     /* Flux orientation is based on the hall sensors */
        update_pwm(pm);
        return;
    }

    /* Execute the selected commutation algorithm */
    switch (cm)
    {
    case CM_ENC_AND_DSM:    /* Encoder and_DSM *//* RZ/T2 add */
    case CM_ENC_AND_CT:     /* Encoder and CT *//* RZ/T2 add */
    case CM_CT:             /* CT *//* RZ/T2 add */
    case CM_FOC:            /* Field Oriented Control */
        /* Invoke Field-Oriented Control algorithm */
        commutate_foc(pm);
        /* Space Vector Modulation. Result is +/-0.5 in pm->out_u/v/w */
        commutate_svm(pm, (float)pm->foc_alpha * (1/32767.0), (float)pm->foc_beta * (1/32767.0));
        /* Update PWM duty ratio - set new phase voltage */
        update_pwm(pm);
        break;
        
    case CM_SVM:            /* Space Vector Modulation only - no current loop */
        {
        float pwm_out_q = pm->output_q;  
        float pwm_out_d = pm->output_d;  
        
        /* Inverse Park Transformation */
        pm->calc_alpha= pwm_out_d * pm->angle_cos - pwm_out_q * pm->angle_sin;
        pm->calc_beta = pwm_out_q * pm->angle_cos + pwm_out_d * pm->angle_sin;
        /* Space Vector Modulation. Result is +/-0.5 in pm->out_u/v/w */
        commutate_svm(pm, pm->calc_alpha * (1/32768.0), pm->calc_beta * (1/32768.0));
        /* Update PWM duty ratio - set new phase voltage */
        update_pwm(pm);
        }
        break;
        
    case CM_FORCED:         /* User-define Flux angle at descrete values */ 
        commutate_set(pm);
        /* Update PWM duty ratio - set new phase voltage */
        update_pwm(pm);
        break;
    default:                /* Each Phase voltage is user-defined */
        break;
    }
}

static void pos_loop(t_motor *pm)
{
    long long work_pos_error;
    long long work_in_vel;

    /* Waiting for the bootstrap circuit charge *//* RZ/T2 add */
    if (pm->charge_state == BS_CHARGEING)
    {
        return;
    }
    
#if defined(__ICCARM__)
    /* Do nothing */
#elif defined(__GNUC__)
    if(SW12_4 == 1) /* SW12_4 : OFF */
    {
        /* Determine if position Control Loop time expired (in PWM Carrier time slices) */
        pm->pos_loop_timer--;
        if (pm->pos_loop_timer > 0)
        {
            return;
        }
        /* Reset position Loop Timer */
        pm->pos_loop_timer = pm->pos_loop_time; 
    }
#endif
   

    
    if((pm->ctrl_mode != CTRM_VELOCITY) && (pm->ctrl_mode != CTRM_TORQUE))
    {   /* position control mode */

        /* Implement velocity Profile Consumption */
        if (pm->vpg_state != VPG_MotionCompleted) 
        {
            /* Check if new velocity / position setpoint is available */
            if (pm->prfl_points != 0) 
            {
                pm->vpg_state = pm->prfl_pull->vpg_state;
                pm->cmd_pos = pm->prfl_pull->position;
                pm->cmd_vel = pm->prfl_pull->velocity;
                pm->cmd_acc = pm->prfl_pull->acceleration;

                pm->prfl_pull++;
                if (pm->prfl_pull == &pm->profileFIFO[VPG_BUFF_SIZE])
                {
                    pm->prfl_pull = &pm->profileFIFO[0];
                }
                pm->prfl_points--;

                if (pm->vpg_state == VPG_MotionCompleted) 
                {
                    pm->act_state |= ACT_MotionComplete;
                }
            
            }
            else
            {
                /* Indicate VPG FIFO is depleted. */
                pm->vpg_overrun++;
            }
        }
        else
        {
            pm->vpg_overrun = 0;
        }
    }
    else
    {   /* velocity control mode or torque control mode *//* RZ/T2 add */
        /* Do nothing */
    }

    /* Calculate PID regulator result */
    if (pm->servo_on) 
    {
        /* Process according to the control mode */
        if((pm->ctrl_mode != CTRM_VELOCITY) && (pm->ctrl_mode != CTRM_TORQUE))
        {   /* position control mode */
            pm->cmd_pos64 = SetSignBit48( (long long)pm->cmd_pos << 16 );
            work_pos_error = SetSignBit48(pm->cmd_pos64 - pm->crnt_pos64);
            work_in_vel = pid_calc_pos64( pm, work_pos_error );
            pm->in_vel64 = SetSignBit48(work_in_vel);
            pm->in_vel = (long)(pm->in_vel64 >> 16);
        }
        else
        {   /* velocity control mode or torque control mode *//* RZ/T2 add */
             pm->pos_error = 0;
             pm->pos_error2 = 0;
             pm->cmd_pos = pm->crnt_pos;
             pm->cmd_pos64 = SetSignBit48( (long long)pm->cmd_pos << 16 );
             pm->in_vel64 = pm->cmd_vel64;
             pm->in_vel = (long)(pm->in_vel64 >> 16);
        }
    }
    else
    {
        pm->pos_error = 0;
        pm->pos_error2 = 0;
        pm->cmd_pos = pm->crnt_pos;
        pm->cmd_pos64 = SetSignBit48( (long long)pm->cmd_pos << 16 );
        pm->in_vel = 0;
        pm->in_vel64 = 0;
        /* RZ/T2 add */
        pm->in_vel64_old = pm->in_vel64;
    }

    /* velocity control */
    vel_loop(pm);
}

/* velocity control */
static void vel_loop(t_motor *pm)
{
    uint8_t k;       /* for loop */
    uint8_t bf_pos;  /* for array position */
    uint8_t af_pos;  /* for array position */
    long long work_vel_error;
    
    long long work_diff_velocity;
    long long work_cur_velocity;
    long long vel_sum = 0;

    short work_cmd_cur;
    short work_trq_cur_limit;
    long long wk_in_vel64;
    long long wk_crnt_vel64;
    long wk_crnt_vel;

    /*************************************************/
    /* array_raw_pos[0]   cuurent Positon value      */
    /* array_raw_pos[1]   1 time past Positon value  */
    /* array_raw_pos[2]   2 time past Positon value  */
    /* array_raw_pos[3]   3 time past Positon value  */
    /*                                               */
    /* array_raw_pos[23] 23 time past Positon value  */
    /* array_raw_pos[24] 24 time past Positon value  */
    /*************************************************/
    for( k = 0; k < ( POS_PAST_DATA - 1 ); k++ )
    {
        af_pos = POS_PAST_DATA - 1 - k;     /* before position */
        bf_pos = af_pos - 1;                /* after position  */

        pm->array_raw_pos[af_pos] = pm->array_raw_pos[bf_pos];
    }
    pm->array_raw_pos[0] = pm->crnt_pos64;    /* array_raw_pos[0] to current position data */

    if( pm->total_num_pos < POS_PAST_DATA )
    {
        pm->total_num_pos++;
    }

    /* diff between most new data and most old data */
    if( pm->total_num_pos == 1 )
    {
        work_cur_velocity = 0;
    }
    else
    {
        work_diff_velocity = SetSignBit48( ( pm->array_raw_pos[0] - pm->array_raw_pos[pm->total_num_pos-1] ) << 16 );
        work_cur_velocity = SetSignBit48( work_diff_velocity / (pm->total_num_pos-1) );
    }

    /**********************************************/
    /* array_vel[0]   cuurent Velocity value      */
    /* array_vel[1]   1 time past Velocity value  */
    /* array_vel[2]   2 time past Velocity value  */
    /* array_vel[3]   3 time past Velocity value  */
    /* array_vel[4]   4 time past Velocity value  */
    /**********************************************/
    for( k = 0; k < ( VEL_AVE_NUM - 1 ); k++ )
    {
        af_pos = VEL_AVE_NUM - 1 - k;       /* before position */
        bf_pos = af_pos - 1;                /* after position  */

        pm->array_vel[af_pos] = pm->array_vel[bf_pos];
        vel_sum += pm->array_vel[af_pos];
        vel_sum = SetSignBit48( vel_sum );
    }
    pm->array_vel[0] = work_cur_velocity;
    vel_sum += pm->array_vel[0];
    vel_sum = SetSignBit48( vel_sum );

    pm->total_num_vel = pm->total_num_pos;
    if( pm->total_num_vel > VEL_AVE_NUM )
    {
        pm->total_num_vel = VEL_AVE_NUM;
    }
    
    if( pm->total_num_vel == 0 )
    {
        pm->crnt_vel64 = 0;
        pm->crnt_vel = 0;
        pm->crnt_acc = 0;
    }
    else
    {
        pm->crnt_vel64 = SetSignBit48( vel_sum / pm->total_num_vel );       //1count/100us
        /* RZ/T2 change */
        wk_crnt_vel = (long)(pm->crnt_vel64 >> 16);
        wk_crnt_vel = (long)(wk_crnt_vel * 0.0002794f/pm->crnt_ds*(( (float)65536)/(float)pm->ec_per_rev)); // [pos] -> [rpm]
        pm->crnt_acc = wk_crnt_vel - pm->crnt_vel;
        pm->crnt_vel = wk_crnt_vel;
    }

    /* RZ/T2 change */
    if ( pm->servo_on == 0 )   /* Servo Off */
//    if ( pm->vpg_state == VPG_MotionCompleted )
    {
        pm->total_num_pos = 0;
        pm->total_num_vel = 0;
    }

    /* Calculate PI regulator result */
    if (pm->servo_on)
    {
        /* Process according to the control mode */
        if(pm->ctrl_mode != CTRM_TORQUE)
        {   /* position control mode or velocity control mode */
            work_vel_error = SetSignBit48( pm->in_vel64 - pm->crnt_vel64 );
            pm->output_q = pid_calc_vel64( pm, work_vel_error );
            pm->output_d = 0;
        }
        else
        {   /* torque control mode *//* RZ/T2 add */
            /* Conversion from Torque to Current */
            work_cmd_cur = torque_to_current( pm );
            /* Absolute value of traget velocity  */

            wk_in_vel64 = pm->in_vel64;
            wk_crnt_vel64 = pm->crnt_vel64;
            /* speed limit pid */
            work_vel_error = SetSignBit48( wk_in_vel64 - wk_crnt_vel64 );
            work_trq_cur_limit = pid_calc_vel64( pm, work_vel_error  );
            /* lower limit */

            /* output & Limit for torque control */
            pm->output_q = torque_limit( pm, work_cmd_cur, work_trq_cur_limit );
            pm->output_d = 0;
        }
    }
    else 
    {
        pm->vel_error = 0;
        pm->vel_error2 = 0;
        pm->output_q = pm->pos_loop_cmd;
    }
}

/* E-Gearing Support Function - set the Slave axis setpoints based on the Gear Ratio */
void set_slave(t_motor *pm)
{
t_motor *ps = pm->slave;

    /* Waiting for the bootstrap circuit charge *//* RZ/T2 add */
    if (pm->charge_state == BS_CHARGEING)
    {
        return;
    }
    /* Determine if position Control Loop time expired (in PWM Carrier time slices) */
    ps->pos_loop_timer--;
    if (ps->pos_loop_timer > 0)
    {
        return;
    }

    /* Reset position Loop Timer */
    ps->pos_loop_timer = ps->pos_loop_time; 

    ps->cmd_pos = (int)(pm->gear_ratio * pm->cmd_pos);
    ps->cmd_vel = (int)(pm->gear_ratio * pm->cmd_vel);
    ps->cmd_acc = (int)(pm->gear_ratio * pm->cmd_acc);
    ps->vpg_state = pm->vpg_state;
    
    if (ps->vpg_state == VPG_MotionCompleted) 
    {
        ps->act_state |= ACT_MotionComplete;
    }

    if (ps->servo_on) 
    {
        ps->output_q = pid_calc(ps, ps->cmd_pos - ps->crnt_pos);
        ps->output_d = 0;
    } 
    else 
    {
        ps->pos_error = 0;
        ps->pos_error2 = 0;
        pm->vel_error = 0;
        pm->vel_error2 = 0;
        ps->cmd_pos = ps->crnt_pos;
        ps->cmd_pos64 = SetSignBit48( (long long)ps->cmd_pos << 16 );
        ps->output_q = ps->pos_loop_cmd;
    }
}

/* Invokes the currently selected velocity Profile Generator */
void vpg_update(t_motor *pm) 
{
    /* Check if motion is started */
    if (pm->vpg_state == VPG_MotionCompleted)
    {
        return;
    }

    /* Is there a room in the FIFO? */
    if (pm->prfl_points >= VPG_BUFF_SIZE)
    {
        return;
    }

    /* Invoke profile generator depending on the profile mode */
    switch (pm->trgtMotion.profile_mode) 
    {
    case VPGM_Trapezoidal: 
        vpg_trap_next(pm, pm->prfl_push_1, pm->prfl_push, 0);
        break;
    case VPGM_Spline: 
        break;
    case VPGM_VelContouring:
        vpg_trap_next(pm, pm->prfl_push_1, pm->prfl_push, 1);
        break;
    case VPGM_PosVelTime: 
        break;
    case VPGM_Bezier: 
        break;
    default:
        return;
    }
    pm->prfl_push_1 = pm->prfl_push;
    pm->prfl_push++;
    if (pm->prfl_push == &pm->profileFIFO[VPG_BUFF_SIZE])
    {
        pm->prfl_push = &pm->profileFIFO[0];
    }
    pm->prfl_points++;
}

/* Executes Periodic Real-Time Tasks */
void m_background(void)
{
    /* Check for control operation suspended */
    if (g_suspend)
    {
        return;
    }
    bootstrap_charge(&g_st_m[3]);
    bootstrap_charge(&g_st_m[2]);
    bootstrap_charge(&g_st_m[6]);
    bootstrap_charge(&g_st_m[7]);
    bootstrap_charge(&g_st_m[8]);

// }
/* Acquire current position */
// for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
// {
    pos_read(&g_st_m[3]);
    pos_read(&g_st_m[2]);
    pos_read(&g_st_m[6]);
    pos_read(&g_st_m[7]);
    pos_read(&g_st_m[8]);

// }
/* Implement position Loop Control */
// for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
// {
    pos_loop(&g_st_m[3]);
    pos_loop(&g_st_m[2]);
    pos_loop(&g_st_m[6]);
    pos_loop(&g_st_m[7]);
    pos_loop(&g_st_m[8]);

// }

// for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
// {
    /* Acquire ADC results */
    crnt_read(&g_st_m[3]);
    crnt_read(&g_st_m[2]);
    crnt_read(&g_st_m[6]);
    crnt_read(&g_st_m[7]);
    crnt_read(&g_st_m[8]);

//  }
   // crnt0_read(&g_st_m[0]);
/* Implement Current Loop Control */
//  for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
//  {
    crnt_loop(&g_st_m[3]);
    crnt_loop(&g_st_m[2]);
    crnt_loop(&g_st_m[6]);
    crnt_loop(&g_st_m[7]);
    crnt_loop(&g_st_m[8]);
#if 0
    /* Bootstrap circuit charging sequence *//* RZ/T2 add */
    for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
    {
        bootstrap_charge(&g_st_m[idx]);
    }
    /* Acquire current position */
    for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
    {
        pos_read(&g_st_m[idx]);
    }
   /* Implement position Loop Control */
    for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
    {
        pos_loop(&g_st_m[idx]);
    }
    for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
    {
        /* Acquire ADC results */
        crnt_read(&g_st_m[idx]);
    }
    /* Implement Current Loop Control */
    for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
    {
        crnt_loop(&g_st_m[idx]);
    }
#endif
    /* Implement Hartbeat */
    m_heartbeat();
    /* Implement Data Collection */
    m_recorder();
    g_tick++;
}

/* Execites Non-Real-Time Tasks */
void m_foreground(void)
{
    /* Process Command Requests */
    if (con2.cmd_req != PTR_NONE)
    {
        m_interpreter(&con2);
    }

    /* Run Veclocity Profile Generators */
    for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
    {
        vpg_update(&g_st_m[idx]);
    }

    /* Check recorder trigger conditions */
    m_rec_begin();

    /* Handle Synchronous Non-Real Time Tasks */
    if (g_tick != g_tick_1)     
    {
        g_tick_1 = g_tick;
        /* Handle Digital Inputs and Hall Sensors */
        if (g_tick & 1)
        {
#if defined(__ICCARM__)
            /* The code below executes once every 200us */
            if (++timer_1ms >= 5)
#elif defined(__GNUC__)
            /* The code below executes once every 100us */
            if (++timer_1ms >= 10)          
#endif
            {
                /* The code below executes once every millisecond */
                timer_1ms = 0;
                /* Handle Interlocks */
                for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
                {
                    interlocks(&g_st_m[idx]);
                }
            }
        }
    }

    m_heartbeat();
}

/* RZ/T2 add */
/******************************************************************************
* Function Name: torque_to_current
* Description  : Conversion from Torque to Current
* Arguments    : pm : structure of motor control(pointer) 
* Return Value : Current command
******************************************************************************/
/* Conversion from Torque to Current */
static short torque_to_current(t_motor *pm)
{
    float temp1 = 0.0f;
    float temp2 = 0.0f;
    float temp3 = 0.0f;
    short result = 0;

    temp1 = ((float)pm->cmd_trq / CNVGAIN_NM_TO_UNM);          /* unit conversion:[uNm] -> [Nm]    */
    temp2 = temp1 * MTR_2_3 / (pm->pole_pairs * pm->mtr_ke);  /* unit conversion:[Nm]  -> [A]     */
    temp3 = temp2 * CUR_BASE_DIG_NUM / CUR_BASE_NUM;          /* unit conversion:[A]   -> [digit] */

    /* Limit to +/-32767 */
    if(temp3 >= LIM_INT16_MAX)
    {
        temp3 = LIM_INT16_MAX;
    }
    else if(temp3 <= LIM_INT16_MIN)
    {
        temp3 = LIM_INT16_MIN;
    }
    else
    {
        /* Do nothing */
    }

    result = (short)temp3;

    return result;
}
/*******************************************************************************
End of function torque_to_current
*******************************************************************************/

/******************************************************************************
* Function Name: torque_limit
* Description  : Limit for torque control
* Arguments    : pm : structure of motor control(pointer) 
               : cmd_cur : Current command
               : limit : Current limit
* Return Value : Current command
******************************************************************************/
static short torque_limit(t_motor *pm, short cmd_cur, short limit)
{
    short output_current_lim;
    short limit_max;
    short limit_min;

    /* velocity sign check */
    if( pm->in_vel64 >=0 )
    {
        limit_max = limit;
        limit_min = -pm->PiOut_limit_vel;
    }
    else
    {
        limit_max = pm->PiOut_limit_vel;
        limit_min = limit;
    }

    /* limit */
    if(cmd_cur > limit_max)
    {
        output_current_lim = limit_max;
    }
    else if(cmd_cur < limit_min)
    {
        output_current_lim = limit_min;
    }
    else
    {
        output_current_lim = cmd_cur;
    }

    return output_current_lim;
}
/*******************************************************************************
End of function torque_limit
*******************************************************************************/

/******************************************************************************
* Function Name: bootstrap_charge
* Description  : Bootstrap circuit charging sequence
* Arguments    : *pm : Motor Control Parameters(pointer)
* Return Value : none
******************************************************************************/
static void bootstrap_charge (t_motor *pm)
{

    switch (pm->charge_state)
    {
    case BS_UNCHARGED:
        {
//            if(pm->servo_on == 1)
            if((pm->act_state & ACT_PowerOn) != 0)
            {
                /* Boot strap circuit charge start */
                pm->charge_state = BS_CHARGEING;
            }
        }
        break;
    case BS_CHARGEING:
        {
            pm->charge_cycle++;
            if(pm->charge_cycle > BS_CHARGE_TIME_CNT)
            {
                /* set current offset */
                pm->adc1_offs = pm->adc1_raw;
                pm->adc2_offs = pm->adc2_raw;
                pm->adc3_offs = pm->adc3_raw;
                /* Bootstrap circuit end of charging */
                pm->charge_state = BS_CHARGE_END;
            }
        }
        break;
    case BS_CHARGE_END:
        {
            /* Do nothing */
        }
        break;
    default:
        return;
    }

    if(DSM_wait_state == 0)
    {
        DSM_wait_count++;
        if(DSM_wait_count > 10)
        {
            DSM_wait_state = 1;
        }
    }

}
/*******************************************************************************
End of function bootstrap_charge
*******************************************************************************/
