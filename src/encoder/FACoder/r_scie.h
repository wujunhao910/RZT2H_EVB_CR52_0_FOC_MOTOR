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

#ifndef R_SCIE_H
#define R_SCIE_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_uart_api.h"
#include "r_sci_uart_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** SCIE Event codes */
typedef enum e_scie_sf_event
{
    SCIE_EVENT_RX_COMPLETE   = (1UL << 0), ///< Receive complete event
    SCIE_EVENT_TX_COMPLETE   = (1UL << 1), ///< Transmit complete event
    SCIE_EVENT_RX_CHAR       = (1UL << 2), ///< Character received
    SCIE_EVENT_ERR_PARITY    = (1UL << 3), ///< Parity error event
    SCIE_EVENT_ERR_FRAMING   = (1UL << 4), ///< Mode fault error event
    SCIE_EVENT_ERR_OVERFLOW  = (1UL << 5), ///< FIFO Overflow error event
    SCIE_EVENT_BREAK_DETECT  = (1UL << 6), ///< Break detect error event
    SCIE_EVENT_TX_DATA_EMPTY = (1UL << 7), ///< Last byte is transmitting, ready for more data
} scie_event_t;

/** SCIE Data bit length definition */
typedef enum e_scie_data_bits
{
    SCIE_DATA_BITS_9 = 0U,             ///< Data bits 9-bit
    SCIE_DATA_BITS_8 = 2U,             ///< Data bits 8-bit
    SCIE_DATA_BITS_7 = 3U,             ///< Data bits 7-bit
} scie_data_bits_t;

/** SCIE Parity definition */
typedef enum e_scie_parity
{
    SCIE_PARITY_OFF  = 0U,             ///< No parity
    SCIE_PARITY_EVEN = 2U,             ///< Even parity
    SCIE_PARITY_ODD  = 3U,             ///< Odd parity
} scie_parity_t;

/** SCIE Stop bits definition */
typedef enum e_scie_stop_bits
{
    SCIE_STOP_BITS_1 = 0U,             ///< Stop bit 1-bit
    SCIE_STOP_BITS_2 = 1U,             ///< Stop bits 2-bit
} scie_stop_bits_t;

/** SCIE Callback parameter definition */
typedef struct st_scie_callback_arg
{
    uint32_t     channel;              ///< Device channel number
    scie_event_t event;                ///< Event code

    /** Contains the next character received for the events SCIE_EVENT_RX_CHAR, SCIE_EVENT_ERR_PARITY,
     * SCIE_EVENT_ERR_FRAMING, or SCIE_EVENT_ERR_OVERFLOW.  Otherwise unused. */
    uint32_t     data;
    void const * p_context;            ///< Context provided to user during callback
} scie_callback_args_t;

/** SCIE Configuration */
typedef struct st_scie_cfg
{
    /* SCIE generic configuration */
    uint8_t          channel;          ///< Select a channel corresponding to the channel number of the hardware.
    scie_data_bits_t data_bits;        ///< Data bit length (8 or 7 or 9)
    scie_parity_t    parity;           ///< Parity type (none or odd or even)
    scie_stop_bits_t stop_bits;        ///< Stop bit length (1 or 2)
    uint8_t          rxi_ipl;          ///< Receive interrupt priority
    IRQn_Type        rxi_irq;          ///< Receive interrupt IRQ number
    uint8_t          txi_ipl;          ///< Transmit interrupt priority
    IRQn_Type        txi_irq;          ///< Transmit interrupt IRQ number
    uint8_t          tei_ipl;          ///< Transmit end interrupt priority
    IRQn_Type        tei_irq;          ///< Transmit end interrupt IRQ number
    uint8_t          eri_ipl;          ///< Error interrupt priority
    IRQn_Type        eri_irq;          ///< Error interrupt IRQ number

    /** Optional transfer instance used to receive multiple bytes without interrupts.  Set to NULL if unused.
     * If NULL, the number of bytes allowed in the read API is limited to one byte at a time. */
    transfer_instance_t const * p_transfer_rx;

    /** Optional transfer instance used to send multiple bytes without interrupts.  Set to NULL if unused.
     * If NULL, the number of bytes allowed in the write APIs is limited to one byte at a time. */
    transfer_instance_t const * p_transfer_tx;

    /* Configuration for SCIE Event processing */
    void (* p_callback)(scie_callback_args_t * p_args); ///< Pointer to callback function
    void const * p_context;                             ///< User defined context passed into callback function

    /* Pointer to SCIE peripheral specific configuration */
    void const * p_extend;                              ///< SCIE hardware dependent configuration
} scie_cfg_t;

/** SCIE control block.  Allocate an instance specific control block to pass into the SCIE API calls.
 */
typedef void scie_ctrl_t;

/** Enumeration for SCIE clock source.
 * This enumeration name will be changed in the major release. */
typedef enum e_scie_clk_src
{
    SCIE_CLOCK_INT,                      ///< Use internal clock for baud generation
    SCIE_CLOCK_INT_WITH_BAUDRATE_OUTPUT, ///< Use internal clock for baud generation and output on SCK
    SCIE_CLOCK_EXT8X,                    ///< Use external clock 8x baud rate
    SCIE_CLOCK_EXT16X                    ///< Use external clock 16x baud rate
} scie_clk_src_t;

