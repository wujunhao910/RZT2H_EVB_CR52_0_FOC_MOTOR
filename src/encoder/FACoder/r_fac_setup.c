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
* Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* System Name  : FA-CODER sample program
* File Name    : main.c
* Version      : 
* Device       : RZ
* Abstract     : Main processing source file for FA-CODER.
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* H/W Platform : RZ/T2H
* Description  : FA-CODER sample program on RZ devices.
* Limitation   : None
*******************************************************************************/
/*******************************************************************************
* History      : History is managed by Revision Control System.
*******************************************************************************/
/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "bsp_api.h"
#include "hal_data.h"
#include "r_fac_rzt2_dat.h"
#include "r_fac_rzt2_if.h"

#include "m_common.h"

#define FA_CODER_FMT23      0
#define FA_CODER_FMT17      1
#define FA_CODER_FMT17_NEG  0
#define FA_CODER_FMT14      0

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define MY_PRINTF_END       "\n"      /* Line feed code */
//#define MY_PRINTF(...)      (printf(__VA_ARGS__))
#define MY_PRINTF(...)

#define ARG_MAX             (4)         /* maximum number of comannd arguments */
#define CMD_BUF_SIZE        (256)       /* command buffer size */
#define CMD_NUM             (10)        /* number of commands */
#define EXIT_CMD_NUM        (9)         /* exit command number */
#define CMD_DELIMITER       (" \t\r\n") /* command line delimiter */
#define TIMOTN_VALUE        (4000)      /* timeout */

/* EC-lib macros */
#define R_FAC_FREQ (R_ECL_FREQ_10000KHZ)  //r_ecl_rzt2_if.h

/* "single" command parameter */
#define CMD_SINGLE_ARG_NUM  (1)
#define CMD_SINGLE_ID       (0)
#if FA_CODER_FMT14                      /* The 14-bit FA-CODER format includes only two bytes absolute single-turn position */
#define CMD_SINGLE_DFNUM    (2)
#else
#define CMD_SINGLE_DFNUM    (3)         /* The 17-bit and 23-bit FA-CODER includes three bytes absolute single-turn position */
#endif
#define RXDF_SINGLE0_INDEX  (0)
#define RXDF_SINGLE0_MASK   (0xFFu)
#define RXDF_SINGLE0_BIT    (0)
#define RXDF_SINGLE1_INDEX  (1)
#define RXDF_SINGLE1_MASK   (0xFFu)
#define RXDF_SINGLE1_BIT    (8)
#define RXDF_SINGLE2_INDEX  (2)
#define RXDF_SINGLE2_MASK   (0xFFu)
#define RXDF_SINGLE2_BIT    (16)

/* "multi" command parameter */
#define CMD_MULTI_ARG_NUM   (1)
#define CMD_MULTI_ID        (1)
#define CMD_MULTI_DFNUM     (3)
#define RXDF_MULTI0_INDEX   (0)
#define RXDF_MULTI0_MASK    (0xFFu)
#define RXDF_MULTI0_BIT     (0)
#define RXDF_MULTI1_INDEX   (1)
#define RXDF_MULTI1_MASK    (0xFFu)
#define RXDF_MULTI1_BIT     (8)

/* "encid" command parameter */
#define CMD_ENCID_ARG_NUM   (1)
#define CMD_ENCID_ID        (2)
#define CMD_ENCID_DFNUM     (1)
#define RXDF_ENCID_INDEX    (0)
#define RXDF_ENCID_MASK     (0xFFu)
#define RXDF_ENCID_BIT      (0)

/* "req" command parameter */
#define CMD_REQ_ARG_NUM     (3)
#define CMD_REQ_ARG_ID      (1)
#define CMD_REQ_ARG_DFNUM   (2)
#define CMD_REQ_ARG_BASE    (10)
#define REQ_ID_MAX          (15)
#define REQ_DFNUM_MIN       (1)
#define REQ_DFNUM_MAX       (8)

/* "E2PROM" command parameter */
#define CMD_E2PROM_W_ARG_NUM    (3)
#define CMD_E2PROM_R_ARG_NUM    (2)
#define CMD_E2PROM_ARG_ADR      (1)
#define CMD_E2PROM_ARG_DATA     (2)
#define CMD_E2PROM_ARG_BASE     (10)
#define E2PROM_ID_MAX           (15)
#define E2PROM_ADR_MIN          (0)
#define E2PROM_ADR_MAX          (79)
#define E2PROM_WRITE_DATA_MAX   (255)

