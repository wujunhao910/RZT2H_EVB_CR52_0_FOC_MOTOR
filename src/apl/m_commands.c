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
* File Name    : m_commands.c
* Version      : 1.0
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Source file of Command.
*******************************************************************************/

/*****************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <string.h>
#include <math.h>

#include "m_common.h"
#include "m_commands.h"
#include "m_recorder.h"
#include "r_cg_macrodriver.h"
#include "r_dsmif.h"

#include "m_biplane.h"


#define OSPI_DEVICE_START_ADDRESS (0x40000000)

/* RZ/T2 add */
enum ParameterCode {
    PC_NONE,
    PC_WORD,
    PC_LONG,
	PC_LONGLONG
};

/*****************************************************************************
Global variables
******************************************************************************/
/* exported variables */
extern t_motor m1,m2;
extern short g_suspend;
/* RZ/T2 add */
extern t_decode mDecodePtrTbl[]; 

/*****************************************************************************
Static variables and functions
******************************************************************************/
/* prototype definitions of static functions */
/* RZ/T2 add */
static unsigned char ascii_hex_sub( unsigned char arg);
static short short_pvt_ascii_hex (unsigned char * buf);
static long long_pvt_ascii_hex (unsigned char * buf);

static int motor_param_qflash_w(t_motor *pm, int bsize);

/* static variables */
static const char * s_version = "RZ/T2H V.1.00 Firmware , (c) Renesas Electronics Corporation";

/*****************************************************************************
Global functions
******************************************************************************/
void m_Version(t_console *pc, t_motor *pm) 
{
    strcpy((char *)pc->ptx, s_version);
    pc->tx_count += strlen(s_version);
    pc->ptx += pc->tx_count;
}

void m_Position(t_console *pc, t_motor *pm) 
{
    if (pc->set != 0) 
    {
        set_position(pm, pc->arg);
        if (pm->module_type == TYPE_EGEAR)
        {
            set_position(pm->slave, (long)((double)pm->crnt_pos * pm->gear_ratio));
        }
    }
    else 
    {
        print_dec(pc, pm->crnt_pos);
    }
}

void m_PosInvert(t_console *pc, t_motor *pm) 
{
    if (pc->set != 0) 
    {
        pm->pos_inv_mode = pc->arg;
    }
    else 
    {
        print_dec(pc, pm->pos_inv_mode);
    }
}

void m_Inputs(t_console *pc, t_motor *pm) 
{
    if (pc->set != 0) 
    {
        pc->err = PE_INVALID_ACCESS;    /* The Input variable is read-only */
    }
    else 
    {
        unsigned short data;
        
        /* Get Hall Sensors state */
        data  = (m1.dinputs & 0x0070) >> 4;	
        data |= (m2.dinputs & 0x0070);
        /* Get Digital Inputs state */
        data |= (m1.dinputs & 0x000f) << 8;
        data |= (m2.dinputs & 0x000f) << 12;
        print_hex(pc, data);
    }
}

void m_Index(t_console *pc, t_motor *pm) 
{
    if (pc->set != 0) 
    {
        pc->err = PE_INVALID_ACCESS;    /* The Index variable is read-only */
    }
    else 
    {
        print_dec(pc, pm->index_pos);
        pm->act_state &= ~ACT_PosCaptured;
    }
}

void m_Abs(t_console *pc, t_motor *pm) 
{   
    if (pc->set != 0) 
    {
        pm->buffMotion.profile_mode = pm->dflt_vgp_mode;
        pm->buffMotion.position = pc->arg;
    } 
    else 
    {
        print_dec (pc, pm->buffMotion.position);
    }
}

void m_Rel(t_console *pc, t_motor *pm) 
{
    if (pc->set != 0) 
    {
        pm->buffMotion.profile_mode = pm->dflt_vgp_mode;
        pm->buffMotion.position_rel = pc->arg;
    } 
    else 
    {
        print_dec (pc, pm->buffMotion.position_rel);
    }
}

void m_Forward(t_console *pc, t_motor *pm) 
{
    if (pc->set != 0) 
    {
        pm->buffMotion.profile_mode = VPGM_VelContouring;
        pm->buffMotion.dir_sign = 1;
    }
}

void m_Reverse(t_console *pc, t_motor *pm) 
{
    if (pc->set != 0) 
    {
        pm->buffMotion.profile_mode = VPGM_VelContouring;
        pm->buffMotion.dir_sign = -1;
    }
}

static void calc_i2tpars(t_motor *pm) 
{
    pm->I2t_limit = (long)pm->I2t_current * (long)pm->I2t_time;
    pm->I2t_nominal = pm->tc_limit * pm->tc_limit;
    
}

void m_PLimit(t_console *pc, t_motor *pm) 
{
    if (pc->set != 0) 
    {
        pm->I2t_current = pc->arg;
        calc_i2tpars(pm);
    }
    else 
    {
        print_dec(pc, pm->I2t_current);
    }
}

void m_PLimitTime(t_console *pc, t_motor *pm) 
{
    if (pc->set != 0) 
    {
        pm->I2t_time = pc->arg;
        calc_i2tpars(pm);
    }
    else 
    {
        print_dec(pc, pm->I2t_time);
    }
}

void m_CurrentLimit(t_console *pc, t_motor *pm)
{
    if (pc->set != 0) 
    {
        pm->tc_limit = pc->arg;
        calc_i2tpars(pm);
    }
    else 
    {
        print_dec(pc, pm->tc_limit);
    }
}

void m_PosLoopCmd(t_console *pc, t_motor *pm) 
{
    if (pc->set != 0) 
    {
        pm->foc_id_err_int = 0;
        pm->foc_iq_err_int = 0;
        pm->pos_loop_cmd = pc->arg;
    }
    else 
    {
        print_dec(pc, pm->pos_loop_cmd);
    }
}

void m_OutputIQ(t_console *pc, t_motor *pm) 
{
    if (pc->set != 0) 
    {
        pm->foc_id_err_int = 0;
        pm->foc_iq_err_int = 0;
        pm->pos_loop_cmd = pc->arg;
    }
    else 
    {
        print_dec(pc, pm->pos_loop_cmd);
    }
}

void m_OutputID(t_console *pc, t_motor *pm) 
{
    if (pc->set != 0) 
    {
        pm->foc_id_err_int = 0;
        pm->foc_iq_err_int = 0;
        pm->output_d = pc->arg;
    }
    else 
    {
        print_dec(pc, pm->output_d);
    }
}

void servo_on(t_motor *pm)
{
    if (pm->servo_on == 0) 
    {
        pm->vpg_state = VPG_MotionCompleted;
        pm->prfl_points = 0;
        pm->cmd_pos = pm->crnt_pos;
        pm->trgtMotion.position = pm->crnt_pos;
        pm->buffMotion.position = pm->crnt_pos;
        
        pm->foc_id_err_int = 0;
        pm->foc_iq_err_int = 0;
        pm->integral_err = 0;
        pm->integral_err_vel = 0;
        pm->integral_err2 = 0;
        pm->integral_err2_vel = 0;
        
        pm->act_state |= ACT_ServoOn | ACT_MotionComplete;
        pm->servo_on = 1;
        
        calc_i2tpars(pm);
    }
    pm->act_state &= ~(ACT_AmpFault | ACT_PosError | ACT_WrapAround | ACT_OverCurrent | ACT_Inhibit);
}

