/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#include "bsp_api.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (49)
#endif
/* ISR prototypes */
void gpt_int_select_isr(void);
void sci_uart_rxi_isr(void);
void sci_uart_txi_isr(void);
void sci_uart_tei_isr(void);
void sci_uart_eri_isr(void);
void m_sci5_rxi_interrupt(void);
void m_sci5_txi_interrupt(void);
void m_sci5_tei_interrupt(void);
void m_sci5_eri_interrupt(void);
void fac0_rxi_isr(void);
void fac0_txi_isr(void);
void fac0_tei_isr(void);
void fac0_eri_isr(void);
void fac1_eri_isr(void);
void fac1_rxi_isr(void);
void fac1_txi_isr(void);
void fac1_tei_isr(void);
void fac2_eri_isr(void);
void fac2_rxi_isr(void);
void fac2_txi_isr(void);
void fac2_tei_isr(void);
void fac3_eri_isr(void);
void fac3_rxi_isr(void);
void fac3_txi_isr(void);
void fac3_tei_isr(void);
void fac4_eri_isr(void);
void fac4_rxi_isr(void);
void fac4_txi_isr(void);
void fac4_tei_isr(void);
void fac5_eri_isr(void);
void fac5_rxi_isr(void);
void fac5_txi_isr(void);
void fac5_tei_isr(void);
void fac6_eri_isr(void);
void fac6_rxi_isr(void);
void fac6_txi_isr(void);
void fac6_tei_isr(void);
void fac7_eri_isr(void);
void fac7_rxi_isr(void);
void fac7_txi_isr(void);
void fac7_tei_isr(void);
void fac8_eri_isr(void);
void fac8_rxi_isr(void);
void fac8_txi_isr(void);
void fac8_tei_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_GPT02_0_INT0 ((IRQn_Type) 147) /* GPT02_0_INT0 (GPT02_0 selected interrupt 0) */
#define VECTOR_NUMBER_SCI0_RXI ((IRQn_Type) 384) /* SCI0_RXI (SCI0 Receive data full) */
#define VECTOR_NUMBER_SCI0_TXI ((IRQn_Type) 385) /* SCI0_TXI (SCI0 Transmit data empty) */
#define VECTOR_NUMBER_SCI0_TEI ((IRQn_Type) 386) /* SCI0_TEI (SCI0 Transmit end) */
#define VECTOR_NUMBER_SCI0_ERI ((IRQn_Type) 387) /* SCI0_ERI (SCI0 Receive error) */
#define VECTOR_NUMBER_SCI5_RXI ((IRQn_Type) 388) /* SCI5_RXI (SCI5 Receive data full) */
#define VECTOR_NUMBER_SCI5_TXI ((IRQn_Type) 389) /* SCI5_TXI (SCI5 Transmit data empty) */
#define VECTOR_NUMBER_SCI5_TEI ((IRQn_Type) 390) /* SCI5_TEI (SCI5 Transmit end) */
#define VECTOR_NUMBER_SCI5_ERI ((IRQn_Type) 391) /* SCI5_ERI (SCI5 Receive error) */
#define VECTOR_NUMBER_ENCIF00_INT1 ((IRQn_Type) 392) /* ENCIF00_INT1 (ENCIF00 combined interrupt 1) */
#define VECTOR_NUMBER_ENCIF00_INT2 ((IRQn_Type) 393) /* ENCIF00_INT2 (ENCIF00 combined interrupt 2) */
#define VECTOR_NUMBER_ENCIF00_INT3 ((IRQn_Type) 394) /* ENCIF00_INT3 (ENCIF00 combined interrupt 3) */
#define VECTOR_NUMBER_ENCIF00_INT0 ((IRQn_Type) 395) /* ENCIF00_INT0 (ENCIF00 combined interrupt 0) */
#define VECTOR_NUMBER_SCI4_ERI ((IRQn_Type) 396) /* SCI4_ERI (SCI4 Receive error) */
#define VECTOR_NUMBER_SCI4_RXI ((IRQn_Type) 397) /* SCI4_RXI (SCI4 Receive data full) */
#define VECTOR_NUMBER_SCI4_TXI ((IRQn_Type) 398) /* SCI4_TXI (SCI4 Transmit data empty) */
#define VECTOR_NUMBER_SCI4_TEI ((IRQn_Type) 399) /* SCI4_TEI (SCI4 Transmit end) */
#define VECTOR_NUMBER_ENCIF01_INT0 ((IRQn_Type) 400) /* ENCIF01_INT0 (ENCIF01 combined interrupt 0) */
#define VECTOR_NUMBER_ENCIF01_INT1 ((IRQn_Type) 401) /* ENCIF01_INT1 (ENCIF01 combined interrupt 1) */
#define VECTOR_NUMBER_ENCIF01_INT2 ((IRQn_Type) 402) /* ENCIF01_INT2 (ENCIF01 combined interrupt 2) */
#define VECTOR_NUMBER_ENCIF01_INT3 ((IRQn_Type) 403) /* ENCIF01_INT3 (ENCIF01 combined interrupt 3) */
#define VECTOR_NUMBER_ENCIF02_INT0 ((IRQn_Type) 404) /* ENCIF02_INT0 (ENCIF02 combined interrupt 0) */
#define VECTOR_NUMBER_ENCIF02_INT1 ((IRQn_Type) 405) /* ENCIF02_INT1 (ENCIF02 combined interrupt 1) */
#define VECTOR_NUMBER_ENCIF02_INT2 ((IRQn_Type) 406) /* ENCIF02_INT2 (ENCIF02 combined interrupt 2) */
#define VECTOR_NUMBER_ENCIF02_INT3 ((IRQn_Type) 407) /* ENCIF02_INT3 (ENCIF02 combined interrupt 3) */
#define VECTOR_NUMBER_ENCIF03_INT0 ((IRQn_Type) 408) /* ENCIF03_INT0 (ENCIF03 combined interrupt 0) */
#define VECTOR_NUMBER_ENCIF03_INT1 ((IRQn_Type) 409) /* ENCIF03_INT1 (ENCIF03 combined interrupt 1) */
#define VECTOR_NUMBER_ENCIF03_INT2 ((IRQn_Type) 410) /* ENCIF03_INT2 (ENCIF03 combined interrupt 2) */
#define VECTOR_NUMBER_ENCIF03_INT3 ((IRQn_Type) 411) /* ENCIF03_INT3 (ENCIF03 combined interrupt 3) */
#define VECTOR_NUMBER_ENCIF04_INT0 ((IRQn_Type) 412) /* ENCIF04_INT0 (ENCIF04 combined interrupt 0) */
#define VECTOR_NUMBER_ENCIF04_INT1 ((IRQn_Type) 413) /* ENCIF04_INT1 (ENCIF04 combined interrupt 1) */
#define VECTOR_NUMBER_ENCIF04_INT2 ((IRQn_Type) 414) /* ENCIF04_INT2 (ENCIF04 combined interrupt 2) */
#define VECTOR_NUMBER_ENCIF04_INT3 ((IRQn_Type) 415) /* ENCIF04_INT3 (ENCIF04 combined interrupt 3) */
#define VECTOR_NUMBER_ENCIF05_INT0 ((IRQn_Type) 416) /* ENCIF05_INT0 (ENCIF05 combined interrupt 0) */
#define VECTOR_NUMBER_ENCIF05_INT1 ((IRQn_Type) 417) /* ENCIF05_INT1 (ENCIF05 combined interrupt 1) */
#define VECTOR_NUMBER_ENCIF05_INT2 ((IRQn_Type) 418) /* ENCIF05_INT2 (ENCIF05 combined interrupt 2) */
#define VECTOR_NUMBER_ENCIF05_INT3 ((IRQn_Type) 419) /* ENCIF05_INT3 (ENCIF05 combined interrupt 3) */
#define VECTOR_NUMBER_ENCIF06_INT0 ((IRQn_Type) 420) /* ENCIF06_INT0 (ENCIF06 combined interrupt 0) */
#define VECTOR_NUMBER_ENCIF06_INT1 ((IRQn_Type) 421) /* ENCIF06_INT1 (ENCIF06 combined interrupt 1) */
#define VECTOR_NUMBER_ENCIF06_INT2 ((IRQn_Type) 422) /* ENCIF06_INT2 (ENCIF06 combined interrupt 2) */
#define VECTOR_NUMBER_ENCIF06_INT3 ((IRQn_Type) 423) /* ENCIF06_INT3 (ENCIF06 combined interrupt 3) */
#define VECTOR_NUMBER_ENCIF07_INT0 ((IRQn_Type) 424) /* ENCIF07_INT0 (ENCIF07 combined interrupt 0) */
#define VECTOR_NUMBER_ENCIF07_INT1 ((IRQn_Type) 425) /* ENCIF07_INT1 (ENCIF07 combined interrupt 1) */
#define VECTOR_NUMBER_ENCIF07_INT2 ((IRQn_Type) 426) /* ENCIF07_INT2 (ENCIF07 combined interrupt 2) */
#define VECTOR_NUMBER_ENCIF07_INT3 ((IRQn_Type) 427) /* ENCIF07_INT3 (ENCIF07 combined interrupt 3) */
#define VECTOR_NUMBER_ENCIF08_INT0 ((IRQn_Type) 428) /* ENCIF08_INT0 (ENCIF08 combined interrupt 0) */
#define VECTOR_NUMBER_ENCIF08_INT1 ((IRQn_Type) 429) /* ENCIF08_INT1 (ENCIF08 combined interrupt 1) */
#define VECTOR_NUMBER_ENCIF08_INT2 ((IRQn_Type) 430) /* ENCIF08_INT2 (ENCIF08 combined interrupt 2) */
#define VECTOR_NUMBER_ENCIF08_INT3 ((IRQn_Type) 431) /* ENCIF08_INT3 (ENCIF08 combined interrupt 3) */
typedef enum IRQn
{
    SoftwareGeneratedInt0 = -32,
    SoftwareGeneratedInt1 = -31,
    SoftwareGeneratedInt2 = -30,
    SoftwareGeneratedInt3 = -29,
    SoftwareGeneratedInt4 = -28,
    SoftwareGeneratedInt5 = -27,
    SoftwareGeneratedInt6 = -26,
    SoftwareGeneratedInt7 = -25,
    SoftwareGeneratedInt8 = -24,
    SoftwareGeneratedInt9 = -23,
    SoftwareGeneratedInt10 = -22,
    SoftwareGeneratedInt11 = -21,
    SoftwareGeneratedInt12 = -20,
    SoftwareGeneratedInt13 = -19,
    SoftwareGeneratedInt14 = -18,
    SoftwareGeneratedInt15 = -17,
    DebugCommunicationsChannelInt = -10,
    PerformanceMonitorCounterOverflowInt = -9,
    CrossTriggerInterfaceInt = -8,
    VritualCPUInterfaceMaintenanceInt = -7,
    HypervisorTimerInt = -6,
    VirtualTimerInt = -5,
    NonSecurePhysicalTimerInt = -2,
    GPT02_0_INT0_IRQn = 147, /* GPT02_0_INT0 (GPT02_0 selected interrupt 0) */
    SCI0_RXI_IRQn = 384, /* SCI0_RXI (SCI0 Receive data full) */
    SCI0_TXI_IRQn = 385, /* SCI0_TXI (SCI0 Transmit data empty) */
    SCI0_TEI_IRQn = 386, /* SCI0_TEI (SCI0 Transmit end) */
    SCI0_ERI_IRQn = 387, /* SCI0_ERI (SCI0 Receive error) */
    SCI5_RXI_IRQn = 388, /* SCI5_RXI (SCI5 Receive data full) */
    SCI5_TXI_IRQn = 389, /* SCI5_TXI (SCI5 Transmit data empty) */
    SCI5_TEI_IRQn = 390, /* SCI5_TEI (SCI5 Transmit end) */
    SCI5_ERI_IRQn = 391, /* SCI5_ERI (SCI5 Receive error) */
    ENCIF00_INT1_IRQn = 392, /* ENCIF00_INT1 (ENCIF00 combined interrupt 1) */
    ENCIF00_INT2_IRQn = 393, /* ENCIF00_INT2 (ENCIF00 combined interrupt 2) */
    ENCIF00_INT3_IRQn = 394, /* ENCIF00_INT3 (ENCIF00 combined interrupt 3) */
    ENCIF00_INT0_IRQn = 395, /* ENCIF00_INT0 (ENCIF00 combined interrupt 0) */
    SCI4_ERI_IRQn = 396, /* SCI4_ERI (SCI4 Receive error) */
    SCI4_RXI_IRQn = 397, /* SCI4_RXI (SCI4 Receive data full) */
    SCI4_TXI_IRQn = 398, /* SCI4_TXI (SCI4 Transmit data empty) */
    SCI4_TEI_IRQn = 399, /* SCI4_TEI (SCI4 Transmit end) */
    ENCIF01_INT0_IRQn = 400, /* ENCIF01_INT0 (ENCIF01 combined interrupt 0) */
    ENCIF01_INT1_IRQn = 401, /* ENCIF01_INT1 (ENCIF01 combined interrupt 1) */
    ENCIF01_INT2_IRQn = 402, /* ENCIF01_INT2 (ENCIF01 combined interrupt 2) */
    ENCIF01_INT3_IRQn = 403, /* ENCIF01_INT3 (ENCIF01 combined interrupt 3) */
    ENCIF02_INT0_IRQn = 404, /* ENCIF02_INT0 (ENCIF02 combined interrupt 0) */
    ENCIF02_INT1_IRQn = 405, /* ENCIF02_INT1 (ENCIF02 combined interrupt 1) */
    ENCIF02_INT2_IRQn = 406, /* ENCIF02_INT2 (ENCIF02 combined interrupt 2) */
    ENCIF02_INT3_IRQn = 407, /* ENCIF02_INT3 (ENCIF02 combined interrupt 3) */
    ENCIF03_INT0_IRQn = 408, /* ENCIF03_INT0 (ENCIF03 combined interrupt 0) */
    ENCIF03_INT1_IRQn = 409, /* ENCIF03_INT1 (ENCIF03 combined interrupt 1) */
    ENCIF03_INT2_IRQn = 410, /* ENCIF03_INT2 (ENCIF03 combined interrupt 2) */
    ENCIF03_INT3_IRQn = 411, /* ENCIF03_INT3 (ENCIF03 combined interrupt 3) */
    ENCIF04_INT0_IRQn = 412, /* ENCIF04_INT0 (ENCIF04 combined interrupt 0) */
    ENCIF04_INT1_IRQn = 413, /* ENCIF04_INT1 (ENCIF04 combined interrupt 1) */
    ENCIF04_INT2_IRQn = 414, /* ENCIF04_INT2 (ENCIF04 combined interrupt 2) */
    ENCIF04_INT3_IRQn = 415, /* ENCIF04_INT3 (ENCIF04 combined interrupt 3) */
    ENCIF05_INT0_IRQn = 416, /* ENCIF05_INT0 (ENCIF05 combined interrupt 0) */
    ENCIF05_INT1_IRQn = 417, /* ENCIF05_INT1 (ENCIF05 combined interrupt 1) */
    ENCIF05_INT2_IRQn = 418, /* ENCIF05_INT2 (ENCIF05 combined interrupt 2) */
    ENCIF05_INT3_IRQn = 419, /* ENCIF05_INT3 (ENCIF05 combined interrupt 3) */
    ENCIF06_INT0_IRQn = 420, /* ENCIF06_INT0 (ENCIF06 combined interrupt 0) */
    ENCIF06_INT1_IRQn = 421, /* ENCIF06_INT1 (ENCIF06 combined interrupt 1) */
    ENCIF06_INT2_IRQn = 422, /* ENCIF06_INT2 (ENCIF06 combined interrupt 2) */
    ENCIF06_INT3_IRQn = 423, /* ENCIF06_INT3 (ENCIF06 combined interrupt 3) */
    ENCIF07_INT0_IRQn = 424, /* ENCIF07_INT0 (ENCIF07 combined interrupt 0) */
    ENCIF07_INT1_IRQn = 425, /* ENCIF07_INT1 (ENCIF07 combined interrupt 1) */
    ENCIF07_INT2_IRQn = 426, /* ENCIF07_INT2 (ENCIF07 combined interrupt 2) */
    ENCIF07_INT3_IRQn = 427, /* ENCIF07_INT3 (ENCIF07 combined interrupt 3) */
    ENCIF08_INT0_IRQn = 428, /* ENCIF08_INT0 (ENCIF08 combined interrupt 0) */
    ENCIF08_INT1_IRQn = 429, /* ENCIF08_INT1 (ENCIF08 combined interrupt 1) */
    ENCIF08_INT2_IRQn = 430, /* ENCIF08_INT2 (ENCIF08 combined interrupt 2) */
    ENCIF08_INT3_IRQn = 431, /* ENCIF08_INT3 (ENCIF08 combined interrupt 3) */
    SHARED_PERIPHERAL_INTERRUPTS_MAX_ENTRIES = BSP_VECTOR_TABLE_MAX_ENTRIES
} IRQn_Type;

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif /* VECTOR_DATA_H */
