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
* File Name    : m_rzt.c
* Version      : 1.0
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Source file of Current loop.
*******************************************************************************/

#include <math.h>

#include "r_cg_macrodriver.h"
#include "r_cg_scifa.h"
#include "r_dsmif.h"


#include "m_biplane.h"
#include "m_common.h"
#include "bsp_api.h"

#include "r_fac_rzt2_dat.h"
#include "r_fac_rzt2_if.h"


void m_sci5_rxi_interrupt(void);
void m_sci5_txi_interrupt(void);
void m_sci5_eri_interrupt(void);
void m_sci5_tei_interrupt(void);

void spibsc_init(void);
int32_t main_endat(const int32_t idx, int32_t br);
void endat_close(const int32_t idx);

int32_t main_biss(const int32_t idx, int32_t br);
void biss_close(const int32_t idx);

int32_t main_a_as(const int32_t idx, int32_t br);
void a_as_close(const int32_t idx);

int32_t main_fac(const int32_t idx, int32_t br);
void fac_close(const int32_t idx);

extern int32_t main_hfdsl(const int32_t idx, int32_t br);
extern int32_t hfdsl_close(const int32_t idx);

static int _cntr = 0;
short   g_counter = 0;
short   g_suspend = 0;

t_console con2;
t_motor g_st_m[MOTOR_NUM];
t_motor m1,m2;
long _ErrDspTimer  = 0;
uint32_t led_dsp_flag = 0;

static void setup_scif(t_console *pc, R_SCI0_Type volatile *sci0)
{
    pc->rx_count = 0;
    pc->tx_count = 0;
    pc->prx = pc->rx_buf;
    pc->ptx = pc->tx_buf;
    pc->cmd_req = PTR_NONE;
    pc->arg = 0;
    pc->pSCI0 = sci0;
    pc->channel = '1';
    
    pc->pkt_state = PS_IDLE;
    
    pc->pSCI0->CCR0_b.RE = 1U;
    pc->pSCI0->CCR0_b.RIE = 1U;
}