/* "reset" command parameter */
#define CMD_RESET_ARG_NUM   (1)
#define CMD_RESET_SINGLE_ID (8)
#define CMD_RESET_MULTI_ID  (0x0c)
#define CMD_RESET_ALL_ID    (7)
#define CMD_RESET_DFNUM     (3)
#define RESET_CMD_CONT      (10)

/* "exit" command parameter */
#define CMD_EXIT_ARG_NUM    (1)

/* port set parameter */
#define PSEL_VALUE          (0x2B)          /* Value of MPC.PxxPFS.PSEL */

/* module stop */
#define PRCR_PRKEY_BIT      (0xa500)
#define PRCR_PRC1_BIT       (2)
#define MSTPCRA2_BIT        (4)

/* timer setting */
#define TIMER_VALUE         (0xFFFF)
#define CMSTR2_CONT_START   (1)
#define WAIT_CONT           (378)

/*******************************************************************************
Typedef definitions
*******************************************************************************/
typedef char char_t;
typedef void (*cmd_func_t)(char_t *parg[], const uint32_t arg_num);

/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/

/*******************************************************************************
Private variables and functions
*******************************************************************************/

static r_fac_err_t fac_trans_req(uint8_t id, r_fac_req_t *const preq, uint16_t tout);
static r_fac_err_t fac_trans_async(uint8_t id, r_fac_req_t *const preq, uint16_t tout);
static r_fac_err_t fac_trans_e2prom(uint8_t id, r_fac_e2prom_data_t *const pe2prom_data, uint16_t tout);

static void callback_req_result(r_fac_result_t *presult, uint8_t *prxdf);
static void callback_req_result0(r_fac_result_t *presult, uint8_t *prxdf);
static void callback_req_result1(r_fac_result_t *presult, uint8_t *prxdf);
static void callback_req_result2(r_fac_result_t *presult, uint8_t *prxdf);
static void callback_req_result3(r_fac_result_t *presult, uint8_t *prxdf);
static void callback_req_result4(r_fac_result_t *presult, uint8_t *prxdf);
static void callback_req_result5(r_fac_result_t *presult, uint8_t *prxdf);
static void callback_req_result6(r_fac_result_t *presult, uint8_t *prxdf);
static void callback_req_result7(r_fac_result_t *presult, uint8_t *prxdf);
static void callback_req_result8(r_fac_result_t *presult, uint8_t *prxdf);

static void callback_e2prom_result(r_fac_result_t *presult, uint8_t adf, uint8_t edf);

static void enable_int(void);


volatile static bool fac_flg_done;
volatile static bool fac_flgs[MOTOR_NUM];
static r_fac_result_t *pfac_result;

static uint8_t *pfac_rxdf;
static uint8_t pfac_rxdf0[3];
static uint8_t pfac_rxdf1[3];
static uint8_t pfac_rxdf2[3];
static uint8_t pfac_rxdf3[3];
static uint8_t pfac_rxdf4[3];
static uint8_t pfac_rxdf5[3];
static uint8_t pfac_rxdf6[3];
static uint8_t pfac_rxdf7[3];
static uint8_t pfac_rxdf8[3];

volatile static uint8_t fac_adf;
static uint8_t fac_edf;

extern t_motor m1;

extern void enc_fac_ch0_int_isr(void);
extern void enc_fac_ch1_int_isr(void);

#ifndef RAM_EXECUTION

#ifdef __ICCARM__
#pragma section="A_ENCIF0_WBLOCK"
#pragma section="A_ENCIF1_WBLOCK"
#endif  // __ICCARM__

#ifdef __GNUC__
#define A_ENCIF0_WBLOCK_ADDR	(uint8_t*)(0x00028000u)
#define A_ENCIF1_WBLOCK_ADDR	(uint8_t*)(0x00044000u)
#endif

#endif

static const int32_t fac_id_tbl[FAC_ID_NUM] =
{
    R_FAC0_ID,  R_FAC1_ID,  R_FAC2_ID,  R_FAC3_ID,
    R_FAC4_ID,  R_FAC5_ID,  R_FAC6_ID,  R_FAC7_ID,
    R_FAC8_ID,  R_FAC9_ID,  R_FAC10_ID, R_FAC11_ID
};

static const uint8_t * pfac_rxdf_tbl[MOTOR_NUM] =
{
     pfac_rxdf0,
     pfac_rxdf1,
     pfac_rxdf2,
     pfac_rxdf3,
     pfac_rxdf4,
     pfac_rxdf5,
     pfac_rxdf6,
     pfac_rxdf7,
     pfac_rxdf8
};

