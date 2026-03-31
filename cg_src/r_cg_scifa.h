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
* File Name    : r_cg_scifa.h
* Version      : 1.00
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Header file of SCIF module.
***********************************************************************************************************************/
#ifndef SCIF_H
#define SCIF_H

#include "bsp_api.h"

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
  Common Control Register 0 (CCR0)
*/

/* Receive Enable */
#define _SCI_RECV_DISABLE                    (0x00000000UL)    /* Receive Disable */
#define _SCI_RECV_ENABLE                     (0x00000001UL)    /* Receive Enable */
/* Transmit Enable */
#define _SCI_TRANS_DISABLE                   (0x00000000UL)    /* Transmit Disable */
#define _SCI_TRANS_ENABLE                    (0x00000010UL)    /* Transmit Enable */
/* Multi-Processor Interrupt Enable */
#define _SCI_MULTI_PROCESS_INT_DISABLE       (0x00000000UL)    /* Non-Multi-Processor reception */
#define _SCI_MULTI_PROCESS_INT_ENABLE        (0x00000100UL)    /* Multi -Processor reception */
/* Data Compare Match Enable */
#define _SCI_DATA_COMP_MATCH_DISABLE         (0x00000000UL)    /* Address match function is disabled */
#define _SCI_DATA_COMP_MATCH_ENABLE          (0x00000200UL)    /* Address match function is enabled */
/* ID frame select Bit */
#define _SCI_ID_FRM_SEL_DISABLE              (0x00000000UL)    /* always compared */
#define _SCI_ID_FRM_SEL_ENABLE               (0x00000400UL)    /* when the MPB bit is "1" (ID frame ) only */
/* Receive Interrupt Enable */
#define _SCI_RECV_INT_DISABLE                (0x00000000UL)    /* Receive Interrupt Disable */
#define _SCI_RECV_INT_ENABLE                 (0x00010000UL)    /* Receive Interrupt Enable */
/* Transmit Interrupt Enable */
#define _SCI_TRANS_INT_DISABLE               (0x00000000UL)    /* Transmit Interrupt Disable */
#define _SCI_TRANS_INT_ENABLE                (0x00200000UL)    /* Transmit Interrupt Enable */
/* Transmit End Interrupt Enable */
#define _SCI_TRANS_END_INT_DISABLE           (0x00000000UL)    /* Transmit End Interrupt Disable */
#define _SCI_TRANS_END_INT_ENABLE            (0x00200000UL)    /* Transmit End Interrupt Enable */
/* SSn# Pin Function Enable */
#define _SCI_SSN_PIN_FUNC_DISABLE            (0x00000000UL)    /* Transmit End Interrupt Disable */
#define _SCI_SSN_PIN_FUNC_ENABLE             (0x00200000UL)    /* Transmit End Interrupt Enable */

/*
  Common Control Register 1 (CCR1)
*/