/** SCIE instance control block. */
typedef struct st_scie_instance_ctrl
{
    /* Parameters to control SCIE peripheral device */
    uint8_t  fifo_depth;               // FIFO depth of the channel
    uint8_t  rx_transfer_in_progress;  // Set to 1 if a receive transfer is in progress, 0 otherwise
    uint8_t  data_bytes         : 2;   // 1 byte for 7 or 8 bit data, 2 bytes for 9 bit data
    uint8_t  bitrate_modulation : 1;   // 1 if bit rate modulation is enabled, 0 otherwise
    uint32_t open;                     // Used to determine if the channel is configured

    bsp_io_port_pin_t flow_pin;

    /* Source buffer pointer used to fill hardware FIFO from transmit ISR. */
    uint8_t const * p_tx_src;

    /* Size of source buffer pointer used to fill hardware FIFO from transmit ISR. */
    uint32_t tx_src_bytes;

    /* Destination buffer pointer used for receiving data. */
    uint8_t const * p_rx_dest;

    /* Size of destination buffer pointer used for receiving data. */
    uint32_t rx_dest_bytes;

    /* Pointer to the configuration block. */
    scie_cfg_t const * p_cfg;

    /* Base register for this channel */
    R_SCI0_Type * p_reg;

    void (* p_callback)(scie_callback_args_t *); // Pointer to callback that is called when a scie_event_t occurs.
    scie_callback_args_t * p_callback_memory;    // Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.

    /* Pointer to context to be passed into callback function */
    void const * p_context;
} scie_instance_ctrl_t;

/** Asynchronous Start Bit Edge Detection configuration. */
typedef enum e_scie_start_bit
{
    SCIE_START_BIT_LOW_LEVEL    = 0x0, ///< Detect low level on RXDn pin as start bit
    SCIE_START_BIT_FALLING_EDGE = 0x1, ///< Detect falling level on RXDn pin as start bit
} scie_start_bit_t;

/** CTS/RTS function of the SSn pin. */
typedef enum e_scie_ctsrts_config
{
    SCIE_CTSRTS_RTS_OUTPUT = 0x0,  ///< Disable CTS function (RTS output function is enabled)
    SCIE_CTSRTS_CTS_INPUT  = 0x1,  ///< Enable CTS function
} scie_ctsrts_config_t;

/** Noise cancellation configuration. */
typedef enum e_scie_noise_cancellation
{
    SCIE_NOISE_CANCELLATION_DISABLE                 = 0x0, ///< Disable noise cancellation
    SCIE_NOISE_CANCELLATION_ENABLE                  = 0x1, ///< Enable noise cancellation, The base clock signal divided by 1
    SCIE_NOISE_CANCELLATION_ENABLE_FILTER_CKS_DIV_1 = 0x2, ///< Enable noise cancellation, The on-chip baud rate generator source clock divided by 1
    SCIE_NOISE_CANCELLATION_ENABLE_FILTER_CKS_DIV_2 = 0x3, ///< Enable noise cancellation, The on-chip baud rate generator source clock divided by 2
    SCIE_NOISE_CANCELLATION_ENABLE_FILTER_CKS_DIV_4 = 0x4, ///< Enable noise cancellation, The on-chip baud rate generator source clock divided by 4
    SCIE_NOISE_CANCELLATION_ENABLE_FILTER_CKS_DIV_8 = 0x5, ///< Enable noise cancellation, The on-chip baud rate generator source clock divided by 8
} scie_noise_cancellation_t;

/** Synchronizer circuit configuration. */
typedef enum e_scie_synchronizer
{
    SCIE_SYNCHRONIZER_NOT_BYPASS = 0x0, ///< Synchronizer bypass disable
    SCIE_SYNCHRONIZER_BYPASS     = 0x1  ///< Synchronizer bypass enable
} scie_synchronizer_t;

/** Register settings to achieve a desired baud rate and modulation duty. */
typedef struct st_scie_baud_setting_t
{
    union
    {
        uint32_t baudrate_bits;

        struct
        {
            uint32_t       : 4;
            uint32_t bgdm  : 1;        ///< Baud Rate Generator Double-Speed Mode Select
            uint32_t abcs  : 1;        ///< Asynchronous Mode Base Clock Select
            uint32_t abcse : 1;        ///< Asynchronous Mode Extended Base Clock Select 1
            uint32_t       : 1;
            uint32_t brr   : 8;        ///< Bit Rate Register setting
            uint32_t brme  : 1;        ///< Bit Rate Modulation Enable
            uint32_t       : 3;
            uint32_t cks   : 2;        ///< CKS  value to get divisor (CKS = N)
            uint32_t       : 2;
            uint32_t mddr  : 8;        ///< Modulation Duty Register setting
        } baudrate_bits_b;
    };
} scie_baud_setting_t;

/** SCIE device Configuration */
typedef struct st_scie_extended_cfg
{
    scie_clk_src_t            clock;          ///< The source clock for the baud-rate generator. If internal optionally output baud rate on SCK
    scie_start_bit_t          rx_edge_start;  ///< Start reception on falling edge
    scie_noise_cancellation_t noise_cancel;   ///< Noise cancellation setting
    scie_baud_setting_t     * p_baud_setting; ///< Register settings for a desired baud rate.
    scie_ctsrts_config_t      ctsrts_en;      ///< CTS/RTS function of the SSn pin
    scie_synchronizer_t       sync_bypass;    ///< Clock synchronizer selection
} scie_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/*******************************************************************************
 * Public Functions
 *******************************************************************************/
fsp_err_t R_SCIE_Open(scie_ctrl_t * const p_api_ctrl, scie_cfg_t const * const p_cfg);
fsp_err_t R_SCIE_Close(scie_ctrl_t * const p_api_ctrl);
fsp_err_t R_SCIE_BaudSet (scie_ctrl_t * const p_api_ctrl, void const * const p_baud_setting);
fsp_err_t R_SCIE_BaudCalculate (uint32_t baudrate, bool bitrate_modulation,
                                uint32_t baud_rate_error_x_1000, scie_baud_setting_t * const p_baud_setting);

#endif /* R_SCIE_H */