void (*callback_req_result_tbl[])(r_fac_result_t *, uint8_t *) = {
    callback_req_result0,
    callback_req_result1,
    callback_req_result2,
    callback_req_result3,
    callback_req_result4,
    callback_req_result5,
    callback_req_result6,
    callback_req_result7,
    callback_req_result8
};

static int32_t cur_id;

/*******************************************************************************
* Function Name: main_fac
* Description  : Main processing of FA-CODER sample program
* Arguments    : None
* Return Value : Error code of Encoder IF
*******************************************************************************/
int32_t main_fac(const int32_t idx, int32_t br)
{
    int32_t ret_code = 0;
    r_fac_err_t err_code;
    r_fac_info_t fac_info;

    if(idx < FAC_ID_NUM){
      cur_id = fac_id_tbl[idx];
    }else{
      goto func_end;
    }

    /* Enable IRQ interrupt */
    __enable_irq();
    __ISB();

    fac_info.bitrate = br;
    err_code = R_FAC_Open(cur_id, &fac_info);
    if (R_FAC_SUCCESS != err_code)
    {
        printf("R_FAC_Open: error(%ld)\n", (int32_t)err_code);
        ret_code = (int32_t)err_code;
        goto stop;
    }

stop:

func_end:
    fac_flg_done = true;
    for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
    {
        fac_flgs[idx] = true;
    }
    return ret_code;
}

/*******************************************************************************
End of function main
*******************************************************************************/
int32_t fac_close(const int32_t idx)
{
    uint8_t id;
    int32_t ret_code = 0;
    
    id = fac_id_tbl[idx];
    ret_code = R_FAC_Close(id);
    if (R_FAC_SUCCESS != ret_code)
    {
        MY_PRINTF("R_FAC_Close: error(%d)" MY_PRINTF_END, ret_code);
    }

    return ret_code;
}

/*******************************************************************************
* Function Name: fac_trans_req
* Description  : Sending request to FA-CODER and waiting response.
* Arguments    : id - channnel number
*                preq - Information of request.
* Return Value : Error code of encoder IF.
*******************************************************************************/
static r_fac_err_t fac_trans_req(uint8_t id, r_fac_req_t *const preq, uint16_t tout)
{
    r_fac_err_t err_code;
    uint32_t tm_count=0u;

    preq->presult_cb = &callback_req_result;
    preq->timotn = tout;
    /* Wait for an ongoing transaction to complete*/
    while (!fac_flg_done)
    {
        R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
        tm_count++;
        if(10 < tm_count)
        {
            return R_FAC_ERR_BUSY;
        }
    }
    
    fac_flg_done = false;
    err_code = R_FAC_Control(id, R_FAC_CMD_REQ, preq);
    if (R_FAC_SUCCESS == err_code)
    {
        tm_count=0u;
        while (false == fac_flg_done)
        {
            R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
            tm_count++;
            if(10 < tm_count)
            {
                err_code= R_FAC_ERR_BUSY;
                break;
            }
        }
    }
    else
    {
        MY_PRINTF("  R_FAC_Control(R_FAC_CMD_REQ) error: %ld" MY_PRINTF_END, (int32_t)err_code);
    }
    return err_code;
}
/*******************************************************************************
End of function fac_trans_req
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_trans_async
* Description  : Sending request to FA-CODER and returns WITHOUT waiting response.
* Arguments    : id - channnel number
*                preq - Information of request.
* Return Value : Error code of encoder IF.
*******************************************************************************/
static r_fac_err_t fac_trans_async(uint8_t id, r_fac_req_t *const preq, uint16_t tout)
{
    preq->presult_cb = callback_req_result_tbl[id];
    preq->timotn = tout;
    return R_FAC_Control(fac_id_tbl[id], R_FAC_CMD_REQ, preq);
}
/*******************************************************************************
End of function fac_trans_asyncpe2prom_data);
    if (R_FAC_SUCCESS == err_code)
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_trans_e2prom
* Description  : Sending e2prom to FA-CODER and waiting response.
* Arguments    : id - channnel number
*                pe2prom_data - Information of e2prom.
* Return Value : Error code of encoder IF.
*******************************************************************************/
static r_fac_err_t fac_trans_e2prom(uint8_t id, r_fac_e2prom_data_t *const pe2prom_data, uint16_t tout)
{
    r_fac_err_t err_code;
    uint32_t tm_count=0u;

    pe2prom_data->presult_cb = &callback_e2prom_result;
    pe2prom_data->timotn = tout;
    /* Wait for an ongoing transaction to complete*/
    while (!fac_flg_done)
    {
        R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
        tm_count++;
        if(10 < tm_count)
        {
            return R_FAC_ERR_BUSY;
        }
    }
    
    fac_flg_done = false;
    err_code = R_FAC_Control(id, R_FAC_CMD_E2PROM, pe2prom_data);
    if (R_FAC_SUCCESS == err_code)
    {
        tm_count=0u;
        while (false == fac_flg_done)
        {
            R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
            tm_count++;
            if(10 < tm_count)
            {
                err_code= R_FAC_ERR_BUSY;
                break;
            }
        }
    }
    else
    {
        MY_PRINTF("  R_FAC_Control(R_FAC_CMD_E2PROM) error: %ld" MY_PRINTF_END, (int32_t)err_code);
    }
    return err_code;
}
/*******************************************************************************
End of function fac_trans_e2prom
*******************************************************************************/

