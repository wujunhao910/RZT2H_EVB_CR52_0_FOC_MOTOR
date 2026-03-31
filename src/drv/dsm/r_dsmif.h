/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 **       Definition of DSM interface for RZ/T2
 **       
 **
 **       revision 0.9 (31.Mar.2021)
 **
 **********************************************************************************************************************/


#ifndef _R_DSMIF_H_
#define _R_DSMIF_H_

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
Macro definitions
*******************************************************************************/
/* DSMIF Filter Setting Code -------------------------------------------------*/
#define DSMIF_FILTER_SET_0                      (0U)
#define DSMIF_FILTER_SET_1                      (1U)
#define DSMIF_FILTER_SET_2                      (2U)
#define DSMIF_FILTER_SET_3                      (3U)
#define DSMIF_FILTER_SET_4                      (4U)
#define DSMIF_FILTER_SET_5                      (5U)
#define DSMIF_FILTER_SET_6                      (6U)
#define DSMIF_FILTER_SET_7                      (7U)
#define DSMIF_FILTER_SET_8                      (8U)
#define DSMIF_FILTER_SET_9                      (9U)
#define DSMIF_FILTER_SET_10                     (10U)
#define DSMIF_FILTER_SET_11                     (11U)
#define DSMIF_FILTER_SET_12                     (12U)
#define DSMIF_FILTER_SET_13                     (13U)
#define DSMIF_FILTER_SET_14                     (14U)

/* DSMIF Sinc Filter Setting -------------------------------------------------*/
#define DSMIF_SINC_1                            (1U)
#define DSMIF_SINC_2                            (2U)
#define DSMIF_SINC_3                            (0U)

/* DSMIF Decimation Clock Setting --------------------------------------------*/
#define DSMIF_DIV_MCLK_4                        (3U)
#define DSMIF_DIV_MCLK_8                        (7U)
#define DSMIF_DIV_MCLK_16                       (15U)
#define DSMIF_DIV_MCLK_32                       (31U)
#define DSMIF_DIV_MCLK_64                       (63U)
#define DSMIF_DIV_MCLK_128                      (127U)
#define DSMIF_DIV_MCLK_256                      (255U)

/* DSMIF Bit Shift Setting ---------------------------------------------------*/ 
#define DSMIF_BITSHIFT_0                        (0U)
#define DSMIF_BITSHIFT_1                        (1U)
#define DSMIF_BITSHIFT_2                        (2U)
#define DSMIF_BITSHIFT_3                        (3U)
#define DSMIF_BITSHIFT_4                        (4U)
#define DSMIF_BITSHIFT_5                        (5U)
#define DSMIF_BITSHIFT_6                        (6U)
#define DSMIF_BITSHIFT_7                        (7U)
#define DSMIF_BITSHIFT_8                        (8U)
#define DSMIF_BITSHIFT_9                        (9U)
#define DSMIF_BITSHIFT_10                       (10U)
#define DSMIF_BITSHIFT_11                       (11U)
#define DSMIF_BITSHIFT_12                       (12U)

/* DSMIF Target Register to Read ---------------------------------------------*/
#define DSMIF_READ_X1                           (1U)
#define DSMIF_READ_X2                           (2U)

/* DSMIF Error Status --------------------------------------------------------*/
#define DSMIF_ERR_ERIX                          (1U)
#define DSMIF_ERR_ERXSC                         (2U)
#define DSMIF_ERR_ALL                           (3U)

/* DSMIF Scan Mode -----------------------------------------------------------*/
#define DSMIF_MODE_HIGH                         (0U)
#define DSMIF_MODE_LOW                          (1U)

/* DSMIF Upper Limit ---------------------------------------------------------*/
#define DSMIF_UPPER_LIMIT_5                     (0xF800U)
#define DSMIF_UPPER_LIMIT_6                     (0xFC00U)
#define DSMIF_UPPER_LIMIT_7                     (0xFE00U)
#define DSMIF_UPPER_LIMIT_8                     (0xFF00U)
#define DSMIF_UPPER_LIMIT_9                     (0xFF80U)
#define DSMIF_UPPER_LIMIT_10                    (0xFFC0U)
#define DSMIF_UPPER_LIMIT_12                    (0xFFF0U)
#define DSMIF_UPPER_LIMIT_14                    (0xFFFCU)
#define DSMIF_UPPER_LIMIT_15                    (0xFFFEU)
#define DSMIF_UPPER_LIMIT_16                    (0xFFFFU)

/* Data for Writing to HVA ---------------------------------------------------*/
#define DSMIF_HVA_WRITE_DATA                    (1U)

/* DSMIF Clear Edge ----------------------------------------------------------*/
#define DSMIF_PIC_CLEAR_EDGE                    (1U)

