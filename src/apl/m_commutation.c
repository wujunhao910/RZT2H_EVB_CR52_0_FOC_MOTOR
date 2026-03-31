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
* File Name    : m_commutation.c
* Version      : 1.0
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Source file of Commutation.
*******************************************************************************/

#include <math.h>

#include "m_common.h"

/* Sinusoidal Modulation */
void commutate_sin(float angle_rad, float *p_u, float *p_v, float *p_w) 
{
    *p_u = (short)(cosf(angle_rad)) * 0.5;
    *p_v = (short)(cosf(angle_rad + (MTR_TWOPI / 3))) * 0.5;
    //*p_w = (short)(cosf(pm->angle_rad - (MTR_TWOPI / 3))) * 0.5; 
    *p_w = -(*p_u + *p_v);
}

/* Space Vector Modulation 
*
*  Input parameters:
*       alpha, beta - the flux angle vector components [-1..+1]
*  
*   Output result:
*       pm->out_u, pm->out_v, pm->out_w - phase voltages [-0.5 .. +0.5]
*/
void commutate_svm(t_motor *pm, float alpha, float beta) 
{
    float _x, _y, _z;
    float _u, _v, _w;
    
    _x = beta;
    _y = (beta + alpha * MTR_SQRT_3) * 0.5;
    _z = (beta - alpha * MTR_SQRT_3) * 0.5;

    /* Determine the sector */
    if (_y < 0.0)
    {
        if (_z < 0.0)
        {
            // Sector V
            _u = (1 + _y - _z) * 0.5;
            _v = _u + _z;
            _w = _u - _y;
        }
        else if (_x <= 0.0)
        {
            // Sector IV
            _u = (1 + _x - _z) * 0.5;
            _v = _u + _z;
            _w = _v - _x;
        }
        else
        {
            // Sector III
            _u = (1 - _x + _y) * 0.5;
            _w = _u - _y;
            _v = _w + _x;
        }
    }
    else
    {
        if (_z >= 0.0)
        {
            // Sector II
            _u = (1 + _y - _z) * 0.5;
            _v = _u + _z;
            _w = _u - _y;
        }
        else if (_x <= 0.0)
        {
            // Sector VI
            _u = (1 - _x + _y) * 0.5;
            _w = _u - _y;
            _v = _w + _x;
        }
        else
        {
            // Sector I
            _u = (1 + _x - _z) * 0.5;
            _v = _u + _z;
            _w = _v - _x;
        }
    }
    
    /* Shift and Scale the result range from 0 .. 1 to -0.5 .. 0.5*/
    pm->out_u = (_u - 0.5);
    pm->out_v = (_v - 0.5);
    pm->out_w = (_w - 0.5);
}

#define PI_LIMIT (50000)

/* Field-Oriented Control + Space Vector Modulation 
*
*  Input: 
*       pm->p_iu - u phase current sample (+/- 2048)
*       pm->p_iv - v phase current sample (+/- 2048)
*       pm->angle_sin - sin of rotor angle
*       pm->angle_cos - cos of rotor angle
*       pm->output_d - desired D current (usually = 0)
*       pm->output_q - desired Q current (torque setpoint)
*       pm->foc_kp - proportional coefficient (used for D and Q PI regulators)
*       pm->foc_ki - integral coefficient (used for D and Q PI regulators)
*
*  Output: 
*       pm->foc_id, pm->foc_iq - direct and quadrature currents
*       pm->foc_id_err, pm->foc_iq_err - direct and quadrature current errors
*       pm->foc_id_err_int, pm->foc_iq_err_int - direct and quadrature current errors integrals
*       pm->foc_vd, pm->foc_vq - direct and quadrature flux values
*       pm->foc_alpha, pm->foc_beta - flux vector values
*/
void commutate_foc(t_motor *pm) 
{
    float alpha, beta;
    long vd, vq;

    long work_id_derivative;
    long work_iq_derivative;

    /* Clark Transformation: Calculate alpha and beta angles from the measured current */
    alpha = (float)(*pm->p_iu);
    beta = (float)(*pm->p_iu + *pm->p_iv + *pm->p_iv) * MTR_1_SQRT_3;    /* 1/SQUAREROOT(3) */

    /* Park Transformation: Calculate ID and IQ */
    pm->foc_id = (long)(alpha*pm->angle_cos + beta*pm->angle_sin);
    pm->foc_iq = (long)(beta*pm->angle_cos - alpha*pm->angle_sin);

    pm->foc_id_err_old = pm->foc_id_err;
    pm->foc_iq_err_old = pm->foc_iq_err;
    
    /* Calculate IQ and ID error */
    /* RZ/T2 */
    pm->foc_id_err = (long)pm->output_d - pm->foc_id;
    pm->foc_iq_err = (long)pm->output_q - pm->foc_iq;

    work_id_derivative = pm->foc_id_err - pm->foc_id_err_old;
    work_iq_derivative = pm->foc_iq_err - pm->foc_iq_err_old;
    
    /* Calculate IQ and ID integral error */
    pm->foc_id_err_int += pm->foc_id_err;
    pm->foc_iq_err_int += pm->foc_iq_err;
      
    /* Limit IQ and ID integral error */
    if (pm->foc_id_err_int > PI_LIMIT)
    {
        pm->foc_id_err_int = PI_LIMIT;
    }
    else if (pm->foc_id_err_int < -PI_LIMIT)
    {
        pm->foc_id_err_int = -PI_LIMIT;
    }
    else
    {
        /* Do Nothing */
    }

    if (pm->foc_iq_err_int > PI_LIMIT)
    {
        pm->foc_iq_err_int = PI_LIMIT;
    }
    else if (pm->foc_iq_err_int < -PI_LIMIT)
    {
        pm->foc_iq_err_int = -PI_LIMIT;
    }
    else
    {
        /* Do Nothing */
    }
    
    /* Calculate PI regulator output - Q and D values */
    vd = pm->foc_id_err * pm->foc_kp + pm->foc_id_err_int * pm->foc_ki;
    vq = pm->foc_iq_err * pm->foc_kp + pm->foc_iq_err_int * pm->foc_ki;

    /* Judgment to add a D derivative term *//* RZ/T2 change */
    if(((pm->ctrl_mode != CTRM_VELOCITY)&&(pm->ctrl_mode != CTRM_TORQUE)) || (pm->output_d == pm->output_d_old))
    {
        vd += (work_id_derivative * (long)pm->foc_kd) >> 4;
    }
    else
    {
        /* Do nothing */
    }
    /* Judgment to add a Q derivative term */
    if(((pm->ctrl_mode != CTRM_VELOCITY)&&(pm->ctrl_mode != CTRM_TORQUE)) || (pm->output_q == pm->output_q_old))
    {
        vq += (work_iq_derivative * (long)pm->foc_kd) >> 4;
    }
    else
    {
        /* Do nothing */
    }
    /* Set the previous value */
    pm->output_d_old = pm->output_d;
    pm->output_q_old = pm->output_q;

    /* Limit output */
    if (vd > 32767)
    {
        vd = 32767;
    }
    else if (vd < -32767)
    {
        vd = -32767;
    }
    else
    {
        /* Do Nothing */
    }

    if (vq > 32767)
    {
        vq = 32767;
    }
    else if (vq < -32767)
    {
        vq = -32767;
    }
    else
    {
        /* Do Nothing */
    }

    pm->foc_vq = vq;
    pm->foc_vd = vd;
    
    /* Inverse Park Transformation */
    pm->foc_alpha = pm->foc_vd * pm->angle_cos - pm->foc_vq * pm->angle_sin;
    pm->foc_beta  = pm->foc_vq * pm->angle_cos + pm->foc_vd * pm->angle_sin;
    
    /* estimate torque *//* RZ/T2 add */
    pm->est_trq = estimate_torque( pm );
}

