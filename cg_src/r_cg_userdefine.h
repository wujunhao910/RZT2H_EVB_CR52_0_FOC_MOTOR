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
***********************************************************************************************************************/

/***********************************************************************************************************************
* System Name  : RZ/T2H Motor Solution Kit
* File Name    : r_cg_userdefine.h
* Version      : 1.00
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Header file of user definition. 
***********************************************************************************************************************/
#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/

/* Start user code for function. Do not edit comment generated here */
#ifdef ETHERCAT_EN
#ifdef ENABLE_UART
typedef struct
{
	union
	{
		volatile unsigned long LONG;
		struct
		{
			volatile unsigned long SEMF:1;
			unsigned long :31;
		} BIT;
	} SYTSEMF;
} st_sytsemf;

extern st_sytsemf * SEMFREGx;

#define UART_SEMAPHORE_SET()			( SEMFREGx = (st_sytsemf *)( &SYSTEM.SYTSEMF1.LONG ) )
#define UART_SEMAPHORE_WAIT()			{ while ( 0 == SEMFREGx->SYTSEMF.BIT.SEMF ) { ; } }
#define UART_SEMAPHORE_RELEASE()		( SEMFREGx->SYTSEMF.BIT.SEMF = 1 )
#endif // enable_uart
#define PROFILE_POSITION_MODE			1
#define PROFILE_VELOCITY_MODE			3
#define HOMING_MODE						6
#define CYCLIC_SYNC_POSITION_MODE		8
#define CYCLIC_SYNC_VELOCITY_MODE		9
#define CYCLIC_SYNC_TORQUE_MODE			10
#endif // ethercat
/* End user code. Do not edit comment generated here */
#endif
