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
* Copyright (C) 2015 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name     : m_biplane.h
* Version       : 1.00
* Device(s)     : RZT1
* Tool-Chain    : 
* Description   : 
******************************************************************************/

#include "hal_data.h"

/* Configuration bits - DIP-Switch */
#define CFG0 R_PORT_NSR->PIN_b[0x0A].PIN6
#define CFG1 R_PORT_NSR->PIN_b[0x0A].PIN7
#define CFG2 R_PORT_NSR->PIN_b[0x0B].PIN5
#define CFG3 R_PORT_NSR->PIN_b[0x01].PIN1
#define CFG4 R_PORT_NSR->PIN_b[0x07].PIN6
#define CFG5 R_PORT_NSR->PIN_b[0x0B].PIN2
#define CFG6 R_PORT_NSR->PIN_b[0x16].PIN3
#define CFG7 R_PORT_NSR->PIN_b[0x11].PIN1


/* Serial Interface Driver Enable */
#define EA1EN  R_PORT_NSR->P_b[0x08].POUT_0
#define EA2EN  R_PORT_NSR->P_b[0x12].POUT_3
#define EB1EN  R_PORT_NSR->P_b[0x08].POUT_2
#define EB2EN  R_PORT_NSR->P_b[0x08].POUT_3


/* PWM signal shut OFF */
#define RZ_SHUT_OFF1  R_PORT_NSR->P_b[0x03].POUT_2
#define RZ_SHUT_OFF2  R_PORT_NSR->P_b[0x03].POUT_3

/* POE Output */
#define POE_1 R_PORT_NSR->PMC_b[0x01].PMC4
#define POE_2 R_PORT_NSR->PMC_b[0x12].PMC7

