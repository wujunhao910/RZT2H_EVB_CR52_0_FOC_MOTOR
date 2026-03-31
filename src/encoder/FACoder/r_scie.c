/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_sci_uart.h"
#include "r_scie.h"
#include "r_ioport.h"
#include <string.h>

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
/** Number of divisors in the data table used for baud rate calculation. */
#define SCIE_NUM_DIVISORS_ASYNC           (13U)

/** Valid range of values for the modulation duty register is 128 - 256 (256 = modulation disabled). */
#define SCIE_MDDR_MIN                     (128U)
#define SCIE_MDDR_MAX                     (256U)

/** The bit rate register is 8-bits, so the maximum value is 255. */
#define SCIE_BRR_MAX                      (255U)

/** Clock frequency 96MHz. */
#define SCIE_CLOCK_96MHZ                  (96000000)

/** "SCIU" in ASCII.  Used to determine if the control block is open. */
#define SCIE_OPEN                         (0x53434955U)

#define SCIE_BRR_DEFAULT_VALUE            (0xFFU)
#define SCIE_FCR_DEFAULT_VALUE            (0x1F1F0000)

#define SCIE_CCR0_DEFAULT_VALUE           (0x00000000)
#define SCIE_CCR1_DEFAULT_VALUE           (0x00000010)
#define SCIE_CCR2_DEFAULT_VALUE           (0xFF00FF04)
#define SCIE_CCR3_DEFAULT_VALUE           (0x00001203)
#define SCIE_CCR4_DEFAULT_VALUE           (0x00000000)

#define SCIE_CFCLR_ALL_FLAG_CLEAR         (0xBD070010)

/** SCI CCR0 register bit masks */
#define SCIE_CCR0_IDSEL_MASK              (0x00000400)
#define SCIE_CCR0_TEIE_MASK               (0x00200000)
#define SCIE_CCR0_RE_MASK                 (0x00000001)
#define SCIE_CCR0_TE_MASK                 (0x00000010)
#define SCIE_CCR0_RIE_MASK                (0x00010000)
#define SCIE_CCR0_TIE_MASK                (0x00100000)

/** SCI CCR1 register bit offsets */
#define SCIE_CCR1_CTSE_OFFSET             (0U)
#define SCIE_CCR1_SPB2DT_BIT              (4U)
#define SCIE_CCR1_OUTPUT_ENABLE_MASK      (0x00000020)
#define SCIE_CCR1_PARITY_OFFSET           (8U)
#define SCIE_CCR1_PARITY_MASK             (0x00000300U)
#define SCIE_CCR1_NFCS_OFFSET             (24U)
#define SCIE_CCR1_NFCS_VALUE_MASK         (0x07U)
#define SCIE_CCR1_NFEN_OFFSET             (28U)

/** SCI CCR2 register bit offsets */
#define SCIE_CCR2_BRME_OFFSET             (16U)
#define SCIE_CCR2_ABCSE_OFFSET            (6U)
#define SCIE_CCR2_ABCS_OFFSET             (5U)
#define SCIE_CCR2_BDGM_OFFSET             (4U)
#define SCIE_CCR2_CKS_OFFSET              (20U)
#define SCIE_CCR2_CKS_VALUE_MASK          (0x03U) ///< CKS: 2 bits
#define SCIE_CCR2_BRR_OFFSET              (8U)
#define SCIE_CCR2_BRR_VALUE_MASK          (0xFFU) ///< BRR: 8bits
#define SCIE_CCR2_MDDR_OFFSET             (24U)
#define SCIE_CCR2_MDDR_VALUE_MASK         (0xFFU) ///< MDDR: 8bits

#define SCIE_CCR2_BAUD_SETTING_MASK       ((1U << SCIE_CCR2_BRME_OFFSET) |                          \
                                               (1U << SCIE_CCR2_ABCSE_OFFSET) |                         \
                                               (1U << SCIE_CCR2_ABCS_OFFSET) |                          \
                                               (1U << SCIE_CCR2_BDGM_OFFSET) |                          \
                                               (SCIE_CCR2_CKS_VALUE_MASK << SCIE_CCR2_CKS_OFFSET) | \
                                               (SCIE_CCR2_BRR_VALUE_MASK << SCIE_CCR2_BRR_OFFSET) | \
                                               (SCIE_CCR2_MDDR_VALUE_MASK << SCIE_CCR2_MDDR_OFFSET))