static void servo_off_local(t_motor *pm)
{
    pm->vpg_state = VPG_MotionCompleted;
    pm->prfl_points = 0;
    pm->cmd_pos = pm->crnt_pos;
    pm->pos_error = 0;
    pm->vel_error = 0;
    pm->integral_err = 0;
    pm->integral_err_vel = 0;
    pm->derivative_err = 0;
    pm->derivative_err_vel = 0;
    pm->pos_error2 = 0;
    pm->vel_error2 = 0;
    pm->integral_err2 = 0;
    pm->integral_err2_vel = 0;
    pm->derivative_err2 = 0;
    pm->derivative_err2_vel = 0;
    pm->foc_id_err_old = 0;
    pm->foc_iq_err_old = 0;
    pm->pos_loop_cmd = pm->crnt_bias;
    pm->output_q = pm->crnt_bias;
    pm->output_d = 0;
    pm->output_q_old = pm->output_q;
    pm->output_d_old = pm->output_d;
    pm->act_state |= ACT_MotionComplete;
    pm->act_state &= ~(ACT_ServoOn|ACT_Busy);
    pm->servo_on = 0;
    pm->fsm_home = HS_IDLE;
    if (pm->buffMotion.profile_mode == VPGM_VelContouring) 
    {
        pm->buffMotion.profile_mode = pm->dflt_vgp_mode;
    }

    /* bootstrap_charging initialize *//* RZ/T2 add */
    pm->charge_cycle = 0;
    pm->charge_state = BS_UNCHARGED;
}

void servo_off(t_motor *pm)
{
    servo_off_local(pm);
    if (pm->module_type == TYPE_EGEAR)
    {
        servo_off_local(pm->slave);
    }
    pm->pvt_push = pm->pvt_pointsFIFO;
    pm->pvt_start_point = pm->pvt_pointsFIFO;
    pm->pvt_end_point = pm->pvt_pointsFIFO;
    pm->pvt_points = 0;
}

void update_ctrl(t_motor *pm)
{
    /* If a relative target is requested - transform into absolute target */
    if (pm->buffMotion.position_rel != 0) 
    {
        pm->buffMotion.position = pm->buffMotion.position_rel + pm->crnt_pos;
        pm->buffMotion.position_rel = 0;
    }
    /* Update the motion control parameters with the buffered one */
    pm->trgtMotion.position = pm->buffMotion.position;
    pm->trgtMotion.velocity = pm->buffMotion.velocity;
    pm->trgtMotion.acceleration = pm->buffMotion.acceleration;
    pm->trgtMotion.deceleration = pm->buffMotion.deceleration;
    pm->trgtMotion.accel_jerk = pm->buffMotion.accel_jerk;
    pm->trgtMotion.decel_jerk = pm->buffMotion.decel_jerk;
    pm->trgtMotion.dir_sign = pm->buffMotion.dir_sign;

    /* If the deceleration is not explicitly defined use the acceleration instead */
    if (pm->trgtMotion.deceleration == 0)
    {
        pm->trgtMotion.deceleration = pm->trgtMotion.acceleration;
    }
    pm->pos_error_limit = pm->buff_err_limit;

    /* Disable interrupts that may affect the parameter changes */
#if   defined(__ICCARM__)
    __disable_interrupt();
#elif defined(__GNUC__)
    DI();
#else
#error Unsupported Compiler!
#endif
    /* Update the PID parameters with the buffered one */
    pm->crnt_kp = pm->buff_kp;
    pm->crnt_ki = pm->buff_ki;
    pm->crnt_kd = pm->buff_kd;
    pm->crnt_kvff = pm->buff_kvff;
    pm->crnt_kaff = pm->buff_kaff;
    pm->integral_limit = (long) pm->integral_limit16 << 8;
    if (pm->integral_limit > 0x007fffff)
    {
        pm->integral_limit = 0x007fffff;
    }

    if (pm->crnt_ds)
    {
        pm->pos_loop_time = pm->crnt_ds;
    }

    pm->crnt_kp_vel = pm->buff_kp_vel;
    pm->crnt_ki_vel = pm->buff_ki_vel;
    pm->crnt_kd_vel = pm->buff_kd_vel;
    pm->integral_limit_vel = INITVAL_VEL_ILIMIT;
    pm->PiOut_limit_vel    = INITVAL_VEL_MLIMIT;

    /* Process stop_request */
    if (pm->stop_request == SM_NOSTOP) 
    {   
        if (pm->vpg_state == VPG_MotionCompleted) 
        {
            pm->trgtMotion.profile_mode = pm->buffMotion.profile_mode;
            switch (pm->trgtMotion.profile_mode) {
            case VPGM_Trapezoidal:
                pm->vpg_state = vpg_trap_start(pm, 0);		/* Start motion request in Trapezoidal Profile */
                break;
            case VPGM_Spline:
                break;
            case VPGM_Bezier:
                break;
            case VPGM_PosVelTime:
                break;
            default:
                pm->vpg_state = vpg_trap_start(pm, 1);		/* Start motion request in velocity Mode */
                break;
            }
            if (pm->vpg_state != VPG_MotionCompleted) 
            {
                pm->act_state &= ~(ACT_MotionComplete|ACT_PVTEmpty);
            } 
            else 
            {
                pm->act_state |= ACT_MotionComplete;
            }
        } 
        else 
        {
            /* Change velocity profile on the fly only allowed for velocity mode */
            if (pm->buffMotion.profile_mode == VPGM_VelContouring || pm->buffMotion.profile_mode == VPGM_Trapezoidal)
            {
                pm->trgtMotion.profile_mode = pm->buffMotion.profile_mode;
                pm->direction = pm->trgtMotion.dir_sign;
                pm->prfl_points = 1;
                if (pm->prfl_pull->vpg_state == VPG_MotionCompleted)
                {
                    pm->prfl_pull->vpg_state = VPG_Deceleration;
                }
            }
        }
    } 
    else 
    {
        pm->pvt_push = pm->pvt_pointsFIFO;
        pm->pvt_start_point = pm->pvt_pointsFIFO;
        pm->pvt_end_point = pm->pvt_pointsFIFO;
        pm->pvt_points = 0;
        
        /* If the motion is completed - ignore the stop request */
        if (pm->vpg_state == VPG_MotionCompleted) 
        {
            pm->trgtMotion.position = pm->crnt_pos;
        } 
        else 
        {
            long stop_dist = pm->prfl_pull->stop_dist;
            if (pm->trgtMotion.profile_mode != VPGM_Trapezoidal) 
            {
                pm->trgtMotion.profile_mode = VPGM_Trapezoidal;
                pm->buffMotion.profile_mode = VPGM_Trapezoidal;
                stop_dist = (long)(((double)pm->prfl_pull->velocity * (double)pm->prfl_pull->velocity) / (double)(pm->trgtMotion.deceleration<<1)) >> 16;
            }
            if (pm->stop_request == SM_ABRUPT)          /* Abrupt stop request */
            {
                stop_dist >>= 5;
                pm->trgtMotion.deceleration <<= 5;
            }            
            /* Check the direction and adjust the target with the stopping distance */
            if (pm->trgtMotion.position > pm->crnt_pos)
            {
                pm->trgtMotion.position = pm->crnt_pos + stop_dist;
            }
            else
            {
                pm->trgtMotion.position = pm->crnt_pos - stop_dist;
            }
        }
        pm->buffMotion.position = pm->trgtMotion.position;
    }
    pm->stop_request = SM_NOSTOP;						    /* Clear stop request */

#if   defined(__ICCARM__)
   __enable_interrupt();
#elif defined(__GNUC__)
   EI();
#else
#error Unsupported Compiler!
#endif
}