/*******************************************************************************
* Function Name: callback_req_result
* Description  : Call back function of request command for FA-CODER.
* Arguments    : presult - Result of request for FA-CODER
*                prxdf - Data fields.
* Return Value : None.
*******************************************************************************/
static void callback_req_result(r_fac_result_t *presult, uint8_t *prxdf)
{
    pfac_result = presult;
    pfac_rxdf   = prxdf;
    fac_flg_done    = true;
    return;
}


static void callback_req_result0(r_fac_result_t *presult, uint8_t *prxdf)
{
    pfac_result = presult;
    memcpy(pfac_rxdf0, prxdf, sizeof(uint8_t) * 3);
    fac_flgs[0] = true;
    return;
}

static void callback_req_result1(r_fac_result_t *presult, uint8_t *prxdf)
{

    pfac_result = presult;
    memcpy(pfac_rxdf1, prxdf, sizeof(uint8_t) * 3);
    fac_flgs[1] = true;
    return;
}

static void callback_req_result2(r_fac_result_t *presult, uint8_t *prxdf)
{
    pfac_result = presult;
    memcpy(pfac_rxdf2, prxdf, sizeof(uint8_t) * 3);
    fac_flgs[2] = true;
    return;
}

static void callback_req_result3(r_fac_result_t *presult, uint8_t *prxdf)
{
    pfac_result = presult;
    memcpy(pfac_rxdf3, prxdf, sizeof(uint8_t) * 3);
    fac_flgs[3] = true;
    return;
}

static void callback_req_result4(r_fac_result_t *presult, uint8_t *prxdf)
{
    pfac_result = presult;
    memcpy(pfac_rxdf4, prxdf, sizeof(uint8_t) * 3);
    fac_flgs[4] = true;
    return;
}

static void callback_req_result5(r_fac_result_t *presult, uint8_t *prxdf)
{
    pfac_result = presult;
    memcpy(pfac_rxdf5, prxdf, sizeof(uint8_t) * 3);
    fac_flgs[5] = true;
    return;
}

static void callback_req_result6(r_fac_result_t *presult, uint8_t *prxdf)
{
    pfac_result = presult;
    memcpy(pfac_rxdf6, prxdf, sizeof(uint8_t) * 3);
    fac_flgs[6] = true;
    return;
}

static void callback_req_result7(r_fac_result_t *presult, uint8_t *prxdf)
{
    pfac_result = presult;
    memcpy(pfac_rxdf7, prxdf, sizeof(uint8_t) * 3);
    fac_flgs[7] = true;
    return;
}

static void callback_req_result8(r_fac_result_t *presult, uint8_t *prxdf)
{
    pfac_result = presult;
    memcpy(pfac_rxdf8, prxdf, sizeof(uint8_t) * 3);
    fac_flgs[8] = true;
    return;
}

/*******************************************************************************
End of function callback_req_result
*******************************************************************************/

/*******************************************************************************
* Function Name: callback_e2prom_result
* Description  : Call back function of e2prom for FA-CODER.
* Arguments    : presult - Result of request for FA-CODER
*                adf - ADF register fields.
*                edf - EDF register fields.
* Return Value : None.
*******************************************************************************/
static void callback_e2prom_result(r_fac_result_t *presult, uint8_t adf, uint8_t edf)
{
    pfac_result = presult;
    fac_adf     = adf;
    fac_edf     = edf;
    fac_flg_done    = true;
    return;
}
/*******************************************************************************
End of function callback_e2prom_result
*******************************************************************************/

/*******************************************************************************
* Function Name: enable_int
* Description  : enable of interrupt
* Arguments    : None.
* Return Value : None.
*******************************************************************************/

