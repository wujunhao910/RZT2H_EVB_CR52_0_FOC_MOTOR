/* generated pin source file - do not edit */
#include "bsp_api.h"
#include "r_ioport_api.h"
#include "r_ioport.h"

extern const ioport_extend_cfg_t g_ioport_cfg_extend;

const ioport_pin_cfg_t g_bsp_pin_cfg_data[] =
        {
        { .pin = BSP_IO_PORT_00_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                | (uint32_t) IOPORT_PIN_P000_PFC_09_GTIOC00_0A) },
          { .pin = BSP_IO_PORT_00_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P001_PFC_09_GTIOC00_0B) },
          { .pin = BSP_IO_PORT_00_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P002_PFC_09_GTIOC00_1A) },
          { .pin = BSP_IO_PORT_00_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P003_PFC_09_GTIOC00_1B) },
          { .pin = BSP_IO_PORT_00_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P004_PFC_09_GTIOC00_2A) },
          { .pin = BSP_IO_PORT_00_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P005_PFC_09_GTIOC00_2B) },
          { .pin = BSP_IO_PORT_00_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) },
          { .pin = BSP_IO_PORT_00_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P007_PFC_16_DEE04) },
          { .pin = BSP_IO_PORT_01_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P010_PFC_16_TXDE04) },
          { .pin = BSP_IO_PORT_01_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P011_PFC_16_RXDE04) },
          { .pin = BSP_IO_PORT_01_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P012_PFC_09_GTIOC01_0A) },
          { .pin = BSP_IO_PORT_01_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P013_PFC_09_GTIOC01_0B) },
          { .pin = BSP_IO_PORT_01_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P014_PFC_0A_GTIOC04_1A) },
          { .pin = BSP_IO_PORT_01_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P015_PFC_0A_GTIOC04_1B) },
          { .pin = BSP_IO_PORT_01_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P016_PFC_0A_GTIOC04_2A) },
          { .pin = BSP_IO_PORT_01_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P017_PFC_0A_GTIOC04_2B) },
          { .pin = BSP_IO_PORT_02_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P022_PFC_1D_MCLK22) },
          { .pin = BSP_IO_PORT_02_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P025_PFC_09_GTIOC02_0A) },
          { .pin = BSP_IO_PORT_02_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P026_PFC_09_GTIOC02_0B) },
          { .pin = BSP_IO_PORT_02_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P027_PFC_09_GTIOC02_1A) },
          { .pin = BSP_IO_PORT_03_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P030_PFC_09_GTIOC02_1B) },
          { .pin = BSP_IO_PORT_03_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P031_PFC_09_GTIOC02_2A) },
          { .pin = BSP_IO_PORT_03_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P032_PFC_09_GTIOC02_2B) },
          { .pin = BSP_IO_PORT_03_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P034_PFC_15_DEE02) },
          { .pin = BSP_IO_PORT_03_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P035_PFC_15_TXDE02) },
          { .pin = BSP_IO_PORT_03_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P036_PFC_15_RXDE02) },
          { .pin = BSP_IO_PORT_03_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P037_PFC_09_GTIOC03_0A) },
          { .pin = BSP_IO_PORT_04_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P040_PFC_09_GTIOC03_0B) },
          { .pin = BSP_IO_PORT_04_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P041_PFC_09_GTIOC03_1A) },
          { .pin = BSP_IO_PORT_04_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P042_PFC_09_GTIOC03_1B) },
          { .pin = BSP_IO_PORT_04_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P043_PFC_09_GTIOC03_2A) },
          { .pin = BSP_IO_PORT_04_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P044_PFC_09_GTIOC03_2B) },
          { .pin = BSP_IO_PORT_04_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P046_PFC_15_DEE03) },
          { .pin = BSP_IO_PORT_04_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P047_PFC_15_TXDE03) },
          { .pin = BSP_IO_PORT_05_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P050_PFC_15_RXDE03) },
          { .pin = BSP_IO_PORT_05_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P051_PFC_1C_XSPI0_CKP) },
          { .pin = BSP_IO_PORT_05_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P052_PFC_1C_XSPI0_CKN) },
          { .pin = BSP_IO_PORT_05_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P053_PFC_1C_XSPI0_CS0) },
          { .pin = BSP_IO_PORT_05_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P055_PFC_1C_XSPI0_DS) },
          { .pin = BSP_IO_PORT_05_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P056_PFC_1C_XSPI0_IO0) },
          { .pin = BSP_IO_PORT_05_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P057_PFC_1C_XSPI0_IO1) },
          { .pin = BSP_IO_PORT_06_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P060_PFC_1C_XSPI0_IO2) },
          { .pin = BSP_IO_PORT_06_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P061_PFC_1C_XSPI0_IO3) },
          { .pin = BSP_IO_PORT_06_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P062_PFC_1C_XSPI0_IO4) },
          { .pin = BSP_IO_PORT_06_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P063_PFC_1C_XSPI0_IO5) },
          { .pin = BSP_IO_PORT_06_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P064_PFC_1C_XSPI0_IO6) },
          { .pin = BSP_IO_PORT_06_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P065_PFC_1C_XSPI0_IO7) },
          { .pin = BSP_IO_PORT_06_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P066_PFC_1C_XSPI0_RESET0) },
          { .pin = BSP_IO_PORT_06_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW) },
          { .pin = BSP_IO_PORT_07_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P071_PFC_1D_MCLK00) },
          { .pin = BSP_IO_PORT_07_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P072_PFC_1D_MDAT00) },
          { .pin = BSP_IO_PORT_07_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P073_PFC_1D_MCLK01) },
          { .pin = BSP_IO_PORT_07_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P074_PFC_1D_MDAT01) },
          { .pin = BSP_IO_PORT_07_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P075_PFC_1D_MCLK02) },
          { .pin = BSP_IO_PORT_07_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P076_PFC_1D_MDAT02) },
          { .pin = BSP_IO_PORT_07_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P077_PFC_1D_MCLK10) },
          { .pin = BSP_IO_PORT_08_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P080_PFC_1D_MDAT10) },
          { .pin = BSP_IO_PORT_08_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P081_PFC_01_TMS) },
          { .pin = BSP_IO_PORT_08_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_PIN_P082_PFC_01_TDI) },
          { .pin = BSP_IO_PORT_08_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SCHMITT_TRIGGER_ENABLE | (uint32_t) IOPORT_PIN_P083_PFC_01_TCK) },
          { .pin = BSP_IO_PORT_08_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P084_PFC_01_TDO) },
          { .pin = BSP_IO_PORT_08_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH) },
          { .pin = BSP_IO_PORT_08_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P086_PFC_1E_MCLK11) },
          { .pin = BSP_IO_PORT_08_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P087_PFC_1E_MDAT11) },
          { .pin = BSP_IO_PORT_09_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P090_PFC_1D_MCLK12) },
          { .pin = BSP_IO_PORT_09_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P091_PFC_1D_MDAT12) },
          { .pin = BSP_IO_PORT_09_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P092_PFC_1D_MCLK20) },
          { .pin = BSP_IO_PORT_09_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P093_PFC_1D_MDAT20) },
          { .pin = BSP_IO_PORT_09_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P094_PFC_09_GTIOC04_0A) },
          { .pin = BSP_IO_PORT_09_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P095_PFC_09_GTIOC04_0B) },
          { .pin = BSP_IO_PORT_09_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P096_PFC_1D_MCLK71) },
          { .pin = BSP_IO_PORT_09_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P097_PFC_1D_MDAT71) },
          { .pin = BSP_IO_PORT_10_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P100_PFC_1D_MCLK72) },
          { .pin = BSP_IO_PORT_10_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P101_PFC_1D_MDAT72) },
          { .pin = BSP_IO_PORT_10_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P106_PFC_1D_MCLK21) },
          { .pin = BSP_IO_PORT_10_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P107_PFC_1D_MDAT21) },
          { .pin = BSP_IO_PORT_11_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P111_PFC_1D_MDAT22) },
          { .pin = BSP_IO_PORT_11_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P112_PFC_1D_MCLK30) },
          { .pin = BSP_IO_PORT_11_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P113_PFC_1D_MDAT30) },
          { .pin = BSP_IO_PORT_11_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P114_PFC_1D_MCLK31) },
          { .pin = BSP_IO_PORT_11_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P115_PFC_1D_MDAT31) },
          { .pin = BSP_IO_PORT_11_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P116_PFC_09_GTIOC05_0A) },
          { .pin = BSP_IO_PORT_11_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_PIN_P117_PFC_09_GTIOC05_0B) },
          { .pin = BSP_IO_PORT_12_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_UHIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P120_PFC_09_GTIOC05_1A) },
          { .pin = BSP_IO_PORT_12_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P121_PFC_09_GTIOC05_1B) },
          { .pin = BSP_IO_PORT_12_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P122_PFC_09_GTIOC05_2A) },
          { .pin = BSP_IO_PORT_12_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P123_PFC_09_GTIOC05_2B) },
          { .pin = BSP_IO_PORT_12_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P125_PFC_15_DEE05) },
          { .pin = BSP_IO_PORT_12_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P126_PFC_15_TXDE05) },
          { .pin = BSP_IO_PORT_12_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST | (uint32_t) IOPORT_PIN_P127_PFC_15_RXDE05) },
          { .pin = BSP_IO_PORT_14_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P143_PFC_15_DEE00) },
          { .pin = BSP_IO_PORT_14_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P144_PFC_15_TXDE00) },
          { .pin = BSP_IO_PORT_14_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P145_PFC_15_RXDE00) },
          { .pin = BSP_IO_PORT_14_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P147_PFC_1D_MCLK32) },
          { .pin = BSP_IO_PORT_15_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P150_PFC_1D_MDAT32) },
          { .pin = BSP_IO_PORT_15_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P151_PFC_1D_MCLK40) },
          { .pin = BSP_IO_PORT_15_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P152_PFC_1D_MDAT40) },
          { .pin = BSP_IO_PORT_15_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P153_PFC_1D_MCLK41) },
          { .pin = BSP_IO_PORT_15_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P154_PFC_1D_MDAT41) },
          { .pin = BSP_IO_PORT_15_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P155_PFC_1D_MCLK42) },
          { .pin = BSP_IO_PORT_15_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P156_PFC_1D_MDAT42) },
          { .pin = BSP_IO_PORT_15_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P157_PFC_1D_MCLK50) },
          { .pin = BSP_IO_PORT_16_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P160_PFC_1D_MDAT50) },
          { .pin = BSP_IO_PORT_16_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P161_PFC_1D_MCLK51) },
          { .pin = BSP_IO_PORT_16_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P162_PFC_1D_MDAT51) },
          { .pin = BSP_IO_PORT_16_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P163_PFC_14_RXD5_SCL5_MISO5) },
          { .pin = BSP_IO_PORT_16_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P164_PFC_14_TXD5_SDA5_MOSI5) },
          { .pin = BSP_IO_PORT_17_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_PULLDOWN_ENABLE | (uint32_t) IOPORT_CFG_REGION_NSAFETY
                  | (uint32_t) IOPORT_PIN_P176_PFC_0C_GTETRGD) },
          { .pin = BSP_IO_PORT_18_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW | (uint32_t) IOPORT_CFG_REGION_NSAFETY) },
          { .pin = BSP_IO_PORT_18_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW | (uint32_t) IOPORT_CFG_REGION_NSAFETY) },
          { .pin = BSP_IO_PORT_19_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P190_PFC_09_GTIOC07_0A) },
          { .pin = BSP_IO_PORT_19_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P191_PFC_09_GTIOC07_0B) },
          { .pin = BSP_IO_PORT_19_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P192_PFC_09_GTIOC07_1A) },
          { .pin = BSP_IO_PORT_19_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P193_PFC_09_GTIOC07_1B) },
          { .pin = BSP_IO_PORT_19_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P194_PFC_09_GTIOC07_2A) },
          { .pin = BSP_IO_PORT_19_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P195_PFC_09_GTIOC07_2B) },
          { .pin = BSP_IO_PORT_19_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P196_PFC_1D_MCLK52) },
          { .pin = BSP_IO_PORT_19_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P197_PFC_1D_MDAT52) },
          { .pin = BSP_IO_PORT_22_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH | (uint32_t) IOPORT_CFG_REGION_NSAFETY) },
          { .pin = BSP_IO_PORT_22_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P227_PFC_09_GTIOC06_0A) },
          { .pin = BSP_IO_PORT_23_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P230_PFC_09_GTIOC06_0B) },
          { .pin = BSP_IO_PORT_23_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P231_PFC_09_GTIOC06_1A) },
          { .pin = BSP_IO_PORT_23_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P232_PFC_09_GTIOC06_1B) },
          { .pin = BSP_IO_PORT_23_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P233_PFC_09_GTIOC06_2A) },
          { .pin = BSP_IO_PORT_23_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P234_PFC_09_GTIOC06_2B) },
          { .pin = BSP_IO_PORT_23_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P235_PFC_1D_MCLK60) },
          { .pin = BSP_IO_PORT_23_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P236_PFC_1D_MDAT60) },
          { .pin = BSP_IO_PORT_23_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P237_PFC_1D_MCLK61) },
          { .pin = BSP_IO_PORT_24_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P240_PFC_1D_MDAT61) },
          { .pin = BSP_IO_PORT_24_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P241_PFC_1D_MCLK62) },
          { .pin = BSP_IO_PORT_24_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P242_PFC_1D_MDAT62) },
          { .pin = BSP_IO_PORT_24_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P243_PFC_1D_MCLK70) },
          { .pin = BSP_IO_PORT_24_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P244_PFC_1D_MDAT70) },
          { .pin = BSP_IO_PORT_27_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P274_PFC_14_RXD0_SCL0_MISO0) },
          { .pin = BSP_IO_PORT_27_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P275_PFC_14_TXD0_SDA0_MOSI0) },
          { .pin = BSP_IO_PORT_27_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P277_PFC_09_GTIOC08_0A) },
          { .pin = BSP_IO_PORT_28_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P280_PFC_09_GTIOC08_0B) },
          { .pin = BSP_IO_PORT_28_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P281_PFC_09_GTIOC08_1A) },
          { .pin = BSP_IO_PORT_28_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P282_PFC_09_GTIOC08_1B) },
          { .pin = BSP_IO_PORT_28_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P283_PFC_09_GTIOC08_2A) },
          { .pin = BSP_IO_PORT_28_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P284_PFC_09_GTIOC08_2B) },
          { .pin = BSP_IO_PORT_28_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P286_PFC_15_DEE08) },
          { .pin = BSP_IO_PORT_28_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P287_PFC_15_TXDE08) },
          { .pin = BSP_IO_PORT_29_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P290_PFC_15_RXDE08) },
          { .pin = BSP_IO_PORT_31_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P312_PFC_1D_MCLK80) },
          { .pin = BSP_IO_PORT_31_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P313_PFC_1D_MDAT80) },
          { .pin = BSP_IO_PORT_31_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P314_PFC_1D_MCLK81) },
          { .pin = BSP_IO_PORT_31_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P315_PFC_1D_MDAT81) },
          { .pin = BSP_IO_PORT_31_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P317_PFC_16_DEE01) },
          { .pin = BSP_IO_PORT_32_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P320_PFC_16_TXDE01) },
          { .pin = BSP_IO_PORT_32_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P321_PFC_16_RXDE01) },
          { .pin = BSP_IO_PORT_32_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT
                  | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH | (uint32_t) IOPORT_CFG_REGION_NSAFETY) },
          { .pin = BSP_IO_PORT_32_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P324_PFC_0A_GTIOC01_1A) },
          { .pin = BSP_IO_PORT_32_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P325_PFC_0A_GTIOC01_1B) },
          { .pin = BSP_IO_PORT_32_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P326_PFC_0A_GTIOC01_2A) },
          { .pin = BSP_IO_PORT_32_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P327_PFC_0A_GTIOC01_2B) },
          { .pin = BSP_IO_PORT_33_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P330_PFC_1D_MCLK82) },
          { .pin = BSP_IO_PORT_33_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P331_PFC_1D_MDAT82) },
          { .pin = BSP_IO_PORT_33_PIN_7, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P337_PFC_15_DEE06) },
          { .pin = BSP_IO_PORT_34_PIN_0, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P340_PFC_15_TXDE06) },
          { .pin = BSP_IO_PORT_34_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P341_PFC_15_RXDE06) },
          { .pin = BSP_IO_PORT_34_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P343_PFC_15_DEE07) },
          { .pin = BSP_IO_PORT_34_PIN_4, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P344_PFC_15_TXDE07) },
          { .pin = BSP_IO_PORT_34_PIN_5, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_HIGH | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_CFG_SLEW_RATE_FAST
                  | (uint32_t) IOPORT_PIN_P345_PFC_15_RXDE07) },
          { .pin = BSP_IO_PORT_35_PIN_1, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P351_PFC_1D_MCLK90) },
          { .pin = BSP_IO_PORT_35_PIN_2, .pin_cfg = ((uint32_t) IOPORT_CFG_DRIVE_MID | (uint32_t) IOPORT_CFG_PORT_PERI
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY | (uint32_t) IOPORT_PIN_P352_PFC_1D_MDAT90) },
          { .pin = BSP_IO_PORT_35_PIN_3, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY) },
          { .pin = BSP_IO_PORT_35_PIN_6, .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT
                  | (uint32_t) IOPORT_CFG_REGION_NSAFETY) }, };

const ioport_cfg_t g_bsp_pin_cfg =
{ .number_of_pins = sizeof(g_bsp_pin_cfg_data) / sizeof(ioport_pin_cfg_t),
  .p_pin_cfg_data = &g_bsp_pin_cfg_data[0],
  .p_extend = &g_ioport_cfg_extend, };