void map_phases(t_motor *pm)
{
    switch (pm->phase_config)
    {
    case 0: 
        pm->mapPhaseU = pm->regPhaseU; 
        pm->mapPhaseV = pm->regPhaseV; 
        pm->mapPhaseW = pm->regPhaseW; 
        pm->p_iu = &(pm->adc_iu);
        pm->p_iv = &(pm->adc_iv);
        break;
    case 1: 
        pm->mapPhaseU = pm->regPhaseU; 
        pm->mapPhaseV = pm->regPhaseW; 
        pm->mapPhaseW = pm->regPhaseV; 
        pm->p_iu = &(pm->adc_iu);
        pm->p_iv = &(pm->adc_iw);
        break;
    case 2: 
        pm->mapPhaseU = pm->regPhaseV; 
        pm->mapPhaseV = pm->regPhaseW; 
        pm->mapPhaseW = pm->regPhaseU; 
        pm->p_iu = &(pm->adc_iv);
        pm->p_iv = &(pm->adc_iw);
        break;
    case 3: 
        pm->mapPhaseU = pm->regPhaseV; 
        pm->mapPhaseV = pm->regPhaseU; 
        pm->mapPhaseW = pm->regPhaseW; 
        pm->p_iu = &(pm->adc_iv);
        pm->p_iv = &(pm->adc_iu);
        break;
    case 4: 
        pm->mapPhaseU = pm->regPhaseW; 
        pm->mapPhaseV = pm->regPhaseU; 
        pm->mapPhaseW = pm->regPhaseV; 
        pm->p_iu = &(pm->adc_iw);
        pm->p_iv = &(pm->adc_iu);
        break;
    case 5: 
    default:
        pm->mapPhaseU = pm->regPhaseW; 
        pm->mapPhaseV = pm->regPhaseV; 
        pm->mapPhaseW = pm->regPhaseU; 
        pm->p_iu = &(pm->adc_iw);
        pm->p_iv = &(pm->adc_iv);
        break;
    }
}

void set_cmt_params(t_motor *pm) 
{
    double ecpc;
    pm->phase_corr_cntr = 0;
    if (pm->pole_pairs != 0)
    {
        ecpc = (double)pm->ec_per_rev / (double)pm->pole_pairs;
        pm->ec_per_ecycle = pm->ec_per_rev / pm->pole_pairs;
        pm->phase_corr = pm->ec_per_rev % pm->pole_pairs;
    }
    else
    {
        ecpc = pm->ec_per_rev;
        pm->ec_per_ecycle = pm->ec_per_rev;
        pm->phase_corr = 0;
    }
    pm->counts2rad = (MTR_TWOPI) / ecpc;
}

static void power_on(t_console *pc, t_motor *pm)
{
    volatile int wait;

    map_phases(pm);
    set_cmt_params(pm);
    
    pwm_enable(pm);

    pm->act_state |= ACT_PowerOn;
    pm->act_state &= ~(ACT_AmpFault | ACT_PosError | ACT_WrapAround | ACT_OverCurrent | ACT_Inhibit | ACT_PVTEmpty);

    if ((pm->act_state & ACT_Aligned) == 0)
    {
        if (((pc->set != 0) && (pc->arg == 1)) || (pm->phasing_mode == PIM_HALLS_BASED))
        {
            m_AlignPhase(pc, pm);
        }
    }
}

void m_PowerOn(t_console *pc, t_motor *pm) 
{
    power_on(pc, pm);
}

void m_PowerOff(t_console *pc, t_motor *pm) 
{
    pwm_disable(pm);
    servo_off(pm);
    pm->act_state &= ~ACT_PowerOn;
}

static void update_pid(t_motor *pm)
{
    /* Update the PID parameters with the buffered one */
    pm->crnt_kp = pm->buff_kp;
    pm->crnt_ki = pm->buff_ki;
    pm->crnt_kd = pm->buff_kd;
    pm->integral_limit = (long) pm->integral_limit16 << 8;
    if (pm->integral_limit > 0x007fffff)
    {
        pm->integral_limit = 0x007fffff;
    }
    if (pm->crnt_ds)
    {
        pm->pos_loop_time = pm->crnt_ds;
    }

    pm->crnt_kp_vel = pm->buff_kp_vel;
    pm->crnt_ki_vel = pm->buff_ki_vel;
    pm->crnt_kd_vel = pm->buff_kd_vel;
    pm->integral_limit_vel = INITVAL_VEL_ILIMIT;
    pm->PiOut_limit_vel    = INITVAL_VEL_MLIMIT;
}

void m_ServoOn(t_console *pc, t_motor *pm) 
{
    if (pm->commutation_mode == CM_FORCED)
    {
        return;
    }

    if( ( pm->ErrSts & pm->ErrMsk ) != 0 )
    {
        return;
    }

    if ((pm->act_state & ACT_PowerOn) == 0)
    {
        m_PowerOn(pc, pm);
    }
    
    if (!(pm->act_state & ACT_Aligned)) 
    {
        m_AlignPhase(pc, pm);
    }
    update_pid(pm);
    servo_on(pm);
    if (pm->module_type == TYPE_EGEAR)
    {
        set_position(pm->slave, (long)((double)pm->crnt_pos * pm->gear_ratio));
        update_pid(pm->slave);
        servo_on(pm->slave);
    }
}

void m_ServoOff(t_console *pc, t_motor *pm) 
{
    servo_off(pm);
}

void m_SmoothStop(t_console *pc, t_motor *pm) 
{
	pm->stop_request = SM_SMOOTH;
	pm->fsm_home = HS_IDLE;
    update_ctrl(pm);
}

void m_AbruptStop(t_console *pc, t_motor *pm) 
{
	pm->stop_request = SM_ABRUPT;
	pm->fsm_home = HS_IDLE;
    update_ctrl(pm);
}

void m_Go(t_console *pc, t_motor *pm) 
{
    if (pc->set) 
    {
        pm->buffMotion.position = pc->arg;
    }
    update_ctrl(pm);
}

void m_AlignPhase(t_console *pc, t_motor *pm) 
{
    /* Set flux vector angle */
    pm->phase_vector = 0;
    pm->phase_origin = 0;
    
    /* Set current phase init mode and activate phasing state */
    pm->phasing_mode_crnt = pm->phasing_mode;
    pm->phasing_timer = pm->phasing_time;
    pm->act_state &= ~ACT_Aligned;
    pm->aligning = 1;
    
    pm->dither_last_pos = pm->crnt_pos;
    pm->dither_cycles = 0;
    pm->dither_delta = pm->ec_per_ecycle >> 1 - 1;
    pm->dither_timer = pm->phasing_time >> 7;

    if (pm->dither_timer < 2)
    {
        pm->dither_timer = 2;
    }
}

void m_Output1(t_console *pc, t_motor *pm) 
{
}

void m_Output2(t_console *pc, t_motor *pm) 
{
}

void m_Setup(t_console *pc, t_motor *pm) 
{
    /* Make sure the servo is not on */
    if (pm->servo_on)
    {
        pc->err = PE_INVALID_STATE;    /* Invalid state */
        return;
    }
    pm->phase_config = 0;
    map_phases(pm);
    
    /* Initiate forced phasing at sector 0 */
    pm->act_state &= ~ACT_Aligned;
    pm->aligning = 1;
    pm->phase_vector = 0;
    pm->hall_inverted = 0;
    pm->phasing_timer = pm->phasing_time;
    pm->phasing_mode_crnt = PIM_FORCED;
    
    /* Set the state machine to handle the following steps */
    pm->fsm_home = HS_WAIT_ALIGN_0;
}

/* RZ/T2 change */

