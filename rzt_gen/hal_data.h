/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_gpt_three_phase.h"
#include "r_three_phase_api.h"
#include "r_xspi_ospi.h"
#include "r_spi_flash_api.h"
#include "r_poeg.h"
#include "r_poeg_api.h"
#include "r_sci_uart.h"
#include "r_uart_api.h"
FSP_HEADER
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer8_2;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer8_2_ctrl;
extern const timer_cfg_t g_timer8_2_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT08_2_INT0_DISABLE
  #define TIMER_GPT08_2_INT0_DISABLE
 #else
  #ifdef TIMER_GPT08_2_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT08_2_INT1_DISABLE
  #define TIMER_GPT08_2_INT1_DISABLE
 #else
  #ifdef TIMER_GPT08_2_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT08_2_INT2_DISABLE
  #define TIMER_GPT08_2_INT2_DISABLE
 #else
  #ifdef TIMER_GPT08_2_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT08_2_INT3_DISABLE
  #define TIMER_GPT08_2_INT3_DISABLE
 #else
  #ifdef TIMER_GPT08_2_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer8_1;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer8_1_ctrl;
extern const timer_cfg_t g_timer8_1_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT08_1_INT0_DISABLE
  #define TIMER_GPT08_1_INT0_DISABLE
 #else
  #ifdef TIMER_GPT08_1_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT08_1_INT1_DISABLE
  #define TIMER_GPT08_1_INT1_DISABLE
 #else
  #ifdef TIMER_GPT08_1_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT08_1_INT2_DISABLE
  #define TIMER_GPT08_1_INT2_DISABLE
 #else
  #ifdef TIMER_GPT08_1_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT08_1_INT3_DISABLE
  #define TIMER_GPT08_1_INT3_DISABLE
 #else
  #ifdef TIMER_GPT08_1_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer8_0;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer8_0_ctrl;
extern const timer_cfg_t g_timer8_0_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT08_0_INT0_DISABLE
  #define TIMER_GPT08_0_INT0_DISABLE
 #else
  #ifdef TIMER_GPT08_0_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT08_0_INT1_DISABLE
  #define TIMER_GPT08_0_INT1_DISABLE
 #else
  #ifdef TIMER_GPT08_0_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT08_0_INT2_DISABLE
  #define TIMER_GPT08_0_INT2_DISABLE
 #else
  #ifdef TIMER_GPT08_0_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT08_0_INT3_DISABLE
  #define TIMER_GPT08_0_INT3_DISABLE
 #else
  #ifdef TIMER_GPT08_0_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** GPT Three-Phase Instance. */
extern const three_phase_instance_t g_three_phase8;

/** Access the GPT Three-Phase instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_three_phase_instance_ctrl_t g_three_phase8_ctrl;
extern const three_phase_cfg_t g_three_phase8_cfg;
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer6_2;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer6_2_ctrl;
extern const timer_cfg_t g_timer6_2_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT06_2_INT0_DISABLE
  #define TIMER_GPT06_2_INT0_DISABLE
 #else
  #ifdef TIMER_GPT06_2_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT06_2_INT1_DISABLE
  #define TIMER_GPT06_2_INT1_DISABLE
 #else
  #ifdef TIMER_GPT06_2_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT06_2_INT2_DISABLE
  #define TIMER_GPT06_2_INT2_DISABLE
 #else
  #ifdef TIMER_GPT06_2_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT06_2_INT3_DISABLE
  #define TIMER_GPT06_2_INT3_DISABLE
 #else
  #ifdef TIMER_GPT06_2_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer6_1;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer6_1_ctrl;
extern const timer_cfg_t g_timer6_1_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT06_1_INT0_DISABLE
  #define TIMER_GPT06_1_INT0_DISABLE
 #else
  #ifdef TIMER_GPT06_1_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT06_1_INT1_DISABLE
  #define TIMER_GPT06_1_INT1_DISABLE
 #else
  #ifdef TIMER_GPT06_1_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT06_1_INT2_DISABLE
  #define TIMER_GPT06_1_INT2_DISABLE
 #else
  #ifdef TIMER_GPT06_1_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT06_1_INT3_DISABLE
  #define TIMER_GPT06_1_INT3_DISABLE
 #else
  #ifdef TIMER_GPT06_1_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer6_0;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer6_0_ctrl;
extern const timer_cfg_t g_timer6_0_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT06_0_INT0_DISABLE
  #define TIMER_GPT06_0_INT0_DISABLE
 #else
  #ifdef TIMER_GPT06_0_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT06_0_INT1_DISABLE
  #define TIMER_GPT06_0_INT1_DISABLE
 #else
  #ifdef TIMER_GPT06_0_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT06_0_INT2_DISABLE
  #define TIMER_GPT06_0_INT2_DISABLE
 #else
  #ifdef TIMER_GPT06_0_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT06_0_INT3_DISABLE
  #define TIMER_GPT06_0_INT3_DISABLE
 #else
  #ifdef TIMER_GPT06_0_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** GPT Three-Phase Instance. */
