/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
                        [147] = gpt_int_select_isr, /* GPT02_0_INT0 (GPT02_0 selected interrupt 0) */
            [384] = sci_uart_rxi_isr, /* SCI0_RXI (SCI0 Receive data full) */
            [385] = sci_uart_txi_isr, /* SCI0_TXI (SCI0 Transmit data empty) */
            [386] = sci_uart_tei_isr, /* SCI0_TEI (SCI0 Transmit end) */
            [387] = sci_uart_eri_isr, /* SCI0_ERI (SCI0 Receive error) */
            [388] = m_sci5_rxi_interrupt, /* SCI5_RXI (SCI5 Receive data full) */
            [389] = m_sci5_txi_interrupt, /* SCI5_TXI (SCI5 Transmit data empty) */
            [390] = m_sci5_tei_interrupt, /* SCI5_TEI (SCI5 Transmit end) */
            [391] = m_sci5_eri_interrupt, /* SCI5_ERI (SCI5 Receive error) */
            [392] = fac0_rxi_isr, /* ENCIF00_INT1 (ENCIF00 combined interrupt 1) */
            [393] = fac0_txi_isr, /* ENCIF00_INT2 (ENCIF00 combined interrupt 2) */
            [394] = fac0_tei_isr, /* ENCIF00_INT3 (ENCIF00 combined interrupt 3) */
            [395] = fac0_eri_isr, /* ENCIF00_INT0 (ENCIF00 combined interrupt 0) */
            [396] = sci_uart_eri_isr, /* SCI4_ERI (SCI4 Receive error) */
            [397] = sci_uart_rxi_isr, /* SCI4_RXI (SCI4 Receive data full) */
            [398] = sci_uart_txi_isr, /* SCI4_TXI (SCI4 Transmit data empty) */
            [399] = sci_uart_tei_isr, /* SCI4_TEI (SCI4 Transmit end) */
            [400] = fac1_eri_isr, /* ENCIF01_INT0 (ENCIF01 combined interrupt 0) */
            [401] = fac1_rxi_isr, /* ENCIF01_INT1 (ENCIF01 combined interrupt 1) */
            [402] = fac1_txi_isr, /* ENCIF01_INT2 (ENCIF01 combined interrupt 2) */
            [403] = fac1_tei_isr, /* ENCIF01_INT3 (ENCIF01 combined interrupt 3) */
            [404] = fac2_eri_isr, /* ENCIF02_INT0 (ENCIF02 combined interrupt 0) */
            [405] = fac2_rxi_isr, /* ENCIF02_INT1 (ENCIF02 combined interrupt 1) */
            [406] = fac2_txi_isr, /* ENCIF02_INT2 (ENCIF02 combined interrupt 2) */
            [407] = fac2_tei_isr, /* ENCIF02_INT3 (ENCIF02 combined interrupt 3) */
            [408] = fac3_eri_isr, /* ENCIF03_INT0 (ENCIF03 combined interrupt 0) */
            [409] = fac3_rxi_isr, /* ENCIF03_INT1 (ENCIF03 combined interrupt 1) */
            [410] = fac3_txi_isr, /* ENCIF03_INT2 (ENCIF03 combined interrupt 2) */
            [411] = fac3_tei_isr, /* ENCIF03_INT3 (ENCIF03 combined interrupt 3) */
            [412] = fac4_eri_isr, /* ENCIF04_INT0 (ENCIF04 combined interrupt 0) */
            [413] = fac4_rxi_isr, /* ENCIF04_INT1 (ENCIF04 combined interrupt 1) */
            [414] = fac4_txi_isr, /* ENCIF04_INT2 (ENCIF04 combined interrupt 2) */
            [415] = fac4_tei_isr, /* ENCIF04_INT3 (ENCIF04 combined interrupt 3) */
            [416] = fac5_eri_isr, /* ENCIF05_INT0 (ENCIF05 combined interrupt 0) */
            [417] = fac5_rxi_isr, /* ENCIF05_INT1 (ENCIF05 combined interrupt 1) */
            [418] = fac5_txi_isr, /* ENCIF05_INT2 (ENCIF05 combined interrupt 2) */
            [419] = fac5_tei_isr, /* ENCIF05_INT3 (ENCIF05 combined interrupt 3) */
            [420] = fac6_eri_isr, /* ENCIF06_INT0 (ENCIF06 combined interrupt 0) */
            [421] = fac6_rxi_isr, /* ENCIF06_INT1 (ENCIF06 combined interrupt 1) */
            [422] = fac6_txi_isr, /* ENCIF06_INT2 (ENCIF06 combined interrupt 2) */
            [423] = fac6_tei_isr, /* ENCIF06_INT3 (ENCIF06 combined interrupt 3) */
            [424] = fac7_eri_isr, /* ENCIF07_INT0 (ENCIF07 combined interrupt 0) */
            [425] = fac7_rxi_isr, /* ENCIF07_INT1 (ENCIF07 combined interrupt 1) */
            [426] = fac7_txi_isr, /* ENCIF07_INT2 (ENCIF07 combined interrupt 2) */
            [427] = fac7_tei_isr, /* ENCIF07_INT3 (ENCIF07 combined interrupt 3) */
            [428] = fac8_eri_isr, /* ENCIF08_INT0 (ENCIF08 combined interrupt 0) */
            [429] = fac8_rxi_isr, /* ENCIF08_INT1 (ENCIF08 combined interrupt 1) */
            [430] = fac8_txi_isr, /* ENCIF08_INT2 (ENCIF08 combined interrupt 2) */
            [431] = fac8_tei_isr, /* ENCIF08_INT3 (ENCIF08 combined interrupt 3) */
        };
        #if (1 == BSP_FEATURE_BSP_IRQ_CR52_SEL_SUPPORTED)
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [147] = BSP_PRV_CR52_SEL_ENUM(EVENT_GPT02_0_INT0), /* GPT02_0_INT0 (GPT02_0 selected interrupt 0) */
            [384] = BSP_PRV_CR52_SEL_ENUM(EVENT_SCI0_RXI), /* SCI0_RXI (SCI0 Receive data full) */
            [385] = BSP_PRV_CR52_SEL_ENUM(EVENT_SCI0_TXI), /* SCI0_TXI (SCI0 Transmit data empty) */
            [386] = BSP_PRV_CR52_SEL_ENUM(EVENT_SCI0_TEI), /* SCI0_TEI (SCI0 Transmit end) */
            [387] = BSP_PRV_CR52_SEL_ENUM(EVENT_SCI0_ERI), /* SCI0_ERI (SCI0 Receive error) */
            [388] = BSP_PRV_CR52_SEL_ENUM(EVENT_SCI5_RXI), /* SCI5_RXI (SCI5 Receive data full) */
            [389] = BSP_PRV_CR52_SEL_ENUM(EVENT_SCI5_TXI), /* SCI5_TXI (SCI5 Transmit data empty) */
            [390] = BSP_PRV_CR52_SEL_ENUM(EVENT_SCI5_TEI), /* SCI5_TEI (SCI5 Transmit end) */
            [391] = BSP_PRV_CR52_SEL_ENUM(EVENT_SCI5_ERI), /* SCI5_ERI (SCI5 Receive error) */
            [392] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF00_INT1), /* ENCIF00_INT1 (ENCIF00 combined interrupt 1) */
            [393] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF00_INT2), /* ENCIF00_INT2 (ENCIF00 combined interrupt 2) */
            [394] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF00_INT3), /* ENCIF00_INT3 (ENCIF00 combined interrupt 3) */
            [395] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF00_INT0), /* ENCIF00_INT0 (ENCIF00 combined interrupt 0) */
            [396] = BSP_PRV_CR52_SEL_ENUM(EVENT_SCI4_ERI), /* SCI4_ERI (SCI4 Receive error) */
            [397] = BSP_PRV_CR52_SEL_ENUM(EVENT_SCI4_RXI), /* SCI4_RXI (SCI4 Receive data full) */
            [398] = BSP_PRV_CR52_SEL_ENUM(EVENT_SCI4_TXI), /* SCI4_TXI (SCI4 Transmit data empty) */
            [399] = BSP_PRV_CR52_SEL_ENUM(EVENT_SCI4_TEI), /* SCI4_TEI (SCI4 Transmit end) */
            [400] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF01_INT0), /* ENCIF01_INT0 (ENCIF01 combined interrupt 0) */
            [401] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF01_INT1), /* ENCIF01_INT1 (ENCIF01 combined interrupt 1) */
            [402] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF01_INT2), /* ENCIF01_INT2 (ENCIF01 combined interrupt 2) */
            [403] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF01_INT3), /* ENCIF01_INT3 (ENCIF01 combined interrupt 3) */
            [404] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF02_INT0), /* ENCIF02_INT0 (ENCIF02 combined interrupt 0) */
            [405] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF02_INT1), /* ENCIF02_INT1 (ENCIF02 combined interrupt 1) */
            [406] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF02_INT2), /* ENCIF02_INT2 (ENCIF02 combined interrupt 2) */
            [407] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF02_INT3), /* ENCIF02_INT3 (ENCIF02 combined interrupt 3) */
            [408] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF03_INT0), /* ENCIF03_INT0 (ENCIF03 combined interrupt 0) */
            [409] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF03_INT1), /* ENCIF03_INT1 (ENCIF03 combined interrupt 1) */
            [410] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF03_INT2), /* ENCIF03_INT2 (ENCIF03 combined interrupt 2) */
            [411] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF03_INT3), /* ENCIF03_INT3 (ENCIF03 combined interrupt 3) */
            [412] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF04_INT0), /* ENCIF04_INT0 (ENCIF04 combined interrupt 0) */
            [413] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF04_INT1), /* ENCIF04_INT1 (ENCIF04 combined interrupt 1) */
            [414] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF04_INT2), /* ENCIF04_INT2 (ENCIF04 combined interrupt 2) */
            [415] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF04_INT3), /* ENCIF04_INT3 (ENCIF04 combined interrupt 3) */
            [416] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF05_INT0), /* ENCIF05_INT0 (ENCIF05 combined interrupt 0) */
            [417] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF05_INT1), /* ENCIF05_INT1 (ENCIF05 combined interrupt 1) */
            [418] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF05_INT2), /* ENCIF05_INT2 (ENCIF05 combined interrupt 2) */
            [419] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF05_INT3), /* ENCIF05_INT3 (ENCIF05 combined interrupt 3) */
            [420] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF06_INT0), /* ENCIF06_INT0 (ENCIF06 combined interrupt 0) */
            [421] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF06_INT1), /* ENCIF06_INT1 (ENCIF06 combined interrupt 1) */
            [422] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF06_INT2), /* ENCIF06_INT2 (ENCIF06 combined interrupt 2) */
            [423] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF06_INT3), /* ENCIF06_INT3 (ENCIF06 combined interrupt 3) */
            [424] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF07_INT0), /* ENCIF07_INT0 (ENCIF07 combined interrupt 0) */
            [425] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF07_INT1), /* ENCIF07_INT1 (ENCIF07 combined interrupt 1) */
            [426] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF07_INT2), /* ENCIF07_INT2 (ENCIF07 combined interrupt 2) */
            [427] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF07_INT3), /* ENCIF07_INT3 (ENCIF07 combined interrupt 3) */
            [428] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF08_INT0), /* ENCIF08_INT0 (ENCIF08 combined interrupt 0) */
            [429] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF08_INT1), /* ENCIF08_INT1 (ENCIF08 combined interrupt 1) */
            [430] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF08_INT2), /* ENCIF08_INT2 (ENCIF08 combined interrupt 2) */
            [431] = BSP_PRV_CR52_SEL_ENUM(EVENT_ENCIF08_INT3), /* ENCIF08_INT3 (ENCIF08 combined interrupt 3) */
        };
        #endif
        #endif