/* CTS Enable */
#define _SCI_CTS_FUNC_DISABLE                (0x00000000UL)    /* CTS function is disabled */
#define _SCI_CTS_FUNC_ENABLE                 (0x00000001UL)    /* CTS function is enabled */
/* CTS external pin Enable */
#define _SCI_CTS_EXT_PIN_DISABLE             (0x00000000UL)    /* Alternate setting */
#define _SCI_CTS_EXT_PIN_ENABLE              (0x00000002UL)    /* Dedicated setting */
/* Serial port break data select bit */
#define _SCI_BREAK_DATA_SEL_0                (0x00000000UL)    /* TINV is 1'b0 -> Low, TINV is 1'b1 -> High */
#define _SCI_BREAK_DATA_SEL_1                (0x00000010UL)    /* TINV is 1'b0 -> High, TINV is 1'b1 -> Low */
/* Serial port break I/O bit */
#define _SCI_BREAK_IO_0                      (0x00000000UL)    /* The value of SPB2DT bit isn't output */
#define _SCI_BREAK_IO_1                      (0x00000020UL)    /* The value of SPB2DT bit is output */
/* Parity Enable */
#define _SCI_PARITY_DISABLE                  (0x00000000UL)    /* Parity is disabled */
#define _SCI_PARITY_ENABLE                   (0x00000100UL)    /* Parity is enabled */
/* Parity Mode */
#define _SCI_PARITY_MODE_EVEN                (0x00000000UL)    /* even parity */
#define _SCI_PARITY_MODE_ODD                 (0x00000200UL)    /* odd parity */
/* TxD invert bit */
#define _SCI_TXD_INVERT_DISABLE              (0x00000000UL)    /* Received data from RxD is not inverted and input */
#define _SCI_TXD_INVERT_ENABLE               (0x00001000UL)    /* Received data from RxD is inverted and input */
/* RxD invert bit */
#define _SCI_RXD_INVERT_DISABLE              (0x00000000UL)    /* Transmit data is not inverted and output to TxD */
#define _SCI_RXD_INVERT_ENABLE               (0x00002000UL)    /* Transmit data is inverted and output to TxD */
/* Loopback Control bit */
#define _SCI_LOOPBACK_DISABLE                (0x00000000UL)    /* Normal mode */
#define _SCI_LOOPBACK_ENABLE                 (0x00010000UL)    /* Loopback mode */
/* Half-duplex communication select bit */
#define _SCI_HALF_DUPLEX_DISABLE             (0x00000000UL)    /* TXD terminal, RXD terminal independent */
#define _SCI_HALF_DUPLEX_ENABLE              (0x00100000UL)    /* TXD / RXD terminal combination use */
/* Noise Filter Clock Select */
#define _SCI_NOISE_FILTER_CLK_BASE_DIVIDE_1  (0x00000000UL)    /* The base clock signal divided by 1 */
#define _SCI_NOISE_FILTER_CLK_SRC_DIVIDE_1   (0x01000000UL)    /* The on-chip baud rate generator source clock divided by 1 */
#define _SCI_NOISE_FILTER_CLK_SRC_DIVIDE_2   (0x02000000UL)    /* The on-chip baud rate generator source clock divided by 2 */
#define _SCI_NOISE_FILTER_CLK_SRC_DIVIDE_4   (0x04000000UL)    /* The on-chip baud rate generator source clock divided by 4 */
#define _SCI_NOISE_FILTER_CLK_SRC_DIVIDE_8   (0x08000000UL)    /* The on-chip baud rate generator source clock divided by 8 */
/* Digital Noise Filter Function Enable */
#define _SCI_DIGTAL_NOISE_FILTER_DISABLE     (0x00000000UL)    /* Digital Noise Filter Function is disabled */
#define _SCI_DIGTAL_NOISE_FILTER_ENABLE      (0x10000000UL)    /* Digital Noise Filter Function is enabled */

/*
  Common Control Register 2 (CCR2)
*/

/* Base Clock Pulse */
#define _SCI_BASE_CLK_CYCLE_93               (0x00000000UL)    /* 93 clock cycles */
#define _SCI_BASE_CLK_CYCLE_128              (0x00000001UL)    /* 128 clock cycles */
#define _SCI_BASE_CLK_CYCLE_186              (0x00000002UL)    /* 186 clock cycles */
#define _SCI_BASE_CLK_CYCLE_512              (0x00000003UL)    /* 512 clock cycles */
#define _SCI_BASE_CLK_CYCLE_32               (0x00000004UL)    /* 32 clock cycles */
#define _SCI_BASE_CLK_CYCLE_64               (0x00000005UL)    /* 64 clock cycles */
#define _SCI_BASE_CLK_CYCLE_372              (0x00000006UL)    /* 372 clock cycles */
#define _SCI_BASE_CLK_CYCLE_256              (0x00000007UL)    /* 256 clock cycles */
/* Baud Rate Generator Double-Speed Mode Select */
#define _SCI_BAUDRATE_GEN_MODE_SINGLE        (0x00000000UL)    /* with single frequency */
#define _SCI_BAUDRATE_GEN_MODE_DOUBLE        (0x00000010UL)    /* with doubled frequency */
/* Asynchronous Mode Base Clock Select */
#define _SCI_ASYNC_MODE_BASE_CLK_16          (0x00000000UL)    /* Selects 16 base clock cycles */
#define _SCI_ASYNC_MODE_BASE_CLK_8           (0x00000020UL)    /* Selects 8 base clock cycles */
/* Asynchronous Mode Extended Base Clock Select */
#define _SCI_ASYNC_MODE_EXT_BASE_CLK_0       (0x00000000UL)    /* decided with combination be-tween CCR2.BGDM and CCR2.ABCS.*/
#define _SCI_ASYNC_MODE_EXT_BASE_CLK_1       (0x00000040UL)    /* Baud rate is 6 base clock cycles */
/* Bit Modulation Enable */
#define _SCI_BIT_MODULATION_DISABLE          (0x00000000UL)    /* Bit rate modulation function is disabled */
#define _SCI_BIT_MODULATION_ENABLE           (0x00000100UL)    /* Bit rate modulation function is enabled */
/* Clock Select */
#define _SCI_CLOCK_SEL_DIV_1                 (0x00000000UL)    /* TCLK clock (n = 0) */
#define _SCI_CLOCK_SEL_DIV_4                 (0x00001000UL)    /* TCLK clock/4 (n = 1) */
#define _SCI_CLOCK_SEL_DIV_16                (0x00002000UL)    /* TCLK clock/16 (n = 2) */
#define _SCI_CLOCK_SEL_DIV_64                (0x00003000UL)    /* TCLK clock/64 (n = 3) */