static void set_pars(t_motor *pm)
{
    pm->pars.version = 0x55aa0001;
    pm->pars.module_type = pm->module_type;
    pm->pars.encoder_type = pm->encoder_type;
    pm->pars.halls_type = pm->halls_type;
    pm->pars.hall_inverted = pm->hall_inverted;
    pm->pars.hall_shift = pm->hall_shift;
    
    pm->pars.commutation_mode = pm->commutation_mode;
    pm->pars.auto_stop_mode = pm->auto_stop_mode;
    pm->pars.simulated_mode = pm->simulated_mode;
    pm->pars.pos_capture_mode = pm->pos_capture_mode;
    pm->pars.pos_inv_mode = pm->pos_inv_mode;
    pm->pars.dflt_vgp_mode = pm->dflt_vgp_mode;
    pm->pars.brake_mode = pm->brake_mode;
    
    pm->pars.motor_type = pm->motor_type;
    pm->pars.pole_pairs = pm->pole_pairs;
    pm->pars.phase_config = pm->phase_config;
    pm->pars.pos_scale = pm->pos_scale;
    pm->pars.ec_per_rev = pm->ec_per_rev;
    pm->pars.ec_per_ecycle = pm->ec_per_ecycle;
 
    pm->pars.buffMotion.acceleration = pm->buffMotion.acceleration;
    pm->pars.buffMotion.deceleration = pm->buffMotion.deceleration;
    pm->pars.buffMotion.accel_jerk = pm->buffMotion.accel_jerk;
    pm->pars.buffMotion.decel_jerk = pm->buffMotion.decel_jerk;
      
    pm->pars.home_inv_mask = pm->home_inv_mask;
    pm->pars.home_mask = pm->home_mask;
    pm->pars.home_offset = pm->home_offset;
    pm->pars.dinputs_err_mask = pm->dinputs_err_mask;
    for (short i = 0; i < 8; i++){
        pm->pars.user_data[i] = pm->motor_idx;
    }

    pm->pars.I2t_current = pm->I2t_current;
    pm->pars.I2t_time = pm->I2t_time;
    pm->pars.tc_limit = pm->tc_limit;
    pm->pars.tc_limit_time = pm->tc_limit_time;

    pm->pars.pos_error_limit = pm->pos_error_limit;
    pm->pars.pos_error_time = pm->pos_error_time;
    pm->pars.crnt_ds = pm->crnt_ds;
    pm->pars.crnt_bias = pm->crnt_bias;
    pm->pars.buff_kp = pm->buff_kp;
    pm->pars.buff_ki = pm->buff_ki;
    pm->pars.buff_kd = pm->buff_kd;
    pm->pars.buff_kvff = pm->buff_kvff;
    pm->pars.buff_kaff = pm->buff_kaff;
    pm->pars.buff_err_limit = pm->buff_err_limit;
    pm->pars.integral_limit16 = pm->integral_limit16;
    pm->pars.pos_loop_limit = pm->pos_loop_limit;
    pm->pars.foc_kp = pm->foc_kp;
    pm->pars.foc_ki = pm->foc_ki;
    pm->pars.foc_kd = pm->foc_kd;

    pm->pars.phasing_mode = pm->phasing_mode;
    pm->pars.phasing_power = pm->phasing_power;
    pm->pars.phasing_time = pm->phasing_time;
    pm->pars.phase_adv_gain = pm->phase_adv_gain;
    pm->pars.phase_vel_comp = pm->phase_vel_comp;
    
    pm->pars.enc_timeout = pm->enc_timeout;
    pm->pars.enc_baudrate = pm->enc_baudrate;
    pm->pars.module_addr = pm->module_addr;
    pm->pars.group_addr = pm->group_addr;

    pm->pars.buff_kp_vel = pm->buff_kp_vel;
    pm->pars.buff_ki_vel = pm->buff_ki_vel;
    pm->pars.buff_kd_vel = pm->buff_kd_vel;
}

static void get_pars(t_motor *pm, t_motor_pars *pars)
{
    if (pars->version != 0x55aa0001)
    {
        return;
    }
    pm->module_type = pars->module_type;
    pm->encoder_type = pars->encoder_type;
    pm->halls_type = pars->halls_type;
    pm->hall_inverted = pars->hall_inverted;
    pm->hall_shift = pars->hall_shift;
    
    pm->commutation_mode = pars->commutation_mode;
    pm->auto_stop_mode = pars->auto_stop_mode;
    pm->simulated_mode = pars->simulated_mode;
    pm->pos_capture_mode = pars->pos_capture_mode;
    pm->pos_inv_mode = pars->pos_inv_mode;
    pm->dflt_vgp_mode = pars->dflt_vgp_mode;
    pm->brake_mode = pars->brake_mode;
    
    pm->motor_type = pars->motor_type;
    pm->pole_pairs = pars->pole_pairs;
    pm->phase_config = pars->phase_config;
    pm->pos_scale = pars->pos_scale;
    pm->ec_per_rev = pars->ec_per_rev;
    pm->ec_per_ecycle = pars->ec_per_ecycle;
 
    pm->buffMotion.acceleration = pars->buffMotion.acceleration;
    pm->buffMotion.deceleration = pars->buffMotion.deceleration;
    pm->buffMotion.accel_jerk = pars->buffMotion.accel_jerk;
    pm->buffMotion.decel_jerk = pars->buffMotion.decel_jerk;
      
    pm->home_inv_mask = pars->home_inv_mask;
    pm->home_mask = pars->home_mask;
    pm->home_offset = pars->home_offset;
    pm->dinputs_err_mask = pars->dinputs_err_mask;
    for (short i = 0; i < 8; i++)
    {
        pm->user_data[i] = pars->user_data[i];
    }

    pm->I2t_current = pars->I2t_current;
    pm->I2t_time = pars->I2t_time;
    pm->tc_limit = pars->tc_limit;
    pm->tc_limit_time = pars->tc_limit_time;

    pm->pos_error_limit = pars->pos_error_limit;
    pm->pos_error_time = pars->pos_error_time;
    pm->crnt_ds = pars->crnt_ds;
    pm->crnt_bias = pars->crnt_bias;
    pm->buff_kp = pars->buff_kp;
    pm->buff_ki = pars->buff_ki;
    pm->buff_kd = pars->buff_kd;
    pm->buff_kvff = pars->buff_kvff;
    pm->buff_kaff = pars->buff_kaff;
    pm->buff_err_limit = pars->buff_err_limit;
    pm->integral_limit16 = pars->integral_limit16;
    pm->pos_loop_limit = pars->pos_loop_limit;
    pm->foc_kp = pars->foc_kp;
    pm->foc_ki = pars->foc_ki;
    pm->foc_kd = pars->foc_kd;

    pm->buff_kp_vel = pars->buff_kp_vel;
    pm->buff_ki_vel = pars->buff_ki_vel;
    pm->buff_kd_vel = pars->buff_kd_vel;

    pm->phasing_mode = pars->phasing_mode;
    pm->phasing_power = pars->phasing_power;
    pm->phasing_time = pars->phasing_time;
    pm->phase_adv_gain = pars->phase_adv_gain;
    pm->phase_vel_comp = pars->phase_vel_comp;
    
    pm->enc_timeout = pars->enc_timeout;
    pm->enc_baudrate = pars->enc_baudrate;
    
    /* Set default gearing parameters */
    pm->gear_in = 1;
    pm->gear_out = 1;
    pm->gear_ratio = 1.0;
    
    /* Validate the gearing parameters */
    if (pars->gear_in > 0 && pars->gear_out > 0)
    {
        pm->gear_in = pars->gear_in;
        pm->gear_out = pars->gear_out;
        pm->gear_ratio = (double) pars->gear_out / (double) pars->gear_in;
    }
    else if (pm->module_type == TYPE_EGEAR)
    {
        pm->module_type = TYPE_DUAL_CH;
    }
    else
    {
        /* Do Nothing */
    }
    pm->module_addr = pars->module_addr;
    pm->group_addr = pars->group_addr;
}

void m_Restore(t_console *pc, t_motor *pm) 
{
#if   defined(__ICCARM__)
    /* Do nothing */
#elif defined(__GNUC__)
    t_motor_pars *r_param = (t_motor_pars *)(OSPI_DEVICE_START_ADDRESS + pm->flash_pars_offs);
    get_pars(pm, (t_motor_pars *)r_param);
#endif
}

void m_Save(t_console *pc, t_motor *pm)
{
#if   defined(__ICCARM__)
    /* Do nothing */
#elif defined(__GNUC__)
    int ret;
    g_suspend = 1;      /* Suspend PWM IRQ Handler - no control operation during FLASH Writing */
    set_pars(pm);
    
    LED2 = 0;
    ret= motor_param_qflash_w(pm, sizeof(t_motor_pars));
    if (ret != 0)
    {
        LED2 = 1;
        pc->err = PE_EXECUTE;    /* Execution error */
    }
    g_suspend = 0;
#endif
}

void m_Reset(t_console *pc, t_motor *pm) 
{
    setup_motor(pm, 1);
}