/** SCI CCR3 register bit masks */
#define SCIE_CCR3_BPEN_OFFSET             (7U)
#define SCIE_CCR3_CHR_OFFSET              (8U)
#define SCIE_CCR3_STP_OFFSET              (14U)
#define SCIE_CCR3_RxDSEL_OFFSET           (15U)
#define SCIE_CCR3_FM_OFFSET               (20U)
#define SCIE_CCR3_CKE_OFFSET              (24U)
#define SCIE_CCR3_CKE_MASK                (0x03000000U)
#define SCIE_CCR3_CKE_VALUE_MASK          (0x03U)

#define SCIE_INVALID_16BIT_PARAM          (0xFFFFU)

#define SCIE_EVENT_LEVEL                  (0u)
#define SCIE_EVENT_EDGE                   (1u)

/***********************************************************************************************************************
 * Private constants
 **********************************************************************************************************************/
static const int32_t SCIE_100_PERCENT_X_1000 = 100000;
static const int32_t SCIE_MDDR_DIVISOR       = 256;

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef struct st_baud_setting_const_t
{
    uint8_t bgdm  : 1;                 /**< BGDM value to get divisor */
    uint8_t abcs  : 1;                 /**< ABCS value to get divisor */
    uint8_t abcse : 1;                 /**< ABCSE value to get divisor */
    uint8_t cks   : 2;                 /**< CKS  value to get divisor (CKS = N) */
} baud_setting_const_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_scie_config_set(scie_instance_ctrl_t * const p_ctrl, scie_cfg_t const * const p_cfg);
static void r_scie_baud_set(R_SCI0_Type * p_sci_reg, scie_baud_setting_t const * const p_baud_setting);
static void r_scie_irq_cfg(scie_instance_ctrl_t * const p_ctrl, uint8_t const ipl, IRQn_Type const p_irq);
static void r_scie_irqs_cfg(scie_instance_ctrl_t * const p_ctrl, scie_cfg_t const * const p_cfg);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
/** Name of module used by error logger macro */
#if BSP_CFG_ERROR_LOG != 0
static const char g_module_name[] = "scie";
#endif

/** Baud rate divisor information */
static const baud_setting_const_t g_async_baud[SCIE_NUM_DIVISORS_ASYNC] =
{
    {0U, 0U, 1U, 0U},                  /* BGDM, ABCS, ABCSE, n */
    {1U, 1U, 0U, 0U},
    {1U, 0U, 0U, 0U},
    {0U, 0U, 1U, 1U},
    {0U, 0U, 0U, 0U},
    {1U, 0U, 0U, 1U},
    {0U, 0U, 1U, 2U},
    {0U, 0U, 0U, 1U},
    {1U, 0U, 0U, 2U},
    {0U, 0U, 1U, 3U},
    {0U, 0U, 0U, 2U},
    {1U, 0U, 0U, 3U},
    {0U, 0U, 0U, 3U}
};

