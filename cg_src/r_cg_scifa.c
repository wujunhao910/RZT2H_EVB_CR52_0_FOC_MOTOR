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
* File Name    : r_cg_scifa.c
* Version      : 1.00
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Source file of SCIF module.
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_scifa.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"
#include "bsp_api.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

const uint8_t * gp_sci5_tx_address;   /* SCI5 transmit buffer address */
uint16_t        g_sci5_tx_count;      /* SCI5 transmit data number */
uint8_t *       gp_sci5_rx_address;   /* SCI5 receive buffer address */
uint16_t        g_sci5_rx_count;      /* SCI5 receive data number */
uint16_t        g_sci5_rx_length;     /* SCI5 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************


/***********************************************************************************************************************
* Function Name: R_SCI5_Create
* Description  : This function initializes SCI5.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCI5_Create(void)
{
    volatile uint32_t dummy_32;
    uint32_t w_count;

    /* Cancel SCI5 module stop state */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_SYSC_S->MSTPCRG = 0;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* Disable SCI5 ERI interrupt */
    R_BSP_IrqDisable(VECTOR_NUMBER_SCI5_ERI);
    /* Disable SCI5 RXI interrupt */
    R_BSP_IrqDisable(VECTOR_NUMBER_SCI5_RXI);
    /* Disable SCI5 TXI interrupt */
    R_BSP_IrqDisable(VECTOR_NUMBER_SCI5_TXI);
    /* Disable SCI5 TEI interrupt */
    R_BSP_IrqDisable(VECTOR_NUMBER_SCI5_TEI);

    /* Clear transmit/receive enable bits */
    R_SCI5->CCR0_b.TE = 0U;
    R_SCI5->CCR0_b.RE = 0U;

	/* Reset transmit/receive FIFO data register operation */
    R_SCI5->FCR_b.TFRST = 1U;
    R_SCI5->FCR_b.RFRST = 1U;

    /* Read and clear status flags */
    R_SCI5->CFCLR = 0UL;
    R_SCI5->FFCLR = 0UL;

    /* Set transmission/reception format */
    R_SCI5->CCR1 = _SCI_BREAK_DATA_SEL_1 | _SCI_PARITY_DISABLE | _SCI_LOOPBACK_DISABLE;
    R_SCI5->CCR2 = _SCI_BASE_CLK_CYCLE_32 | _SCI_BAUDRATE_GEN_MODE_DOUBLE | _SCI_ASYNC_MODE_BASE_CLK_8 | _SCI_CLOCK_SEL_DIV_1;
    /* Set bit rate */
    R_SCI5->CCR2_b.BRR = 0x67U;

    R_SCI5->CCR3 = _SCI_CLOCK_PHASE_SEL_NOT_DELAY | _SCI_CLOCK_POLARITY_SEL_1 | _SCI_CHAR_LENGTH_8BIT | _SCI_LSB_FIRST | _SCI_STOP_BIT_1 |_SCI_COMM_MODE_ASYNC | _SCI_FIFO_MODE_ENABLE | _SCI_485_DRIVER_DISABLE | _SCI_CLK_ASYNC_0;

    /* Wait for at least 1-bit interval */
    for (w_count = 0U; w_count < _SCIF_1BIT_INTERVAL_2; w_count++)
    {
        nop();
    }

    /* Set FIFO trigger conditions */
	R_SCI5->FCR = _SCI_RECV_DATA_ERR_SEL_RXI;
    R_SCI5->FCR_b.TTRG = 0;
    R_SCI5->FCR_b.RTRG = 1;

    /* Disable transmit/receive FIFO data register reset operation */
    R_SCI5->FCR_b.TFRST = 1U;
    R_SCI5->FCR_b.RFRST = 1U;

    /* Set SCI5 ERI interrupt priority */
    R_BSP_IrqCfg(VECTOR_NUMBER_SCI5_ERI, _SCIF_PRIORITY_LEVEL2, NULL);
    /* Set SCI5 RXI interrupt priority */
    R_BSP_IrqCfg(VECTOR_NUMBER_SCI5_RXI, _SCIF_PRIORITY_LEVEL2, NULL);
    /* Set SCI5 TXI interrupt priority */
    R_BSP_IrqCfg(VECTOR_NUMBER_SCI5_TXI, _SCIF_PRIORITY_LEVEL2, NULL);
    /* Set SCI5 TEI interrupt priority */
    R_BSP_IrqCfg(VECTOR_NUMBER_SCI5_TEI, _SCIF_PRIORITY_LEVEL2, NULL);

    R_SCI5->CCR0_b.TE = 1U;
    while(1U != R_SCI5->CCR0_b.TE)
    {
      ;
    }    
}




/***********************************************************************************************************************
* Function Name: R_SCI5_Start
* Description  : This function starts SCI5.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCI5_Start(void)
{
    /* Enable TXIF2 ERI interrupt */
    R_BSP_IrqEnable(VECTOR_NUMBER_SCI5_ERI);
    /* Enable RXIF2 RXI interrupt */
    R_BSP_IrqEnable(VECTOR_NUMBER_SCI5_RXI);
    /* Enable BRIF2 TXI interrupt */
    R_BSP_IrqEnable(VECTOR_NUMBER_SCI5_TXI);
    /* Enable DRIF2 TEI interrupt */
    R_BSP_IrqEnable(VECTOR_NUMBER_SCI5_TEI);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