/* Setup default motor parameters*/
void setup_motor(t_motor *pm, unsigned int is_reset_cmd)
{
    map_phases(pm);
    pm->pwm_period = *(pm->regPWMPeriod);
    /* Set 50% PWM for all phases */
    pm->pwm_period_half = pm->pwm_period >> 1;
    /* RZ/T2 change */
    *pm->regPhaseU = pm->pwm_period;
    *pm->regPhaseV = pm->pwm_period;
    *pm->regPhaseW = pm->pwm_period;
    
    /* Set Phase Output Value at 50% of the total range */
    pm->PhaseU = 32767;
    pm->PhaseV = 32767;
    pm->PhaseW = 32767;
   // pm->PhaseU = 8192;
  //  pm->PhaseV = 8192;
  //  pm->PhaseW = 8192;

    pm->act_state = ACT_MotionComplete;
    pm->act_state_1 = 0;
    
    pm->index_pos = 0;

    pm->module_type = TYPE_DUAL_CH;
    if ((0 != is_reset_cmd) && (ETYPE_INCREMENTAL != pm->encoder_type))
    {
        close_encoder(pm, pm->encoder_type);
    }
    /* RZ/T2 change */
    pm->encoder_type = ETYPE_APE_FACODER;
    pm->servo_on = 0;
    pm->pos_loop_timer = 0;
    pm->pos_read_timer = 0;
    pm->pos_loop_time = 2;	// Equivalent to 100us
    pm->crnt_ds = 2;

    pm->gear_in = 1;
    pm->gear_out = 1;
    pm->gear_ratio = 1.0;
    
    pm->halls_type = HTYPE_PARALLEL;

    pm->hall_inverted = 1;
    pm->hall_shift = -1;
    pm->hall_state_1 = 0;
    pm->hall_change_pos = 0;

    pm->phasing_time = 5000;   // 100us * 5000 = 0.5s
    pm->phasing_power = 6553; // ~25% of max output
    pm->phasing_timer = pm->phasing_time;

    // TSM3101
    pm->phasing_mode = PIM_FORCED;
    pm->phasing_mode_crnt = PIM_FORCED;

    
    pm->pos_scale = 0;

    // TSM3101
    pm->phase_config = 0;
   pm->pole_pairs = 5;
    //pm->pole_pairs = 2;

    // TSM3101
    //pm->ec_per_rev = 65536;
    pm->ec_per_rev = 131072;
    //pm->ec_per_rev = 32768;
    pm->real_res_prev = 0;

    pm->ec_per_ecycle = pm->ec_per_rev / pm->pole_pairs;
    pm->pos_offset = 0;
    pm->foc_kp = 10;
    pm->foc_ki = 1;
    pm->foc_kd = 0;

    pm->phase_vel_comp = 10;
    pm->phase_adv_gain = 0;
    pm->motor_type = 3;        // Number of phases: 2 - DC brush, 3 - PMSM / BLDC
    pm->vpg_overrun = 0;
    pm->dinputs_err_mask = 0;
    pm->pos_inv_mode = 0;

    pm->buffMotion.position = 0;
    pm->buffMotion.velocity = INITIAL_VELOCITY;
    pm->buffMotion.acceleration = INITIAL_ACCELERATION;
    pm->buffMotion.deceleration = INITIAL_DECELERATION;
    pm->buffMotion.profile_mode = pm->dflt_vgp_mode = VPGM_Trapezoidal;

    pm->tc_limit = TC_LIMIT_VAL_DFLT;
    pm->tc_limit_time = TC_LIMIT_TIME_VAL_DFLT;


   // pm->buff_kp = 1500;
   // pm->buff_ki = 1500;
    pm->buff_kp = 30;
    pm->buff_ki = 1;
    pm->buff_kd = 0;
    pm->buff_kvff = 0;
    pm->buff_kaff = 0;
    pm->integral_limit16 = 0x7fff;
    pm->buff_err_limit = POS_ERROR_LIMIT_VAL_DFLT;
    pm->pos_error_time = POS_ERROR_LIMIT_TIME_VAL_DFLT;

    pm->pos_loop_limit = 0x00FFFFFF;  


    pm->buff_kp_vel = INITVAL_VEL_KP;
    pm->buff_ki_vel = INITVAL_VEL_KI;
    pm->buff_kd_vel = INITVAL_VEL_KD;

    pm->stop_request = SM_ABRUPT;
    pm->auto_stop_mode = SM_NOSTOP;

    /* RZ/T2 change */
    pm->commutation_mode = CM_ENC_AND_DSM;
    pm->phase_angle = -1;
    pm->phase_offset = 0;
    pm->phase_vector = 0;

    set_position(pm, 0);
    servo_off(pm);
    update_ctrl(pm);

    /* Finite State Machines Setup */
    pm->fsm_home = HS_IDLE;
    

#if   defined(__ICCARM__)
    /* Do nothing */
#elif defined(__GNUC__)
    /* Restore data from Flash */
   // m_Restore(0, pm);
#endif

    pm->pvt_push = pm->pvt_pointsFIFO;
    pm->pvt_start_point = pm->pvt_pointsFIFO;
    pm->pvt_end_point = pm->pvt_pointsFIFO;
    pm->pvt_points = 0;

    pm->ErrSts = 0;
    pm->ErrMsk		= ERROR_MASK_DFLT;
    pm->Lvolt_Val	= LVOLT_VAL_DFLT;
    pm->Hvolt_Val	= HVOLT_VAL_DFLT;
    pm->Ovc_Val		= OVC_VAL_DFLT;
    pm->Ovs_Val		= OVS_VAL_DFLT;
    pm->WOvs_Val	= WOVS_VAL_DFLT;
    pm->WPosMax_Val	= WPOSMAX_VAL_DFLT;
    pm->WPosMin_Val	= WPOSMIN_VAL_DFLT;
    pm->WOvs_time	= 0;	/* 3sec */
    pm->WEmp_Val	= EMP_VAL_DFLT;
    pm->WInvOverTemp_Val = WINVOVERTEMP_VAL_DFLT;

    /* RZ/T2 add */
    /* control mode initialize*/
    pm->ctrl_mode = CTRM_POSITION;
    pm->cmd_dir = RDIR_CW;
    pm->cmd_vel_rpm = 0;
    pm->cmd_vel64 = 0;
    pm->cmd_trq = 0;
    pm->est_trq = 0;
    pm->mtr_ke = MTR_KE_NUM;

    /* bootstrap_charging initialize */
    pm->charge_cycle = 0;
    pm->charge_state = BS_UNCHARGED;
}

void m_EncoderType(t_console *pc, t_motor *pm) 
{
    if (pc->set != 0) 
    {
        if (pm->encoder_type != pc->arg)
        {
            if (pc->arg == ETYPE_INCREMENTAL ||            /* Absolute -> Incremental works always */
                pm->encoder_type == ETYPE_INCREMENTAL)     /* Incremental -> Absolute works always */
            {
                /* Initilaize the encoder hardware if the current selection is Incremental ...*/
                /* ... and the Absolute encoder hardware was never initialized before */  
                close_encoder(pm, pm->encoder_type);
                pm->encoder_type = pc->arg;
                setup_encoder(pm, pc->arg);
            }
            else                                            
            {
                /* Absolute -> Absolute does not work */
                pc->err = PE_INVALID_STATE;
            }
        }
    }
    else 
    {
        print_dec(pc, pm->encoder_type);
    }
}

void m_EncReadID(t_console *pc, t_motor *pm)
{
short id = 0;

    switch(pm->encoder_type)
    {
    case ETYPE_APE_FACODER:
        id = fac_enc_id(pm);
        break;
    case ETYPE_APE_AFORMAT:
#if 0 /* A-format is not supported. */
        id = a_as_enc_id(pm);
#endif
        break;
    case ETYPE_APE_ENDAT:
#if 0 /* EnDat is not supported. */
        id = endat_enc_id(pm);
#endif
        break;
    case ETYPE_APE_BISS:
#if 0 /* BiSS is not supported */
        id = bissc_enc_id(pm);
#endif
        break;
    case ETYPE_APE_HIPERFACE_DSL:
#if 0 /* HIPERFACE DSL is not supported. */
        id = hfdsl_enc_id(pm);
#endif
        break;
    }
    print_hex(pc, id);
}