/******************************************************************************
* Function Name: setup_dsm
* Description  : DSMIF module initial settings
* Arguments    : none
* Return Value : none
******************************************************************************/
//static void setup_dsm()
void setup_dsm()
{

    unsigned long dummy;

    /* Cancel DSMIF stop state in LPC */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    dummy=0u;
    R_BSP_MODULE_START(FSP_IP_DSMIF, dummy);
    dummy = BSP_MSTP_REG_FSP_IP_DSMIF(dummy);
    dummy=1u;
    R_BSP_MODULE_START(FSP_IP_DSMIF, dummy);
    dummy = BSP_MSTP_REG_FSP_IP_DSMIF(dummy);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    static const st_dsmif_ctrl_t s_param={
        .int_en    = 0u,                       /* Interrupt Control Register setting */
/*      .int_en    = DSMIF_INT_EN_OVC_LO|DSMIF_INT_EN_OVC_HI|DSMIF_INT_EN_SC, */ /* Interrupt Control Register setting */
        .mclk_mode = DSMIF_MCLK_SLAVE,         /* AD conversion clock master/slave mode */
        .mdat_edge = DSMIF_MDAT_EDGE_NEG,      /* Capture MDATn at the nega/pos edge of MCLKn */
        .ckdiv     = 0u,                       /* AD conversion clock division ratio */
        .captrigA  = DSMIF_CAP_TRIG0,          /* Current capture trigger A selection bit */
        .captrigB  = DSMIF_CAP_NTRIG,          /* Current capture trigger B selection bit */
        .ditsel    = DSMIF_SEL_INIT_TRG0,      /* Current measurement filter Initialization trigger selection bit for frequency division counter for decimation. */
        .dedge     = DSMIF_INIT_EDGE_POS,      /* Current measurement filter Initialization trigger for division counter for decimation Edge selection bit. */
    };
    
    static const st_dsmif_ovcsc_ctrl_t s_ovcsc_param={
        .ovc_thres.low  = 2048,                /* -300mV=32768-(300mV*32768/320mV) */
        .ovc_thres.high = 63487,               /* +300mV=32768+(300mV*32767/320mV)=63487.0635 */
        .sc_thres.low   = 1000u,               /* count */
        .sc_thres.high  = 1000u,               /* count */
        .filter_setting = DSMIF_FILTER_SET_4,    
    };
    
    R_DSMIF0->CH[0].DSCSTRTR_b.STRTRG = 1; // DSCSTRTR Start Trigger Register
    R_DSMIF1->CH[0].DSCSTRTR_b.STRTRG = 1; // DSCSTRTR Start Trigger Register
    R_DSMIF2->CH[0].DSCSTRTR_b.STRTRG = 1; // DSCSTRTR Start Trigger Register
    R_DSMIF3->CH[0].DSCSTRTR_b.STRTRG = 1; // DSCSTRTR Start Trigger Register
    R_DSMIF4->CH[0].DSCSTRTR_b.STRTRG = 1; // DSCSTRTR Start Trigger Register
    R_DSMIF5->CH[0].DSCSTRTR_b.STRTRG = 1; // DSCSTRTR Start Trigger Register
    R_DSMIF6->CH[0].DSCSTRTR_b.STRTRG = 1; // DSCSTRTR Start Trigger Register
    R_DSMIF7->CH[0].DSCSTRTR_b.STRTRG = 1; // DSCSTRTR Start Trigger Register
    R_DSMIF8->CH[0].DSCSTRTR_b.STRTRG = 1; // DSCSTRTR Start Trigger Register
    R_DSMIF9->CH[0].DSCSTRTR_b.STRTRG = 1; // DSCSTRTR Start Trigger Register

    /* Initialize error detection */
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT0, DSMIF_CH0, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT0, DSMIF_CH1, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT0, DSMIF_CH2, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT1, DSMIF_CH0, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT1, DSMIF_CH1, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT1, DSMIF_CH2, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT2, DSMIF_CH0, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT2, DSMIF_CH1, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT2, DSMIF_CH2, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT3, DSMIF_CH0, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT3, DSMIF_CH1, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT3, DSMIF_CH2, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT4, DSMIF_CH0, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT4, DSMIF_CH1, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT4, DSMIF_CH2, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT5, DSMIF_CH0, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT5, DSMIF_CH1, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT5, DSMIF_CH2, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT6, DSMIF_CH0, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT6, DSMIF_CH1, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT6, DSMIF_CH2, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT7, DSMIF_CH0, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT7, DSMIF_CH1, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT7, DSMIF_CH2, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT8, DSMIF_CH0, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT8, DSMIF_CH1, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT8, DSMIF_CH2, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);
    R_DSMIF_OvcSCCtrl(DSMIF_UNIT9, DSMIF_CH0, (st_dsmif_ovcsc_ctrl_t*)&s_ovcsc_param);

    R_DSMIF_SetFilter(DSMIF_UNIT0, DSMIF_CH0, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT0, DSMIF_CH1, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT0, DSMIF_CH2, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT1, DSMIF_CH0, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT1, DSMIF_CH1, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT1, DSMIF_CH2, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT2, DSMIF_CH0, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT2, DSMIF_CH1, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT2, DSMIF_CH2, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT3, DSMIF_CH0, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT3, DSMIF_CH1, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT3, DSMIF_CH2, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT4, DSMIF_CH0, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT4, DSMIF_CH1, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT4, DSMIF_CH2, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT5, DSMIF_CH0, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT5, DSMIF_CH1, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT5, DSMIF_CH2, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT6, DSMIF_CH0, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT6, DSMIF_CH1, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT6, DSMIF_CH2, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT7, DSMIF_CH0, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT7, DSMIF_CH1, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT7, DSMIF_CH2, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT8, DSMIF_CH0, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT8, DSMIF_CH1, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT8, DSMIF_CH2, DSMIF_FILTER_SET_5);
    R_DSMIF_SetFilter(DSMIF_UNIT9, DSMIF_CH0, DSMIF_FILTER_SET_5);

    /* Initialize the DSMIF */
    R_DSMIF_Ctrl(DSMIF_UNIT0, DSMIF_CH0, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT0, DSMIF_CH1, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT0, DSMIF_CH2, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT1, DSMIF_CH0, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT1, DSMIF_CH1, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT1, DSMIF_CH2, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT2, DSMIF_CH0, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT2, DSMIF_CH1, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT2, DSMIF_CH2, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT3, DSMIF_CH0, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT3, DSMIF_CH1, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT3, DSMIF_CH2, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT4, DSMIF_CH0, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT4, DSMIF_CH1, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT4, DSMIF_CH2, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT5, DSMIF_CH0, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT5, DSMIF_CH1, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT5, DSMIF_CH2, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT6, DSMIF_CH0, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT6, DSMIF_CH1, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT6, DSMIF_CH2, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT7, DSMIF_CH0, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT7, DSMIF_CH1, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT7, DSMIF_CH2, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT8, DSMIF_CH0, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT8, DSMIF_CH1, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT8, DSMIF_CH2, (st_dsmif_ctrl_t*)&s_param);
    R_DSMIF_Ctrl(DSMIF_UNIT9, DSMIF_CH0, (st_dsmif_ctrl_t*)&s_param);

    /* Start DSM filter */
    R_DSMIF_Start(DSMIF_UNIT0, DSMIF_START_CH0 | DSMIF_START_CH1 | DSMIF_START_CH2);
    R_DSMIF_Start(DSMIF_UNIT1, DSMIF_START_CH0 | DSMIF_START_CH1 | DSMIF_START_CH2);
    R_DSMIF_Start(DSMIF_UNIT2, DSMIF_START_CH0 | DSMIF_START_CH1 | DSMIF_START_CH2);
    R_DSMIF_Start(DSMIF_UNIT3, DSMIF_START_CH0 | DSMIF_START_CH1 | DSMIF_START_CH2);
    R_DSMIF_Start(DSMIF_UNIT4, DSMIF_START_CH0 | DSMIF_START_CH1 | DSMIF_START_CH2);
    R_DSMIF_Start(DSMIF_UNIT5, DSMIF_START_CH0 | DSMIF_START_CH1 | DSMIF_START_CH2);
    R_DSMIF_Start(DSMIF_UNIT6, DSMIF_START_CH0 | DSMIF_START_CH1 | DSMIF_START_CH2);
    R_DSMIF_Start(DSMIF_UNIT7, DSMIF_START_CH0 | DSMIF_START_CH1 | DSMIF_START_CH2);
    R_DSMIF_Start(DSMIF_UNIT8, DSMIF_START_CH0 | DSMIF_START_CH1 | DSMIF_START_CH2);
    R_DSMIF_Start(DSMIF_UNIT9, DSMIF_START_CH0);

    /* Validate error detection */
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT0, DSMIF_CH0);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT0, DSMIF_CH1);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT0, DSMIF_CH2);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT1, DSMIF_CH0);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT1, DSMIF_CH1);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT1, DSMIF_CH2);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT2, DSMIF_CH0);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT2, DSMIF_CH1);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT2, DSMIF_CH2);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT3, DSMIF_CH0);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT3, DSMIF_CH1);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT3, DSMIF_CH2);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT4, DSMIF_CH0);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT4, DSMIF_CH1);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT4, DSMIF_CH2);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT5, DSMIF_CH0);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT5, DSMIF_CH1);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT5, DSMIF_CH2);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT6, DSMIF_CH0);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT6, DSMIF_CH1);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT6, DSMIF_CH2);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT7, DSMIF_CH0);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT7, DSMIF_CH1);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT7, DSMIF_CH2);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT8, DSMIF_CH0);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT8, DSMIF_CH1);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT8, DSMIF_CH2);
    R_DSMIF_OvcSCCtrlValid(DSMIF_UNIT9, DSMIF_CH0);

}
/*******************************************************************************
End of function setup_dsm
*******************************************************************************/