static float vect_u[] = { MTR_2_3,   MTR_2_3, -MTR_1_3, -MTR_2_3, -MTR_1_3,  MTR_1_3};
static float vect_v[] = {-MTR_1_3,  -MTR_2_3,  MTR_2_3,  MTR_1_3, -MTR_1_3, -MTR_2_3};
static float vect_w[] = {-MTR_1_3,   0.0f   , -MTR_1_3,  MTR_1_3,  MTR_2_3,  MTR_1_3};

/* Trapezoidal commutation using one of six possible sectors */
void commutate_set(t_motor *pm)
{
    
    if (pm->phase_vector >= 0 && pm->phase_vector <= 5)
    {
        pm->out_u = vect_u[pm->phase_vector] * 0.5 * (float)pm->output_q * (1/32768.0);
        pm->out_v = vect_v[pm->phase_vector] * 0.5 * (float)pm->output_q * (1/32768.0);
        pm->out_w = vect_w[pm->phase_vector] * 0.5 * (float)pm->output_q * (1/32768.0);
    }
    else
    {
        pm->out_u = 0;
        pm->out_v = 0;
        pm->out_w = 0;
    }
}

/* Hall sensor combinations 
      
    Sector  Binary  Decimal
    0  - 60 010     2    
    60 -120 110     6
    120-180 100     4
    180-240 101     5
    240-300 001     1
    300-360 011     3
*/

static short sector[] = {
    0,      /* 0 */
    4,      /* 1 */
    0,      /* 2 */
    5,      /* 3 */
    2,      /* 4 */
    3,      /* 5 */
    1,      /* 6 */
    0,      /* 7 */
};

void commutate_hall(t_motor *pm) 
{
    int s = sector[pm->hall_state & 0x07];
#if 1
    float angle;
        s *= 60;
        angle = (s + 90) * (2.0 * M_PI / 360.0);
        pm->calc_beta = sinf(angle) * (float)pm->output_q * (1/32768.0);
        pm->calc_alpha = cosf(angle) * (float)pm->output_q * (1/32768.0);
        commutate_svm(pm, pm->calc_alpha, pm->calc_beta);
#else
        pm->phase_vector = (s + 1) % 6;
        commutate_set(pm);
#endif
}

/* RZ/T2 add */
/******************************************************************************
* Function Name: estimate_torque
* Description  : Calculate the torque estimate
* Arguments    : pm : structure of motor control(pointer) 
* Return Value : Hexadecimal(long size)
******************************************************************************/
short estimate_torque(t_motor *pm)
{
    float temp = 0.0f;
    short result = 0;

    temp = pm->foc_iq * MTR_KT_NUM1; // mA * Nm/A = 10^-3 * A * Nm/A = 10^-3 * Nm = mNm

    /* Limit to +/-32767 */
    if(temp >= LIM_INT16_MAX)
    {
        temp = LIM_INT16_MAX;
    }
    else if(temp <= LIM_INT16_MIN)
    {
        temp = LIM_INT16_MIN;
    }
    else
    {
        /* Do nothing */
    }

    result = (short)temp;

    return result;
}
/*******************************************************************************
End of function estimate_torque
*******************************************************************************/