static void enable_int(void)
{
#ifdef __ICCARM__
    __enable_irq();
    __ISB();
#endif /* __ICCARM__ */
#ifdef __CC_ARM
    __asm("cpsie i");
    __asm("isb");
#else
#ifdef __GNUC__
    asm("cpsie i");
    asm("isb");
#endif /* __GNUC__ */
#endif /* __CC_ARM */
}
/*******************************************************************************
End of function enable_int
*******************************************************************************/

long fac_pos(t_motor *pm)
{
    int ch = fac_id_tbl[pm->motor_idx];

    r_fac_req_t r_fac_req;
    uint32_t single_turn,single_turn1;
    int32_t res_new;
    int32_t res_old;
    int32_t pos_new;
    uint8_t origin_flg = false;

    /* Initiate new transaction */
    r_fac_req.txid = CMD_SINGLE_ID;
    r_fac_req.dfnum = CMD_SINGLE_DFNUM;
    switch (pm->motor_idx) {
        case 2:
            fac_trans_async(8, &r_fac_req, (uint16_t)pm->enc_timeout);
            break;
        case 3:
            fac_trans_async(1, &r_fac_req, (uint16_t)pm->enc_timeout);
            break;
        case 6:
            fac_trans_async(3, &r_fac_req, (uint16_t)pm->enc_timeout);
            break;
        case 7:
            fac_trans_async(6, &r_fac_req, (uint16_t)pm->enc_timeout);
            break;
        case 8:
            fac_trans_async(7, &r_fac_req, (uint16_t)pm->enc_timeout);
            break;
        default:
            fac_trans_async(pm->motor_idx, &r_fac_req, (uint16_t)pm->enc_timeout);
            break;
    }

    res_old = (pm->real_res & 0xc0000000);
    switch (pm->motor_idx) {
        case 2:
            single_turn =
                      (((uint32_t)pfac_rxdf_tbl[8][RXDF_SINGLE0_INDEX] & RXDF_SINGLE0_MASK) << RXDF_SINGLE0_BIT)
                    | (((uint32_t)pfac_rxdf_tbl[8][RXDF_SINGLE1_INDEX] & RXDF_SINGLE1_MASK) << RXDF_SINGLE1_BIT)
                    | (((uint32_t)pfac_rxdf_tbl[8][RXDF_SINGLE2_INDEX] & RXDF_SINGLE2_MASK) << RXDF_SINGLE2_BIT);
            break;
        case 3:
            single_turn =
                       (((uint32_t)pfac_rxdf_tbl[1][RXDF_SINGLE0_INDEX] & RXDF_SINGLE0_MASK) << RXDF_SINGLE0_BIT)
                    | (((uint32_t)pfac_rxdf_tbl[1][RXDF_SINGLE1_INDEX] & RXDF_SINGLE1_MASK) << RXDF_SINGLE1_BIT)
                    | (((uint32_t)pfac_rxdf_tbl[1][RXDF_SINGLE2_INDEX] & RXDF_SINGLE2_MASK) << RXDF_SINGLE2_BIT);
            break;
        case 6:
            single_turn =
                       (((uint32_t)pfac_rxdf_tbl[3][RXDF_SINGLE0_INDEX] & RXDF_SINGLE0_MASK) << RXDF_SINGLE0_BIT)
                    | (((uint32_t)pfac_rxdf_tbl[3][RXDF_SINGLE1_INDEX] & RXDF_SINGLE1_MASK) << RXDF_SINGLE1_BIT)
                    | (((uint32_t)pfac_rxdf_tbl[3][RXDF_SINGLE2_INDEX] & RXDF_SINGLE2_MASK) << RXDF_SINGLE2_BIT);
            break;
        case 7:
            single_turn =
                       (((uint32_t)pfac_rxdf_tbl[6][RXDF_SINGLE0_INDEX] & RXDF_SINGLE0_MASK) << RXDF_SINGLE0_BIT)
                    | (((uint32_t)pfac_rxdf_tbl[6][RXDF_SINGLE1_INDEX] & RXDF_SINGLE1_MASK) << RXDF_SINGLE1_BIT)
                    | (((uint32_t)pfac_rxdf_tbl[6][RXDF_SINGLE2_INDEX] & RXDF_SINGLE2_MASK) << RXDF_SINGLE2_BIT);
            break;
        case 8:
            single_turn =
                       (((uint32_t)pfac_rxdf_tbl[7][RXDF_SINGLE0_INDEX] & RXDF_SINGLE0_MASK) << RXDF_SINGLE0_BIT)
                    | (((uint32_t)pfac_rxdf_tbl[7][RXDF_SINGLE1_INDEX] & RXDF_SINGLE1_MASK) << RXDF_SINGLE1_BIT)
                    | (((uint32_t)pfac_rxdf_tbl[7][RXDF_SINGLE2_INDEX] & RXDF_SINGLE2_MASK) << RXDF_SINGLE2_BIT);
            break;
        default:
            single_turn =
                        (((uint32_t)pfac_rxdf_tbl[pm->motor_idx][RXDF_SINGLE0_INDEX] & RXDF_SINGLE0_MASK) << RXDF_SINGLE0_BIT)
                     | (((uint32_t)pfac_rxdf_tbl[pm->motor_idx][RXDF_SINGLE1_INDEX] & RXDF_SINGLE1_MASK) << RXDF_SINGLE1_BIT)
                     | (((uint32_t)pfac_rxdf_tbl[pm->motor_idx][RXDF_SINGLE2_INDEX] & RXDF_SINGLE2_MASK) << RXDF_SINGLE2_BIT);
            break;
    }
#if 0
   // if(pm->motor_idx == 2)
  //    {
          single_turn =
                  (((uint32_t)pfac_rxdf_tbl[1][RXDF_SINGLE0_INDEX] & RXDF_SINGLE0_MASK) << RXDF_SINGLE0_BIT)
                  | (((uint32_t)pfac_rxdf_tbl[1][RXDF_SINGLE1_INDEX] & RXDF_SINGLE1_MASK) << RXDF_SINGLE1_BIT)
                  | (((uint32_t)pfac_rxdf_tbl[1][RXDF_SINGLE2_INDEX] & RXDF_SINGLE2_MASK) << RXDF_SINGLE2_BIT);
        // printf("%x %x %x\n",pfac_rxdf_tbl[8][0],pfac_rxdf_tbl[8][1],pfac_rxdf_tbl[8][2]);
//     }
 //  else{
  //     single_turn =
   //             (((uint32_t)pfac_rxdf_tbl[pm->motor_idx][RXDF_SINGLE0_INDEX] & RXDF_SINGLE0_MASK) << RXDF_SINGLE0_BIT)
  //              | (((uint32_t)pfac_rxdf_tbl[pm->motor_idx][RXDF_SINGLE1_INDEX] & RXDF_SINGLE1_MASK) << RXDF_SINGLE1_BIT)
 //               | (((uint32_t)pfac_rxdf_tbl[pm->motor_idx][RXDF_SINGLE2_INDEX] & RXDF_SINGLE2_MASK) << RXDF_SINGLE2_BIT);
 //   }
    /* Convert result to 32-bit resolution per single turn */
          //res_new = single_turn >>2;
#endif
#if FA_CODER_FMT23
        res_new = (int32_t)(single_turn << 9);
#endif
#if FA_CODER_FMT17
    res_new = (int32_t)(single_turn << 15);
       // res_new = single_turn >>2;
#endif
#if FA_CODER_FMT17_NEG
        if(single_turn!=0){
            res_new = (int32_t)(((~single_turn)&0x1FFFFu) << 15);
        }
#endif
#if FA_CODER_FMT14
        res_new = (int32_t)(single_turn1 << 18);
#endif
    pm->real_res = res_new;
#if 1
    if (res_old == 0 && res_new < 0)
    {
        if (pm->real_rot == (int16_t)0x8000)
        {
            pm->act_state |= ACT_WrapAround;
        }
        pm->real_rot--;      /* decreement rotation */
        origin_flg = true;  /* origin detection */
        pm->captured_pos.Reg16.Low  = 0;
        pm->captured_pos.Reg16.High = (short)((pm->real_rot + 1) & 0xffff);
    }
    else if (res_old == (int32_t)(0xc0000000) && res_new >= 0)
    {
        if (pm->real_rot == (int16_t)0x7fff)
        {
            pm->act_state |= ACT_WrapAround;
        }
        pm->real_rot++;      /* increment rotation */

        origin_flg = true;  /* origin detection */
        pm->captured_pos.Reg16.Low  = 0;
        pm->captured_pos.Reg16.High = (short)(pm->real_rot & 0xffff);
    }

    if(origin_flg == true)
    {
        /* Apply position Offset parameter */
        pm->captured_pos.Reg32 += pm->pos_offset;
        /* Update Activity Status */
        pm->act_state |= ACT_PosCaptured;
        pm->index_pos = pm->captured_pos.Reg32;
    }
#endif
    pos_new = (int32_t)((( (uint32_t)pm->real_rot << 16 ) & 0xffff0000) | (( (uint32_t)pm->real_res >> 16 ) & 0x0000ffff));
    //pos_new = ((uint32_t)pm->real_res);
    return pos_new;
}