void m_startup()
{
    /* RZ/T2 add */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_GPIO);

    for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
    {
        g_st_m[idx].motor_idx = idx;
    }

    g_st_m[0].regPhaseU = (unsigned int *)&(R_GPT00_0->GTCCR[2]);
    g_st_m[0].regPhaseV = (unsigned int *)&(R_GPT00_1->GTCCR[2]);
    g_st_m[0].regPhaseW = (unsigned int *)&(R_GPT00_2->GTCCR[2]);
    g_st_m[0].regPWMPeriod = (unsigned int *)&(R_GPT00_0->GTPR);
    g_st_m[1].regPhaseU = (unsigned int *)&(R_GPT01_0->GTCCR[2]);
    g_st_m[1].regPhaseV = (unsigned int *)&(R_GPT01_1->GTCCR[2]);
    g_st_m[1].regPhaseW = (unsigned int *)&(R_GPT01_2->GTCCR[2]);
    g_st_m[1].regPWMPeriod = (unsigned int *)&(R_GPT01_0->GTPR);
    g_st_m[2].regPhaseU = (unsigned int *)&(R_GPT02_0->GTCCR[2]);
    g_st_m[2].regPhaseV = (unsigned int *)&(R_GPT02_1->GTCCR[2]);
    g_st_m[2].regPhaseW = (unsigned int *)&(R_GPT02_2->GTCCR[2]);
    g_st_m[2].regPWMPeriod = (unsigned int *)&(R_GPT02_0->GTPR);
    g_st_m[3].regPhaseU = (unsigned int *)&(R_GPT03_0->GTCCR[2]);
    g_st_m[3].regPhaseV = (unsigned int *)&(R_GPT03_1->GTCCR[2]);
    g_st_m[3].regPhaseW = (unsigned int *)&(R_GPT03_2->GTCCR[2]);
    g_st_m[3].regPWMPeriod = (unsigned int *)&(R_GPT03_0->GTPR);
    g_st_m[4].regPhaseU = (unsigned int *)&(R_GPT04_0->GTCCR[2]);
    g_st_m[4].regPhaseV = (unsigned int *)&(R_GPT04_1->GTCCR[2]);
    g_st_m[4].regPhaseW = (unsigned int *)&(R_GPT04_2->GTCCR[2]);
    g_st_m[4].regPWMPeriod = (unsigned int *)&(R_GPT04_0->GTPR);
    g_st_m[5].regPhaseU = (unsigned int *)&(R_GPT05_0->GTCCR[2]);
    g_st_m[5].regPhaseV = (unsigned int *)&(R_GPT05_1->GTCCR[2]);
    g_st_m[5].regPhaseW = (unsigned int *)&(R_GPT05_2->GTCCR[2]);
    g_st_m[5].regPWMPeriod = (unsigned int *)&(R_GPT05_0->GTPR);
    g_st_m[6].regPhaseU = (unsigned int *)&(R_GPT06_0->GTCCR[2]);
    g_st_m[6].regPhaseV = (unsigned int *)&(R_GPT06_1->GTCCR[2]);
    g_st_m[6].regPhaseW = (unsigned int *)&(R_GPT06_2->GTCCR[2]);
    g_st_m[6].regPWMPeriod = (unsigned int *)&(R_GPT06_0->GTPR);
    g_st_m[7].regPhaseU = (unsigned int *)&(R_GPT07_0->GTCCR[2]);
    g_st_m[7].regPhaseV = (unsigned int *)&(R_GPT07_1->GTCCR[2]);
    g_st_m[7].regPhaseW = (unsigned int *)&(R_GPT07_2->GTCCR[2]);
    g_st_m[7].regPWMPeriod = (unsigned int *)&(R_GPT07_0->GTPR);
    g_st_m[8].regPhaseU = (unsigned int *)&(R_GPT08_0->GTCCR[2]);
    g_st_m[8].regPhaseV = (unsigned int *)&(R_GPT08_1->GTCCR[2]);
    g_st_m[8].regPhaseW = (unsigned int *)&(R_GPT08_2->GTCCR[2]);
    g_st_m[8].regPWMPeriod = (unsigned int *)&(R_GPT08_0->GTPR);

    for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
    {
        /* Initialize Motor Control Data Structure - Register references */
        g_st_m[idx].regPosCounter = (unsigned short *)&(R_MTU1->TCNT);
        g_st_m[idx].regPosCapture = (unsigned short *)&(R_MTU1->TGRA);
        g_st_m[idx].regTimerStatus = (unsigned char *)&(R_MTU1->TSR);
    
        g_st_m[idx].flash_pars_offs = 0xA00000 + 0x10000 * g_st_m[idx].motor_idx;
        g_st_m[idx].enc_open = 0;
        g_st_m[idx].slave = &m2;
        g_st_m[idx].module_addr = 1;
        g_st_m[idx].group_addr = 0;
        g_st_m[idx].pvt_watermark = 10;
        g_st_m[idx].pvt_period = 200;

        setup_motor(&g_st_m[idx], 0);
    }

    /* Set LED indicators */
    LED1 = 1;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
    LED5 = 0;
    

    setup_scif(&con2, R_SCI5);
    R_SCI5_Start();
    //printf("uart test\n");
    /* Send wakeup character */
    con2.tx_buf[0] = 'R';
    con2.tx_count = 1;
    print_buff(&con2);

    /* Setup trace data structure */
    m_TraceSetup();

    for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
    {
        setup_encoder(&g_st_m[idx], g_st_m[idx].encoder_type);
    }

}


/* Heartbeat */
void m_heartbeat(void)
{
    _cntr++;
    if (_cntr >= 10000)
    {
        _cntr = 0;
        LED1 ^= 1;
    }
}

void ErrLedDsp(void) /* Entry 1ms interval */
{
    _ErrDspTimer++;
    if (_ErrDspTimer >= 100)
    {
        _ErrDspTimer = 0;
#if   defined(__ICCARM__)
    	__disable_interrupt();
#elif defined(__GNUC__)
		DI();
#endif
	for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
	{
	    if((g_st_m[idx].ErrSts & g_st_m[idx].ErrMsk) != 0)
	    {
	        led_dsp_flag = 1;
	    }
	}
	if(led_dsp_flag)
	{
	    LED3 ^= 1;	/* ON/OFF */
	}
#if   defined(__ICCARM__)
    	__enable_interrupt();
#elif defined(__GNUC__)
		EI();
#endif
    }
}