void m_EncAddrEEPROM(t_console *pc, t_motor *pm)
{
    if (pc->set != 0) 
    {
        pm->eeprom_addr = pc->arg;
    }
    else 
    {
        print_dec(pc, pm->eeprom_addr);
    }
}

void m_EncBaudrate(t_console *pc, t_motor *pm)
{
    if (pc->set != 0) 
    {
        pm->enc_baudrate = pc->arg;
    }
    else 
    {
        print_dec(pc, pm->enc_baudrate);
    }
}

void m_EncStatus(t_console *pc, t_motor *pm)
{
    if (pc->set != 0) 
    {
        pc->err = PE_INVALID_ACCESS;        /* Encoder status is read-only */
    }
    else 
    {
        if (pm->enc_open)
        {
            pm->enc_open = 0;
            switch(pm->encoder_type)
            {
            case ETYPE_APE_ENDAT:
#if 0 /* EnDat is not supported. */
                endat_enc_id(pm);
#endif
                break;
            case ETYPE_APE_BISS:
#if 0 /* BiSS is not supported */
                bissc_enc_id(pm);
#endif
                break;
            case ETYPE_APE_AFORMAT:
#if 0 /* A-format is not supported. */
                a_as_enc_id(pm);
#endif
                break;
            case ETYPE_APE_FACODER:
                fac_enc_id(pm); /* The ID read function updates the encoder status as well */
                break;
            case ETYPE_APE_HIPERFACE_DSL:

#if 0 /* HIPERFACE DSL is not supported. */
                hfdsl_enc_id(pm);
#endif
                break;
            default:
                /* Indicate invalid request for the current encoder type */
                pc->err = PE_INVALID_VALUE;    /* Invalid Parameter Value */
                break;
            }
            pm->enc_open = 1;
        }
        print_hex(pc, pm->enc_status);
    }
}

void m_EncDataEEPROM(t_console *pc, t_motor *pm)
{
    if (pc->set != 0) 
    {
        if (pm->enc_open)
        {
            pm->enc_open = 0;
            switch(pm->encoder_type)
            {
            case ETYPE_APE_ENDAT:
#if 0 /* EnDat is not supported. */
                pc->err = endat_eeprom_write(pm, pc->arg);
#endif
                break;
            case ETYPE_APE_BISS:
#if 0 /* BiSS is not supported */
                pc->err = bissc_eeprom_write(pm, pc->arg);
#endif
                break;
            case ETYPE_APE_AFORMAT:
#if 0 /* A-format is not supported. */
                pc->err = a_as_eeprom_write(pm, pc->arg); 
#endif
                break;
            case ETYPE_APE_FACODER:
                pc->err = fac_eeprom_write(pm, pc->arg);
                break;
            case ETYPE_APE_HIPERFACE_DSL:
#if 0 /* HIPERFACE DSL is not supported. */
                pc->err = hfdsl_eeprom_write(pm, pc->arg);
#endif
                break;
            default:
                /* Indicate invalid request for the current encoder type */
                pc->err = PE_INVALID_VALUE;    /* Invalid Parameter Value */
                break;
            }
            pm->enc_open = 1;
        }
    }
    else 
    {
        long data;
        switch(pm->encoder_type)
        {
        case ETYPE_APE_ENDAT:
#if 0 /* EnDat is not supported. */
            pc->err = endat_eeprom_read(pm, &data);
#endif
            break;
        case ETYPE_APE_BISS:
#if 0 /* BiSS is not supported */
            pc->err = bissc_eeprom_read(pm, &data);
#endif
            break;
        case ETYPE_APE_AFORMAT:
#if 0 /* A-format is not supported. */
            pc->err = a_as_eeprom_read(pm, &data);              
#endif
            break;
        case ETYPE_APE_FACODER:
            pc->err = fac_eeprom_read(pm, &data);
            break;
        case ETYPE_APE_HIPERFACE_DSL:
#if 0 /* HIPERFACE DSL is not supported. */
            pc->err = hfdsl_eeprom_read(pm, &data);
#endif
            break;
        default:
            /* Indicate invalid request for the current encoder type */
            pc->err = PE_INVALID_VALUE;    /* Invalid Parameter Value */        
            break;
        }
        print_dec(pc, data);
    }
}

void m_GearIn(t_console *pc, t_motor *pm)
{
    if (pc->set != 0) 
    {
        if (pc->arg > 0)
        {
            pm->gear_in = (short)pc->arg;
            pm->gear_ratio = (double) pm->gear_out / (double) pm->gear_in;    
        }
        else
        {
          pc->err = PE_INVALID_VALUE;    /* Invalid Parameter Value */
        }
    }
    else 
    {
        print_dec(pc, (long)pm->gear_in);
    }
}

void m_GearOut(t_console *pc, t_motor *pm)
{
    if (pc->set != 0) 
    {
        if (pc->arg > 0)
        {
            pm->gear_out = (short)pc->arg;
            pm->gear_ratio = (double) pm->gear_out / (double) pm->gear_in;    
        }
        else
        {
            pc->err = PE_INVALID_VALUE;    /* Invalid Parameter Value */
        }
    }
    else 
    {
        print_dec(pc, (long)pm->gear_out);
    }
}

void m_AddPos(t_console *pc, t_motor *pm)
{
    if (pc->set != 0) 
    {
        if (pm->pvt_points < PVT_BUFF_SIZE)
        {
            pm->pvt_push->position = pc->arg;
            pm->pvt_pos_added = 1;    
        }
        else
        {
            pc->err = PE_BUFFER_OVF;      /* Indicate PVT Buffer overflow */
        }
    }
    else 
    {
        print_dec(pc, pm->pvt_push->position);
    }
}

void m_AddVel(t_console *pc, t_motor *pm)
{
    if (pc->set != 0) 
    {
        if (pm->pvt_points < PVT_BUFF_SIZE)
        {
            pm->pvt_push->velocity = pc->arg;
            pm->pvt_pos_added = 0;
            pm->pvt_points++;
            pm->pvt_push++;
            if (pm->pvt_push >= pm->pvt_pointsFIFO + PVT_BUFF_SIZE)
            {
                pm->pvt_push = pm->pvt_pointsFIFO;
            }
        }
        else
        {
            pc->err = PE_BUFFER_OVF;      /* Indicate PVT Buffer overflow */
        }
    }
    else 
    {
        print_dec(pc, pm->pvt_push->velocity);
    }
}

extern uint32_t led_dsp_flag;
void m_Ereset( t_console *pc, t_motor *pm)
{
    led_dsp_flag = 0;
    LED3 = 0;
    pm->ErrSts = 0;
}
void m_Emask( t_console *pc, t_motor *pm)
{
    if( pc->set != 0)
    {
        pm->ErrMsk = pc->arg;
    }
    else
    {
        print_hex2( pc, pm->ErrMsk );
    }
}
void m_Elvolt( t_console *pc, t_motor *pm)
{
    if( pc->set != 0)
    {
        pm->Lvolt_Val = pc->arg;
    }
    else
    {
        print_dec( pc, pm->Lvolt_Val );
    }
}
void m_Ehvolt( t_console *pc, t_motor *pm)
{
    if( pc->set != 0)
    {
        pm->Hvolt_Val = pc->arg;
    }
    else
    {
        print_dec( pc, pm->Hvolt_Val );
    }
}
void m_Eovc( t_console *pc, t_motor *pm)
{
    if( pc->set != 0)
    {
        pm->Ovc_Val = pc->arg;
    }
    else
    {
        print_dec( pc, pm->Ovc_Val );
    }
}
void m_Eovs( t_console *pc, t_motor *pm)
{
    if( pc->set != 0)
    {
        pm->Ovs_Val = pc->arg;
    }
    else
    {
        print_dec( pc, pm->Ovs_Val );
    }
}
void m_Ewovs( t_console *pc, t_motor *pm)
{
    if( pc->set != 0)
    {
        pm->WOvs_Val = pc->arg;
    }
    else
    {
        print_dec( pc, pm->WOvs_Val );
    }
}
void m_EwposMax( t_console *pc, t_motor *pm)
{
    if( pc->set != 0)
    {
        pm->WPosMax_Val = pc->arg;
    }
    else
    {
        print_dec( pc, pm->WPosMax_Val );
    }
}
void m_EwposMin( t_console *pc, t_motor *pm)
{
    if( pc->set != 0)
    {
        pm->WPosMin_Val = pc->arg;
    }
    else
    {
        print_dec( pc, pm->WPosMin_Val );
    }
}
void m_Eemp( t_console *pc, t_motor *pm)
{
    if( pc->set != 0)
    {
        pm->WEmp_Val = pc->arg;
    }
    else
    {
        print_dec( pc, pm->WEmp_Val );
    }
}
void m_EovTemp( t_console *pc, t_motor *pm)
{
    if( pc->set != 0)
    {
        pm->WInvOverTemp_Val = pc->arg;
    }
    else
    {
        print_dec( pc, pm->WInvOverTemp_Val );
    }
}