static const uint16_t g_div_coefficient[SCIE_NUM_DIVISORS_ASYNC] =
{
    6U,
    8U,
    16U,
    24U,
    32U,
    64U,
    96U,
    128U,
    256U,
    384U,
    512U,
    1024U,
    2048U,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************
* Function Name: R_SCIE_Open
* Description  : Open SCIE driver based on the input configurations.
* Arguments    : p_api_ctrl - pointer to the opened api control information
*                p_cfg - pointer to the configurations
* Return Value : Error code.
*******************************************************************************/
fsp_err_t R_SCIE_Open (scie_ctrl_t * const p_api_ctrl, scie_cfg_t const * const p_cfg)
{
    scie_instance_ctrl_t * p_ctrl = (scie_instance_ctrl_t *) p_api_ctrl;

    p_ctrl->fifo_depth = 0U;

    p_ctrl->p_cfg = p_cfg;

    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    p_ctrl->data_bytes = 1U;

    /* Configure the interrupts. */
    r_scie_irqs_cfg(p_ctrl, p_cfg);

    /* Enable the SCIE channel and reset the registers to their initial state. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_SCIE, p_cfg->channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    if (p_cfg->channel < 8u)
    {
        /* Non-Safety Peripheral */
        p_ctrl->p_reg =
            (R_SCI0_Type *) ((uintptr_t) R_SCIE0 + (p_cfg->channel * ((uintptr_t) R_SCIE1 - (uintptr_t) R_SCIE0)));
    }
    else
    {
        /* Safety Peripheral */
        p_ctrl->p_reg =
            (R_SCI0_Type *) ((uintptr_t) R_SCIE8 + ((p_cfg->channel - 8u) * ((uintptr_t) R_SCIE1 - (uintptr_t) R_SCIE0)));
    }

    p_ctrl->p_reg->CCR0 = SCIE_CCR0_DEFAULT_VALUE;
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CCR0_b.RE, 0);
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CCR0_b.TE, 0);
    p_ctrl->p_reg->CCR1 = SCIE_CCR1_DEFAULT_VALUE;
    p_ctrl->p_reg->CCR2 = SCIE_CCR2_DEFAULT_VALUE;
    p_ctrl->p_reg->CCR3 = SCIE_CCR3_DEFAULT_VALUE;
    p_ctrl->p_reg->CCR4 = SCIE_CCR4_DEFAULT_VALUE;

    /* Set the SCIE configuration settings provided in ::scie_cfg_t and ::scie_extended_cfg_t. */
    r_scie_config_set(p_ctrl, p_cfg);

    p_ctrl->p_reg->CFCLR = SCIE_CFCLR_ALL_FLAG_CLEAR;

    p_ctrl->p_tx_src      = NULL;
    p_ctrl->tx_src_bytes  = 0U;
    p_ctrl->p_rx_dest     = NULL;
    p_ctrl->rx_dest_bytes = 0;

    uint32_t ccr0 = SCIE_CCR0_IDSEL_MASK;

    R_BSP_IrqDetectTypeSet(p_ctrl->p_cfg->rxi_irq, SCIE_EVENT_EDGE);
    R_BSP_IrqDetectTypeSet(p_ctrl->p_cfg->eri_irq, SCIE_EVENT_LEVEL);
    R_BSP_IrqEnable(p_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqEnable(p_ctrl->p_cfg->eri_irq);

    ccr0 |= (SCIE_CCR0_RIE_MASK | SCIE_CCR0_RE_MASK);
    R_BSP_IrqDetectTypeSet(p_ctrl->p_cfg->txi_irq, SCIE_EVENT_EDGE);
    R_BSP_IrqDetectTypeSet(p_ctrl->p_cfg->tei_irq, SCIE_EVENT_LEVEL);
    R_BSP_IrqEnable(p_ctrl->p_cfg->txi_irq);
    R_BSP_IrqEnable(p_ctrl->p_cfg->tei_irq);

    ccr0 |= SCIE_CCR0_TE_MASK;
    p_ctrl->p_reg->CCR0 = ccr0;

    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CCR0_b.RE, 1);
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CCR0_b.TE, 1);

    p_ctrl->flow_pin = (bsp_io_port_pin_t) SCIE_INVALID_16BIT_PARAM;

    p_ctrl->open = SCIE_OPEN;

    return FSP_SUCCESS;
}
/*******************************************************************************
 End of function R_SCIE_Open
*******************************************************************************/

/*******************************************************************************
* Function Name: R_SCIE_Close
* Description  : Close SCIE driver.
* Arguments    : p_api_ctrl - pointer to the api control information
* Return Value : Error code.
*******************************************************************************/
fsp_err_t R_SCIE_Close (scie_ctrl_t * const p_api_ctrl)
{
    scie_instance_ctrl_t * p_ctrl = (scie_instance_ctrl_t *) p_api_ctrl;
#if (SCIE_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(SCIE_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Mark the channel not open so other APIs cannot use it. */
    p_ctrl->open = 0U;

    /* Disable interrupts, receiver, and transmitter. Disable baud clock output.*/
    p_ctrl->p_reg->CCR0 = SCIE_CCR0_DEFAULT_VALUE;
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CCR0_b.RE, 0);
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CCR0_b.TE, 0);
    p_ctrl->p_reg->CCR3 &= ~(SCIE_CCR3_CKE_MASK);

    /* If reception is enabled at build time, disable reception irqs. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);

    /* If transmission is enabled at build time, disable transmission irqs. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);

    /* Remove power to the channel. */
    /* Disable the clock to the SCIE channel. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_STOP(FSP_IP_SCIE, p_ctrl->p_cfg->channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    return FSP_SUCCESS;
}
/*******************************************************************************
 End of function R_SCIE_Close
*******************************************************************************/