/*
  Common Control Register 3 (CCR3)
*/

/* Clock Phase Select */
#define _SCI_CLOCK_PHASE_SEL_DELAY      (0x00000000UL)    /* Clock is delayed */
#define _SCI_CLOCK_PHASE_SEL_NOT_DELAY  (0x00000001UL)    /* Clock is not delayed */
/* Clock Polarity Select */
#define _SCI_CLOCK_POLARITY_SEL_0       (0x00000000UL)    /* SCKn in idle state is 0 */
#define _SCI_CLOCK_POLARITY_SEL_1       (0x00000002UL)    /* SCKn in idle state is 1 */
/* Synchronizer bypass enable bit */
#define _SCI_SYNC_BYPASS_DISABLE        (0x00000000UL)    /* Synchronizer circuit is not bypassed */
#define _SCI_SYNC_BYPASS_ENABLE         (0x00000080UL)    /* Synchronizer circuit is bypassed */
/* Character Length */
#define _SCI_CHAR_LENGTH_9BIT_0         (0x00000000UL)    /* Transmit/receive in 9-bit data length */
#define _SCI_CHAR_LENGTH_9BIT_1         (0x00000100UL)    /* Transmit/receive in 9-bit data length */
#define _SCI_CHAR_LENGTH_8BIT           (0x00000200UL)    /* Transmit/receive in 8-bit data length */
#define _SCI_CHAR_LENGTH_7BIT           (0x00000300UL)    /* Transmit/receive in 7-bit data length */
/* LSB First select bit */
#define _SCI_MSB_FIRST                  (0x00000000UL)    /* 0: MSB first */
#define _SCI_LSB_FIRST                  (0x00001000UL)    /* 1: LSB first */
/* Transmitted/Received Data Invert */
#define _SCI_TXRX_INVERT_DISABLE        (0x00000000UL)    /* Transmitted/Received Data is not inverted */
#define _SCI_TXRX_INVERT_ENABLE         (0x00002000UL)    /* Transmitted/Received Data is inverted */
/* Stop Bit Length */
#define _SCI_STOP_BIT_1                 (0x00000000UL)    /* 1 stop bit */
#define _SCI_STOP_BIT_2                 (0x00004000UL)    /* 2 stop bits */
/* Asynchronous Start Bit Edge Detection Select */
#define _SCI_ASYNC_START_BIT_LOW_LEVE   (0x00000000UL)    /*  The low level on the RxDn pin is detected as the start bit */
#define _SCI_ASYNC_START_BIT_FALL_EDGE  (0x00008000UL)    /* A falling edge on the RxDn pin is detected as the start bit */
/* Communication mode select bit */
#define _SCI_COMM_MODE_ASYNC            (0x00000000UL)    /* Asynchronous mode (Multi-processor mode) */
#define _SCI_COMM_MODE_SMART_CARD       (0x00010000UL)    /* Smart card interface mode */
#define _SCI_COMM_MODE_CLK_SYNC         (0x00020000UL)    /* Clock synchronous mode */
#define _SCI_COMM_MODE_SPI              (0x00030000UL)    /* Simple SPI mode */
#define _SCI_COMM_MODE_I2C              (0x00040000UL)    /* Simple I2C mode */
/* Multi-Processor Mode */
#define _SCI_MULTI_PROCESS_DISABLE      (0x00000000UL)    /* Multi-processor communications function is disabled */
#define _SCI_MULTI_PROCESS_ENABLE       (0x00080000UL)    /* Multi-processor communications function is enabled */
/* FIFO Mode select */
#define _SCI_FIFO_MODE_DISABLE          (0x00000000UL)    /* TDR register, RDR register is non-FIFO buffer configuration */
#define _SCI_FIFO_MODE_ENABLE           (0x00100000UL)    /* TDR register, RDR register is FIFO buffer configuration */
/* Driver enable bit */
#define _SCI_485_DRIVER_DISABLE         (0x00000000UL)    /* RS-485 Driver control function disable */
#define _SCI_485_DRIVER_ENABLE          (0x00200000UL)    /* RS-485 Driver control function enable */
/* Clock enable */
#define _SCI_CLK_ASYNC_0                (0x00000000UL)    /* The SCKn pin is available for use as an I/O port in accord with the I/O port settings */
#define _SCI_CLK_ASYNC_1                (0x01000000UL)    /* The clock with the same frequency as the bit rate is output from the SCKn pin */
#define _SCI_CLK_ASYNC_EXT              (0x02000000UL)    /* External clock */
/* Asynchronous Mode Clock Source select */
#define _SCI_ASYNC_MODE_CLK_SRC_EX      (0x00000000UL)    /* External clock input */
/* GSM Mode */
#define _SCI_GSM_MODE_DISABLE           (0x00000000UL)    /* Non-GSM mode operation */
#define _SCI_GSM_MODE_ENABLE            (0x10000000UL)    /* GSM mode operation */
/* Block Transfer Mode */
#define _SCI_BLOCK_TRANSFER_DISABLE     (0x00000000UL)    /* Non-block transfer mode operation */
#define _SCI_BLOCK_TRANSFER_ENABLE      (0x20000000UL)    /* Block transfer mode operation */

