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
* File Name    : r_cg_systeminit.c
* Version      : 1.00
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Source file of system initializing.
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

#include "hal_data.h"

#include "m_common.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

extern t_motor g_st_m[MOTOR_NUM];

static void ospi_set_DTR_OPI_Mode_enable(void);

/***********************************************************************************************************************
* Function Name: R_Systeminit
* Description  : This function initializes every macro.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Systeminit(void)
{
    DI();
    __asm volatile ("isb");

    for(uint32_t idx = 0; idx < MOTOR_NUM; idx++)
    {
        g_st_m[idx].encoder_type = ETYPE_APE_FACODER;
    }
    /* Set peripheral settings */
    R_IOPORT_Open (&g_ioport_ctrl, &g_bsp_pin_cfg);
    R_IOPORT_PinWrite (&g_ioport_ctrl, 0x805, 1);
    R_ELC_Open(&g_elc_ctrl, &g_elc_cfg);

    R_POEG_Open(&g_poeg0_ctrl, &g_poeg0_cfg);

    R_GPT_THREE_PHASE_Open(&g_three_phase0_ctrl, &g_three_phase0_cfg);
    R_GPT_THREE_PHASE_Open(&g_three_phase1_ctrl, &g_three_phase1_cfg);
    R_GPT_THREE_PHASE_Open(&g_three_phase2_ctrl, &g_three_phase2_cfg);
    R_GPT_THREE_PHASE_Open(&g_three_phase3_ctrl, &g_three_phase3_cfg);
    R_GPT_THREE_PHASE_Open(&g_three_phase4_ctrl, &g_three_phase4_cfg);
    R_GPT_THREE_PHASE_Open(&g_three_phase5_ctrl, &g_three_phase5_cfg);
    R_GPT_THREE_PHASE_Open(&g_three_phase6_ctrl, &g_three_phase6_cfg);
    R_GPT_THREE_PHASE_Open(&g_three_phase7_ctrl, &g_three_phase7_cfg);
    R_GPT_THREE_PHASE_Open(&g_three_phase8_ctrl, &g_three_phase8_cfg);

    if(SW12_4 == 0) /* SW12_4 : ON */
    {
        R_GPT_PeriodSet(g_three_phase0_cfg.p_timer_instance[0]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase0_cfg.p_timer_instance[1]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase0_cfg.p_timer_instance[2]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase1_cfg.p_timer_instance[0]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase1_cfg.p_timer_instance[1]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase1_cfg.p_timer_instance[2]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase2_cfg.p_timer_instance[0]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase2_cfg.p_timer_instance[1]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase2_cfg.p_timer_instance[2]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase3_cfg.p_timer_instance[0]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase3_cfg.p_timer_instance[1]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase3_cfg.p_timer_instance[2]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase4_cfg.p_timer_instance[0]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase4_cfg.p_timer_instance[1]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase4_cfg.p_timer_instance[2]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase5_cfg.p_timer_instance[0]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase5_cfg.p_timer_instance[1]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase5_cfg.p_timer_instance[2]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase6_cfg.p_timer_instance[0]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase6_cfg.p_timer_instance[1]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase6_cfg.p_timer_instance[2]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase7_cfg.p_timer_instance[0]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase7_cfg.p_timer_instance[1]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase7_cfg.p_timer_instance[2]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase8_cfg.p_timer_instance[0]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase8_cfg.p_timer_instance[1]->p_ctrl, 0x61a8);
        R_GPT_PeriodSet(g_three_phase8_cfg.p_timer_instance[2]->p_ctrl, 0x61a8);
    }


    R_GPT00_0->GTIOR_b.OAE = 0;
    R_GPT00_0->GTIOR_b.OBE = 0;
    R_GPT00_1->GTIOR_b.OAE = 0;
    R_GPT00_1->GTIOR_b.OBE = 0;
    R_GPT00_2->GTIOR_b.OAE = 0;
    R_GPT00_2->GTIOR_b.OBE = 0;
    R_GPT01_0->GTIOR_b.OAE = 0;
    R_GPT01_0->GTIOR_b.OBE = 0;
    R_GPT01_1->GTIOR_b.OAE = 0;
    R_GPT01_1->GTIOR_b.OBE = 0;
    R_GPT01_2->GTIOR_b.OAE = 0;
    R_GPT01_2->GTIOR_b.OBE = 0;
    R_GPT02_0->GTIOR_b.OAE = 0;
    R_GPT02_0->GTIOR_b.OBE = 0;
    R_GPT02_1->GTIOR_b.OAE = 0;
    R_GPT02_1->GTIOR_b.OBE = 0;
    R_GPT02_2->GTIOR_b.OAE = 0;
    R_GPT02_2->GTIOR_b.OBE = 0;
    R_GPT03_0->GTIOR_b.OAE = 0;
    R_GPT03_0->GTIOR_b.OBE = 0;
    R_GPT03_1->GTIOR_b.OAE = 0;
    R_GPT03_1->GTIOR_b.OBE = 0;
    R_GPT03_2->GTIOR_b.OAE = 0;
    R_GPT03_2->GTIOR_b.OBE = 0;
    R_GPT04_0->GTIOR_b.OAE = 0;
    R_GPT04_0->GTIOR_b.OBE = 0;
    R_GPT04_1->GTIOR_b.OAE = 0;
    R_GPT04_1->GTIOR_b.OBE = 0;
    R_GPT04_2->GTIOR_b.OAE = 0;
    R_GPT04_2->GTIOR_b.OBE = 0;
    R_GPT05_0->GTIOR_b.OAE = 0;
    R_GPT05_0->GTIOR_b.OBE = 0;
    R_GPT05_1->GTIOR_b.OAE = 0;
    R_GPT05_1->GTIOR_b.OBE = 0;
    R_GPT05_2->GTIOR_b.OAE = 0;
    R_GPT05_2->GTIOR_b.OBE = 0;
    R_GPT06_0->GTIOR_b.OAE = 0;
    R_GPT06_0->GTIOR_b.OBE = 0;
    R_GPT06_1->GTIOR_b.OAE = 0;
    R_GPT06_1->GTIOR_b.OBE = 0;
    R_GPT06_2->GTIOR_b.OAE = 0;
    R_GPT06_2->GTIOR_b.OBE = 0;
    R_GPT07_0->GTIOR_b.OAE = 0;
    R_GPT07_0->GTIOR_b.OBE = 0;
    R_GPT07_1->GTIOR_b.OAE = 0;
    R_GPT07_1->GTIOR_b.OBE = 0;
    R_GPT07_2->GTIOR_b.OAE = 0;
    R_GPT07_2->GTIOR_b.OBE = 0;
    R_GPT08_0->GTIOR_b.OAE = 0;
    R_GPT08_0->GTIOR_b.OBE = 0;
    R_GPT08_1->GTIOR_b.OAE = 0;
    R_GPT08_1->GTIOR_b.OBE = 0;
    R_GPT08_2->GTIOR_b.OAE = 0;
    R_GPT08_2->GTIOR_b.OBE = 0;


    R_RWP_NS->PRCRN = 0x0000A50F;

    R_SYSC_NS->MSTPCRD_b.MSTPCRD00 = 0; // DSMIF Unit 0 Module Stop
    R_SYSC_NS->MSTPCRD_b.MSTPCRD01 = 0; // DSMIF Unit 1 Module Stop
    R_SYSC_NS->MSTPCRD_b.MSTPCRD16 = 0; // DSMIF Unit 2 Module Stop
    R_SYSC_NS->MSTPCRD_b.MSTPCRD17 = 0; // DSMIF Unit 3 Module Stop
    R_SYSC_NS->MSTPCRD_b.MSTPCRD18 = 0; // DSMIF Unit 4 Module Stop
    R_SYSC_NS->MSTPCRD_b.MSTPCRD19 = 0; // DSMIF Unit 5 Module Stop
    R_SYSC_NS->MSTPCRD_b.MSTPCRD20 = 0; // DSMIF Unit 6 Module Stop
    R_SYSC_NS->MSTPCRD_b.MSTPCRD21 = 0; // DSMIF Unit 7 Module Stop
    R_SYSC_NS->MSTPCRD_b.MSTPCRD22 = 0; // DSMIF Unit 8 Module Stop
    R_SYSC_NS->MSTPCRD_b.MSTPCRD23 = 0; // DSMIF Unit 9 Module Stop

    setup_dsm();

    R_GPT_THREE_PHASE_Start(&g_three_phase0_ctrl);
    R_GPT_THREE_PHASE_Start(&g_three_phase1_ctrl);
    R_GPT_THREE_PHASE_Start(&g_three_phase2_ctrl);
    R_GPT_THREE_PHASE_Start(&g_three_phase3_ctrl);
    R_GPT_THREE_PHASE_Start(&g_three_phase4_ctrl);
    R_GPT_THREE_PHASE_Start(&g_three_phase5_ctrl);
    R_GPT_THREE_PHASE_Start(&g_three_phase6_ctrl);
    R_GPT_THREE_PHASE_Start(&g_three_phase7_ctrl);
    R_GPT_THREE_PHASE_Start(&g_three_phase8_ctrl);

    R_SCI_UART_Open(&g_uart0_ctrl, &g_uart0_cfg);
   //printf("motor test,uart open test\n");
    R_SCI5_Create();