extern const three_phase_instance_t g_three_phase6;

/** Access the GPT Three-Phase instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_three_phase_instance_ctrl_t g_three_phase6_ctrl;
extern const three_phase_cfg_t g_three_phase6_cfg;
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer5_2;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer5_2_ctrl;
extern const timer_cfg_t g_timer5_2_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT05_2_INT0_DISABLE
  #define TIMER_GPT05_2_INT0_DISABLE
 #else
  #ifdef TIMER_GPT05_2_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT05_2_INT1_DISABLE
  #define TIMER_GPT05_2_INT1_DISABLE
 #else
  #ifdef TIMER_GPT05_2_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT05_2_INT2_DISABLE
  #define TIMER_GPT05_2_INT2_DISABLE
 #else
  #ifdef TIMER_GPT05_2_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT05_2_INT3_DISABLE
  #define TIMER_GPT05_2_INT3_DISABLE
 #else
  #ifdef TIMER_GPT05_2_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer5_1;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer5_1_ctrl;
extern const timer_cfg_t g_timer5_1_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT05_1_INT0_DISABLE
  #define TIMER_GPT05_1_INT0_DISABLE
 #else
  #ifdef TIMER_GPT05_1_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT05_1_INT1_DISABLE
  #define TIMER_GPT05_1_INT1_DISABLE
 #else
  #ifdef TIMER_GPT05_1_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT05_1_INT2_DISABLE
  #define TIMER_GPT05_1_INT2_DISABLE
 #else
  #ifdef TIMER_GPT05_1_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT05_1_INT3_DISABLE
  #define TIMER_GPT05_1_INT3_DISABLE
 #else
  #ifdef TIMER_GPT05_1_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer5_0;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer5_0_ctrl;
extern const timer_cfg_t g_timer5_0_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT05_0_INT0_DISABLE
  #define TIMER_GPT05_0_INT0_DISABLE
 #else
  #ifdef TIMER_GPT05_0_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT05_0_INT1_DISABLE
  #define TIMER_GPT05_0_INT1_DISABLE
 #else
  #ifdef TIMER_GPT05_0_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT05_0_INT2_DISABLE
  #define TIMER_GPT05_0_INT2_DISABLE
 #else
  #ifdef TIMER_GPT05_0_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT05_0_INT3_DISABLE
  #define TIMER_GPT05_0_INT3_DISABLE
 #else
  #ifdef TIMER_GPT05_0_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** GPT Three-Phase Instance. */
extern const three_phase_instance_t g_three_phase5;

