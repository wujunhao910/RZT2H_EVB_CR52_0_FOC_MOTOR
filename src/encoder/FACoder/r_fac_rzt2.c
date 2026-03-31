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
* Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* System Name  : FAC Encoder IF
* File Name    : r_fac_rzt2.c
* Version      : 
* Device       : RZ
* Abstract     : FAC Encode IF common source file.
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* H/W Platform : RZ/T2H
* Description  : Encoder IF on RZ devices.
* Limitation   : None
*******************************************************************************/
/*******************************************************************************
* History      : History is managed by Revision Control System.
*******************************************************************************/
/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdio.h>
#include "bsp_api.h"
#include "hal_data.h"
#include "r_scie.h"
#include "r_fac_rzt2_if.h"
#include "r_fac_rzt2_config.h"
#include "r_fac_rzt2_dat.h"
#include "iodefine_fac.h"
/*******************************************************************************
Macro definitions
*******************************************************************************/
/* FA-CODER driver Version */
#define FAC_VERSION             (0x00000007u)   /* Version of Encoder I/F */

#define FAC_CMD_NUM             (4)             /* Number of commands */

/* Index of arrays, number of arrays */
#define RXDF0_INDEX             (0)
#define RXDF1_INDEX             (1)
#define RXDF2_INDEX             (2)
#define RXDF3_INDEX             (3)
#define RXDF4_INDEX             (4)
#define RXDF5_INDEX             (5)
#define RXDF6_INDEX             (6)
#define RXDF7_INDEX             (7)

/* Boundary of ID and DFNUM and ADF */
#define REQ_ID_MAX              (15)
#define REQ_DFNUM_MIN           (1)
#define REQ_DFNUM_MAX           (FAC_RXDF_MAX)
#define FAC_RXDF_MAX            (8)

/* Baudrate parameter for setting */
#define FAC_BRATE_2500KBPS      (2500000)
#define FAC_BRATE_5MBPS         (5000000)

#define FAC_DEAST_VAL           (3)
#define FAC_DENGT_VAL           (3)

#define FAC_ELC_EMULATE         FAC_ELC_DISABLE
#define FAC_ELC_DISABLE         (0)  /* disable emulation */
#define FAC_ELC_ENABLE_CPU      (1)  /* enable by CPU */
#define FAC_ELC_ENABLE_DMA      (2)  /* enable by CPU and DMA */

/** SCI CSR register receiver error bit masks */
#define FAC_SCI_CSR_ORER        (R_SCI0_CSR_ORER_Msk)
#define FAC_SCI_CSR_FER         (R_SCI0_CSR_FER_Msk)
#define FAC_SCI_CSR_ORER_Pos    (R_SCI0_CSR_ORER_Pos)
#define FAC_SCI_CSR_FER_Pos     (R_SCI0_CSR_FER_Pos)
#define FAC_SCI_RCVR_ERR        (FAC_SCI_CSR_ORER | FAC_SCI_CSR_FER)

/** SCI CFCLR register receiver clear error bit masks */
#define FAC_SCI_CFCLR_ORERC     (R_SCI0_OFCLR_ORERC_Msk)
#define FAC_SCI_CFCLR_FERC      (R_SCI0_OFCLR_FERC_Msk)
#define FAC_SCI_RCVR_ERRCLR     (FAC_SCI_CFCLR_ORERC | FAC_SCI_CFCLR_FERC)
#define FAC_SCI_CFCLR_ALL       (0xBD070010)

#define VECTOR_NUMBER_GPT0_OVF  VECTOR_NUMBER_GPT00_0_INT0
//#define VECTOR_NUMBER_GPT1_OVF  VECTOR_NUMBER_GPT00_1_INT0

#define TZC_400_8_BASE_ADDRESS              (0x81108000UL)      /* TZC-400-8: Cortex-R52 CPU0,1 AXIS (TCM) */
#define TZC_400_REGION_ATTRIBUTES_0_OFFSET  (0x00000110UL)
#define TZC_400_REGION_ID_ACCESS_0_OFFSET   (0x00000114UL)
#define TZC_400_GATE_KEEPER_OFFSET          (0x00000008UL)
#define TZC_400_SPECULATION_CTRL_OFFSET     (0x0000000CUL)
#define TZC_400_REGION_ATTRIBUTES_0_INIT    (0x0000000FUL)      /* [3:0] filter_en: Filter 0-3 enables */
#define TZC_400_REGION_ID_ACCESS_0_INIT     (0x0000000FUL)      /* [31:16] nsaid_wr_en: NSAID 0-15 write enables 
                                                                 * [15:0] nsaid_rd_en:  NSAID 0-15 read enables */
#define TZC_400_GATE_KEEPER_INIT            (0x0000000FUL)      /* [3:0] open_request = 0xF */
#define TZC_400_SPECULATION_CTRL_INIT       (0x00000003UL)      /* [1] write_spec_disable: Disables write access speculation.
                                                                 * [0] read_spec_disable: Disables read access speculation. */

#define PCLKMHZ                 (500u)
#define PCLK_IN50NS             (PCLKMHZ/20u)
#define PARAMETER_NOT_USED(p)   (void)((p))

/*******************************************************************************
Typedef definitions
*******************************************************************************/
typedef r_fac_err_t (*r_fac_control_func_t)(const int32_t fac_no, void *const pbuf);

/* State of FA-CODER */
typedef enum fac_state_e
{
    FAC_STATE_STOP = 0,
    FAC_STATE_IDLE,
    FAC_STATE_REQ,
    FAC_STATE_E2PROM,
    FAC_STATE_ELC
} fac_state_t;

/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/
extern gpt_instance_ctrl_t g_timer1_ctrl;

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/
/* FAC base address */
R_SCI0_Type* const pfac_base_addr_tbl[FAC_ID_NUM] =
{   R_SCIE0,   R_SCIE1,   R_SCIE2,   R_SCIE3,
    R_SCIE4,   R_SCIE5,   R_SCIE6,   R_SCIE7,
    R_SCIE8,   R_SCIE9,   R_SCIE10,  R_SCIE11
};

/*******************************************************************************
Private variables and functions
*******************************************************************************/
static uint32_t fac_id_to_index(const int32_t id);
static uint32_t fac_cmd_to_index(r_fac_cmd_t cmd);
static r_fac_err_t fac_req(const int32_t fac_no, void *const pbuf);
static r_fac_err_t fac_e2prom(const int32_t fac_no, void *const pbuf);
static r_fac_err_t fac_elctimer(const int32_t fac_no, void *const pbuf);
static r_fac_err_t fac_elcstop(const int32_t fac_no, void *const pbuf);
static uint32_t fac_data_check(const uint32_t fac_index, const uint32_t csr, const uint32_t timeout);
static void fac_set_result(const uint32_t fac_index, const uint32_t csr, const uint32_t timeout);
void fac_eri_isr_common(const uint32_t fac_index);
void fac_rxi_isr_common(const uint32_t fac_index);
void fac_txi_isr_common(const uint32_t fac_index);
void fac_tei_isr_common(const uint32_t fac_index);
void user_fac_callback (scie_callback_args_t * p_args);

/* Configurations of encoder */
static const int32_t fac_id_tbl[FAC_ID_NUM] =
{
    R_FAC0_ID,  R_FAC1_ID,  R_FAC2_ID,  R_FAC3_ID,
    R_FAC4_ID,  R_FAC5_ID,  R_FAC6_ID,  R_FAC7_ID,
    R_FAC8_ID,  R_FAC9_ID,  R_FAC10_ID, R_FAC11_ID
};

/* Commands of R_FAC_Control */
static const r_fac_cmd_t fac_cmd_tbl[FAC_CMD_NUM] =
{
    R_FAC_CMD_REQ, R_FAC_CMD_E2PROM, R_FAC_CMD_ELCTIMER, R_FAC_CMD_ELCSTOP
};

/* Functions fo R_FAC_Control commands (NULL: There is no command for the encoder) */
static const r_fac_control_func_t fac_control_func_tbl[FAC_CMD_NUM] =
{
    &fac_req, &fac_e2prom, &fac_elctimer, &fac_elcstop
};