/**
 * @brief 单圈16位绝对编码器位置获取函数
 * @param pm 电机对象指针
 * @return 32位组合位置（高16位：圈数，低16位：单圈位置）
 */
long fac_pos1(t_motor *pm)
{
    r_fac_req_t r_fac_req;
    uint32_t single_turn;
    int32_t res_new, res_old, pos_new;
    uint8_t origin_flg = false;

    /* 1. 发起通信请求 */
    r_fac_req.txid = CMD_SINGLE_ID;
    r_fac_req.dfnum = CMD_SINGLE_DFNUM;
    fac_trans_async(8, &r_fac_req, (uint16_t)pm->enc_timeout);

    /* 2. 解析接收到的三字节位置数据（小端格式） */
    /* 协议示例：0x02 0x00 0x34 0x12 0x00 0x24
     *          ^    ^    ^    ^    ^    ^
     *         CF  状态 低字节 中字节 高字节 CRC
     */
    single_turn = (((uint32_t)pfac_rxdf_tbl[8][RXDF_SINGLE0_INDEX] & RXDF_SINGLE0_MASK) << RXDF_SINGLE0_BIT)
                | (((uint32_t)pfac_rxdf_tbl[8][RXDF_SINGLE1_INDEX] & RXDF_SINGLE1_MASK) << RXDF_SINGLE1_BIT)
                | (((uint32_t)pfac_rxdf_tbl[8][RXDF_SINGLE2_INDEX] & RXDF_SINGLE2_MASK) << RXDF_SINGLE2_BIT);

    /* 3. 转换为32位内部表示（单圈16位 -> 左移16位） */
    /* 说明：将0-65535映射到32位空间的高16位，低16位为0
     * 例如：0x001234 -> 0x12340000
     */
    res_new = (int32_t)(single_turn << 15);

    /* 4. 跨圈检测：使用滞回比较避免噪声误触发 */
    /* 阈值设置（可根据实际情况调整）：
     * - 正向阈值：60000（约91.5%圈）
     * - 反向阈值：5000（约7.6%圈）
     * 原理：当位置从高阈值区域跳变到低阈值区域，判断为正向跨圈；反之则为反向跨圈
     */
    #define POS_NEAR_MAX  (60000 << 16)  /* 接近最大值（正向跨圈起点） */
    #define POS_NEAR_MIN  ( 5000 << 16)  /* 接近最小值（正向跨圈终点） */
    #define ROT_MAX       32767          /* 16位有符号整数最大值 */
    #define ROT_MIN      (-32768)        /* 16位有符号整数最小值 */

    /* 获取上一次位置用于比较 */
    res_old = pm->real_res_prev;

    /* 检测正向跨圈：从接近最大值跳变到接近最小值 */
    if ((res_old > POS_NEAR_MAX) && (res_new < POS_NEAR_MIN))
    {
        if (pm->real_rot < ROT_MAX)
        {
            pm->real_rot++;                   /* 增加圈数计数 */
        }
        else
        {
            pm->act_state |= ACT_WrapAround;  /* 圈数溢出标记 */
        }
        origin_flg = true;
    }
    /* 检测反向跨圈：从接近最小值跳变到接近最大值 */
    else if ((res_old < POS_NEAR_MIN) && (res_new > POS_NEAR_MAX))
    {
        if (pm->real_rot > ROT_MIN)
        {
            pm->real_rot--;                   /* 减少圈数计数 */
        }
        else
        {
            pm->act_state |= ACT_WrapAround;  /* 圈数下溢标记 */
        }
        origin_flg = true;
    }

    /* 5. 更新位置状态 */
    pm->real_res = res_new;            /* 保存当前单圈位置 */
    pm->real_res_prev = res_new;       /* 更新历史位置，用于下次跨圈检测 */
#if 0
    /* 6. 如果检测到跨圈，进行原点捕获处理 */
    if (origin_flg)
    {
        pm->captured_pos.Reg16.Low = 0;
        pm->captured_pos.Reg16.High = (short)(pm->real_rot & 0xFFFF);
        pm->captured_pos.Reg32 += pm->pos_offset;  /* 应用位置偏移 */
        pm->act_state |= ACT_PosCaptured;          /* 标记位置已捕获 */
        pm->index_pos = pm->captured_pos.Reg32;    /* 更新索引位置 */
    }
#endif
    /* 7. 组合最终位置值：高16位为圈数，低16位为单圈位置 */
    /* 公式：位置 = (圈数 << 16) | (单圈位置 >> 16)
     * 例如：圈数=2，单圈位置=0x12340000
     * 结果：0x00020000 | 0x00001234 = 0x00021234
     */
    pos_new = (int32_t)((((uint32_t)pm->real_rot << 16) & 0xFFFF0000U) |
                        (((uint32_t)res_new >> 16) & 0x0000FFFFU));

    return pos_new;
}