/** Access the GPT Three-Phase instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_three_phase_instance_ctrl_t g_three_phase5_ctrl;
extern const three_phase_cfg_t g_three_phase5_cfg;
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer4_2;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer4_2_ctrl;
extern const timer_cfg_t g_timer4_2_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT04_2_INT0_DISABLE
  #define TIMER_GPT04_2_INT0_DISABLE
 #else
  #ifdef TIMER_GPT04_2_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT04_2_INT1_DISABLE
  #define TIMER_GPT04_2_INT1_DISABLE
 #else
  #ifdef TIMER_GPT04_2_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT04_2_INT2_DISABLE
  #define TIMER_GPT04_2_INT2_DISABLE
 #else
  #ifdef TIMER_GPT04_2_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT04_2_INT3_DISABLE
  #define TIMER_GPT04_2_INT3_DISABLE
 #else
  #ifdef TIMER_GPT04_2_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer4_1;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer4_1_ctrl;
extern const timer_cfg_t g_timer4_1_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT04_1_INT0_DISABLE
  #define TIMER_GPT04_1_INT0_DISABLE
 #else
  #ifdef TIMER_GPT04_1_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT04_1_INT1_DISABLE
  #define TIMER_GPT04_1_INT1_DISABLE
 #else
  #ifdef TIMER_GPT04_1_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT04_1_INT2_DISABLE
  #define TIMER_GPT04_1_INT2_DISABLE
 #else
  #ifdef TIMER_GPT04_1_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT04_1_INT3_DISABLE
  #define TIMER_GPT04_1_INT3_DISABLE
 #else
  #ifdef TIMER_GPT04_1_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer4_0;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer4_0_ctrl;
extern const timer_cfg_t g_timer4_0_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT04_0_INT0_DISABLE
  #define TIMER_GPT04_0_INT0_DISABLE
 #else
  #ifdef TIMER_GPT04_0_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT04_0_INT1_DISABLE
  #define TIMER_GPT04_0_INT1_DISABLE
 #else
  #ifdef TIMER_GPT04_0_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT04_0_INT2_DISABLE
  #define TIMER_GPT04_0_INT2_DISABLE
 #else
  #ifdef TIMER_GPT04_0_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT04_0_INT3_DISABLE
  #define TIMER_GPT04_0_INT3_DISABLE
 #else
  #ifdef TIMER_GPT04_0_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** GPT Three-Phase Instance. */
extern const three_phase_instance_t g_three_phase4;

/** Access the GPT Three-Phase instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_three_phase_instance_ctrl_t g_three_phase4_ctrl;
extern const three_phase_cfg_t g_three_phase4_cfg;
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer3_2;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer3_2_ctrl;
extern const timer_cfg_t g_timer3_2_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT03_2_INT0_DISABLE
  #define TIMER_GPT03_2_INT0_DISABLE
 #else
  #ifdef TIMER_GPT03_2_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT03_2_INT1_DISABLE
  #define TIMER_GPT03_2_INT1_DISABLE
 #else
  #ifdef TIMER_GPT03_2_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT03_2_INT2_DISABLE
  #define TIMER_GPT03_2_INT2_DISABLE
 #else
  #ifdef TIMER_GPT03_2_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT03_2_INT3_DISABLE
  #define TIMER_GPT03_2_INT3_DISABLE
 #else
  #ifdef TIMER_GPT03_2_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer3_1;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer3_1_ctrl;
extern const timer_cfg_t g_timer3_1_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT03_1_INT0_DISABLE
  #define TIMER_GPT03_1_INT0_DISABLE
 #else
  #ifdef TIMER_GPT03_1_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT03_1_INT1_DISABLE
  #define TIMER_GPT03_1_INT1_DISABLE
 #else
  #ifdef TIMER_GPT03_1_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT03_1_INT2_DISABLE
  #define TIMER_GPT03_1_INT2_DISABLE
 #else
  #ifdef TIMER_GPT03_1_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT03_1_INT3_DISABLE
  #define TIMER_GPT03_1_INT3_DISABLE
 #else
  #ifdef TIMER_GPT03_1_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer3_0;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer3_0_ctrl;
extern const timer_cfg_t g_timer3_0_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT03_0_INT0_DISABLE
  #define TIMER_GPT03_0_INT0_DISABLE
 #else
  #ifdef TIMER_GPT03_0_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT03_0_INT1_DISABLE
  #define TIMER_GPT03_0_INT1_DISABLE
 #else
  #ifdef TIMER_GPT03_0_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT03_0_INT2_DISABLE
  #define TIMER_GPT03_0_INT2_DISABLE
 #else
  #ifdef TIMER_GPT03_0_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT03_0_INT3_DISABLE
  #define TIMER_GPT03_0_INT3_DISABLE
 #else
  #ifdef TIMER_GPT03_0_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** GPT Three-Phase Instance. */
extern const three_phase_instance_t g_three_phase3;