/*
  Common Control Register 4 (CCR4)
*/

/* Adjust receive sampling timing enable */
#define _SCI_ADJ_SAMPLE_TIME_DISABLE    (0x00000000UL)    /* Adjust sampling timing disable */
#define _SCI_ADJ_SAMPLE_TIME_ENABLE     (0x00000100UL)    /* Adjust sampling timing enable */
/* Adjust transmit timing enable */
#define _SCI_ADJ_TRANS_TIME_DISABLE     (0x00000000UL)    /* Adjust transmit timing disable */
#define _SCI_ADJ_TRANS_TIME_ENABLE      (0x00000200UL)    /* Adjust transmit timing enable */
/* Adjustment value for receive Sampling Timing */
#define _SCI_ADJ_RECV_SAMP_TIME_1TCLK   (0x00000000UL)    /* 1TCLK delay */
#define _SCI_ADJ_RECV_SAMP_TIME_2TCLK   (0x00010000UL)    /* 2TCLK delay */
#define _SCI_ADJ_RECV_SAMP_TIME_3TCLK   (0x00020000UL)    /* 3TCLK delay */
#define _SCI_ADJ_RECV_SAMP_TIME_4TCLK   (0x00030000UL)    /* 4TCLK delay */
/* Adjustment Direction for receive sampling timing */
#define _SCI_ADJ_DIRECT_SAMP_TIME_BACK  (0x00000000UL)    /* The sampling timing is adjusted backward to the middle of bit */
#define _SCI_ADJ_DIRECT_SAMP_TIME_FWD   (0x00040000UL)    /* The sampling timing is adjusted forward to the middle of bit */
/* Adjustment edge for transmit timing */
#define _SCI_ADJ_EDGE_TRANS_TIME_0      (0x00000000UL)    /* CCR1.TINV is 1'b0 -> rising edge, CCR1.TINV is 1'b1 -> falling edge */
#define _SCI_ADJ_EDGE_TRANS_TIME_1      (0x80000000UL)    /* CCR1.TINV is 1'b0 -> falling edge, CCR1.TINV is 1'b1 -> rising edge */