long fac_enc_id(t_motor *pm)
{
    uint32_t encid=99u;
            
    r_fac_req_t r_fac_req;
    r_fac_err_t err_code;

    r_fac_req.txid = CMD_ENCID_ID;
    r_fac_req.dfnum = CMD_ENCID_DFNUM;
    err_code = fac_trans_async(pm->motor_idx, &r_fac_req, (uint16_t)pm->enc_timeout);

    if (R_FAC_SUCCESS == err_code)
    {
        if (R_FAC_RX_SUCCESS == pfac_result->result)
        {
            uint16_t st = 0;
            encid = ((uint32_t)pfac_rxdf[RXDF_ENCID_INDEX] & RXDF_ENCID_MASK) << RXDF_ENCID_BIT;

            if (pfac_result->rxsfea & 0x01)
                st |= ESTATE_COUNT_ERR;
            if (pfac_result->rxsfea & 0x02)
                st |= ESTATE_MULTI_ERR;
            if (pfac_result->rxsfca & 0x01)
                st |= ESTATE_PARITY_ERR;
            if (pfac_result->rxsfca & 0x02)
                st |= ESTATE_DELIM_ERR;
            
            pm->enc_status = st;
        }
        else
        {
            encid = 0;
        }
    }
    return (long) encid;
}

