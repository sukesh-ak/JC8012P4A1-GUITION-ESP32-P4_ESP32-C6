/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

 #pragma once

 #ifdef __cplusplus
 extern "C" {
 #endif
 
 #include <stdint.h>
 #include "sdkconfig.h"
 #include "ov02c10_regs.h"
 #include "ov02c10_types.h"
 
 #define BIT(nr)                                    (1UL << (nr))
 #define OV02C10_IDI_CLOCK_RATE_800x800_50FPS        (100000000ULL)
 #define OV02C10_MIPI_CSI_LINE_RATE_800x800_50FPS    (OV02C10_IDI_CLOCK_RATE_800x800_50FPS * 4)
 #define OV02C10_IDI_CLOCK_RATE_800x640_50FPS        (100000000ULL)
 #define OV02C10_MIPI_CSI_LINE_RATE_800x640_50FPS    (OV02C10_IDI_CLOCK_RATE_800x640_50FPS * 4)
 #define OV02C10_IDI_CLOCK_RATE_800x1280_50FPS       (100000000ULL)
 #define OV02C10_MIPI_CSI_LINE_RATE_800x1280_50FPS   (OV02C10_IDI_CLOCK_RATE_800x1280_50FPS * 4)
 #define OV02C10_IDI_CLOCK_RATE_1920x1080_30FPS      (81666700ULL)
 #define OV02C10_MIPI_CSI_LINE_RATE_1920x1080_30FPS  (OV02C10_IDI_CLOCK_RATE_1920x1080_30FPS * 5)
 #define OV02C10_IDI_CLOCK_RATE_1280x960_45FPS        (88333333ULL)
 #define OV02C10_MIPI_CSI_LINE_RATE_1280x960_45FPS    (OV02C10_IDI_CLOCK_RATE_1280x960_45FPS * 5)
 #define OV02C10_8BIT_MODE                           (0x18)
 #define OV02C10_10BIT_MODE                          (0x1A)
 #define OV02C10_MIPI_CTRL00_CLOCK_LANE_GATE         BIT(5)
 #define OV02C10_MIPI_CTRL00_LINE_SYNC_ENABLE        BIT(4)
 #define OV02C10_MIPI_CTRL00_BUS_IDLE                BIT(2)
 #define OV02C10_MIPI_CTRL00_CLOCK_LANE_DISABLE      BIT(0)
 
 static const ov02c10_reginfo_t ov02c10_mipi_reset_regs[] = {
     {0x0100, 0x00}, // enable sleep
     {0x0103, 0x01},
     {OV02C10_REG_DELAY, 0x0a},
     {0x4800, BIT(0)},// Ensure streaming off to make `clock lane` go into LP-11 state.
     {OV02C10_REG_END, 0x00},
 };
 
 static const ov02c10_reginfo_t ov02c10_input_24M_MIPI_1lane_raw10_1288x728_30fps[] = {
     {0x0301, 0x08},
     {0x0303, 0x06},
     {0x0304, 0x01},
     {0x0305, 0x77},
     {0x0313, 0x40},
     {0x031c, 0x4f},
     {0x3016, 0x12},
     {0x301b, 0xf0},
     {0x3020, 0x97},
     {0x3021, 0x23},
     {0x3022, 0x01},
     {0x3026, 0xb4},
     {0x3027, 0xf1},
     {0x303b, 0x00},
     {0x303c, 0x4f},
     {0x303d, 0xe6},
     {0x303e, 0x00},
     {0x303f, 0x03},
     {0x3501, 0x04},
     {0x3502, 0x6c},
     {0x3504, 0x0c},
     {0x3507, 0x00},
     {0x3508, 0x08},
     {0x3509, 0x00},
     {0x350a, 0x01},
     {0x350b, 0x00},
     {0x350c, 0x41},
     {0x3600, 0x84},
     {0x3603, 0x08},
     {0x3610, 0x57},
     {0x3611, 0x1b},
     {0x3613, 0x78},
     {0x3623, 0x00},
     {0x3632, 0xa0},
     {0x3642, 0xe8},
     {0x364c, 0x70},
     {0x365d, 0x00},
     {0x365f, 0x0f},
     {0x3708, 0x30},
     {0x3714, 0x24},
     {0x3725, 0x02},
     {0x3737, 0x08},
     {0x3739, 0x28},
     {0x3749, 0x32},
     {0x374a, 0x32},
     {0x374b, 0x32},
     {0x374c, 0x32},
     {0x374d, 0x81},
     {0x374e, 0x81},
     {0x374f, 0x81},
     {0x3752, 0x36},
     {0x3753, 0x36},
     {0x3754, 0x36},
     {0x3761, 0x00},
     {0x376c, 0x81},
     {0x3774, 0x18},
     {0x3776, 0x08},
     {0x377c, 0x81},
     {0x377d, 0x81},
     {0x377e, 0x81},
     {0x37a0, 0x44},
     {0x37a6, 0x44},
     {0x37aa, 0x0d},
     {0x37ae, 0x00},
     {0x37cb, 0x03},
     {0x37cc, 0x01},
     {0x37d8, 0x02},
     {0x37d9, 0x10},
     {0x37e1, 0x10},
     {0x37e2, 0x18},
     {0x37e3, 0x08},
     {0x37e4, 0x08},
     {0x37e5, 0x02},
     {0x37e6, 0x08},
     {0x3800, 0x01},
     {0x3801, 0x40},
     {0x3802, 0x00},
     {0x3803, 0xb4},
     {0x3804, 0x06},
     {0x3805, 0x4f},
     {0x3806, 0x03},
     {0x3807, 0x8F},
     {0x3808, 0x05},
     {0x3809, 0x08},
     {0x380a, 0x02},
     {0x380b, 0xd8},
     {0x380c, 0x08},
     {0x380d, 0xe8},
     {0x380e, 0x04},
     {0x380f, 0x8c},
     {0x3810, 0x00},
     {0x3811, 0x07},
     {0x3812, 0x00},
     {0x3813, 0x04},
     {0x3814, 0x01},
     {0x3815, 0x01},
     {0x3816, 0x01},
     {0x3817, 0x01},
     {0x3820, 0xa0},
     {0x3821, 0x00},
     {0x3822, 0x80},
     {0x3823, 0x08},
     {0x3824, 0x00},
     {0x3825, 0x20},
     {0x3826, 0x00},
     {0x3827, 0x08},
     {0x382a, 0x00},
     {0x382b, 0x08},
     {0x382d, 0x00},
     {0x382e, 0x00},
     {0x382f, 0x23},
     {0x3834, 0x00},
     {0x3839, 0x00},
     {0x383a, 0xd1},
     {0x383e, 0x03},
     {0x393d, 0x29},
     {0x393f, 0x6e},
     {0x394b, 0x06},
     {0x394c, 0x06},
     {0x394d, 0x08},
     {0x394e, 0x0a},
     {0x394f, 0x01},
     {0x3950, 0x01},
     {0x3951, 0x01},
     {0x3952, 0x01},
     {0x3953, 0x01},
     {0x3954, 0x01},
     {0x3955, 0x01},
     {0x3956, 0x01},
     {0x3957, 0x0e},
     {0x3958, 0x08},
     {0x3959, 0x08},
     {0x395a, 0x08},
     {0x395b, 0x13},
     {0x395c, 0x09},
     {0x395d, 0x05},
     {0x395e, 0x02},
     {0x395f, 0x00},
     {0x395f, 0x00},
     {0x3960, 0x00},
     {0x3961, 0x00},
     {0x3962, 0x00},
     {0x3963, 0x00},
     {0x3964, 0x00},
     {0x3965, 0x00},
     {0x3966, 0x00},
     {0x3967, 0x00},
     {0x3968, 0x01},
     {0x3969, 0x01},
     {0x396a, 0x01},
     {0x396b, 0x01},
     {0x396c, 0x10},
     {0x396d, 0xf0},
     {0x396e, 0x11},
     {0x396f, 0x00},
     {0x3970, 0x37},
     {0x3971, 0x37},
     {0x3972, 0x37},
     {0x3973, 0x37},
     {0x3974, 0x00},
     {0x3975, 0x3c},
     {0x3976, 0x3c},
     {0x3977, 0x3c},
     {0x3978, 0x3c},
     {0x3c00, 0x0f},
     {0x3c20, 0x01},
     {0x3c21, 0x08},
     {0x3f00, 0x8b},
     {0x3f02, 0x0f},
     {0x4000, 0xc3},
     {0x4001, 0xe0},
     {0x4002, 0x00},
     {0x4003, 0x40},
     {0x4008, 0x04},
     {0x4009, 0x23},
     {0x400a, 0x04},
     {0x400b, 0x01},
     {0x4041, 0x20},
     {0x4077, 0x06},
     {0x4078, 0x00},
     {0x4079, 0x1a},
     {0x407a, 0x7f},
     {0x407b, 0x01},
     {0x4080, 0x03},
     {0x4081, 0x84},
     {0x4308, 0x03},
     {0x4309, 0xff},
     {0x430d, 0x00},
     {0x4500, 0x07},
     {0x4501, 0x00},
     {0x4503, 0x00},
     {0x450a, 0x04},
     {0x450e, 0x00},
     {0x450f, 0x00},
     {0x4800, 0x64},
     {0x4806, 0x00},
     {0x4813, 0x00},
     {0x4815, 0x40},
     {0x4816, 0x12},
     {0x481f, 0x30},
     {0x4837, 0x15},
     {0x4857, 0x05},
     {0x4884, 0x04},
     {0x4900, 0x00},
     {0x4901, 0x00},
     {0x4902, 0x01},
     {0x4d00, 0x03},
     {0x4d01, 0xd8},
     {0x4d02, 0xba},
     {0x4d03, 0xa0},
     {0x4d04, 0xb7},
     {0x4d05, 0x34},
     {0x4d0d, 0x00},
     {0x5000, 0xfd},
     {0x5001, 0x50},
     {0x5006, 0x00},
     {0x5080, 0x40},
     {0x5181, 0x2b},
     {0x5202, 0xa3},
     {0x5206, 0x01},
     {0x5207, 0x00},
     {0x520a, 0x01},
     {0x520b, 0x00},
     {0x4f00, 0x01},
     {OV02C10_REG_END, 0x00},
 };
 
 static const ov02c10_reginfo_t ov02c10_input_24M_MIPI_1lane_raw10_1920x1080_30fps[] = {
     {0x0301, 0x08},
     {0x0303, 0x06},
     {0x0304, 0x01},
     {0x0305, 0x77},
     {0x0313, 0x40},
     {0x031c, 0x4f},
     {0x3016, 0x12},
     {0x301b, 0xf0},
     {0x3020, 0x97},
     {0x3021, 0x23},
     {0x3022, 0x01},
     {0x3026, 0xb4},
     {0x3027, 0xf1},
     {0x303b, 0x00},
     {0x303c, 0x4f},
     {0x303d, 0xe6},
     {0x303e, 0x00},
     {0x303f, 0x03},
     {0x3501, 0x04},
     {0x3502, 0x6c},
     {0x3504, 0x0c},
     {0x3507, 0x00},
     {0x3508, 0x08},
     {0x3509, 0x00},
     {0x350a, 0x01},
     {0x350b, 0x00},
     {0x350c, 0x41},
     {0x3600, 0x84},
     {0x3603, 0x08},
     {0x3610, 0x57},
     {0x3611, 0x1b},
     {0x3613, 0x78},
     {0x3623, 0x00},
     {0x3632, 0xa0},
     {0x3642, 0xe8},
     {0x364c, 0x70},
     {0x365d, 0x00},
     {0x365f, 0x0f},
     {0x3708, 0x30},
     {0x3714, 0x24},
     {0x3725, 0x02},
     {0x3737, 0x08},
     {0x3739, 0x28},
     {0x3749, 0x32},
     {0x374a, 0x32},
     {0x374b, 0x32},
     {0x374c, 0x32},
     {0x374d, 0x81},
     {0x374e, 0x81},
     {0x374f, 0x81},
     {0x3752, 0x36},
     {0x3753, 0x36},
     {0x3754, 0x36},
     {0x3761, 0x00},
     {0x376c, 0x81},
     {0x3774, 0x18},
     {0x3776, 0x08},
     {0x377c, 0x81},
     {0x377d, 0x81},
     {0x377e, 0x81},
     {0x37a0, 0x44},
     {0x37a6, 0x44},
     {0x37aa, 0x0d},
     {0x37ae, 0x00},
     {0x37cb, 0x03},
     {0x37cc, 0x01},
     {0x37d8, 0x02},
     {0x37d9, 0x10},
     {0x37e1, 0x10},
     {0x37e2, 0x18},
     {0x37e3, 0x08},
     {0x37e4, 0x08},
     {0x37e5, 0x02},
     {0x37e6, 0x08},
     {0x3800, 0x00},
     {0x3801, 0x00},
     {0x3802, 0x00},
     {0x3803, 0x04},
     {0x3804, 0x07},
     {0x3805, 0x8f},
     {0x3806, 0x04},
     {0x3807, 0x43},
     {0x3808, 0x07},
     {0x3809, 0x80},
     {0x380a, 0x04},
     {0x380b, 0x38},
     {0x380c, 0x08},
     {0x380d, 0xe8},
     {0x380e, 0x04},
     {0x380f, 0x8c},
     {0x3810, 0x00},
     {0x3811, 0x07},
     {0x3812, 0x00},
     {0x3813, 0x04},
     {0x3814, 0x01},
     {0x3815, 0x01},
     {0x3816, 0x01},
     {0x3817, 0x01},
     {0x3820, 0xa0},
     {0x3821, 0x00},
     {0x3822, 0x80},
     {0x3823, 0x08},
     {0x3824, 0x00},
     {0x3825, 0x20},
     {0x3826, 0x00},
     {0x3827, 0x08},
     {0x382a, 0x00},
     {0x382b, 0x08},
     {0x382d, 0x00},
     {0x382e, 0x00},
     {0x382f, 0x23},
     {0x3834, 0x00},
     {0x3839, 0x00},
     {0x383a, 0xd1},
     {0x383e, 0x03},
     {0x393d, 0x29},
     {0x393f, 0x6e},
     {0x394b, 0x06},
     {0x394c, 0x06},
     {0x394d, 0x08},
     {0x394e, 0x0a},
     {0x394f, 0x01},
     {0x3950, 0x01},
     {0x3951, 0x01},
     {0x3952, 0x01},
     {0x3953, 0x01},
     {0x3954, 0x01},
     {0x3955, 0x01},
     {0x3956, 0x01},
     {0x3957, 0x0e},
     {0x3958, 0x08},
     {0x3959, 0x08},
     {0x395a, 0x08},
     {0x395b, 0x13},
     {0x395c, 0x09},
     {0x395d, 0x05},
     {0x395e, 0x02},
     {0x395f, 0x00},
     {0x395f, 0x00},
     {0x3960, 0x00},
     {0x3961, 0x00},
     {0x3962, 0x00},
     {0x3963, 0x00},
     {0x3964, 0x00},
     {0x3965, 0x00},
     {0x3966, 0x00},
     {0x3967, 0x00},
     {0x3968, 0x01},
     {0x3969, 0x01},
     {0x396a, 0x01},
     {0x396b, 0x01},
     {0x396c, 0x10},
     {0x396d, 0xf0},
     {0x396e, 0x11},
     {0x396f, 0x00},
     {0x3970, 0x37},
     {0x3971, 0x37},
     {0x3972, 0x37},
     {0x3973, 0x37},
     {0x3974, 0x00},
     {0x3975, 0x3c},
     {0x3976, 0x3c},
     {0x3977, 0x3c},
     {0x3978, 0x3c},
     {0x3c00, 0x0f},
     {0x3c20, 0x01},
     {0x3c21, 0x08},
     {0x3f00, 0x8b},
     {0x3f02, 0x0f},
     {0x4000, 0xc3},
     {0x4001, 0xe0},
     {0x4002, 0x00},
     {0x4003, 0x40},
     {0x4008, 0x04},
     {0x4009, 0x23},
     {0x400a, 0x04},
     {0x400b, 0x01},
     {0x4041, 0x20},
     {0x4077, 0x06},
     {0x4078, 0x00},
     {0x4079, 0x1a},
     {0x407a, 0x7f},
     {0x407b, 0x01},
     {0x4080, 0x03},
     {0x4081, 0x84},
     {0x4308, 0x03},
     {0x4309, 0xff},
     {0x430d, 0x00},
     {0x4500, 0x07},
     {0x4501, 0x00},
     {0x4503, 0x00},
     {0x450a, 0x04},
     {0x450e, 0x00},
     {0x450f, 0x00},
     {0x4800, 0x64},
     {0x4806, 0x00},
     {0x4813, 0x00},
     {0x4815, 0x40},
     {0x4816, 0x12},
     {0x481f, 0x30},
     {0x4837, 0x15},
     {0x4857, 0x05},
     {0x4884, 0x04},
     {0x4900, 0x00},
     {0x4901, 0x00},
     {0x4902, 0x01},
     {0x4d00, 0x03},
     {0x4d01, 0xd8},
     {0x4d02, 0xba},
     {0x4d03, 0xa0},
     {0x4d04, 0xb7},
     {0x4d05, 0x34},
     {0x4d0d, 0x00},
     {0x5000, 0xfd},
     {0x5001, 0x50},
     {0x5006, 0x00},
     {0x5080, 0x40},
     {0x5181, 0x2b},
     {0x5202, 0xa3},
     {0x5206, 0x01},
     {0x5207, 0x00},
     {0x520a, 0x01},
     {0x520b, 0x00},
     {0x4f00, 0x01},
     {0x0100, 0x01},
     {OV02C10_REG_END, 0x00},
 };
 
 static const ov02c10_reginfo_t ov02c10_input_24M_MIPI_2lane_raw10_1920x1080_30fps[] = {
     {0X0103, 0X01},
     {0X0301, 0X08},
     {0X0303, 0X06},
     {0X0304, 0X01},
     {0X0305, 0X90},
     {0X0313, 0X40},
     {0X031c, 0X4f},
     {0X3016, 0X32},
     {0X301b, 0Xf0},
     {0X3020, 0X97},
     {0X3021, 0X23},
     {0X3022, 0X01},
     {0X3026, 0Xb4},
     {0X3027, 0Xf1},
     {0X303b, 0X00},
     {0X303c, 0X4f},
     {0X303d, 0Xe6},
     {0X303e, 0X00},
     {0X303f, 0X03},
     {0X3501, 0X04},
     {0X3502, 0X6c},
     {0X3504, 0X0c},
     {0X3507, 0X00},
     {0X3508, 0X08},
     {0X3509, 0X00},
     {0X350a, 0X01},
     {0X350b, 0X00},
     {0X350c, 0X41},
     {0X3600, 0X84},
     {0X3603, 0X08},
     {0X3610, 0X57},
     {0X3611, 0X1b},
     {0X3613, 0X78},
     {0X3623, 0X00},
     {0X3632, 0Xa0},
     {0X3642, 0Xe8},
     {0X364c, 0X70},
     {0X365d, 0X00},
     {0X365f, 0X0f},
     {0X3708, 0X30},
     {0X3714, 0X24},
     {0X3725, 0X02},
     {0X3737, 0X08},
     {0X3739, 0X28},
     {0X3749, 0X32},
     {0X374a, 0X32},
     {0X374b, 0X32},
     {0X374c, 0X32},
     {0X374d, 0X81},
     {0X374e, 0X81},
     {0X374f, 0X81},
     {0X3752, 0X36},
     {0X3753, 0X36},
     {0X3754, 0X36},
     {0X3761, 0X00},
     {0X376c, 0X81},
     {0X3774, 0X18},
     {0X3776, 0X08},
     {0X377c, 0X81},
     {0X377d, 0X81},
     {0X377e, 0X81},
     {0X37a0, 0X44},
     {0X37a6, 0X44},
     {0X37aa, 0X0d},
     {0X37ae, 0X00},
     {0X37cb, 0X03},
     {0X37cc, 0X01},
     {0X37d8, 0X02},
     {0X37d9, 0X10},
     {0X37e1, 0X10},
     {0X37e2, 0X18},
     {0X37e3, 0X08},
     {0X37e4, 0X08},
     {0X37e5, 0X02},
     {0X37e6, 0X08},
     {0X3800, 0X00},
     {0X3801, 0X00},
     {0X3802, 0X00},
     {0X3803, 0X04},
     {0X3804, 0X07},
     {0X3805, 0X8f},
     {0X3806, 0X04},
     {0X3807, 0X43},
     {0X3808, 0X07},
     {0X3809, 0X80},
     {0X380a, 0X04},
     {0X380b, 0X38},
     {0X380c, 0X04},
     {0X380d, 0X74},
     {0X380e, 0X09},
     {0X380f, 0X18},
     {0X3810, 0X00},
     {0X3811, 0X07},
     {0X3812, 0X00},
     {0X3813, 0X04},
     {0X3814, 0X01},
     {0X3815, 0X01},
     {0X3816, 0X01},
     {0X3817, 0X01},
     {0X3820, 0Xa8},
     {0X3821, 0X00},
     {0X3822, 0X80},
     {0X3823, 0X08},
     {0X3824, 0X00},
     {0X3825, 0X20},
     {0X3826, 0X00},
     {0X3827, 0X08},
     {0X382a, 0X00},
     {0X382b, 0X08},
     {0X382d, 0X00},
     {0X382e, 0X00},
     {0X382f, 0X23},
     {0X3834, 0X00},
     {0X3839, 0X00},
     {0X383a, 0Xd1},
     {0X383e, 0X03},
     {0X393d, 0X29},
     {0X393f, 0X6e},
     {0X394b, 0X06},
     {0X394c, 0X06},
     {0X394d, 0X08},
     {0X394e, 0X0a},
     {0X394f, 0X01},
     {0X3950, 0X01},
     {0X3951, 0X01},
     {0X3952, 0X01},
     {0X3953, 0X01},
     {0X3954, 0X01},
     {0X3955, 0X01},
     {0X3956, 0X01},
     {0X3957, 0X0e},
     {0X3958, 0X08},
     {0X3959, 0X08},
     {0X395a, 0X08},
     {0X395b, 0X13},
     {0X395c, 0X09},
     {0X395d, 0X05},
     {0X395e, 0X02},
     {0X395f, 0X00},
     {0X395f, 0X00},
     {0X3960, 0X00},
     {0X3961, 0X00},
     {0X3962, 0X00},
     {0X3963, 0X00},
     {0X3964, 0X00},
     {0X3965, 0X00},
     {0X3966, 0X00},
     {0X3967, 0X00},
     {0X3968, 0X01},
     {0X3969, 0X01},
     {0X396a, 0X01},
     {0X396b, 0X01},
     {0X396c, 0X10},
     {0X396d, 0Xf0},
     {0X396e, 0X11},
     {0X396f, 0X00},
     {0X3970, 0X37},
     {0X3971, 0X37},
     {0X3972, 0X37},
     {0X3973, 0X37},
     {0X3974, 0X00},
     {0X3975, 0X3c},
     {0X3976, 0X3c},
     {0X3977, 0X3c},
     {0X3978, 0X3c},
     {0X3c00, 0X0f},
     {0X3c20, 0X01},
     {0X3c21, 0X08},
     {0X3f00, 0X8b},
     {0X3f02, 0X0f},
     {0X4000, 0Xc3},
     {0X4001, 0Xe0},
     {0X4002, 0X00},
     {0X4003, 0X40},
     {0X4008, 0X04},
     {0X4009, 0X23},
     {0X400a, 0X04},
     {0X400b, 0X01},
     {0X4041, 0X20},
     {0X4077, 0X06},
     {0X4078, 0X00},
     {0X4079, 0X1a},
     {0X407a, 0X7f},
     {0X407b, 0X01},
     {0X4080, 0X03},
     {0X4081, 0X84},
     {0X4308, 0X03},
     {0X4309, 0Xff},
     {0X430d, 0X00},
     {0X4500, 0X07},
     {0X4501, 0X00},
     {0X4503, 0X00},
     {0X450a, 0X04},
     {0X450e, 0X00},
     {0X450f, 0X00},
     {0X4800, 0X64},
     {0X4806, 0X00},
     {0X4813, 0X00},
     {0X4815, 0X40},
     {0X4816, 0X12},
     {0X481f, 0X30},
     {0X4837, 0X14},
     {0X4857, 0X05},
     {0X4884, 0X04},
     {0X4900, 0X00},
     {0X4901, 0X00},
     {0X4902, 0X01},
     {0X4d00, 0X03},
     {0X4d01, 0Xd8},
     {0X4d02, 0Xba},
     {0X4d03, 0Xa0},
     {0X4d04, 0Xb7},
     {0X4d05, 0X34},
     {0X4d0d, 0X00},
     {0X5000, 0Xfd},
     {0X5001, 0X50},
     {0X5006, 0X00},
     {0X5080, 0X40},
     {0X5181, 0X2b},
     {0X5202, 0Xa3},
     {0X5206, 0X01},
     {0X5207, 0X00},
     {0X520a, 0X01},
     {0X520b, 0X00},
     {0X4f00, 0X01},
     {0X0100, 0X01},
     {OV02C10_REG_END, 0x00},
 };
 
 #ifdef __cplusplus
 }
 #endif
 