/* SCIF Interrupt handlers *//* RZ/T2 change */
void m_rx_interrupt(t_console *pc)
{
    uint16_t count = 0;

    /* Get the amount of receive data stored in FRSR register */
    uint16_t dummy_fdr = pc->pSCI0->FRSR_b.R;

    /* Clear receive FIFO data full flag *//* RZ/T2 add */
    if (pc->pSCI0->CSR_b.RDRF == 1U)
    {
        pc->pSCI0->CFCLR_b.RDRFC = 1U;
    }

    /* Read data from the receive FIFO data register */
    while (count < dummy_fdr)
    {
        uint8_t ch = pc->pSCI0->RDR_b.RDAT;
        count++;
        
        switch (pc->pkt_state)
        {
        case PS_IDLE:

            /* Check for 'Packet Start' character */
            if (ch == (uint8_t)0xAA)
            {
                pc->pkt_state = PS_ADDRESS;
                break;
            }
            /* Check for 'Command Terminator' */
            if (ch == 0x0Du)
            {
                *pc->prx = 0u;
                pc->pkt_state = PS_PROCESS;                
                pc->cmd_req = PTR_ASCII;
                break;
            }
            /* Store the received chanacter if the buffer is not overflowing */
            if (pc->rx_count < RX_BUF_SIZE)
            {
                *pc->prx = ch;
            }
            pc->prx++;
            pc->rx_count++;
            break;
        case PS_ADDRESS:
            /* Address byte received. */
            pc->pkt_chksum = ch;
            pc->pkt_addr = ch;
            pc->pkt_state = PS_LENGTH;                
            break;
        case PS_LENGTH:
            /* Packet length received. */
            pc->pkt_chksum += ch;
            pc->pkt_length = ch;
            pc->pkt_state = PS_CODE;                
            break;
        case PS_CODE:
            /* Packet code received. Switch state to payload receive. */
            pc->pkt_chksum += ch;
            pc->pkt_code = ch;
            pc->pkt_state = PS_PAYLOAD;                
            pc->prx = pc->rx_buf;
            pc->rx_count = 0;
            break;
        case PS_PAYLOAD:
            /* Check if complete payload is received */
            pc->rx_count++;
            if (pc->rx_count > pc->pkt_length)
            {
                /* Validate received checksum */
                if (pc->pkt_chksum == ch)
                {
                    pc->pkt_state = PS_PROCESS;
                    /* Indicate Packet processing request */
                    pc->cmd_req = PTR_PACKET;                
                    break;
                }
                /* Indicate checksum error */
                pc->tx_buf[0] = 0xffu;
                pc->tx_buf[1] = 0xffu;
                pc->tx_count = 2;
                
                pc->prx = pc->rx_buf;
                pc->rx_count = 0;
                
                pc->pkt_state = PS_IDLE;
                print_buff(pc);
                break;
            }
            /* Store the received character, move the pointer */
            pc->pkt_chksum += ch;
            *pc->prx = ch;
            pc->prx++;
            break;
        case PS_PROCESS:    /* Do nothing - ignore any incoming characters */
            break;
        } 
    }

    /* Clear receive FIFO data full flag */
    if (pc->pSCI0->CSR_b.RDRF == 1U)
    {
        pc->pSCI0->CFCLR_b.RDRFC = 1U;
        pc->pSCI0->FFCLR_b.DRC = 1U;
    }
}

void m_tx_interrupt(t_console *pc)
{
    uint16_t count = 0;

    /* Get the amount of untransmitted data stored in the FRDR register */
    uint16_t dummy_fdr = pc->pSCI0->FTSR_b.T;

    /* Write data to the transmit FIFO data register */
    while ((pc->tx_count > 0U) && (count < _SCIF_FIFO_MAX_SIZE - dummy_fdr))
    {
        pc->pSCI0->TDR_b.TDAT = *pc->ptx;
        pc->ptx++;
        pc->tx_count--;
        count++;
    }
    pc->pSCI0->CFCLR_b.TDREC = 1U;
    
    if (pc->tx_count <= 0U)
    {
        pc->pSCI0->CCR0_b.TIE = 0U;
        pc->pSCI0->CCR0_b.TEIE = 1U;
    }
}

void m_err_interrupt(t_console *pc)
{
    if (1U == pc->pSCI0->RDR_b.PER)
    {   
        pc->pSCI0->CFCLR_b.PERC = 1;
    }

    if (1U == pc->pSCI0->RDR_b.FER)
    {   
        pc->pSCI0->CFCLR_b.FERC = 1;
    }

     if (1U == pc->pSCI0->RDR_b.ORER)
    {
        pc->pSCI0->CFCLR_b.ORERC = 1;
    }
}

void m_sci5_eri_interrupt(void)
{
   m_err_interrupt(&con2);
}

void m_sci5_rxi_interrupt(void)
{
    m_rx_interrupt(&con2);
}

void m_sci5_txi_interrupt(void)
{
    m_tx_interrupt(&con2);
}

void m_sci5_tei_interrupt(void)
{
    if (1U == R_SCI5->CSR_b.TEND)
    {
//        R_SCI4->CCR0_b.TE = 0U;
        R_SCI5->CCR0_b.TIE = 0U;
        R_SCI5->CCR0_b.TEIE = 0U;
    }
    /* Clear data ready detect flag */
    if (1U == R_SCI5->RDR_b.DR)
    {
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
        R_SCI5->FFCLR_b.DRC = 1U;
    }
}