/*
  FIFO Control Register (FCR)
*/

/* Receive data ready error select bit */
#define _SCI_RECV_DATA_ERR_SEL_RXI      (0x00000000UL)    /* reception data full interrupt (RXI) */
#define _SCI_RECV_DATA_ERR_SEL_ERI      (0x00000001UL)    /* receive error interrupt (ERI) */
/* Transmit FIFO Data Register Reset */
#define _SCI_TRANS_FIFO_RESET_INVALID   (0x00000000UL)    /* It is invalid. It does not affect the operation */
#define _SCI_TRANS_FIFO_RESET_MADE_0    (0x00008000UL)    /* The number of data stored in Transmit-FIFO(TDR register) are made "0" */
/* Receive FIFO Data Register Reset */
#define _SCI_RECV_FIFO_RESET_INVALID    (0x00000000UL)    /* It is invalid. It does not affect the operation */
#define _SCI_RECV_FIFO_RESET_MADE_0     (0x00800000UL)    /* The number of data stored in Receive-FIFO(RDR register) are made "0" */

/*
    Interrupt Source Priority Register n (PRLn)
*/
/* Interrupt Priority Level Select (PRL[3:0]) */
#define _SCIF_PRIORITY_LEVEL0                   (0x00000000UL) /* Level 0 (highest) */
#define _SCIF_PRIORITY_LEVEL1                   (0x00000001UL) /* Level 1 */
#define _SCIF_PRIORITY_LEVEL2                   (0x00000002UL) /* Level 2 */
#define _SCIF_PRIORITY_LEVEL3                   (0x00000003UL) /* Level 3 */
#define _SCIF_PRIORITY_LEVEL4                   (0x00000004UL) /* Level 4 */
#define _SCIF_PRIORITY_LEVEL5                   (0x00000005UL) /* Level 5 */
#define _SCIF_PRIORITY_LEVEL6                   (0x00000006UL) /* Level 6 */
#define _SCIF_PRIORITY_LEVEL7                   (0x00000007UL) /* Level 7 */
#define _SCIF_PRIORITY_LEVEL8                   (0x00000008UL) /* Level 8 */
#define _SCIF_PRIORITY_LEVEL9                   (0x00000009UL) /* Level 9 */
#define _SCIF_PRIORITY_LEVEL10                  (0x0000000AUL) /* Level 10 */
#define _SCIF_PRIORITY_LEVEL11                  (0x0000000BUL) /* Level 11 */
#define _SCIF_PRIORITY_LEVEL12                  (0x0000000CUL) /* Level 12 */
#define _SCIF_PRIORITY_LEVEL13                  (0x0000000DUL) /* Level 13 */
#define _SCIF_PRIORITY_LEVEL14                  (0x0000000EUL) /* Level 14 */
#define _SCIF_PRIORITY_LEVEL15                  (0x0000000FUL) /* Level 15 */

/* FIFO buffer maximum size */
#define _SCIF_FIFO_MAX_SIZE                     (0x10U) /* Size of 16-stage FIFO buffer */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _SCIF_1BIT_INTERVAL_0                   (0x00000105UL) /* Wait time for 1-bit interval */
#define _SCIF_RX_TRIG_NUM_0                     (0x01U) /* Receive FIFO data trigger number */
#define _SCIF_1BIT_INTERVAL_2                   (0x00000105UL) /* Wait time for 1-bit interval */
#define _SCIF_RX_TRIG_NUM_2                     (0x01U) /* Receive FIFO data trigger number */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    OVERRUN_ERROR,
    BREAK_DETECT,
    RECEIVE_ERROR
} scif_error_type_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_SCI5_Create(void);
void R_SCI5_Start(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
