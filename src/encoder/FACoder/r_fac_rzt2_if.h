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
* Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* System Name  : FAC Encoder IF
* File Name    : r_fac_rzt2_if.h
* Version      : 
* Device       : RZ
* Abstract     : FAC Encoder IF header file.
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* H/W Platform : RZ/T2H
* Description  : Header file of encoder IF on RZ devices.
* Limitation   : None
*******************************************************************************/
/*******************************************************************************
* History      : History is managed by Revision Control System.
*******************************************************************************/

#ifndef R_FAC_RZT2_IF_H
#define R_FAC_RZT2_IF_H

/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
Macro definitions
*******************************************************************************/
/* Bitrate */
#define R_FAC_2500KBPS          (0u)
#define R_FAC_5MBPS             (1u)
#define R_FAC_BITRATE_NUM       (2u)

/*******************************************************************************
Typedef definitions
*******************************************************************************/
/* API error codes */
typedef enum r_fac_err_e
{
    R_FAC_SUCCESS = 0,        /* Success          */
    R_FAC_ERR_INVALID_ARG,    /* Invalid argument */
    R_FAC_ERR_BUSY,           /* Busy             */
    R_FAC_ERR_ACCESS          /* Access error     */
} r_fac_err_t;

/* Command of R_FAC_Control function.*/
typedef enum r_fac_cmd_e
{
    R_FAC_CMD_REQ,            /* Request */
    R_FAC_CMD_E2PROM,         /* E2PROM access */
    R_FAC_CMD_ELCTIMER,       /* ELC Timer operation */
    R_FAC_CMD_ELCSTOP         /* Stop ELC Timer */
} r_fac_cmd_t;

/* FACoder control error */
typedef enum r_fac_rx_err_e
{
    R_FAC_RX_SUCCESS = 0,    /* FA-CODER control success */
    R_FAC_RX_ERR          /* FA-CODER control error (RX) */
} r_fac_rx_err_t;

typedef enum r_fac_e2prom_dir_e
{
    R_FAC_E2PROM_READ,
    R_FAC_E2PROM_WRITE
} r_fac_e2prom_dir_t;

typedef struct r_fac_info_s
{
    uint8_t bitrate;
} r_fac_info_t;

typedef struct r_fac_result_s
{
    r_fac_rx_err_t result;
    bool rse;
    bool ide;
    bool ebusy;
    uint8_t rxid;
    uint8_t rxidp;
    uint8_t rxsfic;
    uint8_t rxsfea;
    uint8_t rxsfca;
    uint8_t crc;
    bool conte;
    bool crce;
    bool sfome;
    bool timote;
    bool rxedfe;
    bool rxadfe;
    bool dfovfe;
    bool orer;
} r_fac_result_t;

typedef void (*r_fac_req_result_cb_t)(r_fac_result_t * presult, uint8_t * prxdf);
typedef void (*r_fac_e2prom_result_cb_t)(r_fac_result_t * presult, uint8_t adf, uint8_t edf);

typedef struct r_fac_req_s
{
    uint8_t txid;
    uint8_t dfnum;
    uint16_t timotn;
    r_fac_req_result_cb_t presult_cb;
} r_fac_req_t;

typedef struct r_fac_e2prom_s
{
    uint16_t timotn;
    uint8_t adr;
    uint8_t data;
    r_fac_e2prom_dir_t dir;
    r_fac_e2prom_result_cb_t presult_cb;
} r_fac_e2prom_data_t;

/*******************************************************************************
Public Functions
*******************************************************************************/
r_fac_err_t R_FAC_Open(const int32_t id, const r_fac_info_t* pinfo);
r_fac_err_t R_FAC_Close(const int32_t id);
r_fac_err_t R_FAC_Control(const int32_t id, const r_fac_cmd_t cmd, void *const pbuf);
uint32_t R_FAC_GetVersion(void);

#endif /* R_FAC_RZT2_IF_H */