void print_buff(t_console *pc)
{
    if (pc->tx_count != 0)
    {
        pc->ptx = pc->tx_buf;
//        pc->pSCI0->CCR0_b.TE = 1U;
        pc->pSCI0->CCR0_b.TIE = 1U;

//        DI();  /* RZ/T2 add */
        pc->pSCI0->TDR_b.TDAT = *pc->ptx;
        pc->pSCI0->CFCLR_b.TDREC = 1U;
        pc->ptx++;
        pc->tx_count--;
//        EI();   /* RZ/T2 add */
    }
}


void close_encoder(t_motor *pm, short enc_type)
{
    int ch = pm->motor_idx;     /* Encoder channel index */

    if (pm->enc_open == 0)
    {
        return;
    }
    
    pm->enc_open = 0;
    switch (enc_type)
    {
    case ETYPE_APE_ENDAT:
#if 0 /* EnDat is not supported. */
        endat_close(ch);
#endif
        break;
    case ETYPE_APE_BISS:
#if 0 /* BiSS is not supported. */
        biss_close(ch);
#endif
        break;
    case ETYPE_APE_AFORMAT:
#if 0 /* A-format is not supported. */
        a_as_close(ch);
#endif
        break;
    case ETYPE_APE_FACODER:
        fac_close(ch);
        break;
    case ETYPE_APE_HIPERFACE_DSL:
#if 0 /* HIPERFACE DSL is not supported. */
        hfdsl_close(ch);
#endif
        break;
    default:
        break;
    }  
}

void setup_encoder(t_motor *pm, short enc_type)
{
    int ch = pm->motor_idx;
    if (pm->enc_open != 0)
    {
        return;
    }
    
    pm->enc_baudrate = R_FAC_2500KBPS;
    pm->enc_open = 1;
    switch (enc_type)
    {
    case ETYPE_APE_ENDAT:
#if 0 /* EnDat is not supported. */
            if (main_endat(ch, (int32_t)pm->enc_baudrate) == 0)
            {
                /* EnDat firmware always converts encoder resolution to 16 bit internally */
                pm->ec_per_rev = 1 << 16;
                set_cmt_params(pm);
                /* rotate update */
                pm->real_rot = (int16_t)((pm->real_pos.Reg32 >> 16) & 0x0000FFFF);
            }
#endif
        break;
    case ETYPE_APE_BISS:
#if 0 /* BiSS is not supported. */
            if (main_biss(ch, (int32_t)pm->enc_baudrate) == 0)
            {
                /* BiSS firmware always converts encoder resolution to 16 bit internally */
                pm->ec_per_rev = 1 << 16;
                set_cmt_params(pm);
                /* rotate update */
                pm->real_rot = (int16_t)((pm->real_pos.Reg32 >> 16) & 0x0000FFFF);
            }
#endif
        break;
    case ETYPE_APE_AFORMAT:
#if 0 /* A-format is not supported. */
            if (main_a_as(ch, (int32_t)pm->enc_baudrate) == 0)
                {
                    /* A-FORMAT Encoder has 16-bit resolution per turn */
                    pm->ec_per_rev = 1 << 16;
                    set_cmt_params(pm);
                    /* rotate update */
                    pm->real_rot = (int16_t)((pm->real_pos.Reg32 >> 16) & 0x0000FFFF);
                }
#endif
        break;
    case ETYPE_APE_FACODER:
        pm->enc_timeout = 2000;
        if (main_fac(ch, (int32_t)pm->enc_baudrate) == 0)
        {
            /* FA-CODER firmware always converts encoder resolution to 16 bit internally */
            pm->ec_per_rev = 1 << 16;
            set_cmt_params(pm);
            /* rotate update */
            pm->real_rot = (int16_t)((pm->real_pos.Reg32 >> 16) & 0x0000FFFF);
        }
        break;
    case ETYPE_APE_HIPERFACE_DSL:
#if 0 /* HIPERFACE DSL is not supported. */
            if (main_hfdsl(ch, (int32_t)pm->enc_baudrate) == 0)
            {
                /* HIPERFACE DSL firmware always converts encoder resolution to 16 bit internally */
                pm->ec_per_rev = 1 << 16;
                set_cmt_params(pm);
                /* rotate update */
                pm->real_rot = (int16_t)((pm->real_pos.Reg32 >> 16) & 0x0000FFFF);
            }
#endif
        break;
    default:
        /* Clear Data for Absolute Encoder */
        pm->real_rot = 0;
        pm->real_res = 0;
        break;
    }  
}

void set_position(t_motor *pm, long pos)
{
long delta;
int i;

    DI();
	/* Sets the actual position while preserving the position error */
	delta = pm->crnt_pos - pos;
	pm->trgtMotion.position -= delta;
	pm->buffMotion.position -= delta;
	pm->cmd_pos -= delta;
    pm->phase_origin -= delta;
    
    /* Adjust positions already in the VPG buffer */
	for (i = 0; i < VPG_BUFF_SIZE; i++)
		pm->profileFIFO[i].position -= delta;
    
	pm->crnt_pos = pos;
    if (pm->pos_inv_mode)
    {
        pos = -(pos);
    }
	if(pm->encoder_type == ETYPE_INCREMENTAL)
	{
		if (pos == 0) 
		{
			pm->pos_offset = pm->real_pos.Reg32 = *(pm->regPosCounter) = 0;
		} 
		else 
		{
			pm->pos_offset = pos - pm->real_pos.Reg32;
			delta = (long)(pm->real_pos.Reg32 & 0xffff0000);
			pm->real_pos.Reg32 -= delta;
			pm->pos_offset += delta;
		}
	}
	else
	{
		pm->pos_offset = pos - pm->real_pos.Reg32;
		delta = (long)(pm->real_pos.Reg32 & 0xffff0000);
		pm->real_rot = 0;
		pm->real_pos.Reg32 -= delta;
		pm->pos_offset += delta;
	}
    EI();
}

short capture_position(t_motor *pm)
{
    /* Check if position capture event occurred */
    if ((*pm->regTimerStatus & 1) == 0)
        return 0;

    /* Read Captured position */
    pm->captured_pos.Reg16.Low = *pm->regPosCapture;
    /* Clear position Capture Flag */
    *pm->regTimerStatus &= ~1;
    return 1;
}