/* RZ/T2 add */
/******************************************************************************
* Function Name: m_CtrlMode
* Description  : Control mode setting
* Arguments    : pc : structure of communication(pointer)
*              : pm : structure of motor control(pointer) 
* Return Value : None
******************************************************************************/
void m_CtrlMode(t_console *pc, t_motor *pm)
{
    if( pc->set != 0)
    {
        pm->ctrl_mode = (short)pc->arg;
    }
    else
    {
        print_dec( pc, pm->ctrl_mode );
    }
}
/*******************************************************************************
End of function m_CtrlMode
*******************************************************************************/

/******************************************************************************
* Function Name: m_CommandDirection
* Description  : Rotation direction setting
* Arguments    : pc : structure of communication(pointer)
*              : pm : structure of motor control(pointer) 
* Return Value : None
******************************************************************************/
void m_CommandDirection(t_console *pc, t_motor *pm)
{
    if( pc->set != 0)
    {
        pm->cmd_dir = (short)pc->arg;
    }
    else
    {
        print_dec( pc, pm->cmd_dir );
    }
}
/*******************************************************************************
End of function m_CommandDirection
*******************************************************************************/

/******************************************************************************
* Function Name: m_CommandVelocity
* Description  : Speed command setting
* Arguments    : pc : structure of communication(pointer)
*              : pm : structure of motor control(pointer) 
* Return Value : None
******************************************************************************/
void m_CommandVelocity( t_console *pc, t_motor *pm)
{
long long temp = 0;

    if( pc->set != 0)
    {
        /* command direction check */
        if(pm->cmd_dir == 0)
        {   /* CW */
            pm->cmd_vel_rpm = (short)pc->arg;
        }
        else
        {   /* CCW */
            pm->cmd_vel_rpm = -(short)pc->arg;
        }
        /* unit conversion:[rpm] -> [(count/pos_loop_cycle_time) / 2^32] */
        temp = (long long)pm->cmd_vel_rpm * VEL_BASE_DIG_NUM * pm->crnt_ds;
        pm->cmd_vel64 = (((temp * pm->ec_per_rev) / CNVGAIN_RPS_TO_RPM) / CNVGAIN_SEC_TO_POS_LP_CYC);
    }
    else
    {
        print_dec( pc, pm->cmd_vel_rpm );
    }
}
/*******************************************************************************
End of function m_CommandVelocity
*******************************************************************************/

/******************************************************************************
* Function Name: m_CommandTorque
* Description  : Torque command setting
* Arguments    : pc : structure of communication(pointer)
*              : pm : structure of motor control(pointer) 
* Return Value : None
******************************************************************************/
void m_CommandTorque(t_console *pc, t_motor *pm)
{
    if( pc->set != 0)
    {
        /* command direction check */
        if(pm->cmd_dir == 0)
        {   /* CW */
            pm->cmd_trq = (short)pc->arg;
        }
        else
        {   /* CCW */
            pm->cmd_trq = -(short)pc->arg;
        }
    }
    else
    {
        print_dec( pc, pm->cmd_trq );
    }
}
/*******************************************************************************
End of function m_CommandTorque
*******************************************************************************/

/******************************************************************************
* Function Name: m_Gpio
* Description  : Send DIP SW information
* Arguments    : pc : structure of communication(pointer)
*              : pm : structure of motor control(pointer) 
* Return Value : None
******************************************************************************/
void m_Gpio(t_console *pc, t_motor *pm) 
{
    unsigned short data;

    if (pc->set != 0) 
    {
        pc->err = PE_INVALID_ACCESS;    /* The Input variable is read-only */
    }
    else 
    {
        data = 0;

        /* Get DipSw state */
        if (CFG0 == 0)
        {
            data |= 0x01;               /* CFG0:ON */
        }
        if (CFG1 == 0)
        {
            data |= 0x02;               /* CFG1:ON */
        }
        if (CFG2 == 0)
        {
            data |= 0x04;               /* CFG2:ON */
        }
        if (CFG3 == 0)
        {
            data |= 0x08;               /* CFG3:ON */
        }
        if (CFG4 == 0)
        {
            data |= 0x10;               /* CFG4:ON */
        }
        if (CFG5 == 0)
        {
            data |= 0x20;               /* CFG5:ON */
        }
        if (CFG6 == 0)
        {
            data |= 0x40;               /* CFG6:ON */
        }
        if (CFG7 == 0)
        {
            data |= 0x80;               /* CFG7:ON */
        }
        print_hex(pc, data);
    }
}
/*******************************************************************************
End of function m_Gpio
*******************************************************************************/

/******************************************************************************
* Function Name: ascii_hex_sub
* Description  : Convert ASCII code to hexadecimal
* Arguments    : arg : ASCII code (pointer)
* Return Value : Hexadecimal
******************************************************************************/
static unsigned char ascii_hex_sub( unsigned char arg)
{
    unsigned char result;
    if(arg >= 0x61)
    {
    	result = arg - 0x57;
    }
    else if(arg >= 0x41)
    {
    	result = arg - 0x37;
    }
    else
    {
    	result = arg - 0x30;
    }
    return result;
}
/*******************************************************************************
End of function ascii_hex_sub
*******************************************************************************/

/******************************************************************************
* Function Name: short_pvt_ascii_hex
* Description  : Convert ASCII code to hexadecimal for PVT
* Arguments    : * buf : Received instruction data(pointer)
* Return Value : Hexadecimal(short size)
******************************************************************************/
static short short_pvt_ascii_hex (unsigned char * buf)
{
    unsigned char *workbuf;
    short result;

    workbuf = buf;

    result = ascii_hex_sub( *workbuf++ ) << 4;
    result += ascii_hex_sub( *workbuf++ );
    
    return result;

}
/*******************************************************************************
End of function short_pvt_ascii_hex
*******************************************************************************/

/******************************************************************************
* Function Name: long_pvt_ascii_hex
* Description  : Convert ASCII code to hexadecimal for PVT(long size)
* Arguments    : * buf : Received instruction data(pointer)
* Return Value : Hexadecimal(long size)
******************************************************************************/
static long long_pvt_ascii_hex (unsigned char * buf)
{
    unsigned char *workbuf;
    long result;

    workbuf = buf;

    result = ascii_hex_sub( *workbuf++ ) << 28;
    result += ascii_hex_sub( *workbuf++ ) << 24;
    result += ascii_hex_sub( *workbuf++ ) << 20;
    result += ascii_hex_sub( *workbuf++ ) << 16;
    result += ascii_hex_sub( *workbuf++ ) << 12;
    result += ascii_hex_sub( *workbuf++ ) << 8;
    result += ascii_hex_sub( *workbuf++ ) << 4;
    result += ascii_hex_sub( *workbuf );
    
    return result;

}
/*******************************************************************************
End of function long_pvt_ascii_hex
*******************************************************************************/