/** Access the GPT Three-Phase instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_three_phase_instance_ctrl_t g_three_phase3_ctrl;
extern const three_phase_cfg_t g_three_phase3_cfg;
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer2_2;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer2_2_ctrl;
extern const timer_cfg_t g_timer2_2_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT02_2_INT0_DISABLE
  #define TIMER_GPT02_2_INT0_DISABLE
 #else
  #ifdef TIMER_GPT02_2_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT02_2_INT1_DISABLE
  #define TIMER_GPT02_2_INT1_DISABLE
 #else
  #ifdef TIMER_GPT02_2_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT02_2_INT2_DISABLE
  #define TIMER_GPT02_2_INT2_DISABLE
 #else
  #ifdef TIMER_GPT02_2_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT02_2_INT3_DISABLE
  #define TIMER_GPT02_2_INT3_DISABLE
 #else
  #ifdef TIMER_GPT02_2_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer2_1;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer2_1_ctrl;
extern const timer_cfg_t g_timer2_1_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT02_1_INT0_DISABLE
  #define TIMER_GPT02_1_INT0_DISABLE
 #else
  #ifdef TIMER_GPT02_1_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT02_1_INT1_DISABLE
  #define TIMER_GPT02_1_INT1_DISABLE
 #else
  #ifdef TIMER_GPT02_1_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT02_1_INT2_DISABLE
  #define TIMER_GPT02_1_INT2_DISABLE
 #else
  #ifdef TIMER_GPT02_1_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT02_1_INT3_DISABLE
  #define TIMER_GPT02_1_INT3_DISABLE
 #else
  #ifdef TIMER_GPT02_1_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer2_0;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer2_0_ctrl;
extern const timer_cfg_t g_timer2_0_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef r_gpt_interrupt
void r_gpt_interrupt(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT02_0_INT0_ENABLE
  #define TIMER_GPT02_0_INT0_ENABLE
 #else
  #ifdef TIMER_GPT02_0_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT02_0_INT1_DISABLE
  #define TIMER_GPT02_0_INT1_DISABLE
 #else
  #ifdef TIMER_GPT02_0_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT02_0_INT2_DISABLE
  #define TIMER_GPT02_0_INT2_DISABLE
 #else
  #ifdef TIMER_GPT02_0_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT02_0_INT3_DISABLE
  #define TIMER_GPT02_0_INT3_DISABLE
 #else
  #ifdef TIMER_GPT02_0_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** GPT Three-Phase Instance. */
extern const three_phase_instance_t g_three_phase2;

/** Access the GPT Three-Phase instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_three_phase_instance_ctrl_t g_three_phase2_ctrl;
extern const three_phase_cfg_t g_three_phase2_cfg;
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer1_2;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer1_2_ctrl;
extern const timer_cfg_t g_timer1_2_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT01_2_INT0_DISABLE
  #define TIMER_GPT01_2_INT0_DISABLE
 #else
  #ifdef TIMER_GPT01_2_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT01_2_INT1_DISABLE
  #define TIMER_GPT01_2_INT1_DISABLE
 #else
  #ifdef TIMER_GPT01_2_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT01_2_INT2_DISABLE
  #define TIMER_GPT01_2_INT2_DISABLE
 #else
  #ifdef TIMER_GPT01_2_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT01_2_INT3_DISABLE
  #define TIMER_GPT01_2_INT3_DISABLE
 #else
  #ifdef TIMER_GPT01_2_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer1_1;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer1_1_ctrl;
extern const timer_cfg_t g_timer1_1_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT01_1_INT0_DISABLE
  #define TIMER_GPT01_1_INT0_DISABLE
 #else
  #ifdef TIMER_GPT01_1_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT01_1_INT1_DISABLE
  #define TIMER_GPT01_1_INT1_DISABLE
 #else
  #ifdef TIMER_GPT01_1_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT01_1_INT2_DISABLE
  #define TIMER_GPT01_1_INT2_DISABLE
 #else
  #ifdef TIMER_GPT01_1_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT01_1_INT3_DISABLE
  #define TIMER_GPT01_1_INT3_DISABLE
 #else
  #ifdef TIMER_GPT01_1_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer1_0;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer1_0_ctrl;
extern const timer_cfg_t g_timer1_0_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT01_0_INT0_DISABLE
  #define TIMER_GPT01_0_INT0_DISABLE
 #else
  #ifdef TIMER_GPT01_0_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT01_0_INT1_DISABLE
  #define TIMER_GPT01_0_INT1_DISABLE
 #else
  #ifdef TIMER_GPT01_0_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT01_0_INT2_DISABLE
  #define TIMER_GPT01_0_INT2_DISABLE
 #else
  #ifdef TIMER_GPT01_0_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT01_0_INT3_DISABLE
  #define TIMER_GPT01_0_INT3_DISABLE
 #else
  #ifdef TIMER_GPT01_0_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** GPT Three-Phase Instance. */