static long abss (long s)
{
  return s > 0 ? s : -s;
}
void crnt_read(t_motor * pm)
{
    uint16_t get_ad_data;
  //  if(pm->motor_idx == 2)
 //  {
    switch (pm->motor_idx) {
        case 2:
            pm->adc1_raw = R_DSMIF_ReadCapDataA(1, DSMIF_CH0) >> 4;
            pm->adc2_raw = R_DSMIF_ReadCapDataA(1, DSMIF_CH1) >> 4;
            pm->adc3_raw = R_DSMIF_ReadCapDataA(1, DSMIF_CH2) >> 4;
            break;
        case 3:
            pm->adc1_raw = R_DSMIF_ReadCapDataA(3, DSMIF_CH0) >> 4;
            pm->adc2_raw = R_DSMIF_ReadCapDataA(3, DSMIF_CH1) >> 4;
            pm->adc3_raw = R_DSMIF_ReadCapDataA(3, DSMIF_CH2) >> 4;
            break;
        case 6:
            pm->adc1_raw = R_DSMIF_ReadCapDataA(4, DSMIF_CH0) >> 4;
            pm->adc2_raw = R_DSMIF_ReadCapDataA(4, DSMIF_CH1) >> 4;
            pm->adc3_raw = R_DSMIF_ReadCapDataA(4, DSMIF_CH2) >> 4;
            break;
        case 7:
            pm->adc1_raw = R_DSMIF_ReadCapDataA(5, DSMIF_CH0) >> 4;
            pm->adc2_raw = R_DSMIF_ReadCapDataA(5, DSMIF_CH1) >> 4;
            pm->adc3_raw = R_DSMIF_ReadCapDataA(5, DSMIF_CH2) >> 4;
            break;
        case 8:
            pm->adc1_raw = R_DSMIF_ReadCapDataA(6, DSMIF_CH0) >> 4;
            pm->adc2_raw = R_DSMIF_ReadCapDataA(6, DSMIF_CH1) >> 4;
            pm->adc3_raw = R_DSMIF_ReadCapDataA(6, DSMIF_CH2) >> 4;
            break;
        default:
            pm->adc1_raw = R_DSMIF_ReadCapDataA(pm->motor_idx, DSMIF_CH0) >> 4;
            pm->adc2_raw = R_DSMIF_ReadCapDataA(pm->motor_idx, DSMIF_CH1) >> 4;
            pm->adc3_raw = R_DSMIF_ReadCapDataA(pm->motor_idx, DSMIF_CH2) >> 4;
            break;
    }

  // } else {

  //      pm->adc1_raw = R_DSMIF_ReadCapDataA(pm->motor_idx, DSMIF_CH0) >> 4;
  //      pm->adc2_raw = R_DSMIF_ReadCapDataA(pm->motor_idx, DSMIF_CH1) >> 4;
  //      pm->adc3_raw = R_DSMIF_ReadCapDataA(pm->motor_idx, DSMIF_CH2) >> 4;
  // }
    
    /* Read raw ADC data */
   // pm->adc1_raw = R_DSMIF_ReadCapDataA(pm->motor_idx, DSMIF_CH0) >> 4;
   // pm->adc2_raw = R_DSMIF_ReadCapDataA(pm->motor_idx, DSMIF_CH1) >> 4;
   // pm->adc3_raw = R_DSMIF_ReadCapDataA(pm->motor_idx, DSMIF_CH2) >> 4;
    //pm->crnt_volt = ((float)((float)(R_DSMIF_ReadCapDataA(DSMIF_UNIT9, DSMIF_CH0) >> 4) - BUS_BOARD_VOLT_INTERCEPT) / BUS_BOARD_VOLT_COEF) * CNVGAIN_VOLTAGE_DIV_VOUT_TO_VIN;
    pm->crnt_volt = 24;

    /* Only report phase current if the power is on*/
    if ((pm->act_state & ACT_PowerOn) && (pm->charge_state == BS_CHARGE_END))
    {
        pm->adc_iu = (long)(((float)(pm->adc1_raw - pm->adc1_offs)* CUR_AD_NUM * CNVGAIN_A_TO_MA) / CUR_AD_DIG_NUM); // [digit] * [mA/digit] = [mA]
        pm->adc_iv = (long)(((float)(pm->adc2_raw - pm->adc2_offs)* CUR_AD_NUM * CNVGAIN_A_TO_MA) / CUR_AD_DIG_NUM); // [digit] * [mA/digit] = [mA]
        pm->adc_iw = (long)(((float)(pm->adc3_raw - pm->adc3_offs)* CUR_AD_NUM * CNVGAIN_A_TO_MA) / CUR_AD_DIG_NUM); // [digit] * [mA/digit] = [mA]
        pm->adc_iu = pm->adc_iu * (-1);
        pm->adc_iv = pm->adc_iv * (-1);
        pm->adc_iw = pm->adc_iw * (-1);
    }
    else
    {
        pm->adc_iu = 0;
        pm->adc_iv = 0;
        pm->adc_iw = 0;
    }

    /* Calculate total current consumption */
    pm->total_current = abss(*pm->p_iu) + abss(*pm->p_iv);
    
}