/* ECM Error Setting for DSMIF -----------------------------------------------*/
#define ECM_ERROR_BIT_DSMIF_ALL                 (0x7E000000U)
    /*
     * The above includes reservation bit 28 of ECMEMK0.
     * It's necessary to make 1 in the initialization time.
     */
#define ECM_ERROR_BIT_DSMIF_XYZ                 (0x60000000U)

/* MPC Definition for DSMIF --------------------------------------------------*/
#define MPC_PN6PFS_PSEL_MCLK3                   (0x28u)
#define MPC_PN7PFS_PSEL_MDAT3                   (0x28u)

/* Unit Number --------------------------------------------------*/
#define DSMIF_UNIT0            (0u)
#define DSMIF_UNIT1            (1u)
#define DSMIF_UNIT2            (2u)
#define DSMIF_UNIT3            (3u)
#define DSMIF_UNIT4            (4u)
#define DSMIF_UNIT5            (5u)
#define DSMIF_UNIT6            (6u)
#define DSMIF_UNIT7            (7u)
#define DSMIF_UNIT8            (8u)
#define DSMIF_UNIT9            (9u)

/* Channel Number --------------------------------------------------*/
#define DSMIF_CH0               (0u)
#define DSMIF_CH1               (1u)
#define DSMIF_CH2               (2u)


/* Channel's start trigger --------------------------------------------------*/
#define DSMIF_START_CH0                         (0x01u)
#define DSMIF_START_CH1                         (0x02u)
#define DSMIF_START_CH2                         (0x04u)


/* Interrupt Control Register --------------------------------------------------*/
#define DSMIF_INT_EN_OVC_LO         (1u)                // Overcurrent lower limit detection interrupt enable
#define DSMIF_INT_EN_OVC_HI         (2u)                // Overcurrent upper limit exceeded output interrupt enable
#define DSMIF_INT_EN_SC             (4u)                // Short circuit detection error interrupt enable bit
#define DSMIF_INT_EN_CUR            (8u)                // Current data register update interrupt enable

/* Current Mesurement Clcok Control Register (CKDIR)--------------------------------------------------*/
#define DSMIF_MCLK_MASTER           (1u)                // AD conversion clock master
#define DSMIF_MCLK_SLAVE            (0u)                // AD conversion clock slave

#define DSMIF_MDAT_EDGE_NEG         (0u)                // Capture MDATn at the negative edge of MCLKn
#define DSMIF_MDAT_EDGE_POS         (1u)                // Capture MDATn at the positive edge of MCLKn

/* Current Mesurement Clcok Control Register (CKDIV)--------------------------------------------------*/
#define DSMIF_MCLK_OUT_DIV8             (0x03u)                // AD conversion clock division ratio
#define DSMIF_MCLK_OUT_DIV10            (0x04u)                // AD conversion clock division ratio
#define DSMIF_MCLK_OUT_DIV16            (0x07u)                // AD conversion clock division ratio
#define DSMIF_MCLK_OUT_DIV20            (0x09u)                // AD conversion clock division ratio
#define DSMIF_MCLK_OUT_DIV32            (0x0Fu)                // AD conversion clock division ratio
#define DSMIF_MCLK_OUT_DIV40            (0x13u)                // AD conversion clock division ratio


/* Current Mesurement Capture Trigger Control Register Current capture trigger -----------------------------*/
#define DSMIF_CAP_NTRIG            (0u)                // Do not capture
#define DSMIF_CAP_TRIG0            (1u)                // Serect Current Data capture trigger 0
#define DSMIF_CAP_TRIG1            (2u)                // Serect Current Data capture trigger 1
#define DSMIF_CAP_TRIG2            (3u)                // Serect Current Data capture trigger 2
#define DSMIF_CAP_TRIG3            (4u)                // Serect Current Data capture trigger 3
#define DSMIF_CAP_TRIG4            (5u)                // Serect Current Data capture trigger 4
#define DSMIF_CAP_TRIG5            (6u)                // Serect Current Data capture trigger 5

/* Current Mesurement Capture Trigger Control Register -----------------------------*/
// Current measurement filter Initialization trigger selection bit for frequency division counter for decimation.
#define DSMIF_SEL_INIT_NONE            (0u)            // Do not initialize
#define DSMIF_SEL_INIT_TRG0            (1u)            // Select Decimation dividing counter initialization trigger 0
#define DSMIF_SEL_INIT_TRG1            (2u)            // Select Decimation dividing counter initialization trigger 1
#define DSMIF_SEL_INIT_TRG2            (3u)            // Select Decimation dividing counter initialization trigger 2

/* Current Mesurement Capture Trigger Control Register -----------------------------*/
// Current measurement filter Initialization trigger for division counter for decimation Edge selection bit.
#define DSMIF_INIT_EDGE_NEG            (0u)            // The frequency division counter for decimation is initialized at the negative edge of initialization tigger.
#define DSMIF_INIT_EDGE_POS            (1u)            // The frequency division counter for decimation is initialized at the positive edge of initialization tigger.