/*******************************************************************************
* Function Name: fac_eeprom_write
* Description  : EEPROM Write
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
long fac_eeprom_write(t_motor *pm, long write_data)                             
{                             
    int ch = pm == &m1 ? R_FAC0_ID : R_FAC1_ID;
    
    r_fac_err_t err_code;
    
    r_fac_e2prom_data_t r_fac_e2prom_data;
    
    r_fac_e2prom_data.adr = (uint8_t)pm->eeprom_addr;
    r_fac_e2prom_data.data = (uint8_t)write_data;
    r_fac_e2prom_data.dir = R_FAC_E2PROM_WRITE;

    err_code = fac_trans_e2prom(ch, &r_fac_e2prom_data, (uint16_t)pm->enc_timeout);

    if (R_FAC_SUCCESS == err_code)
    {
        if (R_FAC_RX_SUCCESS == pfac_result->result)
        {
          /*
            MY_PRINTF("  result:success" MY_PRINTF_END);
            MY_PRINTF("    adf data:     %d" MY_PRINTF_END,  fac_adf);
            MY_PRINTF("    edf data:     %d" MY_PRINTF_END,  fac_edf);
            MY_PRINTF("    request id:   %2XH" MY_PRINTF_END, pfac_result->rxid);
            MY_PRINTF("    parity bit:   %2XH" MY_PRINTF_END, pfac_result->rxidp);
            MY_PRINTF("    crc data:     %2XH" MY_PRINTF_END, pfac_result->crc);
          */
            return 0;
        }
    }
    return -1;
}
/*******************************************************************************
End of function fac_eeprom_write
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_eeprom_read
* Description  : EEPROM Read
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
long fac_eeprom_read(t_motor *pm, long *read_data)
{
    int ch = pm == &m1 ? R_FAC0_ID : R_FAC1_ID;
    
    r_fac_e2prom_data_t r_fac_e2prom_data;
    r_fac_err_t err_code;

    r_fac_e2prom_data.adr = (char)pm->eeprom_addr;
    r_fac_e2prom_data.dir = R_FAC_E2PROM_READ;

    err_code = fac_trans_e2prom(ch, &r_fac_e2prom_data, (uint16_t)pm->enc_timeout);

    if (R_FAC_SUCCESS == err_code)
    {
        if (R_FAC_RX_SUCCESS == pfac_result->result)
        {
          /*
            MY_PRINTF("  result:success" MY_PRINTF_END);
            MY_PRINTF("    adf data:     %d" MY_PRINTF_END,  fac_adf);
            MY_PRINTF("    edf data:     %d" MY_PRINTF_END,  fac_edf);
            MY_PRINTF("    request id:   %2XH" MY_PRINTF_END, pfac_result->rxid);
            MY_PRINTF("    parity bit:   %2XH" MY_PRINTF_END, pfac_result->rxidp);
            MY_PRINTF("    crc data:     %2XH" MY_PRINTF_END, pfac_result->crc);
          */
            *read_data = fac_edf;
            return 0;
        }
    }
    return -1;
}
/*******************************************************************************
End of function fac_eeprom_read
*******************************************************************************/
                             