/* Baud rate settings */
short set_baud_rate(R_SCI0_Type volatile *p_sci, short code)
{
volatile short dummy;

    p_sci->CCR0_b.TE = 0;
    p_sci->CCR0_b.RE = 0;
    
    p_sci->FCR_b.TFRST = 1;
    p_sci->FCR_b.RFRST = 1;
    
    p_sci->CFCLR = 0xbd070010;
    
    /* Set transmission/reception format */
    R_SCI4->CCR1 = _SCI_BREAK_DATA_SEL_1 |
                   _SCI_PARITY_DISABLE |
                   _SCI_LOOPBACK_DISABLE;
    R_SCI4->CCR2 = _SCI_BASE_CLK_CYCLE_32 |
                   _SCI_BAUDRATE_GEN_MODE_DOUBLE |
                   _SCI_ASYNC_MODE_BASE_CLK_8 |
                   _SCI_CLOCK_SEL_DIV_1;
    R_SCI4->CCR3 = _SCI_CLOCK_PHASE_SEL_NOT_DELAY |
                   _SCI_CLOCK_POLARITY_SEL_1 |
                   _SCI_CHAR_LENGTH_8BIT |
                   _SCI_LSB_FIRST |
                   _SCI_STOP_BIT_1 |
                   _SCI_COMM_MODE_ASYNC |
                   _SCI_FIFO_MODE_ENABLE |
                   _SCI_485_DRIVER_DISABLE |
                   _SCI_CLK_ASYNC_0;

    switch (code)
    {
    case 0:     /* 115.2 Kbps */
        /* Set bit rate */
        p_sci->CCR2_b.BRR = 0x4BU;

        /* Set modulation duty */
        p_sci->CCR2_b.BRME = 1U;
        p_sci->CCR2_b.MDDR = 0xBBU;
        break;
        
    case 2:     /* 250 Kbps */
        /* Set bit rate */
        p_sci->CCR2_b.BRR = 0x25U;

        /* Set modulation duty */
        p_sci->CCR2_b.BRME = 1U;
        p_sci->CCR2_b.MDDR = 0xCBU;
        break;

    case 1:     /* 230.4 Kbps */
        /* Set bit rate */
        p_sci->CCR2_b.BRR = 0x2EU;

        /* Set modulation duty */
        p_sci->CCR2_b.BRME = 1U;
        p_sci->CCR2_b.MDDR = 0xE7U;
        break;

    case 3:     /* 460.8 Kbps */
        /* Set bit rate */
        p_sci->CCR2_b.BRR = 0x12U;

        /* Set modulation duty */
        p_sci->CCR2_b.BRME = 1U;
        p_sci->CCR2_b.MDDR = 0xBBU;
        break;

    case 4:     /* 500 Kbps */
        /* Set bit rate */
        p_sci->CCR2_b.BRR = 0x0BU;

        /* Set modulation duty */
        p_sci->CCR2_b.BRME = 1U;
        p_sci->CCR2_b.MDDR = 0x80U;
        break;

    case 5:     /* 921.6 Kbps */
        /* Set bit rate */
        p_sci->CCR2_b.BRR = 0x09U;

        /* Set modulation duty */
        p_sci->CCR2_b.BRME = 1U;
        p_sci->CCR2_b.MDDR = 0xC5U;
        break;

    case 6:     /* 1 Mbps */
        /* Set bit rate */
        p_sci->CCR2_b.BRR = 0x05U;

        /* Set modulation duty */
        p_sci->CCR2_b.BRME = 1U;
        p_sci->CCR2_b.MDDR = 0x80U;
        break;

    case 7:     /* 1.25 Mbps */
        /* Set bit rate */
        p_sci->CCR2_b.BRR = 0x04U;

        /* Set modulation duty */
        p_sci->CCR2_b.BRME = 1U;
        p_sci->CCR2_b.MDDR = 0x86U;
        break;

    case 8:     /* 1.5 Mbps */
        /* Set bit rate */
        p_sci->CCR2_b.BRR = 0x03;

        /* Set modulation duty */
        p_sci->CCR2_b.BRME = 1U;
        p_sci->CCR2_b.MDDR = 0x80U;
        break;
    default:
        return 0;
    }
    p_sci->FCR_b.TFRST = 1;
    p_sci->FCR_b.RFRST = 1;

    p_sci->CCR0_b.RE = 1U;
    p_sci->CCR0_b.RIE = 1U;

    p_sci->CCR0_b.TE = 1U;
    while(1U != p_sci->CCR0_b.TE)
    {
      ;
    }

	return 1;
}

unsigned char ChkPOE(void)
{
    return R_POEG0->POEG0GD0_b.PIDF;
}

/* RZ/T2 add */
/******************************************************************************
* Function Name: pwm_enable
* Description  : PWM output enabled
* Arguments    : pm : structure of motor control(pointer) 
* Return Value : None
******************************************************************************/
void pwm_enable(t_motor *pm)
{
    switch(pm->motor_idx)
    {
        case 0:
            R_GPT00_0->GTIOR_b.OAE = 1;
            R_GPT00_0->GTIOR_b.OBE = 1;
            R_GPT00_1->GTIOR_b.OAE = 1;
            R_GPT00_1->GTIOR_b.OBE = 1;
            R_GPT00_2->GTIOR_b.OAE = 1;
            R_GPT00_2->GTIOR_b.OBE = 1;
            break;
        case 1:
            R_GPT01_0->GTIOR_b.OAE = 1;
            R_GPT01_0->GTIOR_b.OBE = 1;
            R_GPT01_1->GTIOR_b.OAE = 1;
            R_GPT01_1->GTIOR_b.OBE = 1;
            R_GPT01_2->GTIOR_b.OAE = 1;
            R_GPT01_2->GTIOR_b.OBE = 1;
            break;
        case 2:
            R_GPT02_0->GTIOR_b.OAE = 1;
            R_GPT02_0->GTIOR_b.OBE = 1;
            R_GPT02_1->GTIOR_b.OAE = 1;
            R_GPT02_1->GTIOR_b.OBE = 1;
            R_GPT02_2->GTIOR_b.OAE = 1;
            R_GPT02_2->GTIOR_b.OBE = 1;
            break;
        case 3:
            R_GPT03_0->GTIOR_b.OAE = 1;
            R_GPT03_0->GTIOR_b.OBE = 1;
            R_GPT03_1->GTIOR_b.OAE = 1;
            R_GPT03_1->GTIOR_b.OBE = 1;
            R_GPT03_2->GTIOR_b.OAE = 1;
            R_GPT03_2->GTIOR_b.OBE = 1;
            break;
        case 4:
            R_GPT04_0->GTIOR_b.OAE = 1;
            R_GPT04_0->GTIOR_b.OBE = 1;
            R_GPT04_1->GTIOR_b.OAE = 1;
            R_GPT04_1->GTIOR_b.OBE = 1;
            R_GPT04_2->GTIOR_b.OAE = 1;
            R_GPT04_2->GTIOR_b.OBE = 1;
            break;
        case 5:
            R_GPT05_0->GTIOR_b.OAE = 1;
            R_GPT05_0->GTIOR_b.OBE = 1;
            R_GPT05_1->GTIOR_b.OAE = 1;
            R_GPT05_1->GTIOR_b.OBE = 1;
            R_GPT05_2->GTIOR_b.OAE = 1;
            R_GPT05_2->GTIOR_b.OBE = 1;
            break;
        case 6:
            R_GPT06_0->GTIOR_b.OAE = 1;
            R_GPT06_0->GTIOR_b.OBE = 1;
            R_GPT06_1->GTIOR_b.OAE = 1;
            R_GPT06_1->GTIOR_b.OBE = 1;
            R_GPT06_2->GTIOR_b.OAE = 1;
            R_GPT06_2->GTIOR_b.OBE = 1;
            break;
        case 7:
            R_GPT07_0->GTIOR_b.OAE = 1;
            R_GPT07_0->GTIOR_b.OBE = 1;
            R_GPT07_1->GTIOR_b.OAE = 1;
            R_GPT07_1->GTIOR_b.OBE = 1;
            R_GPT07_2->GTIOR_b.OAE = 1;
            R_GPT07_2->GTIOR_b.OBE = 1;
            break;
        case 8:
            R_GPT08_0->GTIOR_b.OAE = 1;
            R_GPT08_0->GTIOR_b.OBE = 1;
            R_GPT08_1->GTIOR_b.OAE = 1;
            R_GPT08_1->GTIOR_b.OBE = 1;
            R_GPT08_2->GTIOR_b.OAE = 1;
            R_GPT08_2->GTIOR_b.OBE = 1;
            break;
        default:
            break;
    }
}
/*******************************************************************************
End of function pwm_enable
*******************************************************************************/