#if   defined(__ICCARM__)
    /* Do nothing */
#elif defined(__GNUC__)
    /* Release xSPI unit 0 from reset */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_SYSC_NS->MRCTLA_b.MRCTLA04 = 0;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);
    /* Open the OSPI instance */
  // R_XSPI_OSPI_Open(&g_ospi0_ctrl, &g_ospi0_cfg);
    /* Set DTR-OPI Enable in configuration register 2 (volatile) */
   //ospi_set_DTR_OPI_Mode_enable();
#endif

    EI();
    __asm volatile ("isb");
}

static void ospi_set_DTR_OPI_Mode_enable(void)
{
    /* For following settings, temporary set protocol 1S-1S-1S */
    R_XSPI_OSPI_SpiProtocolSet(&g_ospi0_ctrl, SPI_FLASH_PROTOCOL_1S_1S_1S);

    /*--------------- Write Enable(WE) (06h) ---------------*/
    spi_flash_direct_transfer_t ospi_test_direct_transfer_WE2 = {0};
    ospi_test_direct_transfer_WE2.command        = 0x06U;
    ospi_test_direct_transfer_WE2.command_length = 1U;
    fsp_err_t err = R_XSPI_OSPI_DirectTransfer(&g_ospi0_ctrl, &ospi_test_direct_transfer_WE2, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
    /*--------------------------------------------------*/

    /*--------------- Write Configuraiton register(WRCR2) (72h) ---------------*/
    uint32_t write_data = 0x02; /* Set DTR OPI Enable */
    spi_flash_direct_transfer_t direct_command_WRCR2_2 = {0};
    direct_command_WRCR2_2.command        = 0x72U;
    direct_command_WRCR2_2.address        = 0x00000000U,
    direct_command_WRCR2_2.command_length = 1U;
    direct_command_WRCR2_2.address_length = 4U;
    direct_command_WRCR2_2.data_length    = 1U;
    direct_command_WRCR2_2.data = write_data;

    err = R_XSPI_OSPI_DirectTransfer(&g_ospi0_ctrl, &direct_command_WRCR2_2, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
    /*-----------------------------------------------------------*/

    /* Change protocol settings from 1S-1S-1S to 8D-8D-8D. */
    R_XSPI_OSPI_SpiProtocolSet(&g_ospi0_ctrl, SPI_FLASH_PROTOCOL_8D_8D_8D);

    /*--------------- Write Enable(WE) (06h) ---------------*/
    spi_flash_direct_transfer_t ospi_test_direct_transfer_WE1 = {0};
    ospi_test_direct_transfer_WE1.command        = 0x06F9U;
    ospi_test_direct_transfer_WE1.command_length = 2U;
    err = R_XSPI_OSPI_DirectTransfer(&g_ospi0_ctrl, &ospi_test_direct_transfer_WE1, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
    /*--------------------------------------------------*/

    /*--------------- Write Configuraiton register(WRCR2) (72h) ---------------*/
    write_data = 0x05; /* Set DC[2:0] = 0x05 (Number of Dummy cycle = 10) */
    spi_flash_direct_transfer_t direct_command_WRCR2_1 = {0};
    direct_command_WRCR2_1.command        = 0x728DU;
    direct_command_WRCR2_1.address        = 0x00000300U;
    direct_command_WRCR2_1.command_length = 2U;
    direct_command_WRCR2_1.address_length = 4U;
    direct_command_WRCR2_1.data_length    = 1U;
    direct_command_WRCR2_1.data = write_data;

    err = R_XSPI_OSPI_DirectTransfer(&g_ospi0_ctrl, &direct_command_WRCR2_1, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
    /*-----------------------------------------------------------*/

    /*---------------- Read Configuration register 2(RDCR2) (71h) ---------------*/
    spi_flash_direct_transfer_t direct_command_RDCR2_2 = {0};
    direct_command_RDCR2_2.command        = 0x718EU;
    direct_command_RDCR2_2.address        = 0x00000300U;
    direct_command_RDCR2_2.command_length = 2U;
    direct_command_RDCR2_2.address_length = 4U;
    direct_command_RDCR2_2.data_length    = 1U;
    direct_command_RDCR2_2.dummy_cycles   = 10U;

    err = R_XSPI_OSPI_DirectTransfer(&g_ospi0_ctrl, &direct_command_RDCR2_2, SPI_FLASH_DIRECT_TRANSFER_DIR_READ);
    /*--------------------------------------------------------------*/
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