/*******************************************************************************
* Function Name: R_SCIE_BaudSet
* Description  : Set baudrate of SCIE driver.
* Arguments    : p_api_ctrl - pointer to the api control information
*                p_baud_setting - pointer to the baud information
* Return Value : Error code.
*******************************************************************************/
fsp_err_t R_SCIE_BaudSet (scie_ctrl_t * const p_api_ctrl, void const * const p_baud_setting)
{
    scie_instance_ctrl_t * p_ctrl = (scie_instance_ctrl_t *) p_api_ctrl;

    /* Disables transmitter and receiver. This terminates any in-progress transmission. */
    p_ctrl->p_reg->CCR0 &= (uint32_t) ~(SCIE_CCR0_TE_MASK | SCIE_CCR0_TIE_MASK | SCIE_CCR0_TEIE_MASK |
                                        SCIE_CCR0_RE_MASK | SCIE_CCR0_RIE_MASK);
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CCR0_b.RE, 0);
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CCR0_b.TE, 0);
    p_ctrl->p_tx_src = NULL;

    /* Apply new baud rate register settings. */
    r_scie_baud_set(p_ctrl->p_reg, p_baud_setting);

    uint32_t mask_enable = 0;

    /* Enable receive. */
    mask_enable |= (SCIE_CCR0_RE_MASK | SCIE_CCR0_RIE_MASK);

    /* Enable transmit. */
    mask_enable |= SCIE_CCR0_TE_MASK;
    p_ctrl->p_reg->CCR0 |= mask_enable;

    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CCR0_b.RE, 1);
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CCR0_b.TE, 1);

    return FSP_SUCCESS;
}
/*******************************************************************************
 End of function R_SCIE_BaudSet
*******************************************************************************/