/* Overcurrent detection invalid/valid */
#define DSMIF_OVC_INVALID           (0u)
#define DSMIF_OVC_VALID             (3u)
/* short circuit detection invalid/valid */
#define DSMIF_SC_INVALID            (0u)
#define DSMIF_SC_VALID              (1u)

/* Channel Error Status Register -----------------------------*/
#define DSMIF_ERR_SATUS_OVC_L_CH0            (0x00000001u)
#define DSMIF_ERR_SATUS_OVC_L_CH1            (0x00000002u)
#define DSMIF_ERR_SATUS_OVC_L_CH2            (0x00000004u)

#define DSMIF_ERR_SATUS_OVC_H_CH0            (0x00000010u)
#define DSMIF_ERR_SATUS_OVC_H_CH1            (0x00000020u)
#define DSMIF_ERR_SATUS_OVC_H_CH2            (0x00000040u)

#define DSMIF_ERR_SATUS_SC_CH0               (0x00000100u)
#define DSMIF_ERR_SATUS_SC_CH1               (0x00000200u)
#define DSMIF_ERR_SATUS_SC_CH2               (0x00000400u)

#define DSMIF_ERR_SATUS_OVCSUM_L             (0x00010000u)
#define DSMIF_ERR_SATUS_OVCSUM_H             (0x00020000u)

/*******************************************************************************
Typedef definitions
*******************************************************************************/
/* The possible return codes from the API functions. */
typedef enum dsmif_return_err_e
{
    DSMIF_SUCCESS = 0,
    DSMIF_ERR_NG,                   // No good
    DSMIF_ERR_TMOUT                 // Timeout error
} dsmif_err_t;

/*******************************************************************************
  Structure
*******************************************************************************/

/* DSMIF filter definitions register (for R_DSMIF_Ctrl function ) ------------------------------*/
typedef struct
{
    uint8_t int_en;                                     // Interrupt Control Register setting
    
    uint8_t mclk_mode;                                  // AD conversion clock master/slave mode
    uint8_t mdat_edge;                                  // Capture MDATn at the nega/pos edge of MCLKn
    uint8_t ckdiv;                                      // AD conversion clock division ratio
    
    uint8_t captrigA;                                   // Current capture trigger A selection bit
    uint8_t captrigB;                                   // Current capture trigger B selection bit
    uint8_t ditsel;                                     // Current measurement filter Initialization trigger selection bit for frequency division counter for decimation.
    uint8_t dedge;                                      // Current measurement filter Initialization trigger for division counter for decimation Edge selection bit.
} st_dsmif_ctrl_t;


/* DSMIF filter definitions register (for R_DSMIF_OvcSCCtrl function )------------------------------*/
typedef struct
{
    uint8_t sincsel;
    uint8_t wordgen;
    uint8_t bitshift;
} st_dsmif_filter_cfg_t;


/* Structure of over current detection threshold (for R_DSMIF_OvcSCCtrl function )------------------------------*/
typedef struct
{
    uint16_t low;
    uint16_t high;
} st_dsmif_ovc_thres_cfg_t;

/* Structure of short circuit detection threshold (for R_DSMIF_OvcSCCtrl function )------------------------------*/
typedef struct
{
    uint16_t low;
    uint16_t high;
} st_dsmif_sc_thres_cfg_t;


/* Structure of short circuit detection and over current detection control (for R_DSMIF_OvcSCCtrl function )------------*/
typedef struct
{
    st_dsmif_ovc_thres_cfg_t ovc_thres;
    st_dsmif_sc_thres_cfg_t  sc_thres;
    uint8_t                  filter_setting;
} st_dsmif_ovcsc_ctrl_t;


/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/
dsmif_err_t R_DSMIF_Ctrl(uint32_t dsmifunum, uint32_t dsmifchnum, st_dsmif_ctrl_t* param);
dsmif_err_t R_DSMIF_Start(uint32_t dsmifunum, uint32_t setval);
uint32_t R_DSMIF_ReadStaus(uint32_t dsmifunum);
dsmif_err_t R_DSMIF_Stop(uint32_t dsmifunum);
uint16_t R_DSMIF_ReadCapDataA(uint32_t dsmifunum, uint32_t dsmifchnum);
void R_DSMIF_SetFilter(uint32_t dsmifunum, uint32_t dsmifchnum, uint8_t filter_setting);
dsmif_err_t R_DSMIF_OvcSCCtrl(uint32_t dsmifunum, uint32_t dsmifchnum, st_dsmif_ovcsc_ctrl_t* param);
dsmif_err_t R_DSMIF_OvcSCCtrlValid(uint32_t dsmifunum, uint32_t dsmifchnum);

#endif /* _R_DSMIF_H_ */

/* End of File */
