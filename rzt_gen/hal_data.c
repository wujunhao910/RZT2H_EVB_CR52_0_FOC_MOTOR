/* generated HAL source file - do not edit */
#include "hal_data.h"

gpt_instance_ctrl_t g_timer8_2_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer8_2_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT42_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT42_UDF,
#elif defined(VECTOR_NUMBER_GPT08_2_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT08_2_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer8_2_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT42_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT42_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_2_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT08_2_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT42_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT42_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_2_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT08_2_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer8_2_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT42_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT42_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_2_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT08_2_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT42_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_2_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT42_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_2_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer8_2_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT8_2,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer8_2_extend,
#if defined(VECTOR_NUMBER_GPT42_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT42_OVF,
#elif defined(VECTOR_NUMBER_GPT08_2_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT08_2_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer8_2 =
{ .p_ctrl = &g_timer8_2_ctrl, .p_cfg = &g_timer8_2_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer8_1_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer8_1_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT41_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT41_UDF,
#elif defined(VECTOR_NUMBER_GPT08_1_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT08_1_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer8_1_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT41_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT41_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_1_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT08_1_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT41_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT41_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_1_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT08_1_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer8_1_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT41_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT41_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_1_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT08_1_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT41_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_1_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT41_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_1_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer8_1_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT8_1,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer8_1_extend,
#if defined(VECTOR_NUMBER_GPT41_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT41_OVF,
#elif defined(VECTOR_NUMBER_GPT08_1_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT08_1_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer8_1 =
{ .p_ctrl = &g_timer8_1_ctrl, .p_cfg = &g_timer8_1_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer8_0_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer8_0_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT40_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT40_UDF,
#elif defined(VECTOR_NUMBER_GPT08_0_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT08_0_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_DOWN_COUNT_START_ADC_A
                  | GPT_ADC_TRIGGER_NONE,
          .dead_time_count_up = 500, .dead_time_count_down = 500, .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .gtiocb_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .interrupt_skip_source_ext1 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext1 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_source_ext2 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext2 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_func_ovf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_unf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_a =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_b = GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer8_0_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT40_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT40_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_0_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT08_0_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT40_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT40_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_0_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT08_0_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer8_0_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT40_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT40_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_0_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT08_0_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT40_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_0_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT40_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT08_0_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer8_0_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT8_0,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer8_0_extend,
#if defined(VECTOR_NUMBER_GPT40_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT40_OVF,
#elif defined(VECTOR_NUMBER_GPT08_0_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT08_0_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer8_0 =
{ .p_ctrl = &g_timer8_0_ctrl, .p_cfg = &g_timer8_0_cfg, .p_api = &g_timer_on_gpt };
gpt_three_phase_instance_ctrl_t g_three_phase8_ctrl;
const three_phase_cfg_t g_three_phase8_cfg =
{ .buffer_mode = (THREE_PHASE_BUFFER_MODE_SINGLE), .p_timer_instance =
{ &g_timer8_0, &g_timer8_1, &g_timer8_2 },
  .callback_ch = THREE_PHASE_CHANNEL_U, .channel_mask = (1 << 0) | (1 << 1) | (1 << 2), .p_context = NULL, .p_extend =
          NULL, };
/* Instance structure to use this module. */
const three_phase_instance_t g_three_phase8 =
{ .p_ctrl = &g_three_phase8_ctrl, .p_cfg = &g_three_phase8_cfg, .p_api = &g_gpt_three_phase_on_gpt_three_phase };
gpt_instance_ctrl_t g_timer6_2_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer6_2_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT32_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT32_UDF,
#elif defined(VECTOR_NUMBER_GPT06_2_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT06_2_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer6_2_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT32_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT32_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_2_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT06_2_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT32_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT32_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_2_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT06_2_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer6_2_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT32_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT32_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_2_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT06_2_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT32_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_2_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT32_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_2_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer6_2_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT6_2,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer6_2_extend,
#if defined(VECTOR_NUMBER_GPT32_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT32_OVF,
#elif defined(VECTOR_NUMBER_GPT06_2_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT06_2_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer6_2 =
{ .p_ctrl = &g_timer6_2_ctrl, .p_cfg = &g_timer6_2_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer6_1_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer6_1_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT31_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT31_UDF,
#elif defined(VECTOR_NUMBER_GPT06_1_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT06_1_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer6_1_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT31_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT31_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_1_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT06_1_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT31_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT31_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_1_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT06_1_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer6_1_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT31_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT31_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_1_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT06_1_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT31_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_1_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT31_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_1_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer6_1_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT6_1,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer6_1_extend,
#if defined(VECTOR_NUMBER_GPT31_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT31_OVF,
#elif defined(VECTOR_NUMBER_GPT06_1_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT06_1_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer6_1 =
{ .p_ctrl = &g_timer6_1_ctrl, .p_cfg = &g_timer6_1_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer6_0_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer6_0_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT30_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT30_UDF,
#elif defined(VECTOR_NUMBER_GPT06_0_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT06_0_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_DOWN_COUNT_START_ADC_A
                  | GPT_ADC_TRIGGER_NONE,
          .dead_time_count_up = 500, .dead_time_count_down = 500, .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .gtiocb_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .interrupt_skip_source_ext1 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext1 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_source_ext2 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext2 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_func_ovf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_unf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_a =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_b = GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer6_0_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT30_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT30_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_0_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT06_0_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT30_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT30_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_0_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT06_0_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer6_0_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT30_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT30_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_0_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT06_0_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT30_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_0_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT30_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT06_0_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer6_0_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT6_0,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer6_0_extend,
#if defined(VECTOR_NUMBER_GPT30_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT30_OVF,
#elif defined(VECTOR_NUMBER_GPT06_0_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT06_0_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer6_0 =
{ .p_ctrl = &g_timer6_0_ctrl, .p_cfg = &g_timer6_0_cfg, .p_api = &g_timer_on_gpt };
gpt_three_phase_instance_ctrl_t g_three_phase6_ctrl;
const three_phase_cfg_t g_three_phase6_cfg =
{ .buffer_mode = (THREE_PHASE_BUFFER_MODE_SINGLE), .p_timer_instance =
{ &g_timer6_0, &g_timer6_1, &g_timer6_2 },
  .callback_ch = THREE_PHASE_CHANNEL_U, .channel_mask = (1 << 0) | (1 << 1) | (1 << 2), .p_context = NULL, .p_extend =
          NULL, };
/* Instance structure to use this module. */
const three_phase_instance_t g_three_phase6 =
{ .p_ctrl = &g_three_phase6_ctrl, .p_cfg = &g_three_phase6_cfg, .p_api = &g_gpt_three_phase_on_gpt_three_phase };
gpt_instance_ctrl_t g_timer5_2_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer5_2_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT27_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT27_UDF,
#elif defined(VECTOR_NUMBER_GPT05_2_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT05_2_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer5_2_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT27_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT27_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_2_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT05_2_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT27_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT27_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_2_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT05_2_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer5_2_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT27_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT27_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_2_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT05_2_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT27_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_2_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT27_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_2_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer5_2_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT5_2,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer5_2_extend,
#if defined(VECTOR_NUMBER_GPT27_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT27_OVF,
#elif defined(VECTOR_NUMBER_GPT05_2_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT05_2_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer5_2 =
{ .p_ctrl = &g_timer5_2_ctrl, .p_cfg = &g_timer5_2_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer5_1_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer5_1_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT26_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT26_UDF,
#elif defined(VECTOR_NUMBER_GPT05_1_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT05_1_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer5_1_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT26_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT26_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_1_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT05_1_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT26_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT26_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_1_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT05_1_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer5_1_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT26_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT26_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_1_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT05_1_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT26_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_1_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT26_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_1_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer5_1_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT5_1,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer5_1_extend,
#if defined(VECTOR_NUMBER_GPT26_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT26_OVF,
#elif defined(VECTOR_NUMBER_GPT05_1_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT05_1_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer5_1 =
{ .p_ctrl = &g_timer5_1_ctrl, .p_cfg = &g_timer5_1_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer5_0_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer5_0_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT25_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT25_UDF,
#elif defined(VECTOR_NUMBER_GPT05_0_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT05_0_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_DOWN_COUNT_START_ADC_A
                  | GPT_ADC_TRIGGER_NONE,
          .dead_time_count_up = 500, .dead_time_count_down = 500, .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .gtiocb_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .interrupt_skip_source_ext1 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext1 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_source_ext2 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext2 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_func_ovf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_unf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_a =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_b = GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer5_0_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT25_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT25_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_0_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT05_0_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT25_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT25_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_0_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT05_0_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer5_0_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT25_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT25_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_0_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT05_0_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT25_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_0_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT25_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT05_0_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer5_0_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT5_0,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer5_0_extend,
#if defined(VECTOR_NUMBER_GPT25_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT25_OVF,
#elif defined(VECTOR_NUMBER_GPT05_0_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT05_0_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer5_0 =
{ .p_ctrl = &g_timer5_0_ctrl, .p_cfg = &g_timer5_0_cfg, .p_api = &g_timer_on_gpt };
gpt_three_phase_instance_ctrl_t g_three_phase5_ctrl;
const three_phase_cfg_t g_three_phase5_cfg =
{ .buffer_mode = (THREE_PHASE_BUFFER_MODE_SINGLE), .p_timer_instance =
{ &g_timer5_0, &g_timer5_1, &g_timer5_2 },
  .callback_ch = THREE_PHASE_CHANNEL_U, .channel_mask = (1 << 0) | (1 << 1) | (1 << 2), .p_context = NULL, .p_extend =
          NULL, };
/* Instance structure to use this module. */
const three_phase_instance_t g_three_phase5 =
{ .p_ctrl = &g_three_phase5_ctrl, .p_cfg = &g_three_phase5_cfg, .p_api = &g_gpt_three_phase_on_gpt_three_phase };
gpt_instance_ctrl_t g_timer4_2_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer4_2_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT22_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT22_UDF,
#elif defined(VECTOR_NUMBER_GPT04_2_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT04_2_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer4_2_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT22_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT22_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_2_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT04_2_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT22_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT22_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_2_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT04_2_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer4_2_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT22_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT22_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_2_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT04_2_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT22_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_2_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT22_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_2_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer4_2_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT4_2,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer4_2_extend,
#if defined(VECTOR_NUMBER_GPT22_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT22_OVF,
#elif defined(VECTOR_NUMBER_GPT04_2_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT04_2_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer4_2 =
{ .p_ctrl = &g_timer4_2_ctrl, .p_cfg = &g_timer4_2_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer4_1_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer4_1_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT21_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT21_UDF,
#elif defined(VECTOR_NUMBER_GPT04_1_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT04_1_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer4_1_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT21_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT21_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_1_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT04_1_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT21_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT21_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_1_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT04_1_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer4_1_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT21_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT21_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_1_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT04_1_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT21_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_1_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT21_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_1_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer4_1_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT4_1,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer4_1_extend,
#if defined(VECTOR_NUMBER_GPT21_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT21_OVF,
#elif defined(VECTOR_NUMBER_GPT04_1_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT04_1_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer4_1 =
{ .p_ctrl = &g_timer4_1_ctrl, .p_cfg = &g_timer4_1_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer4_0_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer4_0_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT20_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT20_UDF,
#elif defined(VECTOR_NUMBER_GPT04_0_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT04_0_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_DOWN_COUNT_START_ADC_A
                  | GPT_ADC_TRIGGER_NONE,
          .dead_time_count_up = 500, .dead_time_count_down = 500, .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .gtiocb_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .interrupt_skip_source_ext1 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext1 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_source_ext2 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext2 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_func_ovf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_unf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_a =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_b = GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer4_0_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT20_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT20_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_0_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT04_0_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT20_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT20_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_0_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT04_0_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer4_0_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT20_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT20_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_0_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT04_0_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT20_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_0_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT20_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT04_0_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer4_0_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT4_0,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer4_0_extend,
#if defined(VECTOR_NUMBER_GPT20_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT20_OVF,
#elif defined(VECTOR_NUMBER_GPT04_0_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT04_0_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer4_0 =
{ .p_ctrl = &g_timer4_0_ctrl, .p_cfg = &g_timer4_0_cfg, .p_api = &g_timer_on_gpt };
gpt_three_phase_instance_ctrl_t g_three_phase4_ctrl;
const three_phase_cfg_t g_three_phase4_cfg =
{ .buffer_mode = (THREE_PHASE_BUFFER_MODE_SINGLE), .p_timer_instance =
{ &g_timer4_0, &g_timer4_1, &g_timer4_2 },
  .callback_ch = THREE_PHASE_CHANNEL_U, .channel_mask = (1 << 0) | (1 << 1) | (1 << 2), .p_context = NULL, .p_extend =
          NULL, };
/* Instance structure to use this module. */
const three_phase_instance_t g_three_phase4 =
{ .p_ctrl = &g_three_phase4_ctrl, .p_cfg = &g_three_phase4_cfg, .p_api = &g_gpt_three_phase_on_gpt_three_phase };
gpt_instance_ctrl_t g_timer3_2_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer3_2_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT17_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT17_UDF,
#elif defined(VECTOR_NUMBER_GPT03_2_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT03_2_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer3_2_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT17_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT17_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_2_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT03_2_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT17_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT17_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_2_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT03_2_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer3_2_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT17_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT17_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_2_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT03_2_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT17_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_2_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT17_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_2_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer3_2_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT3_2,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer3_2_extend,
#if defined(VECTOR_NUMBER_GPT17_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT17_OVF,
#elif defined(VECTOR_NUMBER_GPT03_2_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT03_2_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer3_2 =
{ .p_ctrl = &g_timer3_2_ctrl, .p_cfg = &g_timer3_2_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer3_1_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer3_1_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT16_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT16_UDF,
#elif defined(VECTOR_NUMBER_GPT03_1_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT03_1_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer3_1_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT16_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT16_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_1_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT03_1_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT16_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT16_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_1_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT03_1_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer3_1_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT16_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT16_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_1_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT03_1_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT16_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_1_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT16_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_1_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer3_1_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT3_1,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer3_1_extend,
#if defined(VECTOR_NUMBER_GPT16_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT16_OVF,
#elif defined(VECTOR_NUMBER_GPT03_1_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT03_1_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer3_1 =
{ .p_ctrl = &g_timer3_1_ctrl, .p_cfg = &g_timer3_1_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer3_0_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer3_0_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT15_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT15_UDF,
#elif defined(VECTOR_NUMBER_GPT03_0_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT03_0_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_DOWN_COUNT_START_ADC_A
                  | GPT_ADC_TRIGGER_NONE,
          .dead_time_count_up = 500, .dead_time_count_down = 500, .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .gtiocb_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .interrupt_skip_source_ext1 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext1 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_source_ext2 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext2 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_func_ovf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_unf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_a =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_b = GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer3_0_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT15_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT15_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_0_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT03_0_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT15_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT15_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_0_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT03_0_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer3_0_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT15_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT15_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_0_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT03_0_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT15_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_0_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT15_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT03_0_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer3_0_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT3_0,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer3_0_extend,
#if defined(VECTOR_NUMBER_GPT15_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT15_OVF,
#elif defined(VECTOR_NUMBER_GPT03_0_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT03_0_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer3_0 =
{ .p_ctrl = &g_timer3_0_ctrl, .p_cfg = &g_timer3_0_cfg, .p_api = &g_timer_on_gpt };
gpt_three_phase_instance_ctrl_t g_three_phase3_ctrl;
const three_phase_cfg_t g_three_phase3_cfg =
{ .buffer_mode = (THREE_PHASE_BUFFER_MODE_SINGLE), .p_timer_instance =
{ &g_timer3_0, &g_timer3_1, &g_timer3_2 },
  .callback_ch = THREE_PHASE_CHANNEL_U, .channel_mask = (1 << 0) | (1 << 1) | (1 << 2), .p_context = NULL, .p_extend =
          NULL, };
/* Instance structure to use this module. */
const three_phase_instance_t g_three_phase3 =
{ .p_ctrl = &g_three_phase3_ctrl, .p_cfg = &g_three_phase3_cfg, .p_api = &g_gpt_three_phase_on_gpt_three_phase };
gpt_instance_ctrl_t g_timer2_2_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer2_2_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT12_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT12_UDF,
#elif defined(VECTOR_NUMBER_GPT02_2_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT02_2_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer2_2_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT12_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT12_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_2_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT02_2_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT12_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT12_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_2_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT02_2_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer2_2_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT12_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT12_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_2_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT02_2_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT12_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_2_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT12_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_2_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer2_2_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT2_2,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer2_2_extend,
#if defined(VECTOR_NUMBER_GPT12_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT12_OVF,
#elif defined(VECTOR_NUMBER_GPT02_2_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT02_2_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer2_2 =
{ .p_ctrl = &g_timer2_2_ctrl, .p_cfg = &g_timer2_2_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer2_1_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer2_1_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT11_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT11_UDF,
#elif defined(VECTOR_NUMBER_GPT02_1_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT02_1_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer2_1_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT11_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT11_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_1_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT02_1_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT11_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT11_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_1_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT02_1_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer2_1_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT11_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT11_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_1_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT02_1_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT11_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_1_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT11_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_1_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer2_1_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT2_1,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer2_1_extend,
#if defined(VECTOR_NUMBER_GPT11_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT11_OVF,
#elif defined(VECTOR_NUMBER_GPT02_1_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT02_1_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer2_1 =
{ .p_ctrl = &g_timer2_1_ctrl, .p_cfg = &g_timer2_1_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer2_0_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer2_0_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT10_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT10_UDF,
#elif defined(VECTOR_NUMBER_GPT02_0_INT0)
    .trough_ipl          = (1),
    .trough_irq          = VECTOR_NUMBER_GPT02_0_INT0,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_DOWN_COUNT_START_ADC_A
                  | GPT_ADC_TRIGGER_NONE,
          .dead_time_count_up = 500, .dead_time_count_down = 500, .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .gtiocb_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .interrupt_skip_source_ext1 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext1 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_source_ext2 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext2 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_func_ovf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_unf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_a =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_b = GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer2_0_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT10_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT10_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_0_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT02_0_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT10_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT10_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_0_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT02_0_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer2_0_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT10_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT10_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_0_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT02_0_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT10_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_0_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT10_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT02_0_INT0)
    .trough_source_select = 0,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer2_0_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT2_0,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = r_gpt_interrupt,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer2_0_extend,
#if defined(VECTOR_NUMBER_GPT10_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT10_OVF,
#elif defined(VECTOR_NUMBER_GPT02_0_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT02_0_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer2_0 =
{ .p_ctrl = &g_timer2_0_ctrl, .p_cfg = &g_timer2_0_cfg, .p_api = &g_timer_on_gpt };
gpt_three_phase_instance_ctrl_t g_three_phase2_ctrl;
const three_phase_cfg_t g_three_phase2_cfg =
{ .buffer_mode = (THREE_PHASE_BUFFER_MODE_SINGLE), .p_timer_instance =
{ &g_timer2_0, &g_timer2_1, &g_timer2_2 },
  .callback_ch = THREE_PHASE_CHANNEL_U, .channel_mask = (1 << 0) | (1 << 1) | (1 << 2), .p_context = NULL, .p_extend =
          NULL, };
/* Instance structure to use this module. */
const three_phase_instance_t g_three_phase2 =
{ .p_ctrl = &g_three_phase2_ctrl, .p_cfg = &g_three_phase2_cfg, .p_api = &g_gpt_three_phase_on_gpt_three_phase };
gpt_instance_ctrl_t g_timer1_2_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer1_2_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT7_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT7_UDF,
#elif defined(VECTOR_NUMBER_GPT01_2_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT01_2_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer1_2_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT7_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT7_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_2_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT01_2_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT7_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT7_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_2_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT01_2_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer1_2_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT7_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT7_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_2_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT01_2_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT7_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_2_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT7_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_2_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer1_2_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT1_2,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer1_2_extend,
#if defined(VECTOR_NUMBER_GPT7_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT7_OVF,
#elif defined(VECTOR_NUMBER_GPT01_2_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT01_2_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer1_2 =
{ .p_ctrl = &g_timer1_2_ctrl, .p_cfg = &g_timer1_2_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer1_1_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer1_1_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT6_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT6_UDF,
#elif defined(VECTOR_NUMBER_GPT01_1_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT01_1_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer1_1_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT6_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT6_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_1_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT01_1_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT6_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT6_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_1_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT01_1_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer1_1_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT6_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT6_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_1_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT01_1_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT6_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_1_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT6_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_1_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer1_1_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT1_1,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer1_1_extend,
#if defined(VECTOR_NUMBER_GPT6_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT6_OVF,
#elif defined(VECTOR_NUMBER_GPT01_1_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT01_1_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer1_1 =
{ .p_ctrl = &g_timer1_1_ctrl, .p_cfg = &g_timer1_1_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer1_0_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer1_0_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT5_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT5_UDF,
#elif defined(VECTOR_NUMBER_GPT01_0_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT01_0_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_DOWN_COUNT_START_ADC_A
                  | GPT_ADC_TRIGGER_NONE,
          .dead_time_count_up = 500, .dead_time_count_down = 500, .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .gtiocb_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .interrupt_skip_source_ext1 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext1 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_source_ext2 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext2 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_func_ovf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_unf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_a =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_b = GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer1_0_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT5_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT5_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_0_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT01_0_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT5_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT5_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_0_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT01_0_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer1_0_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT5_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT5_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_0_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT01_0_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT5_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_0_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT5_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT01_0_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer1_0_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT1_0,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer1_0_extend,
#if defined(VECTOR_NUMBER_GPT5_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT5_OVF,
#elif defined(VECTOR_NUMBER_GPT01_0_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT01_0_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer1_0 =
{ .p_ctrl = &g_timer1_0_ctrl, .p_cfg = &g_timer1_0_cfg, .p_api = &g_timer_on_gpt };
gpt_three_phase_instance_ctrl_t g_three_phase1_ctrl;
const three_phase_cfg_t g_three_phase1_cfg =
{ .buffer_mode = (THREE_PHASE_BUFFER_MODE_SINGLE), .p_timer_instance =
{ &g_timer1_0, &g_timer1_1, &g_timer1_2 },
  .callback_ch = THREE_PHASE_CHANNEL_U, .channel_mask = (1 << 0) | (1 << 1) | (1 << 2), .p_context = NULL, .p_extend =
          NULL, };
/* Instance structure to use this module. */
const three_phase_instance_t g_three_phase1 =
{ .p_ctrl = &g_three_phase1_ctrl, .p_cfg = &g_three_phase1_cfg, .p_api = &g_gpt_three_phase_on_gpt_three_phase };
gpt_instance_ctrl_t g_timer7_2_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer7_2_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT37_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT37_UDF,
#elif defined(VECTOR_NUMBER_GPT07_2_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT07_2_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer7_2_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT37_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT37_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_2_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT07_2_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT37_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT37_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_2_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT07_2_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer7_2_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT37_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT37_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_2_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT07_2_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT37_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_2_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT37_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_2_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer7_2_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT7_2,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer7_2_extend,
#if defined(VECTOR_NUMBER_GPT37_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT37_OVF,
#elif defined(VECTOR_NUMBER_GPT07_2_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT07_2_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer7_2 =
{ .p_ctrl = &g_timer7_2_ctrl, .p_cfg = &g_timer7_2_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer7_1_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer7_1_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT36_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT36_UDF,
#elif defined(VECTOR_NUMBER_GPT07_1_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT07_1_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer7_1_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT36_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT36_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_1_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT07_1_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT36_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT36_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_1_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT07_1_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer7_1_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT36_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT36_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_1_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT07_1_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT36_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_1_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT36_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_1_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer7_1_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT7_1,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer7_1_extend,
#if defined(VECTOR_NUMBER_GPT36_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT36_OVF,
#elif defined(VECTOR_NUMBER_GPT07_1_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT07_1_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer7_1 =
{ .p_ctrl = &g_timer7_1_ctrl, .p_cfg = &g_timer7_1_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer7_0_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer7_0_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT35_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT35_UDF,
#elif defined(VECTOR_NUMBER_GPT07_0_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT07_0_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_DOWN_COUNT_START_ADC_A
                  | GPT_ADC_TRIGGER_NONE,
          .dead_time_count_up = 500, .dead_time_count_down = 500, .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .gtiocb_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .interrupt_skip_source_ext1 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext1 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_source_ext2 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext2 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_func_ovf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_unf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_a =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_b = GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer7_0_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT35_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT35_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_0_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT07_0_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT35_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT35_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_0_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT07_0_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer7_0_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT35_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT35_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_0_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT07_0_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT35_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_0_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT35_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT07_0_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer7_0_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT7_0,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer7_0_extend,
#if defined(VECTOR_NUMBER_GPT35_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT35_OVF,
#elif defined(VECTOR_NUMBER_GPT07_0_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT07_0_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer7_0 =
{ .p_ctrl = &g_timer7_0_ctrl, .p_cfg = &g_timer7_0_cfg, .p_api = &g_timer_on_gpt };
gpt_three_phase_instance_ctrl_t g_three_phase7_ctrl;
const three_phase_cfg_t g_three_phase7_cfg =
{ .buffer_mode = (THREE_PHASE_BUFFER_MODE_SINGLE), .p_timer_instance =
{ &g_timer7_0, &g_timer7_1, &g_timer7_2 },
  .callback_ch = THREE_PHASE_CHANNEL_U, .channel_mask = (1 << 0) | (1 << 1) | (1 << 2), .p_context = NULL, .p_extend =
          NULL, };
/* Instance structure to use this module. */
const three_phase_instance_t g_three_phase7 =
{ .p_ctrl = &g_three_phase7_ctrl, .p_cfg = &g_three_phase7_cfg, .p_api = &g_gpt_three_phase_on_gpt_three_phase };
xspi_ospi_instance_ctrl_t g_ospi0_ctrl;

static const spi_flash_erase_command_t g_ospi0_erase_command_list[] =
{
#if 4096 > 0
  { .command = 0x21DE, .size = 4096 },
#endif
#if 65536 > 0
  { .command = 0xDC23, .size = 65536 },
#endif
#if 0xC738 > 0
  { .command = 0xC738, .size = SPI_FLASH_ERASE_SIZE_CHIP_ERASE },
#endif
        };

static xspi_ospi_timing_setting_t g_ospi0_timing_settings =
{ .command_to_command_interval = XSPI_OSPI_COMMAND_INTERVAL_CLOCKS_7, .cs_pullup_lag =
          XSPI_OSPI_CS_PULLUP_CLOCKS_NO_EXTENSION,
  .cs_pulldown_lead = XSPI_OSPI_CS_PULLDOWN_CLOCKS_NO_EXTENSION };

const xspi_ospi_opi_command_set_t g_ospi0_opi_command_set =
{ .dual_read_command = 0xEE11,
  .page_program_command = 0x12ED,
  .write_enable_command = 0x06F9,
  .status_command = 0x05FA,
  .command_bytes = 2 };

static xspi_ospi_address_space_t g_ospi0_address_space_settings =
{ .unit0_cs0_end_address = XSPI_OSPI_CFG_UNIT_0_CS_0_END_ADDRESS, .unit0_cs1_start_address =
          XSPI_OSPI_CFG_UNIT_0_CS_1_START_ADDRESS,
  .unit0_cs1_end_address = XSPI_OSPI_CFG_UNIT_0_CS_1_END_ADDRESS, .unit1_cs0_end_address =
          XSPI_OSPI_CFG_UNIT_1_CS_0_END_ADDRESS,
  .unit1_cs1_start_address = XSPI_OSPI_CFG_UNIT_1_CS_1_START_ADDRESS, .unit1_cs1_end_address =
          XSPI_OSPI_CFG_UNIT_1_CS_1_END_ADDRESS, };

static const xspi_ospi_extended_cfg_t g_ospi0_extended_cfg =
{ .unit = 0,
  .chip_select = XSPI_OSPI_CHIP_SELECT_0,
  .memory_size = XSPI_OSPI_MEMORY_SIZE_64MB,
  .p_timing_settings = &g_ospi0_timing_settings,
  .p_opi_commands = &g_ospi0_opi_command_set,
  .opi_mem_read_dummy_cycles = 10,
  .p_autocalibration_preamble_pattern_addr = (uint8_t*) 0x00,
  .data_latch_delay_clocks = 0x08,
#if 0 == 0
  .prefetch_en = (xspi_ospi_prefetch_function_t) XSPI_OSPI_CFG_UNIT_0_PREFETCH_FUNCTION,
#else
    .prefetch_en                             = (xspi_ospi_prefetch_function_t) XSPI_OSPI_CFG_UNIT_1_PREFETCH_FUNCTION,
#endif
#if BSP_FEATURE_XSPI_VOLTAGE_SETTING_SUPPORTED
 #if 0 == 0
    .io_voltage                              = (xspi_ospi_io_voltage_t) XSPI_OSPI_CFG_UNIT_0_IOVOLTAGE,
 #else
    .io_voltage                              = (xspi_ospi_io_voltage_t) XSPI_OSPI_CFG_UNIT_1_IOVOLTAGE,
 #endif
#endif
  .byte_order = XSPI_OSPI_BYTE_ORDER_0123,
  .p_address_space = &g_ospi0_address_space_settings, };
const spi_flash_cfg_t g_ospi0_cfg =
{ .spi_protocol = SPI_FLASH_PROTOCOL_1S_1S_1S, .address_bytes = SPI_FLASH_ADDRESS_BYTES_4, .page_size_bytes = 0, //Unused
  .page_program_command = 0x12,
  .read_command = 0x13,
  .write_enable_command = 0x06,
  .status_command = 0x05,
  .write_status_bit = 0,
  .p_erase_command_list = &g_ospi0_erase_command_list[0],
  .erase_command_list_length = sizeof(g_ospi0_erase_command_list) / sizeof(g_ospi0_erase_command_list[0]),
  .p_extend = &g_ospi0_extended_cfg, };
/** This structure encompasses everything that is needed to use an instance of this interface. */
const spi_flash_instance_t g_ospi0 =
{ .p_ctrl = &g_ospi0_ctrl, .p_cfg = &g_ospi0_cfg, .p_api = &g_spi_flash_on_xspi_ospi, };
poeg_instance_ctrl_t g_poeg0_ctrl;
const poeg_cfg_t g_poeg0_cfg =
{ .trigger = (poeg_trigger_t) (POEG_TRIGGER_PIN | POEG_TRIGGER_SOFTWARE),
  .polarity = POEG_GTETRG_POLARITY_ACTIVE_HIGH,
  .noise_filter = POEG_GTETRG_NOISE_FILTER_CLK_SOURCE_DIV_128,
  .unit = 0,
  .channel = 3,
  .ipl = (BSP_IRQ_DISABLED),
  .p_callback = NULL,
  .p_context = NULL,
#if defined(VECTOR_NUMBER_POEG0_GROUP3)
    .irq       = VECTOR_NUMBER_POEG0_GROUP3,
#else
  .irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const poeg_instance_t g_poeg0 =
{ .p_ctrl = &g_poeg0_ctrl, .p_cfg = &g_poeg0_cfg, .p_api = &g_poeg_on_poeg };
gpt_instance_ctrl_t g_timer0_2_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer0_2_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT2_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT2_UDF,
#elif defined(VECTOR_NUMBER_GPT00_2_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT00_2_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer0_2_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT2_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT2_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_2_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT00_2_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT2_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT2_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_2_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT00_2_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer0_2_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT2_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT2_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_2_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT00_2_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT2_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_2_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT2_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_2_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer0_2_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT0_2,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer0_2_extend,
#if defined(VECTOR_NUMBER_GPT2_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT2_OVF,
#elif defined(VECTOR_NUMBER_GPT00_2_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT00_2_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer0_2 =
{ .p_ctrl = &g_timer0_2_ctrl, .p_cfg = &g_timer0_2_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer0_1_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer0_1_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT1_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT1_UDF,
#elif defined(VECTOR_NUMBER_GPT00_1_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT00_1_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_NONE, .dead_time_count_up = 500, .dead_time_count_down =
                  500,
          .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .gtiocb_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .interrupt_skip_source_ext1 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext1 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_source_ext2 = GPT_INTERRUPT_SKIP_SOURCE_NONE, .interrupt_skip_count_ext2 =
                  GPT_INTERRUPT_SKIP_COUNT_0,
          .interrupt_skip_func_ovf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_unf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_a = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_b =
                  GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer0_1_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT1_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT1_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_1_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT00_1_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT1_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT1_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_1_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT00_1_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer0_1_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT1_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT1_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_1_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT00_1_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT1_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_1_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT1_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_1_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer0_1_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT0_1,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer0_1_extend,
#if defined(VECTOR_NUMBER_GPT1_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT1_OVF,
#elif defined(VECTOR_NUMBER_GPT00_1_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT00_1_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer0_1 =
{ .p_ctrl = &g_timer0_1_ctrl, .p_cfg = &g_timer0_1_cfg, .p_api = &g_timer_on_gpt };
gpt_instance_ctrl_t g_timer0_0_ctrl;
#if 1
const gpt_extended_pwm_cfg_t g_timer0_0_pwm_extend =
        {
#if defined(VECTOR_NUMBER_GPT0_UDF)
    .trough_ipl          = (BSP_IRQ_DISABLED),
    .trough_irq          = VECTOR_NUMBER_GPT0_UDF,
#elif defined(VECTOR_NUMBER_GPT00_0_INT0xFF)
    .trough_ipl          = FSP_NOT_DEFINED,
    .trough_irq          = VECTOR_NUMBER_GPT00_0_INT0xFF,
#else
          .trough_ipl = (BSP_IRQ_DISABLED),
          .trough_irq = FSP_INVALID_VECTOR,
#endif
          .poeg_link = GPT_POEG_LINK_POEG3,
          .output_disable = GPT_OUTPUT_DISABLE_NONE, .adc_trigger = GPT_ADC_TRIGGER_DOWN_COUNT_START_ADC_A
                  | GPT_ADC_TRIGGER_NONE,
          .dead_time_count_up = 500, .dead_time_count_down = 500, .adc_a_compare_match = 0, .adc_b_compare_match = 0, .interrupt_skip_source =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_adc = GPT_INTERRUPT_SKIP_ADC_NONE, .gtioca_disable_setting =
                  GPT_GTIOC_DISABLE_SET_HI_Z,
          .gtiocb_disable_setting = GPT_GTIOC_DISABLE_SET_HI_Z, .interrupt_skip_source_ext1 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext1 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_source_ext2 =
                  GPT_INTERRUPT_SKIP_SOURCE_NONE,
          .interrupt_skip_count_ext2 = GPT_INTERRUPT_SKIP_COUNT_0, .interrupt_skip_func_ovf =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_unf = GPT_INTERRUPT_SKIP_SELECT_NONE, .interrupt_skip_func_adc_a =
                  GPT_INTERRUPT_SKIP_SELECT_NONE,
          .interrupt_skip_func_adc_b = GPT_INTERRUPT_SKIP_SELECT_NONE, };
#endif
const gpt_extended_cfg_t g_timer0_0_extend =
        { .gtioca =
        { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW },
          .gtiocb =
          { .output_enabled = true, .stop_level = GPT_PIN_LEVEL_HIGH },
          .start_source = (gpt_source_t) (GPT_SOURCE_NONE), .stop_source = (gpt_source_t) (GPT_SOURCE_NONE), .clear_source =
                  (gpt_source_t) (GPT_SOURCE_NONE),
#if (0 == (0))
          .count_up_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .count_down_source = (gpt_source_t) (GPT_SOURCE_NONE),
#else
    .count_up_source     = (gpt_source_t) ((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0x000FFFFU),
    .count_down_source   = (gpt_source_t) (((GPT_PHASE_COUNTING_MODE_1_UP | (GPT_PHASE_COUNTING_MODE_1_DN << 16)) & 0xFFFF0000U) >> 16),
#endif
          .capture_a_source = (gpt_source_t) (GPT_SOURCE_NONE),
          .capture_b_source = (gpt_source_t) (GPT_SOURCE_NONE),
#if defined(VECTOR_NUMBER_GPT0_CCMPA)
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_a_irq       = VECTOR_NUMBER_GPT0_CCMPA,
    .capture_a_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_0_INT0xFF)
    .capture_a_ipl       = FSP_NOT_DEFINED,
    .capture_a_irq       = VECTOR_NUMBER_GPT00_0_INT0xFF,
    .capture_a_source_select = 0xFF,
#else
          .capture_a_ipl = (BSP_IRQ_DISABLED),
          .capture_a_irq = FSP_INVALID_VECTOR, .capture_a_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT0_CCMPB)
    .capture_b_irq       = VECTOR_NUMBER_GPT0_CCMPB,
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_0_INT0xFF)
    .capture_b_irq       = VECTOR_NUMBER_GPT00_0_INT0xFF,
    .capture_b_ipl       = FSP_NOT_DEFINED,
    .capture_b_source_select = 0xFF,
#else
          .capture_b_ipl = (BSP_IRQ_DISABLED),
          .capture_b_irq = FSP_INVALID_VECTOR, .capture_b_source_select = BSP_IRQ_DISABLED,
#endif
          .capture_filter_gtioca = GPT_CAPTURE_FILTER_NONE,
          .capture_filter_gtiocb = GPT_CAPTURE_FILTER_NONE,
#if 1
          .p_pwm_cfg = &g_timer0_0_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if defined(VECTOR_NUMBER_GPT0_DTE)
    .dead_time_ipl       = (BSP_IRQ_DISABLED),
    .dead_time_irq       = VECTOR_NUMBER_GPT0_DTE,
    .dead_time_error_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_0_INT0xFF)
    .dead_time_ipl       = FSP_NOT_DEFINED,
    .dead_time_irq       = VECTOR_NUMBER_GPT00_0_INT0xFF,
    .dead_time_error_source_select = 0xFF,
#else
          .dead_time_ipl = (BSP_IRQ_DISABLED),
          .dead_time_irq = FSP_INVALID_VECTOR, .dead_time_error_source_select = BSP_IRQ_DISABLED,
#endif
          .icds = 0,
#if (2U == BSP_FEATURE_GPT_REGISTER_MASK_TYPE)
 #if (1U == BSP_FEATURE_GPT_INPUT_CAPTURE_SIGNAL_SELECTABLE)
    .gtioc_isel          = GPT_INPUT_SIGNAL_SELECT_GTIOC00_4A_4B,
 #endif
#endif

#if defined(VECTOR_NUMBER_GPT0_OVF)
    .cycle_end_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_0_INT0xFF)
    .cycle_end_source_select = 0xFF,
#else
          .cycle_end_source_select = BSP_IRQ_DISABLED,
#endif
#if defined(VECTOR_NUMBER_GPT0_UDF)
    .trough_source_select = BSP_IRQ_DISABLED,
#elif defined(VECTOR_NUMBER_GPT00_0_INT0xFF)
    .trough_source_select = 0xFF,
#else
          .trough_source_select = BSP_IRQ_DISABLED,
#endif
        };
const timer_cfg_t g_timer0_0_cfg =
{ .mode = TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM,
/* Actual period: 0.00005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x30d4,
  .duty_cycle_counts = 0x186a, .source_div = (timer_source_div_t) 0, .channel = GPT_CHANNEL_UNIT0_0,
#if (1 == BSP_FEATURE_BSP_IRQ_GPT_SEL_SUPPORTED)
    .p_callback          = NULL,
#else
  .p_callback = NULL,
#endif
  .p_context = NULL,
  .p_extend = &g_timer0_0_extend,
#if defined(VECTOR_NUMBER_GPT0_OVF)
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
    .cycle_end_irq       = VECTOR_NUMBER_GPT0_OVF,
#elif defined(VECTOR_NUMBER_GPT00_0_INT0xFF)
    .cycle_end_ipl       = FSP_NOT_DEFINED,
    .cycle_end_irq       = VECTOR_NUMBER_GPT00_0_INT0xFF,
#else
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer0_0 =
{ .p_ctrl = &g_timer0_0_ctrl, .p_cfg = &g_timer0_0_cfg, .p_api = &g_timer_on_gpt };
gpt_three_phase_instance_ctrl_t g_three_phase0_ctrl;
const three_phase_cfg_t g_three_phase0_cfg =
{ .buffer_mode = (THREE_PHASE_BUFFER_MODE_SINGLE), .p_timer_instance =
{ &g_timer0_0, &g_timer0_1, &g_timer0_2 },
  .callback_ch = THREE_PHASE_CHANNEL_U, .channel_mask = (1 << 0) | (1 << 1) | (1 << 2), .p_context = NULL, .p_extend =
          NULL, };
/* Instance structure to use this module. */
const three_phase_instance_t g_three_phase0 =
{ .p_ctrl = &g_three_phase0_ctrl, .p_cfg = &g_three_phase0_cfg, .p_api = &g_gpt_three_phase_on_gpt_three_phase };
sci_uart_instance_ctrl_t g_uart5_ctrl;

#define FSP_NOT_DEFINED (1)
#if (FSP_NOT_DEFINED) != (FSP_NOT_DEFINED)

            /* If the transfer module is DMAC, define a DMAC transfer callback. */
            extern void sci_uart_tx_dmac_callback(sci_uart_instance_ctrl_t * p_instance_ctrl);

            void g_uart5_tx_transfer_callback (transfer_callback_args_t * p_args)
            {
                FSP_PARAMETER_NOT_USED(p_args);
                sci_uart_tx_dmac_callback(&g_uart5_ctrl);
            }
            #endif

#if (FSP_NOT_DEFINED) != (FSP_NOT_DEFINED)

            /* If the transfer module is DMAC, define a DMAC transfer callback. */
            extern void sci_uart_rx_dmac_callback(sci_uart_instance_ctrl_t * p_instance_ctrl);

            void g_uart5_rx_transfer_callback (transfer_callback_args_t * p_args)
            {
                FSP_PARAMETER_NOT_USED(p_args);
                sci_uart_rx_dmac_callback(&g_uart5_ctrl);
            }
            #endif
#undef FSP_NOT_DEFINED

sci_baud_setting_t g_uart5_baud_setting =
        {
        /* Baud rate calculated with 0.160% error. */.baudrate_bits_b.abcse = 0,
          .baudrate_bits_b.abcs = 0, .baudrate_bits_b.bgdm = 1, .baudrate_bits_b.cks = 0, .baudrate_bits_b.brr = 51, .baudrate_bits_b.mddr =
                  (uint8_t) 256,
          .baudrate_bits_b.brme = false };

/** UART extended configuration for UARTonSCI HAL driver */
const sci_uart_extended_cfg_t g_uart5_cfg_extend =
{ .clock = SCI_UART_CLOCK_INT, .rx_edge_start = SCI_UART_START_BIT_FALLING_EDGE, .noise_cancel =
          SCI_UART_NOISE_CANCELLATION_DISABLE,
  .rx_fifo_trigger = SCI_UART_RX_FIFO_TRIGGER_MAX, .p_baud_setting = &g_uart5_baud_setting,
#if 1
  .clock_source = SCI_UART_CLOCK_SOURCE_SCI5ASYNCCLK,
#else
                .clock_source           = SCI_UART_CLOCK_SOURCE_PCLKM,
#endif
  .flow_control = SCI_UART_FLOW_CONTROL_RTS,
#if 0xFF != 0xFF
                .flow_control_pin       = BSP_IO_PORT_FF_PIN_0xFF,
                #else
  .flow_control_pin = (bsp_io_port_pin_t) UINT16_MAX,
#endif
  .rs485_setting =
  { .enable = SCI_UART_RS485_DISABLE, .polarity = SCI_UART_RS485_DE_POLARITY_HIGH, .assertion_time = 1, .negation_time =
            1, }, };

/** UART interface configuration */
const uart_cfg_t g_uart5_cfg =
{ .channel = 5, .data_bits = UART_DATA_BITS_8, .parity = UART_PARITY_OFF, .stop_bits = UART_STOP_BITS_1, .p_callback =
          NULL,
  .p_context = NULL, .p_extend = &g_uart5_cfg_extend, .p_transfer_tx = g_uart5_P_TRANSFER_TX, .p_transfer_rx =
          g_uart5_P_TRANSFER_RX,
  .rxi_ipl = (2), .txi_ipl = (2), .tei_ipl = (2), .eri_ipl = (2),
#if defined(VECTOR_NUMBER_SCI5_RXI)
                .rxi_irq             = VECTOR_NUMBER_SCI5_RXI,
#else
  .rxi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI5_TXI)
                .txi_irq             = VECTOR_NUMBER_SCI5_TXI,
#else
  .txi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI5_TEI)
                .tei_irq             = VECTOR_NUMBER_SCI5_TEI,
#else
  .tei_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI5_ERI)
                .eri_irq             = VECTOR_NUMBER_SCI5_ERI,
#else
  .eri_irq = FSP_INVALID_VECTOR,
#endif
        };

/* Instance structure to use this module. */
const uart_instance_t g_uart5 =
{ .p_ctrl = &g_uart5_ctrl, .p_cfg = &g_uart5_cfg, .p_api = &g_uart_on_sci };
sci_uart_instance_ctrl_t g_uart0_ctrl;

#define FSP_NOT_DEFINED (1)
#if (FSP_NOT_DEFINED) != (FSP_NOT_DEFINED)

            /* If the transfer module is DMAC, define a DMAC transfer callback. */
            extern void sci_uart_tx_dmac_callback(sci_uart_instance_ctrl_t * p_instance_ctrl);

            void g_uart0_tx_transfer_callback (transfer_callback_args_t * p_args)
            {
                FSP_PARAMETER_NOT_USED(p_args);
                sci_uart_tx_dmac_callback(&g_uart0_ctrl);
            }
            #endif

#if (FSP_NOT_DEFINED) != (FSP_NOT_DEFINED)

            /* If the transfer module is DMAC, define a DMAC transfer callback. */
            extern void sci_uart_rx_dmac_callback(sci_uart_instance_ctrl_t * p_instance_ctrl);

            void g_uart0_rx_transfer_callback (transfer_callback_args_t * p_args)
            {
                FSP_PARAMETER_NOT_USED(p_args);
                sci_uart_rx_dmac_callback(&g_uart0_ctrl);
            }
            #endif
#undef FSP_NOT_DEFINED

sci_baud_setting_t g_uart0_baud_setting =
        {
        /* Baud rate calculated with 0.160% error. */.baudrate_bits_b.abcse = 0,
          .baudrate_bits_b.abcs = 0, .baudrate_bits_b.bgdm = 1, .baudrate_bits_b.cks = 0, .baudrate_bits_b.brr = 51, .baudrate_bits_b.mddr =
                  (uint8_t) 256,
          .baudrate_bits_b.brme = false };

/** UART extended configuration for UARTonSCI HAL driver */
const sci_uart_extended_cfg_t g_uart0_cfg_extend =
{ .clock = SCI_UART_CLOCK_INT, .rx_edge_start = SCI_UART_START_BIT_FALLING_EDGE, .noise_cancel =
          SCI_UART_NOISE_CANCELLATION_DISABLE,
  .rx_fifo_trigger = SCI_UART_RX_FIFO_TRIGGER_MAX, .p_baud_setting = &g_uart0_baud_setting,
#if 1
  .clock_source = SCI_UART_CLOCK_SOURCE_SCI0ASYNCCLK,
#else
                .clock_source           = SCI_UART_CLOCK_SOURCE_PCLKM,
#endif
  .flow_control = SCI_UART_FLOW_CONTROL_RTS,
#if 0xFF != 0xFF
                .flow_control_pin       = BSP_IO_PORT_FF_PIN_0xFF,
                #else
  .flow_control_pin = (bsp_io_port_pin_t) UINT16_MAX,
#endif
  .rs485_setting =
  { .enable = SCI_UART_RS485_DISABLE, .polarity = SCI_UART_RS485_DE_POLARITY_HIGH, .assertion_time = 1, .negation_time =
            1, }, };

/** UART interface configuration */
const uart_cfg_t g_uart0_cfg =
{ .channel = 0, .data_bits = UART_DATA_BITS_8, .parity = UART_PARITY_OFF, .stop_bits = UART_STOP_BITS_1, .p_callback =
          user_uart_callback,
  .p_context = NULL, .p_extend = &g_uart0_cfg_extend, .p_transfer_tx = g_uart0_P_TRANSFER_TX, .p_transfer_rx =
          g_uart0_P_TRANSFER_RX,
  .rxi_ipl = (30), .txi_ipl = (30), .tei_ipl = (30), .eri_ipl = (30),
#if defined(VECTOR_NUMBER_SCI0_RXI)
                .rxi_irq             = VECTOR_NUMBER_SCI0_RXI,
#else
  .rxi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI0_TXI)
                .txi_irq             = VECTOR_NUMBER_SCI0_TXI,
#else
  .txi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI0_TEI)
                .tei_irq             = VECTOR_NUMBER_SCI0_TEI,
#else
  .tei_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI0_ERI)
                .eri_irq             = VECTOR_NUMBER_SCI0_ERI,
#else
  .eri_irq = FSP_INVALID_VECTOR,
#endif
        };

/* Instance structure to use this module. */
const uart_instance_t g_uart0 =
{ .p_ctrl = &g_uart0_ctrl, .p_cfg = &g_uart0_cfg, .p_api = &g_uart_on_sci };
void g_hal_init(void)
{
    g_common_init ();
}