extern const three_phase_instance_t g_three_phase1;

/** Access the GPT Three-Phase instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_three_phase_instance_ctrl_t g_three_phase1_ctrl;
extern const three_phase_cfg_t g_three_phase1_cfg;
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer7_2;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer7_2_ctrl;
extern const timer_cfg_t g_timer7_2_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT07_2_INT0_DISABLE
  #define TIMER_GPT07_2_INT0_DISABLE
 #else
  #ifdef TIMER_GPT07_2_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT07_2_INT1_DISABLE
  #define TIMER_GPT07_2_INT1_DISABLE
 #else
  #ifdef TIMER_GPT07_2_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT07_2_INT2_DISABLE
  #define TIMER_GPT07_2_INT2_DISABLE
 #else
  #ifdef TIMER_GPT07_2_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT07_2_INT3_DISABLE
  #define TIMER_GPT07_2_INT3_DISABLE
 #else
  #ifdef TIMER_GPT07_2_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer7_1;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer7_1_ctrl;
extern const timer_cfg_t g_timer7_1_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT07_1_INT0_DISABLE
  #define TIMER_GPT07_1_INT0_DISABLE
 #else
  #ifdef TIMER_GPT07_1_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT07_1_INT1_DISABLE
  #define TIMER_GPT07_1_INT1_DISABLE
 #else
  #ifdef TIMER_GPT07_1_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT07_1_INT2_DISABLE
  #define TIMER_GPT07_1_INT2_DISABLE
 #else
  #ifdef TIMER_GPT07_1_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT07_1_INT3_DISABLE
  #define TIMER_GPT07_1_INT3_DISABLE
 #else
  #ifdef TIMER_GPT07_1_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer7_0;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer7_0_ctrl;
extern const timer_cfg_t g_timer7_0_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT07_0_INT0_DISABLE
  #define TIMER_GPT07_0_INT0_DISABLE
 #else
  #ifdef TIMER_GPT07_0_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT07_0_INT1_DISABLE
  #define TIMER_GPT07_0_INT1_DISABLE
 #else
  #ifdef TIMER_GPT07_0_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT07_0_INT2_DISABLE
  #define TIMER_GPT07_0_INT2_DISABLE
 #else
  #ifdef TIMER_GPT07_0_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT07_0_INT3_DISABLE
  #define TIMER_GPT07_0_INT3_DISABLE
 #else
  #ifdef TIMER_GPT07_0_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** GPT Three-Phase Instance. */
extern const three_phase_instance_t g_three_phase7;

/** Access the GPT Three-Phase instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_three_phase_instance_ctrl_t g_three_phase7_ctrl;
extern const three_phase_cfg_t g_three_phase7_cfg;
extern const spi_flash_instance_t g_ospi0;
extern xspi_ospi_instance_ctrl_t g_ospi0_ctrl;
extern const spi_flash_cfg_t g_ospi0_cfg;
/** POEG Instance. */
extern const poeg_instance_t g_poeg0;

/** Access the POEG instance using these structures when calling API functions directly (::p_api is not used). */
extern poeg_instance_ctrl_t g_poeg0_ctrl;
extern const poeg_cfg_t g_poeg0_cfg;