/******************************************************************************
* Function Name: pwm_disable
* Description  : PWM output disabled
* Arguments    : pm : structure of motor control(pointer) 
* Return Value : None
******************************************************************************/
void pwm_disable(t_motor *pm)
{
    switch(pm->motor_idx)
    {
        case 0:
            R_GPT00_0->GTIOR_b.OAE = 0;
            R_GPT00_0->GTIOR_b.OBE = 0;
            R_GPT00_1->GTIOR_b.OAE = 0;
            R_GPT00_1->GTIOR_b.OBE = 0;
            R_GPT00_2->GTIOR_b.OAE = 0;
            R_GPT00_2->GTIOR_b.OBE = 0;
            break;
        case 1:
            R_GPT01_0->GTIOR_b.OAE = 0;
            R_GPT01_0->GTIOR_b.OBE = 0;
            R_GPT01_1->GTIOR_b.OAE = 0;
            R_GPT01_1->GTIOR_b.OBE = 0;
            R_GPT01_2->GTIOR_b.OAE = 0;
            R_GPT01_2->GTIOR_b.OBE = 0;
            break;
        case 2:
            R_GPT02_0->GTIOR_b.OAE = 0;
            R_GPT02_0->GTIOR_b.OBE = 0;
            R_GPT02_1->GTIOR_b.OAE = 0;
            R_GPT02_1->GTIOR_b.OBE = 0;
            R_GPT02_2->GTIOR_b.OAE = 0;
            R_GPT02_2->GTIOR_b.OBE = 0;
            break;
        case 3:
            R_GPT03_0->GTIOR_b.OAE = 0;
            R_GPT03_0->GTIOR_b.OBE = 0;
            R_GPT03_1->GTIOR_b.OAE = 0;
            R_GPT03_1->GTIOR_b.OBE = 0;
            R_GPT03_2->GTIOR_b.OAE = 0;
            R_GPT03_2->GTIOR_b.OBE = 0;
            break;
        case 4:
            R_GPT04_0->GTIOR_b.OAE = 0;
            R_GPT04_0->GTIOR_b.OBE = 0;
            R_GPT04_1->GTIOR_b.OAE = 0;
            R_GPT04_1->GTIOR_b.OBE = 0;
            R_GPT04_2->GTIOR_b.OAE = 0;
            R_GPT04_2->GTIOR_b.OBE = 0;
            break;
        case 5:
            R_GPT05_0->GTIOR_b.OAE = 0;
            R_GPT05_0->GTIOR_b.OBE = 0;
            R_GPT05_1->GTIOR_b.OAE = 0;
            R_GPT05_1->GTIOR_b.OBE = 0;
            R_GPT05_2->GTIOR_b.OAE = 0;
            R_GPT05_2->GTIOR_b.OBE = 0;
            break;
        case 6:
            R_GPT06_0->GTIOR_b.OAE = 0;
            R_GPT06_0->GTIOR_b.OBE = 0;
            R_GPT06_1->GTIOR_b.OAE = 0;
            R_GPT06_1->GTIOR_b.OBE = 0;
            R_GPT06_2->GTIOR_b.OAE = 0;
            R_GPT06_2->GTIOR_b.OBE = 0;
            break;
        case 7:
            R_GPT07_0->GTIOR_b.OAE = 0;
            R_GPT07_0->GTIOR_b.OBE = 0;
            R_GPT07_1->GTIOR_b.OAE = 0;
            R_GPT07_1->GTIOR_b.OBE = 0;
            R_GPT07_2->GTIOR_b.OAE = 0;
            R_GPT07_2->GTIOR_b.OBE = 0;
            break;
        case 8:
            R_GPT08_0->GTIOR_b.OAE = 0;
            R_GPT08_0->GTIOR_b.OBE = 0;
            R_GPT08_1->GTIOR_b.OAE = 0;
            R_GPT08_1->GTIOR_b.OBE = 0;
            R_GPT08_2->GTIOR_b.OAE = 0;
            R_GPT08_2->GTIOR_b.OBE = 0;
            break;
        default:
            break;
    }
}
/*******************************************************************************
End of function pwm_disable
*******************************************************************************/