/*******************************************************************************
* Function Name: R_SCIE_BaudCalculate
* Description  : Calculate baud register settings of the SCIE driver.
* Arguments    : basudrate - Baud rate [bps]
*                bitrate_modulation - Flag to enable bitrate modulation
*                baud_rate_error_x_1000 - baud_rate_percent_error x 1000 required to function
*                p_baud_setting - pointer to store result of baud setting information
* Return Value : Error code.
*******************************************************************************/
fsp_err_t R_SCIE_BaudCalculate (uint32_t baudrate, bool bitrate_modulation,
                                uint32_t baud_rate_error_x_1000, scie_baud_setting_t * const p_baud_setting)
{
    p_baud_setting->baudrate_bits_b.brr  = SCIE_BRR_MAX;
    p_baud_setting->baudrate_bits_b.brme = 0U;
    p_baud_setting->baudrate_bits_b.mddr = SCIE_MDDR_MIN;

    /* Find the best BRR (bit rate register) value.
     *  In table g_async_baud, divisor values are stored for BGDM, ABCS, ABCSE and N values.  Each set of divisors
     *  is tried, and the settings with the lowest bit rate error are stored. The formula to calculate BRR is as
     *  follows and it must be 255 or less:
     *  BRR = (PCLK / (div_coefficient * baud)) - 1
     */
    int32_t  hit_bit_err = SCIE_100_PERCENT_X_1000;
    uint32_t hit_mddr    = 0U;
    uint32_t divisor     = 0U;
    uint32_t freq_hz     = SCIE_CLOCK_96MHZ;

    for (uint32_t select_16_base_clk_cycles = 0U;
         select_16_base_clk_cycles <= 1U && (hit_bit_err > ((int32_t) baud_rate_error_x_1000));
         select_16_base_clk_cycles++)
    {
        for (uint32_t i = 0U; i < SCIE_NUM_DIVISORS_ASYNC; i++)
        {
            /* if select_16_base_clk_cycles == true:  Skip this calculation for divisors that are not acheivable with 16 base clk cycles per bit.
             *  if select_16_base_clk_cycles == false: Skip this calculation for divisors that are only acheivable without 16 base clk cycles per bit.
             */
            if (((uint8_t) select_16_base_clk_cycles) ^ (g_async_baud[i].abcs | g_async_baud[i].abcse))
            {
                continue;
            }

            divisor = (uint32_t) g_div_coefficient[i] * baudrate;
            uint32_t temp_brr = freq_hz / divisor;

            if (temp_brr <= (SCIE_BRR_MAX + 1U))
            {
                while (temp_brr > 0U)
                {
                    temp_brr -= 1U;

                    /* Calculate the bit rate error. The formula is as follows:
                     *  bit rate error[%] = {(PCLK / (baud * div_coefficient * (BRR + 1)) - 1} x 100
                     *  calculates bit rate error[%] to three decimal places
                     */
                    int32_t err_divisor = (int32_t) (divisor * (temp_brr + 1U));

                    /* Promoting to 64 bits for calculation, but the final value can never be more than 32 bits, as
                     * described below, so this cast is safe.
                     *    1. (temp_brr + 1) can be off by an upper limit of 1 due to rounding from the calculation:
                     *       freq_hz / divisor, or:
                     *       freq_hz / divisor <= (temp_brr + 1) < (freq_hz / divisor) + 1
                     *    2. Solving for err_divisor:
                     *       freq_hz <= err_divisor < freq_hz + divisor
                     *    3. Solving for bit_err:
                     *       0 >= bit_err >= (freq_hz * 100000 / (freq_hz + divisor)) - 100000
                     *    4. freq_hz >= divisor (or temp_brr would be -1 and we would never enter this while loop), so:
                     *       0 >= bit_err >= 100000 / freq_hz - 100000
                     *    5. Larger frequencies yield larger bit errors (absolute value).  As the frequency grows,
                     *       the bit_err approaches -100000, so:
                     *       0 >= bit_err >= -100000
                     *    6. bit_err is between -100000 and 0.  This entire range fits in an int32_t type, so the cast
                     *       to (int32_t) is safe.
                     */
                    int32_t bit_err = (int32_t) (((((int64_t) freq_hz) * SCIE_100_PERCENT_X_1000) /
                                                  err_divisor) - SCIE_100_PERCENT_X_1000);

                    uint32_t mddr = 0U;
                    if (bitrate_modulation)
                    {
                        /* Calculate the MDDR (M) value if bit rate modulation is enabled,
                         * The formula to calculate MBBR (from the M and N relationship given in the hardware manual) is as follows
                         * and it must be between 128 and 256.
                         * MDDR = ((div_coefficient * baud * 256) * (BRR + 1)) / PCLK */
                        mddr = (uint32_t) err_divisor / (freq_hz / SCIE_MDDR_MAX);

                        /* The maximum value that could result from the calculation above is 256, which is a valid MDDR
                         * value, so only the lower bound is checked. */
                        if (mddr < SCIE_MDDR_MIN)
                        {
                            break;
                        }

                        /* Adjust bit rate error for bit rate modulation. The following formula is used:
                         *  bit rate error [%] = ((bit rate error [%, no modulation] + 100) * MDDR / 256) - 100
                         */
                        bit_err = (((bit_err + SCIE_100_PERCENT_X_1000) * (int32_t) mddr) /
                                   SCIE_MDDR_DIVISOR) - SCIE_100_PERCENT_X_1000;
                    }

                    /* Take the absolute value of the bit rate error. */
                    if (bit_err < 0)
                    {
                        bit_err = -bit_err;
                    }

                    /* If the absolute value of the bit rate error is less than the previous lowest absolute value of
                     *  bit rate error, then store these settings as the best value.
                     */
                    if (bit_err < hit_bit_err)
                    {
                        p_baud_setting->baudrate_bits_b.bgdm  = g_async_baud[i].bgdm;
                        p_baud_setting->baudrate_bits_b.abcs  = g_async_baud[i].abcs;
                        p_baud_setting->baudrate_bits_b.abcse = g_async_baud[i].abcse;
                        p_baud_setting->baudrate_bits_b.cks   = g_async_baud[i].cks;
                        p_baud_setting->baudrate_bits_b.brr   = (uint8_t) temp_brr;
                        hit_bit_err = bit_err;
                        hit_mddr    = mddr;
                    }

                    if (bitrate_modulation)
                    {
                        p_baud_setting->baudrate_bits_b.brme = 1U;
                        p_baud_setting->baudrate_bits_b.mddr = (uint8_t) hit_mddr;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }

    /* Return an error if the percent error is larger than the maximum percent error allowed for this instance */
    FSP_ERROR_RETURN((hit_bit_err <= (int32_t) baud_rate_error_x_1000), FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}
/*******************************************************************************
 End of function R_SCIE_BaudCalculate
*******************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures SCIE related registers based on user configurations.
 *
 * @param[in]     p_ctrl  Pointer to SCIE control structure
 * @param[in]     p_cfg   Pointer to SCIE specific configuration structure
 **********************************************************************************************************************/
static void r_scie_config_set (scie_instance_ctrl_t * const p_ctrl, scie_cfg_t const * const p_cfg)
{
    /* CCR3 register setting. */
    uint32_t ccr3 = SCIE_CCR3_DEFAULT_VALUE;

    /* FIFO support is disabled. */
    p_ctrl->p_reg->FCR = SCIE_FCR_DEFAULT_VALUE;

    /* Configure stop bits. */
    ccr3 |= (uint32_t) p_cfg->stop_bits << SCIE_CCR3_STP_OFFSET;

    /* Configure CKE bits. */
    scie_extended_cfg_t * p_extend = (scie_extended_cfg_t *) p_cfg->p_extend;
    ccr3 |= (p_extend->clock & SCIE_CCR3_CKE_VALUE_MASK) << SCIE_CCR3_CKE_OFFSET;

    /* Starts reception on falling edge of RXD if enabled in extension (otherwise reception starts at low level
     * of RXD). */
    ccr3 |= (p_extend->rx_edge_start & 1U) << SCIE_CCR3_RxDSEL_OFFSET;

    /* Configure SPEN bit. */
    ccr3 |= (p_extend->sync_bypass & 1U) << SCIE_CCR3_BPEN_OFFSET;

    /* Write to the CCR3 register. */
    p_ctrl->p_reg->CCR3 = ccr3;

    /* CCR1 register setting. */
    uint32_t ccr1 = SCIE_CCR1_DEFAULT_VALUE;

    /* Set the default level of the TX pin to 1. */
    ccr1 |= (uint32_t) (1U << SCIE_CCR1_SPB2DT_BIT | SCIE_CCR1_OUTPUT_ENABLE_MASK);

    /* Configure CTS flow control if CTS/RTS flow control is enabled. */
    ccr1 |= (uint32_t) (p_extend->ctsrts_en << SCIE_CCR1_CTSE_OFFSET);

    p_ctrl->p_reg->CCR1 = ccr1;

    /* Set the baud rate settings for the internal baud rate generator. */
    r_scie_baud_set(p_ctrl->p_reg, p_extend->p_baud_setting);
}

/*******************************************************************************
End of function r_scie_config_set
*******************************************************************************/

/*******************************************************************************************************************//**
 * Sets interrupt priority and initializes vector info.
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 * @param[in]  ipl                       Interrupt priority level
 * @param[in]  irq                       IRQ number for this interrupt
 **********************************************************************************************************************/
static void r_scie_irq_cfg (scie_instance_ctrl_t * const p_ctrl, uint8_t const ipl, IRQn_Type const irq)
{
    /* Disable interrupts, set priority, and store control block in the vector information so it can be accessed
     * from the callback. */
    R_BSP_IrqDisable(irq);

    R_BSP_IrqCfg(irq, ipl, p_ctrl);
}

/*******************************************************************************
End of function r_scie_irq_cfg
*******************************************************************************/

/*******************************************************************************************************************//**
 * Sets interrupt priority and initializes vector info for all interrupts.
 *
 * @param[in]  p_ctrl                    Pointer to SCIE instance control block
 * @param[in]  p_cfg                     Pointer to SCIE specific configuration structure
 **********************************************************************************************************************/
static void r_scie_irqs_cfg (scie_instance_ctrl_t * const p_ctrl, scie_cfg_t const * const p_cfg)
{
    r_scie_irq_cfg(p_ctrl, p_cfg->eri_ipl, p_cfg->eri_irq);
    r_scie_irq_cfg(p_ctrl, p_cfg->rxi_ipl, p_cfg->rxi_irq);
    r_scie_irq_cfg(p_ctrl, p_cfg->txi_ipl, p_cfg->txi_irq);
    r_scie_irq_cfg(p_ctrl, p_cfg->tei_ipl, p_cfg->tei_irq);
}

/*******************************************************************************
End of function r_scie_irqs_cfg
*******************************************************************************/

/*******************************************************************************************************************//**
 * Changes baud rate based on predetermined register settings.
 *
 * @param[in]  p_sci_reg       Base pointer for SCI registers
 * @param[in]  p_baud_setting  Pointer to other divisor related settings
 *
 * @note       The transmitter and receiver (TE and RE bits in SCR) must be disabled prior to calling this function.
 **********************************************************************************************************************/
static void r_scie_baud_set (R_SCI0_Type * p_sci_reg, scie_baud_setting_t const * const p_baud_setting)
{
    p_sci_reg->CCR2 = (uint32_t) ((p_sci_reg->CCR2 & ~(SCIE_CCR2_BAUD_SETTING_MASK)) |
                                  (p_baud_setting->baudrate_bits & SCIE_CCR2_BAUD_SETTING_MASK));
}

/*******************************************************************************
End of function r_scie_baud_set
*******************************************************************************/