static fac_state_t fac_state[FAC_ID_NUM] =
{
    FAC_STATE_STOP
};

//static uint32_t fac_isr_id[FAC_ID_NUM];
static r_fac_req_result_cb_t pfac_req_result_cb[FAC_ID_NUM] =
{
    NULL
};
static r_fac_e2prom_result_cb_t pfac_e2prom_result_cb[FAC_ID_NUM] =
{
    NULL
};

/* Baudrate parameter for setting */
static const uint32_t fac_brate_tbl[R_FAC_BITRATE_NUM] =
{
    FAC_BRATE_2500KBPS,
    FAC_BRATE_5MBPS
};

scie_instance_ctrl_t g_fac_ctrl[FAC_ID_NUM];
scie_baud_setting_t g_fac_baud_setting =  // settings for 96MHz SCIE clock
{   .baudrate_bits_b.abcse = 1,
    .baudrate_bits_b.abcs = 0,
    .baudrate_bits_b.bgdm = 0,
    .baudrate_bits_b.cks = 0,
    .baudrate_bits_b.brr = 4,
    .baudrate_bits_b.mddr = 200,
    .baudrate_bits_b.brme = true
};

const scie_extended_cfg_t g_fac_cfg_extend =
{   .clock = SCIE_CLOCK_INT,
    .rx_edge_start = SCIE_START_BIT_FALLING_EDGE,
    .noise_cancel = SCIE_NOISE_CANCELLATION_DISABLE,
    .p_baud_setting = &g_fac_baud_setting,
    .ctsrts_en = SCIE_CTSRTS_RTS_OUTPUT,
    .sync_bypass = SCIE_SYNCHRONIZER_NOT_BYPASS,
};

const scie_cfg_t g_fac_cfg[FAC_ID_NUM] =
{ { .channel = 0, .data_bits = SCIE_DATA_BITS_8, .parity = SCIE_PARITY_OFF, .stop_bits = SCIE_STOP_BITS_1,
    .p_callback =  user_fac_callback,
    .p_context = NULL,
    .p_extend = &g_fac_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = (12), .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
    .rxi_irq = ENCIF00_INT1_IRQn,
    .txi_irq = ENCIF00_INT2_IRQn,
    .tei_irq = ENCIF00_INT3_IRQn,
    .eri_irq = ENCIF00_INT0_IRQn },
  { .channel = 1, .data_bits = SCIE_DATA_BITS_8, .parity = SCIE_PARITY_OFF, .stop_bits = SCIE_STOP_BITS_1,
    .p_callback =  user_fac_callback,
    .p_context = NULL,
    .p_extend = &g_fac_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = (12), .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
    .rxi_irq = ENCIF01_INT1_IRQn,
    .txi_irq = ENCIF01_INT2_IRQn,
    .tei_irq = ENCIF01_INT3_IRQn,
    .eri_irq = ENCIF01_INT0_IRQn },
  { .channel = 2, .data_bits = SCIE_DATA_BITS_8, .parity = SCIE_PARITY_OFF, .stop_bits = SCIE_STOP_BITS_1,
    .p_callback =  user_fac_callback,
    .p_context = NULL,
    .p_extend = &g_fac_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = (12), .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
    .rxi_irq = ENCIF02_INT1_IRQn,
    .txi_irq = ENCIF02_INT2_IRQn,
    .tei_irq = ENCIF02_INT3_IRQn,
    .eri_irq = ENCIF02_INT0_IRQn },
  { .channel = 3, .data_bits = SCIE_DATA_BITS_8, .parity = SCIE_PARITY_OFF, .stop_bits = SCIE_STOP_BITS_1,
    .p_callback =  user_fac_callback,
    .p_context = NULL,
    .p_extend = &g_fac_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = (12), .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
    .rxi_irq = ENCIF03_INT1_IRQn,
    .txi_irq = ENCIF03_INT2_IRQn,
    .tei_irq = ENCIF03_INT3_IRQn,
    .eri_irq = ENCIF03_INT0_IRQn },
  { .channel = 4, .data_bits = SCIE_DATA_BITS_8, .parity = SCIE_PARITY_OFF, .stop_bits = SCIE_STOP_BITS_1,
    .p_callback =  user_fac_callback,
    .p_context = NULL,
    .p_extend = &g_fac_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = (12), .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
    .rxi_irq = ENCIF04_INT1_IRQn,
    .txi_irq = ENCIF04_INT2_IRQn,
    .tei_irq = ENCIF04_INT3_IRQn,
    .eri_irq = ENCIF04_INT0_IRQn },
  { .channel = 5, .data_bits = SCIE_DATA_BITS_8, .parity = SCIE_PARITY_OFF, .stop_bits = SCIE_STOP_BITS_1,
    .p_callback =  user_fac_callback,
    .p_context = NULL,
    .p_extend = &g_fac_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = (12), .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
    .rxi_irq = ENCIF05_INT1_IRQn,
    .txi_irq = ENCIF05_INT2_IRQn,
    .tei_irq = ENCIF05_INT3_IRQn,
    .eri_irq = ENCIF05_INT0_IRQn },
  { .channel = 6, .data_bits = SCIE_DATA_BITS_8, .parity = SCIE_PARITY_OFF, .stop_bits = SCIE_STOP_BITS_1,
    .p_callback =  user_fac_callback,
    .p_context = NULL,
    .p_extend = &g_fac_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = (12), .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
    .rxi_irq = ENCIF06_INT1_IRQn,
    .txi_irq = ENCIF06_INT2_IRQn,
    .tei_irq = ENCIF06_INT3_IRQn,
    .eri_irq = ENCIF06_INT0_IRQn },
  { .channel = 7, .data_bits = SCIE_DATA_BITS_8, .parity = SCIE_PARITY_OFF, .stop_bits = SCIE_STOP_BITS_1,
    .p_callback =  user_fac_callback,
    .p_context = NULL,
    .p_extend = &g_fac_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = (12), .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
    .rxi_irq = ENCIF07_INT1_IRQn,
    .txi_irq = ENCIF07_INT2_IRQn,
    .tei_irq = ENCIF07_INT3_IRQn,
    .eri_irq = ENCIF07_INT0_IRQn },
  { .channel = 8, .data_bits = SCIE_DATA_BITS_8, .parity = SCIE_PARITY_OFF, .stop_bits = SCIE_STOP_BITS_1,
    .p_callback =  user_fac_callback,
    .p_context = NULL,
    .p_extend = &g_fac_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = (12), .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
    .rxi_irq = ENCIF08_INT1_IRQn,
    .txi_irq = ENCIF08_INT2_IRQn,
    .tei_irq = ENCIF08_INT3_IRQn,
    .eri_irq = ENCIF08_INT0_IRQn },
#if 0
  { .channel = 9, .data_bits = SCIE_DATA_BITS_8, .parity = SCIE_PARITY_OFF, .stop_bits = SCIE_STOP_BITS_1,
    .p_callback =  user_fac_callback,
    .p_context = NULL,
    .p_extend = &g_fac_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = (12), .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
    .rxi_irq = VECTOR_NUMBER_ENCIF09_INT1,
    .txi_irq = VECTOR_NUMBER_ENCIF09_INT2,
    .tei_irq = VECTOR_NUMBER_ENCIF09_INT3,
    .eri_irq = VECTOR_NUMBER_ENCIF09_INT0 },
  { .channel = 10, .data_bits = SCIE_DATA_BITS_8, .parity = SCIE_PARITY_OFF, .stop_bits = SCIE_STOP_BITS_1,
    .p_callback =  user_fac_callback,
    .p_context = NULL,
    .p_extend = &g_fac_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = (12), .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
    .rxi_irq = VECTOR_NUMBER_ENCIF10_INT1,
    .txi_irq = VECTOR_NUMBER_ENCIF10_INT2,
    .tei_irq = VECTOR_NUMBER_ENCIF10_INT3,
    .eri_irq = VECTOR_NUMBER_ENCIF10_INT0 },
  { .channel = 11, .data_bits = SCIE_DATA_BITS_8, .parity = SCIE_PARITY_OFF, .stop_bits = SCIE_STOP_BITS_1,
    .p_callback =  user_fac_callback,
    .p_context = NULL,
    .p_extend = &g_fac_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = (12), .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
    .rxi_irq = VECTOR_NUMBER_ENCIF11_INT1,
    .txi_irq = VECTOR_NUMBER_ENCIF11_INT2,
    .tei_irq = VECTOR_NUMBER_ENCIF11_INT3,
    .eri_irq = VECTOR_NUMBER_ENCIF11_INT0 }
#endif
};