/******************************************************************************
* Function Name: m_InitPvt
* Description  : IPVT command support
* Arguments    : pc : structure of communication(pointer)
*			   : pm : structure of motor control(pointer) 
* Return Value : None
******************************************************************************/
void m_InitPvt(t_console *pc, t_motor *pm) 
{
    unsigned char * pbuf;

    if (pc->cmd_req != PTR_ASCII)
    {
    	return;  /* Not Support Because it's implemented elsewhere */
    }

    /* Make sure the controller is not running PVT stream */
    if (pm->vpg_state != VPG_MotionCompleted)
    {
        pc->err  = PE_INVALID_STATE;
    }
    else
    {
        // pc->rx_buf = "IPVT xxyy" xx=watermark, yy=period
        pbuf = pc->rx_buf + 5;
        if (*pbuf == 0)
        {
            pc->err = PE_INVALID_VALUE;
        }
        else
        {
            pm->pvt_points = 0;
            pm->pvt_push = &pm->pvt_pointsFIFO[0];
            pm->pvt_watermark = short_pvt_ascii_hex( pbuf );
            pbuf += 2;                                      /* Next short data for ascii */
            pm->pvt_period = short_pvt_ascii_hex( pbuf );
        }
    }
}
/*******************************************************************************
End of function m_InitPvt
*******************************************************************************/

/******************************************************************************
* Function Name: m_SetPvt
* Description  : SPVT command support
* Arguments    : pc : structure of communication(pointer)
*			   : pm : structure of motor control(pointer) 
* Return Value : None
******************************************************************************/
void m_SetPvt(t_console *pc, t_motor *pm) 
{
    long pvt_buf[PVT_BUFF_SIZE];
    short i,j;
    short points;
    long *pl;
    
    if (pc->cmd_req != PTR_ASCII)
    {
    	return;              /* Not Support! Because it's implemented elsewhere */
	}

    // rx_buf = "SPVT 1234567887654321..."
    j = 5;
    for ( i = 0 ; i < PVT_BUFF_SIZE ; i++)
    {
        if ( pc->rx_buf[j] == '\0' )
        {
            break;
        }
        pvt_buf[i] = long_pvt_ascii_hex( &pc->rx_buf[j] );
        j += 8;                                        /* ascii to hex long size */
    }

    if ( i == 0 )
    {
        pc->err = PE_INVALID_PARAM;
    }
    else
    {
        points = i / 2 - 1;                            /* a point have 2 parameter */
        pl = &pvt_buf[0];

        if (pm->pvt_points + points >= PVT_BUFF_SIZE)
        {
            pc->err = PE_BUFFER_OVF;
        }
        else
        {
            while (points -- >= 0)
            {
                pm->pvt_push->position = *pl++;
                pm->pvt_push->velocity = *pl++;
                pm->pvt_points++;
                pm->pvt_push++;
                if (pm->pvt_push >= &pm->pvt_pointsFIFO[PVT_BUFF_SIZE])
                {
                    pm->pvt_push = &pm->pvt_pointsFIFO[0];
                }
            }    
            if (pm->pvt_points >= pm->pvt_watermark)
            {
                pm->act_state &= ~ACT_PVTWatermark;
            }
        }
    }
}
/*******************************************************************************
End of function m_SetPvt
*******************************************************************************/

/******************************************************************************
* Function Name: m_ReadValue
* Description  : RVAL command support
* Arguments    : pc : structure of communication(pointer)
*			   : pm : structure of motor control(pointer) 
* Return Value : None
******************************************************************************/
void m_ReadValue(t_console *pc, t_motor *pm) 
{
  void* readptr;
  float fval;
  char *pchar;
  long lval;
    
    if ( mDecodePtrTbl[pc->arg].size == 0 || (pc->arg) > 31)
    {
        pc->err = PE_INVALID_PARAM;
        return;
    }
    else
    {
        switch(pm->motor_idx)
        {
            case 0:
                readptr = mDecodePtrTbl[pc->arg].ptr1;
                break;
            case 1:
                readptr = mDecodePtrTbl[pc->arg].ptr2;
                break;
            case 2:
                readptr = mDecodePtrTbl[pc->arg].ptr3;
                break;
            case 3:
                readptr = mDecodePtrTbl[pc->arg].ptr4;
                break;
            case 4:
                readptr = mDecodePtrTbl[pc->arg].ptr5;
                break;
            case 5:
                readptr = mDecodePtrTbl[pc->arg].ptr6;
                break;
            case 6:
                readptr = mDecodePtrTbl[pc->arg].ptr7;
                break;
            case 7:
                readptr = mDecodePtrTbl[pc->arg].ptr8;
                break;
            case 8:
                readptr = mDecodePtrTbl[pc->arg].ptr9;
                break;
            default:
                break;
        }
    }

    if( (pc->arg) == 31 )                     /* for float (angle_rad) */ 
    {
        // convert float to long
        fval = *((float*)readptr);
        pchar = (char*)&fval;
        *( (char*)&lval + 0) = *(pchar + 0);
        *( (char*)&lval + 1) = *(pchar + 1);
        *( (char*)&lval + 2) = *(pchar + 2);
        *( (char*)&lval + 3) = *(pchar + 3);
        print_hex2( pc, lval);
    }
    else
    {
        switch( mDecodePtrTbl[pc->arg].size )
        {
        case 2:
            pc->data_type = PC_WORD;
            print_dec(pc,*(short*)readptr);
            break;
        case 4:
            pc->data_type = PC_LONG;
            print_dec(pc,*(long*)readptr);
            break;
        case 8:
            pc->data_type = PC_LONGLONG;
            print_dec2(pc, *(long long*)readptr);
            break;
        default:
            pc->err = PE_INVALID_PARAM;
            break;
        }
    }
}
/*******************************************************************************
End of function m_ReadValue

*******************************************************************************/

/******************************************************************************
* Function Name: motor_param_qflash_w
* Description  : Write Motor Parameter to QSPI
* Arguments    : pm : structure of motor control(pointer)
*			   : Restoring size
* Return Value : int
******************************************************************************/
static int motor_param_qflash_w(t_motor *pm, int bsize)
{
    fsp_err_t err = FSP_SUCCESS;

    DI();
    asm("isb");

    /* Sector Erase */
    /*---------- Sector Erase ----------*/
    err = R_XSPI_OSPI_Erase(&g_ospi0_ctrl, (uint8_t *)(OSPI_DEVICE_START_ADDRESS + pm->flash_pars_offs), 0x10000);
    if(err != FSP_SUCCESS)
    {
        return (int)err;
    }

    /* Wait for status register to update. */
    spi_flash_status_t status_erase;
    do
    {
         (void) R_XSPI_OSPI_StatusGet(&g_ospi0_ctrl, &status_erase);
    } while (true == status_erase.write_in_progress);

    if(0u == SW12_1)
    {
        return FSP_ERR_WRITE_FAILED;
    }

    uint32_t * p_word_aligned_dest = (uint32_t *) (OSPI_DEVICE_START_ADDRESS + pm->flash_pars_offs);
    uint32_t * p_word_aligned_src  = (uint32_t *) &pm->pars;
    for (uint32_t i = 0; i < bsize / 4U; i++)
    {
        err= R_XSPI_OSPI_Write (&g_ospi0_ctrl, (uint8_t const*)p_word_aligned_src, (uint8_t*)p_word_aligned_dest, 4);
        if(err != FSP_SUCCESS)
        {
            return (int)err;
        }

        /* Wait for status register to update. */
        spi_flash_status_t status_write;
        do
        {
            (void) R_XSPI_OSPI_StatusGet(&g_ospi0_ctrl, &status_write);
        } while (true == status_write.write_in_progress);
        p_word_aligned_dest++;
        p_word_aligned_src++;
    }

    EI();
    asm("isb");

    return (int)err;

}
/*******************************************************************************
End of function motor_param_qflash_w
*******************************************************************************/