#ifndef NULL
void NULL(poeg_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer0_2;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer0_2_ctrl;
extern const timer_cfg_t g_timer0_2_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT00_2_INT0_DISABLE
  #define TIMER_GPT00_2_INT0_DISABLE
 #else
  #ifdef TIMER_GPT00_2_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT00_2_INT1_DISABLE
  #define TIMER_GPT00_2_INT1_DISABLE
 #else
  #ifdef TIMER_GPT00_2_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT00_2_INT2_DISABLE
  #define TIMER_GPT00_2_INT2_DISABLE
 #else
  #ifdef TIMER_GPT00_2_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT00_2_INT3_DISABLE
  #define TIMER_GPT00_2_INT3_DISABLE
 #else
  #ifdef TIMER_GPT00_2_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer0_1;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer0_1_ctrl;
extern const timer_cfg_t g_timer0_1_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT00_1_INT0_DISABLE
  #define TIMER_GPT00_1_INT0_DISABLE
 #else
  #ifdef TIMER_GPT00_1_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT00_1_INT1_DISABLE
  #define TIMER_GPT00_1_INT1_DISABLE
 #else
  #ifdef TIMER_GPT00_1_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT00_1_INT2_DISABLE
  #define TIMER_GPT00_1_INT2_DISABLE
 #else
  #ifdef TIMER_GPT00_1_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT00_1_INT3_DISABLE
  #define TIMER_GPT00_1_INT3_DISABLE
 #else
  #ifdef TIMER_GPT00_1_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer0_0;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer0_0_ctrl;
extern const timer_cfg_t g_timer0_0_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

/** Error check the duplicated channel number, same GPT_INT number between MTU3 and GPT */
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
 #ifndef TIMER_GPT00_0_INT0_DISABLE
  #define TIMER_GPT00_0_INT0_DISABLE
 #else
  #ifdef TIMER_GPT00_0_INT0_ENABLE
   #error "GPT_INT0 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT00_0_INT1_DISABLE
  #define TIMER_GPT00_0_INT1_DISABLE
 #else
  #ifdef TIMER_GPT00_0_INT1_ENABLE
   #error "GPT_INT1 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT00_0_INT2_DISABLE
  #define TIMER_GPT00_0_INT2_DISABLE
 #else
  #ifdef TIMER_GPT00_0_INT2_ENABLE
   #error "GPT_INT2 of GPT_SEL cannot be duplicated"
  #endif
 #endif
 #ifndef TIMER_GPT00_0_INT3_DISABLE
  #define TIMER_GPT00_0_INT3_DISABLE
 #else
  #ifdef TIMER_GPT00_0_INT3_ENABLE
   #error "GPT_INT3 of GPT_SEL cannot be duplicated"
  #endif
 #endif
#endif
/** GPT Three-Phase Instance. */
extern const three_phase_instance_t g_three_phase0;

/** Access the GPT Three-Phase instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_three_phase_instance_ctrl_t g_three_phase0_ctrl;
extern const three_phase_cfg_t g_three_phase0_cfg;
/** UART on SCI Instance. */
extern const uart_instance_t g_uart5;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t g_uart5_ctrl;
extern const uart_cfg_t g_uart5_cfg;
extern const sci_uart_extended_cfg_t g_uart5_cfg_extend;

#ifndef NULL
void NULL(uart_callback_args_t *p_args);
#endif

#define FSP_NOT_DEFINED (1)
#if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
#define g_uart5_P_TRANSFER_TX (NULL)
#else
                #define g_uart5_P_TRANSFER_TX (&FSP_NOT_DEFINED)
            #endif
#if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
#define g_uart5_P_TRANSFER_RX (NULL)
#else
                #define g_uart5_P_TRANSFER_RX (&FSP_NOT_DEFINED)
            #endif
#undef FSP_NOT_DEFINED
/** UART on SCI Instance. */
extern const uart_instance_t g_uart0;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t g_uart0_ctrl;
extern const uart_cfg_t g_uart0_cfg;
extern const sci_uart_extended_cfg_t g_uart0_cfg_extend;

#ifndef user_uart_callback
void user_uart_callback(uart_callback_args_t *p_args);
#endif

#define FSP_NOT_DEFINED (1)
#if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
#define g_uart0_P_TRANSFER_TX (NULL)
#else
                #define g_uart0_P_TRANSFER_TX (&FSP_NOT_DEFINED)
            #endif
#if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
#define g_uart0_P_TRANSFER_RX (NULL)
#else
                #define g_uart0_P_TRANSFER_RX (&FSP_NOT_DEFINED)
            #endif
#undef FSP_NOT_DEFINED
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