const uint8_t fac_com_tbl[REQ_ID_MAX] =
{ 0x02, 0x8A, 0x92, 0x1A, 0xA2, 0x2A, 0x32, 0xBA,
  0xC2, 0x4A, 0x52, 0xDA, 0x62, 0xEA, 0xF2 };

static int16_t fac_recv_buff_index[FAC_ID_NUM];
static int16_t fac_send_buff_index[FAC_ID_NUM];
static int16_t fac_recv_bytes[FAC_ID_NUM];
static int16_t fac_send_bytes[FAC_ID_NUM];
static uint32_t fac_recv_buff[FAC_ID_NUM][32];
static uint8_t fac_send_buff[FAC_ID_NUM][4];
static r_fac_result_t fac_rx_result[FAC_ID_NUM];
static uint8_t rxdf[FAC_ID_NUM][FAC_RXDF_MAX];
#if FAC_ELC_EMULATE == FAC_ELC_ENABLE_DMA
static uint32_t fac_ccr0_trig[FAC_ID_NUM];
#endif

/*******************************************************************************
* Function Name: R_FAC_Open
* Description  : Open encode IF.
* Arguments    : id - encoder ID.
*                pinfo - information of encoder.
* Return Value : Error code.
*******************************************************************************/
r_fac_err_t R_FAC_Open(const int32_t id, const r_fac_info_t* pinfo)
{
    r_fac_err_t result = R_FAC_SUCCESS;
    uint32_t id_index;
    scie_baud_setting_t *p_baud_setting;
    uint32_t baud_rate;
    bool enable_bitrate_modulation;
    uint32_t error_rate_x_1000;
    fsp_err_t err;
#if FAC_ELC_EMULATE == FAC_ELC_ENABLE_DMA
    uint32_t *p_reg;
#endif
    uint32_t i;

    /* check index */
    id_index = fac_id_to_index(id);
    if (FAC_ID_NUM <= id_index)
    {
        goto error_invalid_arg;
    }

    if (FAC_STATE_STOP != fac_state[id_index])
    {
        goto error_already_open;
    }

    R_SCIE_Open(&g_fac_ctrl[id_index], &g_fac_cfg[id_index]);
    R_FAC_SCI(id_index)->CCR0_b.RE = 0;
    p_baud_setting = ((scie_extended_cfg_t *)g_fac_cfg[id_index].p_extend)->p_baud_setting;
    baud_rate = fac_brate_tbl[pinfo->bitrate];
    enable_bitrate_modulation = true;
    error_rate_x_1000 = 100;
    err = R_SCIE_BaudCalculate(baud_rate, enable_bitrate_modulation, error_rate_x_1000, p_baud_setting);
    if (err){
        goto error_invalid_arg;
    }
    err = R_SCIE_BaudSet(&g_fac_ctrl[id_index], (void *) p_baud_setting);
    if (err){
        goto error_invalid_arg;
    }
#if FAC_ELC_EMULATE == FAC_ELC_ENABLE_DMA
    err = R_DMAC_Open(&g_transfer0_ctrl, &g_transfer0_cfg);
    if (err){
        goto error_invalid_arg;
    }
#if defined(BSP_CFG_CORE_CR52)
    /* TZC-400-8(Cortex-R52 CPU0 AXIS (TCM)) settings */
    p_reg = (uint32_t *)(TZC_400_8_BASE_ADDRESS + TZC_400_REGION_ATTRIBUTES_0_OFFSET);
    *p_reg = TZC_400_REGION_ATTRIBUTES_0_INIT;
    p_reg = (uint32_t *)(TZC_400_8_BASE_ADDRESS + TZC_400_REGION_ID_ACCESS_0_OFFSET);
    *p_reg = TZC_400_REGION_ID_ACCESS_0_INIT;
    p_reg = (uint32_t *)(TZC_400_8_BASE_ADDRESS + TZC_400_GATE_KEEPER_OFFSET);
    *p_reg = TZC_400_GATE_KEEPER_INIT;
    p_reg = (uint32_t *)(TZC_400_8_BASE_ADDRESS + TZC_400_SPECULATION_CTRL_OFFSET);
    *p_reg = TZC_400_SPECULATION_CTRL_INIT;
#endif
#endif
    R_FAC_SCI(id_index)->CCR3_b.DEN = 1;
    R_FAC_SCI(id_index)->DCR_b.DEAST = FAC_DEAST_VAL;
    R_FAC_SCI(id_index)->DCR_b.DENGT = FAC_DENGT_VAL;
    
    for (i = 0; i < FAC_ID_NUM; i++){
        if (fac_state[i] != FAC_STATE_STOP){
            break;
        }
    }
    if (i >= FAC_ID_NUM)  /* Timers are shared by FAC channels */
    {
//        R_BSP_IrqDisable(VECTOR_NUMBER_GPT1_OVF);
//        R_BSP_IrqCfg(VECTOR_NUMBER_GPT1_OVF, 11, NULL);
//        R_BSP_IrqEnable(VECTOR_NUMBER_GPT1_OVF);
#if FAC_ELC_EMULATE == FAC_ELC_ENABLE_CPU
        R_BSP_IrqDisable(VECTOR_NUMBER_GPT0_OVF);
        R_BSP_IrqCfg(VECTOR_NUMBER_GPT0_OVF, 11, NULL);
        R_BSP_IrqEnable(VECTOR_NUMBER_GPT0_OVF);
#endif
    }

    fac_state[id_index] = FAC_STATE_IDLE;

    goto func_end;
    
error_already_open:
    result = R_FAC_ERR_ACCESS;
    goto func_end;
    
error_invalid_arg:
    result = R_FAC_ERR_INVALID_ARG;
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function R_FAC_Open
*******************************************************************************/

/*******************************************************************************
* Function Name: R_FAC_Close
* Description  : Close encode IF.
* Arguments    : id - Encoder id.
* Return Value : Error code.
*******************************************************************************/
r_fac_err_t R_FAC_Close(const int32_t id)
{
    r_fac_err_t result = R_FAC_SUCCESS;
    uint32_t id_index;

    /* check index */
    id_index = fac_id_to_index(id);
    if (FAC_ID_NUM <= id_index)
    {
        goto error_invalid_arg;
    }

    switch(fac_state[id_index])
    {
        case FAC_STATE_STOP:

            /* Do Nothing */
        break;
        case FAC_STATE_IDLE:

            /* Stop encoder. */
            R_SCIE_Close(&g_fac_ctrl[id_index]);

            /* set FA-CODER Status */
            fac_state[id_index] = FAC_STATE_STOP;
        break;
        case FAC_STATE_E2PROM:
        case FAC_STATE_REQ:
            result = R_FAC_ERR_BUSY;
        break;
        default:
            result = R_FAC_ERR_ACCESS;
        break;
    }
    goto func_end;

error_invalid_arg:
    result = R_FAC_ERR_INVALID_ARG;
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function R_FAC_Close
*******************************************************************************/

/*******************************************************************************
* Function Name: R_FAC_Control
* Description  : Control command for encode IF.
* Arguments    : id - encoder ID.
*                cmd - Command.
*                pbuf - Address of buffer.
* Return Value : Error code.
*******************************************************************************/
r_fac_err_t R_FAC_Control(const int32_t id, const r_fac_cmd_t cmd, void *const pbuf)
{
    r_fac_err_t result = R_FAC_SUCCESS;
    uint32_t cmd_index;
    uint32_t id_index;

    /* check index */
    id_index = fac_id_to_index(id);
    if (FAC_ID_NUM <= id_index)
    {
        goto error_invalid_arg;
    }
    
    if (FAC_STATE_STOP == fac_state[id_index])
    {
        goto error_not_open;
    }
    else
    {
        /* Do Noting */
    }

    /* Search for function executing the command. */
    cmd_index = fac_cmd_to_index(cmd);
    if (FAC_CMD_NUM <= cmd_index)
    {
        goto error_invalid_arg;
    }

    /* check command */
    if (NULL == fac_control_func_tbl[cmd_index])
    {
        goto error_invalid_arg;
    }

    /* Execute command. */
    result = fac_control_func_tbl[cmd_index]((int32_t)id_index, pbuf);
    
    goto func_end;
    
error_not_open:
    result = R_FAC_ERR_ACCESS;
    goto func_end;

error_invalid_arg:
    result = R_FAC_ERR_INVALID_ARG;
    goto func_end;
    
func_end:
    return result;
}
/*******************************************************************************
 End of function R_FAC_Control
*******************************************************************************/

/*******************************************************************************
* Function Name: R_FAC_GetVersion
* Description  : Get version of encoder IF.
* Arguments    : None.
* Return Value : Version of encoder IF.
*******************************************************************************/
uint32_t R_FAC_GetVersion(void)
{
    return FAC_VERSION;
}
/*******************************************************************************
End of function R_FAC_GetVersion
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_id_to_index
* Description  : Get fac_no of encoder IF configuration.
* Arguments    : id - encoder ID.
* Return Value : Index of encoder IF.
*******************************************************************************/
static uint32_t fac_id_to_index(const int32_t id)
{
    uint32_t fac_no;

    for (fac_no = 0; fac_no < FAC_ID_NUM; fac_no++)
    {
        if (id == fac_id_tbl[fac_no])
        {
            break;
        }
    }

    return fac_no;
}
/*******************************************************************************
End of function fac_id_to_index
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_cmd_to_index
* Description  : Get index of command.
* Arguments    : cmd - Command.
* Return Value : Index of command.
*******************************************************************************/
static uint32_t fac_cmd_to_index(r_fac_cmd_t cmd)
{
    uint32_t index;

    for (index = 0; index < FAC_CMD_NUM; index++)
    {
        if (cmd == fac_cmd_tbl[index])
        {
            break;
        }
    }

    return index;
}
/*******************************************************************************
End of function fac_cmd_to_index
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_req
* Description  : Send request to FA-CODER driver.
* Arguments    : fac_no - encoder number.
*                pbuf - Buffer address.
* Return Value : Error code.
*******************************************************************************/
static r_fac_err_t fac_req(const int32_t fac_no, void *const pbuf)
{
    r_fac_err_t result = R_FAC_SUCCESS;
    r_fac_req_t * pfac_req = pbuf;
    uint8_t fac_id;
    uint32_t ccr0_reg;
    uint32_t count;
    
    if (NULL == pfac_req)
    {
        goto error_invalid_arg;
    }
    
    fac_id = pfac_req->txid;
    
    /* check upper limit of ID. */
    if (REQ_ID_MAX < fac_id)
    {
        goto error_invalid_arg;
    }
    
    /* check range of data field number. */
    if ((REQ_DFNUM_MIN > pfac_req->dfnum)
        || (REQ_DFNUM_MAX < pfac_req->dfnum))
    {
        goto error_invalid_arg;
    }
    
    switch ((int32_t)fac_state[fac_no])
    {
        case (int32_t)FAC_STATE_IDLE:

            /* set address for callback function */
            pfac_req_result_cb[fac_no] = pfac_req->presult_cb;

            /* set state of control to request */
            fac_state[fac_no] = FAC_STATE_REQ;

            fac_send_buff[fac_no][0] = fac_com_tbl[fac_id];
            fac_send_bytes[fac_no] = 1;
            fac_send_buff_index[fac_no] = 0;
            fac_recv_bytes[fac_no] = (int16_t)(pfac_req->dfnum + 3);
            fac_recv_buff_index[fac_no] = 0;

            /* set timeout */
            count = pfac_req->timotn * PCLK_IN50NS; // 
//            R_GPT_PeriodSet(&g_timer1_ctrl, count);

            ccr0_reg = R_FAC_SCI(fac_no)->CCR0;
            ccr0_reg &= ~0x00310011u;  // set TEIE = 0, TIE = 0, RIE = 0, TE = 0, RE = 0
            R_FAC_SCI(fac_no)->CCR0 = ccr0_reg;
            R_FAC_SCI(fac_no)->CFCLR = FAC_SCI_CFCLR_ALL;
            ccr0_reg |=  0x00100010u;  // set TIE = 1, TE = 1
            R_FAC_SCI(fac_no)->CCR0 = ccr0_reg;

        break;
        case (int32_t)FAC_STATE_REQ:
        case (int32_t)FAC_STATE_E2PROM:
        case (int32_t)FAC_STATE_ELC:
            result = R_FAC_ERR_BUSY;
        break;
        default:
            result = R_FAC_ERR_ACCESS;
        break;
    }
    
    goto func_end;
    
error_invalid_arg:
    result = R_FAC_ERR_INVALID_ARG;
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function fac_req
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_e2prom
* Description  : Access E2PROM of FA-CODER.
* Arguments    : fac_no - encoder number.
*                pbuf - Buffer address.
* Return Value : Error code.
*******************************************************************************/
static r_fac_err_t fac_e2prom(const int32_t fac_no, void *const pbuf)
{
    r_fac_err_t result = R_FAC_SUCCESS;
    r_fac_e2prom_data_t * pfac_e2prom = pbuf;
    uint32_t ccr0_reg;
    
    if (NULL == pfac_e2prom)
    {
        goto error_invalid_arg;
    }
    
    if ((R_FAC_E2PROM_READ != pfac_e2prom->dir) && (R_FAC_E2PROM_WRITE != pfac_e2prom->dir))
    {
        goto error_invalid_arg;
    }
    
    switch ((int32_t)fac_state[fac_no])
    {
        case (int32_t)FAC_STATE_IDLE:

            /* set address for callback function */
            pfac_e2prom_result_cb[fac_no] = pfac_e2prom->presult_cb;

            /* set state of control to e2prom */
            fac_state[fac_no] = FAC_STATE_E2PROM;

            if (R_FAC_E2PROM_READ == pfac_e2prom->dir)
            {
                fac_send_buff[fac_no][0] = fac_com_tbl[R_FAC_TX_ID_E2PROM_R];
                fac_send_buff[fac_no][1] = (uint8_t)pfac_e2prom->adr;
                fac_send_buff[fac_no][2] = fac_send_buff[fac_no][0] ^ fac_send_buff[fac_no][1];
                fac_send_bytes[fac_no] = 3;
                fac_recv_bytes[fac_no] = 4;
            }
            else
            {
                fac_send_buff[fac_no][0] = fac_com_tbl[R_FAC_TX_ID_E2PROM_W];
                fac_send_buff[fac_no][1] = (uint8_t)pfac_e2prom->adr;
                fac_send_buff[fac_no][2] = (uint8_t)pfac_e2prom->data;
                fac_send_buff[fac_no][3] =   fac_send_buff[fac_no][0]
                                           ^ fac_send_buff[fac_no][1] ^ fac_send_buff[fac_no][2];
                fac_send_bytes[fac_no] = 4;
                fac_recv_bytes[fac_no] = 4;
            }
            fac_send_buff_index[fac_no] = 0;
            fac_recv_buff_index[fac_no] = 0;
            ccr0_reg = R_FAC_SCI(fac_no)->CCR0;
            ccr0_reg &= ~0x00310011u;  // set TEIE = 0, TIE = 0, RIE = 0, TE = 0, RE = 0
            R_FAC_SCI(fac_no)->CCR0 = ccr0_reg;
            R_FAC_SCI(fac_no)->CFCLR = FAC_SCI_CFCLR_ALL;
            ccr0_reg |=  0x00100010u;  // set TIE = 1, TE = 1
            R_FAC_SCI(fac_no)->CCR0 = ccr0_reg;

        break;
        case (int32_t)FAC_STATE_REQ:
        case (int32_t)FAC_STATE_E2PROM:
        case (int32_t)FAC_STATE_ELC:
            result = R_FAC_ERR_BUSY;
        break;
        default:
            result = R_FAC_ERR_ACCESS;
        break;
    }
    
    goto func_end;
    
error_invalid_arg:
    result = R_FAC_ERR_INVALID_ARG;
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function fac_e2prom
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_elctimer
* Description  : Send elctimer request to FA-CODER driver.
* Arguments    : fac_no - encoder number.
*                pbuf - Buffer address.
* Return Value : Error code.
*******************************************************************************/
static r_fac_err_t fac_elctimer(const int32_t fac_no, void *const pbuf)
{
    r_fac_err_t result = R_FAC_SUCCESS;
    r_fac_req_t * pfac_req = pbuf;
    uint8_t fac_id;
#if FAC_ELC_EMULATE != FAC_ELC_DISABLE
    uint32_t ccr0_reg;
    uint32_t count;
#endif
    
    if (NULL == pfac_req)
    {
        goto error_invalid_arg;
    }
    
    fac_id = pfac_req->txid;
    
    /* check upper limit of ID. */
    if (REQ_ID_MAX < fac_id)
    {
        goto error_invalid_arg;
    }
    
    /* check range of data field number. */
    if ((REQ_DFNUM_MIN > pfac_req->dfnum)
        || (REQ_DFNUM_MAX < pfac_req->dfnum))
    {
        goto error_invalid_arg;
    }
    
    switch ((int32_t)fac_state[fac_no])
    {
        case (int32_t)FAC_STATE_IDLE:

#if FAC_ELC_EMULATE != FAC_ELC_DISABLE
            /* set address for callback function */
            pfac_req_result_cb[fac_no] = pfac_req->presult_cb;

            /* set state of control to request */
            fac_state[fac_no] = FAC_STATE_ELC;

            fac_send_buff[fac_no][0] = fac_com_tbl[fac_id];
            fac_send_bytes[fac_no] = 1;
            fac_send_buff_index[fac_no] = 0;
            fac_recv_bytes[fac_no] = (int16_t)(pfac_req->dfnum + 3);
            fac_recv_buff_index[fac_no] = 0;

            /* set timeout */
            count = pfac_req->timotn * PCLK_IN50NS; // 
            R_GPT_PeriodSet(&g_timer1_ctrl, count);

            ccr0_reg = R_FAC_SCI(fac_no)->CCR0;
            ccr0_reg &= ~0x00310011u;  // set TEIE = 0, TIE = 0, RIE = 0, TE = 0, RE = 0
            R_FAC_SCI(fac_no)->CCR0 = ccr0_reg;
            R_FAC_SCI(fac_no)->CFCLR = FAC_SCI_CFCLR_ALL;

#if FAC_ELC_EMULATE == FAC_ELC_ENABLE_DMA
            /* set DMAC transferring data and addresses */
            fac_ccr0_trig[fac_no] = ccr0_reg | 0x00100010u;  // set TIE = 1, TE = 1
            g_transfer0_cfg.p_info->p_src  = (void *)&fac_ccr0_trig[fac_no];
            g_transfer0_cfg.p_info->p_dest = (void *)&R_FAC_SCI(fac_no)->CCR0;
            R_DMAC_Reconfigure(&g_transfer0_ctrl, g_transfer0_cfg.p_info);
            R_DMAC_Enable(&g_transfer0_ctrl);
#endif

#else  /* FAC_ELC_EMULATE == FAC_ELC_DISABLE */
            result = R_FAC_ERR_INVALID_ARG;
#endif
        break;
        case (int32_t)FAC_STATE_REQ:
        case (int32_t)FAC_STATE_E2PROM:
        case (int32_t)FAC_STATE_ELC:
            result = R_FAC_ERR_BUSY;
        break;
        default:
            result = R_FAC_ERR_ACCESS;
        break;
    }
    
    goto func_end;
    
error_invalid_arg:
    result = R_FAC_ERR_INVALID_ARG;
    goto func_end;

func_end:
    return result;
}
/*******************************************************************************
End of function fac_elctimer
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_elcstop
* Description  : Send elcstop to FA-CODER driver.
* Arguments    : fac_no - encoder number.
*                pbuf - Buffer address.
* Return Value : Error code.
*******************************************************************************/
static r_fac_err_t fac_elcstop(const int32_t fac_no, void *const pbuf)
{
    uint32_t ccr0_reg;
    PARAMETER_NOT_USED(pbuf);
    r_fac_err_t result = R_FAC_SUCCESS;
    
    switch ((int32_t)fac_state[fac_no])
    {
        case (int32_t)FAC_STATE_ELC:

#if FAC_ELC_EMULATE == FAC_ELC_ENABLE_DMA
            R_DMAC_Disable(&g_transfer0_ctrl);
#endif
            /* clear address for callback function */
            pfac_req_result_cb[fac_no] = NULL;

            /* set state of control to request */
            fac_state[fac_no] = FAC_STATE_IDLE;

            ccr0_reg = R_FAC_SCI(fac_no)->CCR0;
            ccr0_reg &= ~0x00310011u;  // set TEIE = 0, TIE = 0, RIE = 0, TE = 0, RE = 0
            R_FAC_SCI(fac_no)->CCR0 = ccr0_reg;

        break;
        case (int32_t)FAC_STATE_IDLE:
        case (int32_t)FAC_STATE_REQ:
        case (int32_t)FAC_STATE_E2PROM:
        default:
            result = R_FAC_ERR_ACCESS;
        break;
    }
    
    goto func_end;
    
func_end:
    return result;
}
/*******************************************************************************
End of function fac_elcstop
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_data_check
* Description  : Set result of register access.
* Arguments    : fac_index - ch number.
*                csr - common status.
*                timeout - timeout flag.
* Return Value : Error code.
*******************************************************************************/
static uint32_t fac_data_check(const uint32_t fac_index, const uint32_t csr, const uint32_t timeout)
{
    uint32_t rxresult;
    int16_t fac_485_reqnum;
    int16_t e2prom_com;
    uint8_t s_cf, s_adf, s_edf, r_cf, r_sf, r_adf, r_edf, r_crc, crc;

    fac_485_reqnum = (int16_t)(fac_recv_bytes[fac_index] - 1);
    //fac_485_reqnum = (int16_t)(fac_recv_bytes[fac_index]);
    
    if (fac_send_buff[fac_index][0] == fac_com_tbl[R_FAC_TX_ID_E2PROM_R])
    {
        e2prom_com = R_FAC_TX_ID_E2PROM_R;
        rxdf[fac_index][RXDF0_INDEX] = (uint8_t)fac_recv_buff[fac_index][1];
        rxdf[fac_index][RXDF1_INDEX] = (uint8_t)fac_recv_buff[fac_index][2];
    }
    else if (fac_send_buff[fac_index][0] == fac_com_tbl[R_FAC_TX_ID_E2PROM_W])
    {
        e2prom_com = R_FAC_TX_ID_E2PROM_W;
        rxdf[fac_index][RXDF0_INDEX] = (uint8_t)fac_recv_buff[fac_index][1];
        rxdf[fac_index][RXDF1_INDEX] = (uint8_t)fac_recv_buff[fac_index][2];
    }
    else
    {
        e2prom_com = 0;
        rxdf[fac_index][RXDF0_INDEX] = (uint8_t)fac_recv_buff[fac_index][2];
        rxdf[fac_index][RXDF1_INDEX] = (uint8_t)fac_recv_buff[fac_index][3];
        rxdf[fac_index][RXDF2_INDEX] = (uint8_t)fac_recv_buff[fac_index][4];
        rxdf[fac_index][RXDF3_INDEX] = (uint8_t)fac_recv_buff[fac_index][5];
        rxdf[fac_index][RXDF4_INDEX] = (uint8_t)fac_recv_buff[fac_index][6];
        rxdf[fac_index][RXDF5_INDEX] = (uint8_t)fac_recv_buff[fac_index][7];
        rxdf[fac_index][RXDF6_INDEX] = (uint8_t)fac_recv_buff[fac_index][8];
        rxdf[fac_index][RXDF7_INDEX] = (uint8_t)fac_recv_buff[fac_index][9];
    }

    memset((void*)&fac_rx_result[fac_index], 0, sizeof(r_fac_result_t));

    s_cf  = (uint8_t)fac_send_buff[fac_index][0]; /* CF */
    r_cf  = (uint8_t)fac_recv_buff[fac_index][0]; /* CF */
    if (e2prom_com != 0)
    {
        r_sf  = 0;
        s_adf = (uint8_t)fac_send_buff[fac_index][1]; /* ADF */
        r_adf = (uint8_t)fac_recv_buff[fac_index][1]; /* ADF */
        s_edf = (uint8_t)fac_send_buff[fac_index][2]; /* EDF */
        r_edf = (uint8_t)fac_recv_buff[fac_index][2]; /* EDF */
    }
    else
    {
        r_sf  = (uint8_t)fac_recv_buff[fac_index][1]; /* SF */
        s_adf = 0;
        r_adf = 0;
        s_edf = 0;
        r_edf = 0;
    }
    r_crc = (uint8_t)fac_recv_buff[fac_index][fac_485_reqnum]; /* CRC */

    /* CRC Calculate */
    crc = 0x00;
    while(fac_485_reqnum > 0)
    {
      fac_485_reqnum--;
      crc ^= (uint8_t)fac_recv_buff[fac_index][fac_485_reqnum];
    }
    
    fac_rx_result[fac_index].ide    = (s_cf != r_cf);
    fac_rx_result[fac_index].ebusy  = r_adf>>7;
    fac_rx_result[fac_index].rxid   = (r_cf>>3) & 0x0F;
    fac_rx_result[fac_index].rxidp  = r_cf>>7;
    fac_rx_result[fac_index].rxsfic = r_sf & 0x0F;
    fac_rx_result[fac_index].rxsfea = (r_sf >>4) & 0x03;
    fac_rx_result[fac_index].rxsfca = (r_sf >>6) & 0x03;
    fac_rx_result[fac_index].crc    = r_crc;
    fac_rx_result[fac_index].conte  = ((r_cf>>3) + (r_cf>>4) + (r_cf>>5) + (r_cf>>6) + (r_cf>>7)) & 0x01;
    fac_rx_result[fac_index].crce   = (crc != r_crc);
    fac_rx_result[fac_index].sfome  = (csr & FAC_SCI_CSR_FER) >> FAC_SCI_CSR_FER_Pos;    // Error Start bit
    fac_rx_result[fac_index].timote = timeout;    // Timeout
    fac_rx_result[fac_index].rxedfe = (e2prom_com == R_FAC_TX_ID_E2PROM_W) && (s_edf != r_edf); // Error EDF
    fac_rx_result[fac_index].rxadfe = (s_adf != r_adf);    // Error ADF
    fac_rx_result[fac_index].dfovfe = 0;    // Data num error
    fac_rx_result[fac_index].orer   = (csr & FAC_SCI_CSR_ORER) >> FAC_SCI_CSR_ORER_Pos;  // Overrun error

    fac_rx_result[fac_index].rse    =   fac_rx_result[fac_index].conte | fac_rx_result[fac_index].crce
                                      | fac_rx_result[fac_index].sfome | fac_rx_result[fac_index].timote
                                      | fac_rx_result[fac_index].rxedfe | fac_rx_result[fac_index].rxadfe
                                      | fac_rx_result[fac_index].dfovfe | fac_rx_result[fac_index].orer;
    if(   (0 == fac_rx_result[fac_index].rse) && (0 == fac_rx_result[fac_index].ide)
       && (0 == fac_rx_result[fac_index].ebusy))
    {
        fac_rx_result[fac_index].result = R_FAC_RX_SUCCESS;
    }
    else
    {
        fac_rx_result[fac_index].result = R_FAC_RX_ERR;
    }

    rxresult = fac_rx_result[fac_index].result;

    return rxresult;  
}

/*******************************************************************************
End of function fac_data_check
*******************************************************************************/

static uint32_t fac_data_check1(const uint32_t fac_index, const uint32_t csr, const uint32_t timeout)
{
    uint32_t rxresult;
      int16_t fac_485_reqnum;
      int16_t e2prom_com;
      uint8_t s_cf, s_adf, s_edf, r_cf, r_sf, r_adf, r_edf, r_crc, crc;

      fac_485_reqnum = (int16_t)(fac_recv_bytes[fac_index] - 1);
      //fac_485_reqnum = (int16_t)(fac_recv_bytes[fac_index]);


      e2prom_com = 0;
      rxdf[fac_index][RXDF0_INDEX] = (uint8_t)fac_recv_buff[fac_index][2];
      rxdf[fac_index][RXDF1_INDEX] = (uint8_t)fac_recv_buff[fac_index][3];
      rxdf[fac_index][RXDF2_INDEX] = (uint8_t)fac_recv_buff[fac_index][4];
      rxdf[fac_index][RXDF3_INDEX] = (uint8_t)fac_recv_buff[fac_index][1];
      rxdf[fac_index][RXDF4_INDEX] = (uint8_t)fac_recv_buff[fac_index][5];

      memset((void*)&fac_rx_result[fac_index], 0, sizeof(r_fac_result_t));

      s_cf  = (uint8_t)fac_send_buff[fac_index][0]; /* CF */
      r_cf  = (uint8_t)fac_recv_buff[fac_index][0]; /* CF */

     r_sf  = (uint8_t)fac_recv_buff[fac_index][1]; /* SF */
     s_adf = 0;
     r_adf = 0;
     s_edf = 0;
     r_edf = 0;

      r_crc = (uint8_t)fac_recv_buff[fac_index][fac_485_reqnum]; /* CRC */

      /* CRC Calculate */
      crc = 0x00;
      while(fac_485_reqnum > 0)
      {
        fac_485_reqnum--;
        crc ^= (uint8_t)fac_recv_buff[fac_index][fac_485_reqnum];
      }
#if 1
      fac_rx_result[fac_index].ide    = (s_cf != r_cf);
      fac_rx_result[fac_index].ebusy  = r_adf>>7;
      fac_rx_result[fac_index].rxid   = (r_cf>>3) & 0x0F;
      fac_rx_result[fac_index].rxidp  = r_cf>>7;
      fac_rx_result[fac_index].rxsfic = r_sf & 0x0F;
      fac_rx_result[fac_index].rxsfea = (r_sf >>4) & 0x03;
      fac_rx_result[fac_index].rxsfca = (r_sf >>6) & 0x03;
      fac_rx_result[fac_index].crc    = r_crc;
      fac_rx_result[fac_index].conte  = ((r_cf>>3) + (r_cf>>4) + (r_cf>>5) + (r_cf>>6) + (r_cf>>7)) & 0x01;
      fac_rx_result[fac_index].crce   = (crc != r_crc);
      fac_rx_result[fac_index].sfome  = (csr & FAC_SCI_CSR_FER) >> FAC_SCI_CSR_FER_Pos;    // Error Start bit
      fac_rx_result[fac_index].timote = timeout;    // Timeout
      fac_rx_result[fac_index].rxedfe = (e2prom_com == R_FAC_TX_ID_E2PROM_W) && (s_edf != r_edf); // Error EDF
      fac_rx_result[fac_index].rxadfe = (s_adf != r_adf);    // Error ADF
      fac_rx_result[fac_index].dfovfe = 0;    // Data num error
      fac_rx_result[fac_index].orer   = (csr & FAC_SCI_CSR_ORER) >> FAC_SCI_CSR_ORER_Pos;  // Overrun error

      fac_rx_result[fac_index].rse    =   fac_rx_result[fac_index].conte | fac_rx_result[fac_index].crce
                                        | fac_rx_result[fac_index].sfome | fac_rx_result[fac_index].timote
                                        | fac_rx_result[fac_index].rxedfe | fac_rx_result[fac_index].rxadfe
                                        | fac_rx_result[fac_index].dfovfe | fac_rx_result[fac_index].orer;
      if(   (0 == fac_rx_result[fac_index].rse) && (0 == fac_rx_result[fac_index].ide)
         && (0 == fac_rx_result[fac_index].ebusy))
      {
#endif
          fac_rx_result[fac_index].result = R_FAC_RX_SUCCESS;
#if 1
      }
      else
      {
          fac_rx_result[fac_index].result = R_FAC_RX_ERR;
      }
#endif
      rxresult = fac_rx_result[fac_index].result;

      return rxresult;
}

/*******************************************************************************
* Function Name: fac_set_result
* Description  : Set result of register access.
* Arguments    : fac_index - ch number.
*                csr - common status.
*                timeout - timeout flag.
* Return Value : none.
*******************************************************************************/
static void fac_set_result(const uint32_t fac_index, const uint32_t csr, const uint32_t timeout)
{
    uint32_t rxresult;

    rxresult = fac_data_check(fac_index, csr, timeout);
    PARAMETER_NOT_USED(rxresult);

    if (fac_state[fac_index] == FAC_STATE_REQ || fac_state[fac_index] == FAC_STATE_ELC)
    {
        if (NULL != pfac_req_result_cb[fac_index])
        {
            pfac_req_result_cb[fac_index](&fac_rx_result[fac_index], &rxdf[fac_index][0]);
        }
    }
    else
    {
        if (NULL != pfac_e2prom_result_cb[fac_index])
        {
            pfac_e2prom_result_cb[fac_index](&fac_rx_result[fac_index], rxdf[fac_index][RXDF0_INDEX],
                                             rxdf[fac_index][RXDF1_INDEX]);
        }
    }

    if (fac_state[fac_index] != FAC_STATE_ELC)
    {
        fac_state[fac_index] = FAC_STATE_IDLE;
    }
#if FAC_ELC_EMULATE == FAC_ELC_ENABLE_DMA
    else
    {
        R_DMAC_Reconfigure(&g_transfer0_ctrl, g_transfer0_cfg.p_info);
        R_DMAC_Enable(&g_transfer0_ctrl);
    }
#endif
}
/*******************************************************************************
End of function fac_set_result
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_eri_isr_common
* Description  : Receive error interrupt handler of FA-CODER.
* Arguments    : fac_index - ch number.
* Return Value : None.
*******************************************************************************/
void fac_eri_isr_common(const uint32_t fac_index)
{
    uint32_t ccr0_reg;
    uint32_t csr;
    uint32_t timeout = 0;
    
    fac_recv_buff[fac_index][fac_recv_buff_index[fac_index]] = R_FAC_SCI(fac_index)->RDR;
    fac_recv_buff_index[fac_index]++;

    csr = R_FAC_SCI(fac_index)->CSR & FAC_SCI_RCVR_ERR;

//    R_GPT_Stop(&g_timer1_ctrl);
//    R_GPT_Reset(&g_timer1_ctrl);  // clear counter
#if FAC_ELC_EMULATE == FAC_ELC_ENABLE_DMA
    if (fac_state[fac_index] == FAC_STATE_ELC)
    {
        R_DMAC_Disable(&g_transfer0_ctrl);
    }
#endif
    ccr0_reg = R_FAC_SCI(fac_index)->CCR0;
    ccr0_reg &= ~0x00310011u;  // set TEIE = 0, TIE = 0, RIE = 0, TE = 0, RE = 0
    R_FAC_SCI(fac_index)->CCR0 = ccr0_reg;
    fac_set_result(fac_index, csr, timeout);
}
/*******************************************************************************
End of function fac_eri_isr_common
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_rxi_isr_common
* Description  : Receive data interrupt handler of FA-CODER.
* Arguments    : fac_index - ch number.
* Return Value : None.
*******************************************************************************/
void fac_rxi_isr_common(const uint32_t fac_index)
{
    uint32_t ccr0_reg;
    uint32_t csr = 0;
    uint32_t timeout = 0;

    fac_recv_buff[fac_index][fac_recv_buff_index[fac_index]] = R_FAC_SCI(fac_index)->RDR;
    fac_recv_buff_index[fac_index]++;
    
    if(fac_recv_buff_index[fac_index] >= fac_recv_bytes[fac_index])
    {
//        R_GPT_Stop(&g_timer1_ctrl);
//        R_GPT_Reset(&g_timer1_ctrl);  // clear counter
        ccr0_reg = R_FAC_SCI(fac_index)->CCR0;
        ccr0_reg &= ~0x00310011u;  // set TEIE = 0, TIE = 0, RIE = 0, TE = 0, RE = 0
        R_FAC_SCI(fac_index)->CCR0 = ccr0_reg;
        fac_set_result(fac_index, csr, timeout);
    }
}
/*******************************************************************************
End of function fac_rxi_isr_common
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_txi_isr_common
* Description  : Transmit data interrupt handler of FA-CODER.
* Arguments    : fac_index - ch number.
* Return Value : None.
*******************************************************************************/
void fac_txi_isr_common(const uint32_t fac_index)
{
    uint32_t ccr0_reg;
    
    if(fac_send_buff_index[fac_index] < fac_send_bytes[fac_index])
    {
        R_FAC_SCI(fac_index)->TDR = (uint32_t)fac_send_buff[fac_index][fac_send_buff_index[fac_index]];
        fac_send_buff_index[fac_index]++;
    }
    else
    {
        ccr0_reg = R_FAC_SCI(fac_index)->CCR0;
        ccr0_reg &= ~0x00100000u;  // set TIE = 0
        ccr0_reg |=  0x00200000u;  // set TEIE = 1
        R_FAC_SCI(fac_index)->CCR0 = ccr0_reg;
    }
}
/*******************************************************************************
End of function fac_txi_isr_common
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_tei_isr_common
* Description  : Transmit end interrupt handler of FA-CODER.
* Arguments    : fac_index - ch number.
* Return Value : None.
*******************************************************************************/
void fac_tei_isr_common(const uint32_t fac_index)
{
    uint32_t ccr0_reg;
    
    fac_send_buff_index[fac_index] = 0;
    fac_recv_buff_index[fac_index] = 0;
    ccr0_reg = R_FAC_SCI(fac_index)->CCR0;
    ccr0_reg &= ~0x00300000u;  // set TEIE = 0, TIE = 0
    ccr0_reg |=  0x00010001u;  // set RIE = 1, RE = 1
    R_FAC_SCI(fac_index)->CCR0 = ccr0_reg;
    
//    R_GPT_Start(&g_timer1_ctrl);
}
/*******************************************************************************
End of function fac_tei_isr_common
*******************************************************************************/

/*******************************************************************************
* Function Name: fac0_eri_isr
* Description  : Receive error interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac0_eri_isr(void)
{
    fac_eri_isr_common(FAC0_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac0_eri_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac0_rxi_isr
* Description  : Receive data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac0_rxi_isr(void)
{
    fac_rxi_isr_common(FAC0_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac0_rxi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac0_txi_isr
* Description  : Transmit data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac0_txi_isr(void)
{
    fac_txi_isr_common(FAC0_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac0_txi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac0_tei_isr
* Description  : Transmit end interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac0_tei_isr(void)
{
    fac_tei_isr_common(FAC0_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac0_tei_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac1_eri_isr
* Description  : Receive error interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac1_eri_isr(void)
{
    fac_eri_isr_common(FAC1_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac1_eri_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac1_rxi_isr
* Description  : Receive data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac1_rxi_isr(void)
{
    fac_rxi_isr_common(FAC1_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac1_rxi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac1_txi_isr
* Description  : Transmit data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac1_txi_isr(void)
{
    fac_txi_isr_common(FAC1_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac1_txi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac1_tei_isr
* Description  : Transmit end interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac1_tei_isr(void)
{
    fac_tei_isr_common(FAC1_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac1_tei_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac2_eri_isr
* Description  : Receive error interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac2_eri_isr(void)
{
    fac_eri_isr_common(FAC2_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac2_eri_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac2_rxi_isr
* Description  : Receive data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac2_rxi_isr(void)
{
    fac_rxi_isr_common(FAC2_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac2_rxi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac2_txi_isr
* Description  : Transmit data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac2_txi_isr(void)
{
    fac_txi_isr_common(FAC2_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac2_txi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac2_tei_isr
* Description  : Transmit end interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac2_tei_isr(void)
{
    fac_tei_isr_common(FAC2_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac2_tei_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac3_eri_isr
* Description  : Receive error interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac3_eri_isr(void)
{
    fac_eri_isr_common(FAC3_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac3_eri_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac3_rxi_isr
* Description  : Receive data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac3_rxi_isr(void)
{
    fac_rxi_isr_common(FAC3_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac3_rxi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac3_txi_isr
* Description  : Transmit data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac3_txi_isr(void)
{
    fac_txi_isr_common(FAC3_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac3_txi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac3_tei_isr
* Description  : Transmit end interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac3_tei_isr(void)
{
    fac_tei_isr_common(FAC3_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac3_tei_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac4_eri_isr
* Description  : Receive error interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac4_eri_isr(void)
{
    fac_eri_isr_common(FAC4_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac4_eri_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac4_rxi_isr
* Description  : Receive data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac4_rxi_isr(void)
{
    fac_rxi_isr_common(FAC4_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac4_rxi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac4_txi_isr
* Description  : Transmit data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac4_txi_isr(void)
{
    fac_txi_isr_common(FAC4_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac4_txi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac4_tei_isr
* Description  : Transmit end interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac4_tei_isr(void)
{
    fac_tei_isr_common(FAC4_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac4_tei_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac5_eri_isr
* Description  : Receive error interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac5_eri_isr(void)
{
    fac_eri_isr_common(FAC5_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac5_eri_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac5_rxi_isr
* Description  : Receive data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac5_rxi_isr(void)
{
    fac_rxi_isr_common(FAC5_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac5_rxi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac5_txi_isr
* Description  : Transmit data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac5_txi_isr(void)
{
    fac_txi_isr_common(FAC5_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac5_txi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac5_tei_isr
* Description  : Transmit end interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac5_tei_isr(void)
{
    fac_tei_isr_common(FAC5_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac5_tei_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac6_eri_isr
* Description  : Receive error interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac6_eri_isr(void)
{
    fac_eri_isr_common(FAC6_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac6_eri_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac6_rxi_isr
* Description  : Receive data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac6_rxi_isr(void)
{
    fac_rxi_isr_common(FAC6_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac6_rxi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac6_txi_isr
* Description  : Transmit data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac6_txi_isr(void)
{
    fac_txi_isr_common(FAC6_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac6_txi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac6_tei_isr
* Description  : Transmit end interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac6_tei_isr(void)
{
    fac_tei_isr_common(FAC6_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac6_tei_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac7_eri_isr
* Description  : Receive error interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac7_eri_isr(void)
{
    fac_eri_isr_common(FAC7_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac7_eri_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac7_rxi_isr
* Description  : Receive data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac7_rxi_isr(void)
{
    fac_rxi_isr_common(FAC7_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac7_rxi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac7_txi_isr
* Description  : Transmit data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac7_txi_isr(void)
{
    fac_txi_isr_common(FAC7_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac7_txi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac7_tei_isr
* Description  : Transmit end interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac7_tei_isr(void)
{
    fac_tei_isr_common(FAC7_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac7_tei_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac8_eri_isr
* Description  : Receive error interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac8_eri_isr(void)
{
    fac_eri_isr_common(FAC8_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac8_eri_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac8_rxi_isr
* Description  : Receive data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac8_rxi_isr(void)
{
    fac_rxi_isr_common(FAC8_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac8_rxi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac8_txi_isr
* Description  : Transmit data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac8_txi_isr(void)
{
    fac_txi_isr_common(FAC8_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac8_txi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac8_tei_isr
* Description  : Transmit end interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac8_tei_isr(void)
{
    fac_tei_isr_common(FAC8_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac8_tei_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac9_eri_isr
* Description  : Receive error interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac9_eri_isr(void)
{
    fac_eri_isr_common(FAC9_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac9_eri_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac9_rxi_isr
* Description  : Receive data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac9_rxi_isr(void)
{
    fac_rxi_isr_common(FAC9_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac9_rxi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac9_txi_isr
* Description  : Transmit data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac9_txi_isr(void)
{
    fac_txi_isr_common(FAC9_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac9_txi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac9_tei_isr
* Description  : Transmit end interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac9_tei_isr(void)
{
    fac_tei_isr_common(FAC9_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac9_tei_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac10_eri_isr
* Description  : Receive error interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac10_eri_isr(void)
{
    fac_eri_isr_common(FAC10_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac10_eri_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac10_rxi_isr
* Description  : Receive data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac10_rxi_isr(void)
{
    fac_rxi_isr_common(FAC10_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac10_rxi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac10_txi_isr
* Description  : Transmit data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac10_txi_isr(void)
{
    fac_txi_isr_common(FAC10_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac10_txi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac10_tei_isr
* Description  : Transmit end interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac10_tei_isr(void)
{
    fac_tei_isr_common(FAC10_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac10_tei_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac11_eri_isr
* Description  : Receive error interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac11_eri_isr(void)
{
    fac_eri_isr_common(FAC11_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac11_eri_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac11_rxi_isr
* Description  : Receive data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac11_rxi_isr(void)
{
    fac_rxi_isr_common(FAC11_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac11_rxi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac11_txi_isr
* Description  : Transmit data interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac11_txi_isr(void)
{
    fac_txi_isr_common(FAC11_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac11_txi_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac11_tei_isr
* Description  : Transmit end interrupt handler of FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac11_tei_isr(void)
{
    fac_tei_isr_common(FAC11_INDEX);
    __DMB();
}
/*******************************************************************************
End of function fac11_tei_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: user_fac_callback
* Description  : User callback function for FA-CODER.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void user_fac_callback (scie_callback_args_t * p_args)
{
    PARAMETER_NOT_USED(p_args);
}
/*******************************************************************************
End of function user_fac_callback
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_gpt0_isr
* Description  : GPT0 interrupt handler for FA-CODER ELC command emulation.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac_gpt0_isr(void)
{
#if FAC_ELC_EMULATE == FAC_ELC_ENABLE_CPU
    uint32_t ccr0_reg;
    uint32_t fac_index;
    
    for (fac_index = 0; fac_index <= FAC_ID_NUM; fac_index++)
    {
        if (fac_state[fac_index] == FAC_STATE_ELC)
        {
            ccr0_reg = R_FAC_SCI(fac_index)->CCR0;
            ccr0_reg |= 0x00100010u;  // set TIE = 1, TE = 1
            R_FAC_SCI(fac_index)->CCR0 = ccr0_reg;
        }
    }
#endif
}
/*******************************************************************************
End of function fac_gpt0_isr
*******************************************************************************/

/*******************************************************************************
* Function Name: fac_gpt1_isr
* Description  : GPT1 interrupt handler for FA-CODER watchdog.
* Arguments    : None.
* Return Value : None.
*******************************************************************************/
void fac_gpt1_isr(void)
{
    uint32_t ccr0_reg;
    uint32_t fac_index;
    uint32_t csr = 0;
    uint32_t timeout = 1;
    
    R_GPT_Stop(&g_timer1_ctrl);
    R_GPT_Reset(&g_timer1_ctrl);  // clear counter
    
    for (fac_index = 0; fac_index <= FAC_ID_NUM; fac_index++)
    {
        if (   fac_state[fac_index] == FAC_STATE_REQ || fac_state[fac_index] == FAC_STATE_E2PROM
            || fac_state[fac_index] == FAC_STATE_ELC)
        {
#if FAC_ELC_EMULATE == FAC_ELC_ENABLE_DMA
            if (fac_state[fac_index] == FAC_STATE_ELC)
            {
                R_DMAC_Disable(&g_transfer0_ctrl);
            }
#endif
            ccr0_reg = R_FAC_SCI(fac_index)->CCR0;
            ccr0_reg &= ~0x00310011u;  // set TEIE = 0, TIE = 0, RIE = 0, TE = 0, RE = 0
            R_FAC_SCI(fac_index)->CCR0 = ccr0_reg;
            
            fac_set_result(fac_index, csr, timeout);
        }
    }
}
/*******************************************************************************
End of function fac_gpt1_isr
*******************************************************************************/
