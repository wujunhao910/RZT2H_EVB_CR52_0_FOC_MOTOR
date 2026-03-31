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
*******************************************************************************/
/*******************************************************************************
* System Name  : RZ/T2H Motor Solution Kit
* File Name    : m_common.h
* Version      : 1.0
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Header file of common.
*******************************************************************************/

#include "bsp_api.h"

void setup_dsm(void);


#define MOTOR_NUM 9
#if !defined(__GNUC__)
#define     M_PI    3.14159265358979323846
#define     M_PI_2  1.57079632679489661923
#define     M_PI_4  0.785398163397448309616
#endif //__GNUC__

#define     MTR_TWOPI       (M_PI*2.0)              // 2*pi
#define     MTR_SQRT_2_3    (0.81649658f)           // sqrt(2/3)
#define     MTR_SQRT_3      (1.73205080f)
#define     MTR_1_SQRT_3    (1.0/1.73205080f)
#define     MTR_1_3         (1.0/3.0)               // 1/3
#define     MTR_2_3         (2.0/3.0)               // 2/3


/* Activity Status Flags */
#define ACT_MotionComplete  0x0001      /* Motion completed */
#define ACT_ServoOn         0x0002      /* Servo Control is ON */
#define ACT_PowerOn         0x0004      /* PWM Amplifier enabled */
#define ACT_PosCaptured     0x0008      /* Position captured on external trigger */

#define ACT_Reserved        0x0010      /*  */
#if 1    // EtherCAT
#define ACT_Homed           0x0020
#else // ethercat
#define ACT_Reserved2       0x0020      /*  */
#endif // ethercat
#define ACT_PVTWatermark    0x0040        /* PVT FIFO Buffer emptied below the watermark */
#define ACT_Aligned         0x0080      /* Phasing completed */

#define ACT_Busy            0x0100      /* Firmware is busy (moving, homing or phasing) */
#define ACT_OverCurrent     0x0200      /* Current overload is registered */
#define ACT_Inhibit         0x0400      /* External Inhibit Input is troggered */
#define ACT_PVTEmpty        0x0800      /* PVT buffer depleted - interpolation starved */

#define ACT_MtOverTemp      0x1000      /* Motor Overheating is detected */
#define ACT_AmpFault        0x2000      /* PWM Amplifier Failure */
#define ACT_PosError        0x4000      /* Position Error Exceeded */
#define ACT_WrapAround      0x8000      /* Position Counter wrwaparound */

/* Absolute Position Encoder status bits */
#define APE_Overspeed       0x0001      /* Motor shaft rotated over the speed limit during power off mode */
#define APE_FullAbsStatus   0x0002      /* Power on while motor shaft spins faster than limit */
#define APE_CountingErr     0x0004      /* Counting error or PS error */
#define APE_Overflow        0x0008      /* Multi-turn counter overflow */
#define APE_MultiTurnErr    0x0020      /* Bit-jump in multi-turn data during power on */
#define APE_BatteryErr      0x0040      /* Voltage below 2.5V at power on*/
#define APE_BatteryAlarm    0x0080      /* Voltage below 3.1V at power on */
#define APE_EEPROMBusy      0x0100      /* EEPROM access ongoing */
#define APE_EEPROMErr       0x0200      /* EEPROM access error */
#define APE_Overtemp        0x0400      /* Temperature above 95deg C */

/* Control Module Types */
#define TYPE_SINGLE_CH        1           /* Single channel motion controller */
#define TYPE_EGEAR            2           /* Dual channel motion controller - locked in e-gearing mode */
#define TYPE_DUAL_CH        3           /* Dual channel motion controller - two independent motors */

/* Phase Init Mode */
#define PIM_FORCED          0
#define PIM_HALLS_BASED     1
#define PIM_DITHERING       2

/* bootstrap_charge Status *//* RZ/T2 add */
#define BS_UNCHARGED        0
#define BS_CHARGEING        1
#define BS_CHARGE_END       2
#define BS_CHARGE_TIME_CNT  (50 * 20)   /* Bootstrap circuit charging time (20ms) */

/* Stopping Modes */
#define SM_NOSTOP           0
#define SM_ABRUPT            1
#define SM_SMOOTH            2

/* Hall Sensors Types */
#define HTYPE_PARALLEL        0
#define HTYPE_SERIAL        1
#define HTYPE_NONE            2

/* Encoder status flags */
#define ESTATE_OVERSPEED    0x0001
#define ESTATE_INIT_ERR        0x0002
#define ESTATE_COUNT_ERR    0x0004
#define ESTATE_MULTI_OVF    0x0008
#define ESTATE_MULTI_ERR    0x0020
#define ESTATE_BATT_ERR        0x0040
#define ESTATE_BATT_ALARM    0x0080
#define ESTATE_EEPROM_BUSY    0x0100
#define ESTATE_EEPROM_ERR    0x0200
#define ESTATE_OVER_TEMP    0x0400

#define ESTATE_PARITY_ERR   0x0800
#define ESTATE_DELIM_ERR    0x1000

/* Velocity Control Parameter Initial Value */
#define INITVAL_VEL_KP        3
#define INITVAL_VEL_KI        1
#define INITVAL_VEL_KD        0
/* RZ/T2 */
/* #define INITVAL_VEL_ILIMIT    0x007fffff */
/* #define INITVAL_VEL_MLIMIT    32500 */
#define INITVAL_VEL_ILIMIT    0x7fffffff
#define INITVAL_VEL_MLIMIT    32767

/* PID regulator Parameter */
#define PID_POS_INPUT_LIMIT 2147483647LL     /* 2^31 -1 */
#define PID_POS_KP_SHIFT    0
#define PID_POS_KI_SHIFT    8
#define PID_POS_KD_SHIFT    0
#define PID_POS_KVFF_SHIFT  8
#define PID_POS_KAFF_SHIFT  8
#define PID_VEL_INPUT_LIMIT 140737488355327LL  /* 2^47 - 1 */
#define PID_VEL_KP_SHIFT    28
#define PID_VEL_KI_SHIFT    32
#define PID_VEL_KD_SHIFT    16

/* Encoder Types */
enum ETYPE {
    ETYPE_INCREMENTAL = 0,
    ETYPE_APE_ENDAT,
    ETYPE_APE_BISS,
    ETYPE_APE_FACODER,
    ETYPE_APE_AFORMAT,
    ETYPE_APE_HIPERFACE_DSL,
};

/* Velocity Profile Generator States */
typedef enum VPG_STATE {
   VPG_MotionCompleted,
   VPG_Acceleration,
   VPG_Deceleration,
   VPG_Plateau,
   VPG_Streaming
} t_vpg_state;

/* Velocity Profile Generator Modes */
enum VPGMode {
   VPGM_Trapezoidal = 0,
   VPGM_Spline,
   VPGM_Bezier,
   VPGM_PosVelTime,
   VPGM_VelContouring  
};

/* Motor Commutation Modes *//* RZ/T2 change */
enum CommutationModes {
    CM_SVM = 0,
    CM_FOC,
    CM_HALLS,
    CM_FORCED,
    CM_ENC_AND_DSM,
    CM_ENC_AND_CT,
    CM_CT
};

/* Home Procedure State Machine */
enum HOMING_STATES {
    HS_IDLE,
    HS_FINDING_LIMIT,
    HS_FINDING_INDEX,
    HS_FINDING_HARDSTOP,
    HS_WAIT_STOP,
    HS_WAIT_STOP2,
    HS_WAIT_STOP3,

    HS_MOVETO_TARGET,
    HS_MOVETO_START,

    HS_WAIT_ALIGN_0,
    HS_WAIT_ALIGN_1
};

enum ParserStates {
    PS_IDLE,
    PS_ADDRESS,
    PS_LENGTH,
    PS_CODE,
    PS_PAYLOAD,
    PS_PROCESS
};

enum ProcotolTypeRequest {
    PTR_NONE,
    PTR_ASCII,
    PTR_PACKET
};

enum PacketCode {
    PC_MODULEID = 0,    /* 0 */
    PC_REPORT,          /* 1 */
    PC_FUNCTION,        /* 2 */
    PC_INIT_PVT,        /* 3 */
    PC_SET_PVT,         /* 4 */
    PC_SET_PAR,         /* 5 */
    PC_GET_PAR,         /* 6 */
    PC_GET_TRACE,       /* 7 */    
    PC_BAUDRATE = 15,   /* 15 */
};

enum PacketError {
    PE_OK = 0,          /* 0 */
    PE_INVALID_CODE,    /* 1 */
    PE_INVALID_PARAM,   /* 2 */
    PE_INVALID_FORMAT,  /* 3 */
    PE_INVALID_VALUE,   /* 4 */
    PE_INVALID_ACCESS,  /* 5 */
    PE_INTERLOCK,       /* 6 */
    PE_AT_FAULT,        /* 7 */
    PE_INVALID_STATE,   /* 8 */
    PE_BUFFER_OVF,      /* 9 */
    PE_EXECUTE,         /* 10 */  
    
    PE_CHECKSUM = 255   /* 255 - Must be the last code */
};

/* RZ/T2 add */
enum CtrlMode {
    CTRM_POSITION = 0,     /* 0 */
    CTRM_VELOCITY,         /* 1 */
    CTRM_TORQUE,           /* 2 */
};
/* RZ/T2 add */
enum RotateDirection {
    RDIR_CW = 0,           /* 0 */
    RDIR_CCW,              /* 1 */
};

/* Buffers size definitions */
#define TX_BUF_SIZE     1024
#define RX_BUF_SIZE     512

#define PP_BUFF_SIZE    100
#define PC_BUFF_SIZE    10
#define VPG_BUFF_SIZE   40
#define TRACE_BUFFER_SIZE 512

#define PVT_BUFF_SIZE   100

#define POS_PAST_DATA     25
#define VEL_AVE_NUM       5

typedef union {
   struct {
      short Low;
      short High;
   } Reg16;
   long     Reg32;
} TReg32;

typedef struct {
   long     position;
   long     position_rel;
   long     velocity;
   long     acceleration;
   long     deceleration;
   long     accel_jerk;
   long     decel_jerk;
   short    dir_sign;
   short    profile_mode;
} TMotionParams;

typedef struct {
   long     position;
   long     velocity;
   long     acceleration;
   long     stop_dist;
   t_vpg_state  vpg_state;
} TMotionProfile;

typedef struct {
   long     position;
   long     velocity;
} TPosVel;

/* Persistent Parameters */
typedef struct {
    long   version;
    /* Configuration Settings */
    short           module_type;
    short           encoder_type;

    short           halls_type;
    short           hall_inverted;
    short           hall_shift;
    
    short           commutation_mode;
    short           auto_stop_mode;         /* 0 = Disable, 1 = Motor Stop on error, 2 = Enable Motor Off On Error */
    unsigned char   simulated_mode;
    unsigned short  pos_capture_mode;
    short           pos_inv_mode;
    short           dflt_vgp_mode;
    unsigned char   brake_mode;
    
    /* Motor configuration */
    short           motor_type;             /* 3 for BLDC, 2 for DC Brush or Voice Coil, 0 for Independent Phase Control */
    short           pole_pairs;             /* Number of pole pairs per rotor revolution */
    short           phase_config;           /* Mapping between the outputs and the motor windings */
    short           pos_scale;              /* Encoder resolution scalling to the power of 2 */
    long            ec_per_rev;
    long            ec_per_ecycle;          /* Number of encoder count per electrical phase */    
 
    /* Velocity Profile Generator Parameters */
    TMotionParams   buffMotion;
    
    /* Home Procedure Control */
    unsigned short  home_inv_mask;
    unsigned short  home_mask;
    long            home_offset;
    long            user_data[8];
    unsigned short  dinputs_err_mask;

    /* Overcurrent protection control */
    short           I2t_current;
    short           I2t_time;
    unsigned long  tc_limit;
    unsigned short  tc_limit_time;

    /* Maximum Position Error Tracking */
    short           pos_error_limit;
    short           pos_error_time;

    /* Position Control Loop Gains */
    short           crnt_ds;
    short           crnt_bias;
    short           buff_kp, buff_ki, buff_kd;
    short           buff_kvff, buff_kaff, buff_bp;
    short           buff_err_limit;
    short           integral_limit16;
    long            pos_loop_limit;

    /* Velocity Control Loop Gains */
    short           buff_kp_vel, buff_ki_vel, buff_kd_vel;

    /* Field Oriented Control Gains */
    short           foc_kp, foc_ki;
    short           foc_kd;
    long           foc_iq_err, foc_id_err;

    /* Phasing Parameters */
    short           phasing_mode;
    short           phasing_power;
    short           phasing_time;
    short           phase_adv_gain;
    short           phase_vel_comp;
    
    long            enc_timeout;
    long            enc_baudrate;
    
    short           gear_in;
    short           gear_out;
    short           module_addr;
    short           group_addr;
    
    short           pvt_period;
    short           pvt_watermark;
} t_motor_pars;

typedef struct motor {

    unsigned short  motor_idx;

    /* Configuration Settings */
    short           module_type;
    short           module_addr;
    short           group_addr;
    short           encoder_type;
    short           halls_type;
    
    short           commutation_mode;
    short           auto_stop_mode;         /* 0 = Disable, 1 = Motor Stop on error, 2 = Enable Motor Off On Error */
    unsigned char   simulated_mode;
    unsigned short  pos_capture_mode;
    short           pos_inv_mode;
    short           dflt_vgp_mode;
    unsigned char   brake_mode;
    
    short           gear_in;
    short           gear_out;
    double          gear_ratio;
    
    /* Motor configuration */
    short           motor_type;             /* 3 for BLDC, 2 for DC Brush or Voice Coil, 0 for Independent Phase Control */
    short           pole_pairs;             /* Number of pole pairs per rotor revolution */
    short           phase_config;           /* Mapping between the outputs and the motor windings */
    short           pos_scale;              /* Encoder resolution scalling to the power of 2 */
    
    /* Current Status Variables */
    short           servo_on;               /* 0 = Open position Loop, 1 = Closed position Loop */
    short           act_state;
    short           act_state_1;
    volatile short           aligning;
    unsigned short  dinputs, dinputs_1, dinputs_2, dinchng;
    unsigned short  dinputs_err_mask;
 
    /* Velocity Profile Generator FIFO Buffer */
    TMotionProfile  profileFIFO[VPG_BUFF_SIZE];
    TMotionProfile  *prfl_push;  
    TMotionProfile  *prfl_push_1;
    TMotionProfile  *prfl_pull;  
    volatile short  prfl_points;

    /* PVT Streaming Support*/
    volatile short  pvt_points;             /* Number of PVT Points in the buffer */
    TPosVel         pvt_pointsFIFO[PVT_BUFF_SIZE];
    TPosVel         *pvt_push;
    TPosVel         *pvt_end_point;
    TPosVel         *pvt_start_point;
    TPosVel         pvt_start;
    double          f_vel0;
    double          f_vel1;
    double          f_time;
    long            frac_vel;
    short           pvt_pos_added;          /* Flag for pairing Position and Velocity added */
    short           pvt_step;               /* Interpolation step (0 to pvt_period - 1) */
    
    unsigned short  pvt_period;             /* Number of Position Loop cycles (crnt_ds) */
    unsigned short  pvt_watermark;          /* FIFO Buffer level - sets flag if level pvt_points goes below */
    
    /* Velocity Profile Generator Parameters */
    TMotionParams   buffMotion;
    TMotionParams   trgtMotion;
    
    long            cmd_pos;
    long long       cmd_pos64;
    long            cmd_vel;
    long            cmd_acc;
    long            delta_pos;
    short           direction;

    t_vpg_state     vpg_state;
    short           vpg_overrun;

    short           stop_request;           /* 0 = No Stop Req, 1 = Abrupt, 2 = Smooth Stop */

    /* Spline based velocity profile generator variables */
    long            start_pos_accel;        /* The position at which the acceleration phase begins */
    long            start_pos_decel;        /* The position at which the deceleration phase begins */
    short           decel_started;          /* Indicates if the deceleration parameters were set */
    double          _fA0, _fA1, _fA2, _fA3; /* Acceleration spline coefficients */
    double          _fD1, _fD2;
    double          _fD3, _fD4, _fD5;       /* Deceleration spline coefficients */
    double          max_vel_calc;           /* Maximum velocity calculated based on the motion parameters */
    double          max_acc_calc;           /* Maximum acceleration calculated based on the motion parameters */
    double          max_dec_calc;           /* Maximum deceleration calculated based on the motion parameters */
    double          pos_calc;
    
    long            time_accel;
    long            time_decel;
    long            time_plateau;
    long            time_current;
    long            time_total;
    long            dist_accel;
    long            dist_platoe;
    long            dist_decel;
    
    /* Encoder Position Feedback */
    volatile long   crnt_pos;
    long            crnt_pos_1;
    long            crnt_vel;
    long            crnt_acc;               /* Motor acceleration *//* RZ/T2 add */
    long long       crnt_vel64;
    volatile TReg32 real_pos;
    volatile TReg32 captured_pos;
    volatile long   index_pos;
    long            pos_offset;
    long long       crnt_pos64;
    short           real_rot;               /* rotate */
    long            real_res;               /* resolution */

    /* Home Procedure Control */
    short           fsm_home;       /* Finite state machine for the homing procedure */
    unsigned short  home_inv_mask;
    unsigned short  home_mask;
    long            home_idx_pos;
    short           home_switch;
    long            home_offset;
    long            user_data[8];

    /* Dithering Phasing Control */
    long            dither_last_pos;
    short           dither_last_vel;
    short           dither_cycles;
    short           dither_timer;
    long            dither_delta;
    long            dither_acc;
    long            dither_vel;

    /* I squared t protection control */
    short           I2t_current;    /* Peak current derived from the motor thermal characteristics */
    short           I2t_time;       /* Time at peak current the motor is rated at */
    long            I2t_integral;   /* Calculated runtime as integral of (total_current^2 - climit^2) */
    long            I2t_limit;        /* Calculated as I2t_current * I2t_time */
    long            I2t_nominal;     /* Calculated runtime as tc_limit^2 */
    unsigned long  total_current;  /* Calculated runtime as abs (Iu) + abs(Iv) */

    unsigned long  tc_limit;
    unsigned short  tc_limit_time;
    unsigned short  tc_limit_timer;

    /* Maximum Position Error Tracking */
    short           pos_error;
    long            pos_error2;
    short           pos_error_limit;
    short           pos_error_time;
    short           pos_error_timer;

    /* Maximum Position Error Fault Conditions */
    long            mecmd_pos;
    long            mecmd_vel;
    short           mecmd_output;
    long            mecrnt_pos;
    unsigned short  mecrnt_output;
    
    /* Position Control Loop Gains */
    short           crnt_kp, crnt_ki, crnt_kd;
    short           crnt_kvff, crnt_kaff, crnt_bp;
    short           crnt_ds;                /* Multiples of 50us */
    short           crnt_bias;

    short           buff_kp, buff_ki, buff_kd;
    short           buff_kvff, buff_kaff, buff_bp;
    short           buff_err_limit;

    short           integral_limit16;
    long            integral_limit;

    short           pos_loop_cmd;
    long            pos_loop_limit;

    short           derivative_err;
    long            integral_err;
    long            derivative_err2;
    long long       integral_err2;
    short           pos_loop_time;      /* Desired position loop cycle time [us] */
    short           pos_loop_timer;
    short           pos_read_timer;

    /* Velocity Control Loop Gains */
    long            in_vel;
    long long       in_vel64;
    long            vel_error;
    long            integral_err_vel;
    long            derivative_err_vel;
    long long       vel_error2;
    long long       integral_err2_vel;
    long long       derivative_err2_vel;
    short           crnt_kp_vel, crnt_ki_vel, crnt_kd_vel;
    short           buff_kp_vel, buff_ki_vel, buff_kd_vel;

    long            integral_limit_vel;
    long            PiOut_limit_vel;

    long long       array_raw_pos[POS_PAST_DATA];
    long long       array_vel[POS_PAST_DATA];
    unsigned char   total_num_pos;
    unsigned char   total_num_vel;

    /* Output variables */
    short           output_q;           /* Position Loop Output - Current/Torque Setpoint */
    short           output_d;           
    float           out_u;              /* Phase voltages */
    float           out_v;
    float           out_w;
    
    /* Field Oriented Control Gains */
    short           foc_kp, foc_ki;
    short           foc_kd;
    long           foc_id_err_old;
    long           foc_iq_err_old;
    long            foc_iq_err_int, foc_id_err_int;
    long           foc_iq_err, foc_id_err;

    long           foc_id, foc_iq;       /* Measured D and Q currents */
    short           foc_vd, foc_vq;       /* Calculated D and Q voltages */    
    float           foc_alpha, foc_beta;
    float           calc_alpha, calc_beta;

    /* control mode *//* RZ/T2 add */
    unsigned short  ctrl_mode;      /* ctrl mode (0:position 1:velocity 2:torque) */
    unsigned short  cmd_dir;        /* command direction (0:CW 1:CCW) */
    short           cmd_vel_rpm;    /* command velocity[rpm] */
    long long       cmd_vel64;      /* command velocity[(count/pos_loop_cycle) / 2^32] */
    short           cmd_trq;        /* command torque[mNm] */
    short           est_trq;        /* estimate torque[mNm] */
    float           mtr_ke;         /* back EMF constant[(Vpeak/(rad/s)] */
    long long       in_vel64_old;   /* Previous value for 64-bit target velocity */
    short           output_d_old;   /* Previous value for target d-axis current */
    short           output_q_old;   /* Previous value for target q-axis current */

    /* Raw ADC readings / Current Feedback */
    short           adc1_raw, adc2_raw, adc3_raw;
    short           adc1_offs, adc2_offs, adc3_offs;
    long           adc_iu, adc_iv, adc_iw;
    long           *p_iu, *p_iv;
    
    /* Hall Sensors Feedback */
    unsigned short  hall_state;
    unsigned short  hall_state_1;
    long            hall_change_pos;
    short           hall_inverted;
    short           hall_shift;

    /* Phasing Parameters */
    long            phase_origin;
    short           phasing_mode;
    short           phasing_mode_crnt;
    short           phasing_power;
    short           phasing_time;
    volatile long   phasing_timer;
    short           phase_adv_gain;
    short           phase_vel_comp;
    
    /* Motor Commutation Parameters */
    short           phase_angle;             /* Flux Vector angle */
    short           phase_offset;            /* Flux Vector offset from Index pulse to Max of Phase A */
    short           phase_vector;        
    short           phase_corr;             /* Phase angle correction for factional encoder counts per electrocal cycle */
    short           phase_corr_cntr;    
    unsigned short  PhaseU, PhaseV, PhaseW; /* Phase PWM Output */

    short           pwm_period;
    short           pwm_period_half;

    long            ec_per_rev;
    long            ec_per_ecycle;          /* Number of encoder count per electrical phase */
    
    double          counts2rad;             /* Converts angle from counts to radian */
    float           angle_rad;
    float           angle_sin;
    float           angle_cos;
    
    /* bootstrap_charging Parameters *//* RZ/T2 add */
    long            charge_cycle;
    volatile unsigned short  charge_state;

    /* Hardware registers ----------------------------------------------------*/
    unsigned short  *regPosCounter;
    unsigned short  *regPosCapture;
    unsigned char   *regTimerStatus;
    
    volatile unsigned int *mapPhaseU;
    volatile unsigned int *mapPhaseV;
    volatile unsigned int *mapPhaseW;

    volatile unsigned int *regPhaseU;
    volatile unsigned int *regPhaseV;
    volatile unsigned int *regPhaseW;
    volatile unsigned int *regPWMPeriod;
    
    unsigned short  *regADC1;
    unsigned short  *regADC2;
    
    long            flash_pars_offs;
    t_motor_pars    pars;
    
    /* Absolute encoder parameters and status */
    long            eeprom_addr;
    long            enc_timeout;
    long            enc_baudrate;
    unsigned short  enc_status;
    short           enc_open;
    
    struct motor * slave;
    unsigned long   ErrSts;
    unsigned long   ErrMsk;
              long  Lvolt_Val;
              long  Hvolt_Val;
              long  Ovc_Val;
              long  Ovs_Val;
              long  WOvs_Val;
              long  WOvs_time;
              long  WPosMax_Val;
              long  WPosMin_Val;
              long  crnt_volt;
              long  WEmp_Val;
              long  WInvOverTemp_Val;
              long  crnt_temp;
              int32_t real_res_prev;
              uint8_t df8[3];
} t_motor;

typedef struct 
{
    short   Mode;      // 0 - stopped, 1 - continuous, 2 - until full
    short   Trigger;
    short   RateMult;
    short   Count;     // Number of samples stored
    float   Level;
    short   buff_size;
} t_trace;

typedef struct 
{
    unsigned char tx_buf[TX_BUF_SIZE];
    unsigned char rx_buf[RX_BUF_SIZE];
    unsigned char volatile *ptx, *prx;
    unsigned short volatile rx_count, tx_count;
    unsigned short volatile cmd_req;
    R_SCI0_Type volatile *pSCI0;
    long arg;
    unsigned char err;
    unsigned char set;
    unsigned char channel;
    
    unsigned char pkt_addr;
    unsigned char pkt_length;
    unsigned char pkt_code;
    unsigned char pkt_chksum;
    unsigned char pkt_state;
    unsigned short data_type;
} t_console;


void m_heartbeat(void);
void m_recorder(void);
void m_rec_begin(void);
void m_foreground(void);
void m_background(void);
void m_startup(void);
void m_interpreter(t_console *pc);

void print_buff(t_console *pc);
void setup_encoder(t_motor *pm, short enc_type);
void close_encoder(t_motor *pm, short enc_type);
void set_position(t_motor *pm, long pos);
short capture_position(t_motor *pm);
/* RZ/T2 add */
void pwm_enable(t_motor *pm);
void pwm_disable(t_motor *pm);

void fsm_homing(t_motor *pm); 
void interlocks(t_motor *pm); 
void vpg_update(t_motor *pm); 
void setup_motor(t_motor *pm, unsigned int is_reset_cmd);
void servo_off(t_motor *pm);
void update_ctrl(t_motor *pm);
void update_pwm(t_motor *pm);
void update_pwm2(t_motor *pm);
void map_phases(t_motor *pm);
void set_cmt_params(t_motor *pm);

void commutate_hall(t_motor *pm);
void commutate_set(t_motor *pm);
void commutate_svm(t_motor *pm, float alpha, float beta);
void commutate_foc(t_motor *pm);

void forced_phasing(t_motor *pm);
void hall_phasing(t_motor *pm);
void dither_phasing(t_motor *pm);

void print_dec (t_console *pc, long value);
void print_hex (t_console *pc, short Value); 
/* RZ/T2 add */
void print_dec2 (t_console *pc, long long value);

long pid_calc(t_motor *pm, long posErr);
long pi_calc_vel(t_motor *pm, long bias);
long long pid_calc_pos64(t_motor *pm, long long posErr);
short pid_calc_vel64(t_motor *pm, long long velErr);

void pos_read(t_motor *pm);
void crnt_read(t_motor *pm);
short set_baud_rate(R_SCI0_Type volatile *p_sci, short code);
              
t_vpg_state vpg_trap_start (t_motor *pm, short jogging);
void  vpg_trap_next (t_motor *pm, TMotionProfile *crntPars, TMotionProfile *cmdPars, short jogging);

void m_Position(t_console *pc, t_motor *pm);
void m_Inputs(t_console *pc, t_motor *pm);
void m_Index(t_console *pc, t_motor *pm);
void m_Go(t_console *pc, t_motor *pm);
void m_Forward(t_console *pc, t_motor *pm);
void m_Reverse(t_console *pc, t_motor *pm);
void m_Abs(t_console *pc, t_motor *pm);
void m_Rel(t_console *pc, t_motor *pm);
void m_Setup(t_console *pc, t_motor *pm);
void m_Reset(t_console *pc, t_motor *pm);
void m_ServoOn(t_console *pc, t_motor *pm);
void m_ServoOff(t_console *pc, t_motor *pm);
void m_PowerOn(t_console *pc, t_motor *pm);
void m_PowerOff(t_console *pc, t_motor *pm);
void m_SmoothStop(t_console *pc, t_motor *pm);
void m_AbruptStop(t_console *pc, t_motor *pm);
void m_StartHoming(t_console *pc, t_motor *pm);
void m_AlignPhase(t_console *pc, t_motor *pm);
void m_Version(t_console *pc, t_motor *pm);
void m_Output1(t_console *pc, t_motor *pm);
void m_Output2(t_console *pc, t_motor *pm);
void m_PosLoopCmd(t_console *pc, t_motor *pm);
void m_OutputIQ(t_console *pc, t_motor *pm);
void m_OutputID(t_console *pc, t_motor *pm);
void m_CurrentLimit(t_console *pc, t_motor *pm);
void m_EncoderType(t_console *pc, t_motor *pm);
void m_PLimit(t_console *pc, t_motor *pm);
void m_PLimitTime(t_console *pc, t_motor *pm);
void m_PosInvert(t_console *pc, t_motor *pm);
void m_Save(t_console *pc, t_motor *pm);
void m_Restore(t_console *pc, t_motor *pm);
void m_LogChannel0(t_console *pc, t_motor *pm);
void m_LogChannel1(t_console *pc, t_motor *pm);
void m_LogChannel2(t_console *pc, t_motor *pm);
void m_LogChannel3(t_console *pc, t_motor *pm);
void m_Trace(t_console *pc, t_motor *pm);
void m_Play(t_console *pc, t_motor *pm);
void m_TraceSetup(void);

void m_EncReadID(t_console *pc, t_motor *pm);
void m_EncAddrEEPROM(t_console *pc, t_motor *pm);
void m_EncDataEEPROM(t_console *pc, t_motor *pm);
void m_EncBaudrate(t_console *pc, t_motor *pm);
void m_EncStatus(t_console *pc, t_motor *pm);

void m_GearIn(t_console *pc, t_motor *pm);
void m_GearOut(t_console *pc, t_motor *pm);

void m_AddPos(t_console *pc, t_motor *pm);
void m_AddVel(t_console *pc, t_motor *pm);

long endat_pos(t_motor *pm);
long endat_enc_id(t_motor *pm);
long endat_eeprom_read(t_motor *pm, long *read_data);
long endat_eeprom_write(t_motor *pm, long write_data);

long bissc_get_pos(t_motor *pm);
long bissc_enc_id(t_motor *pm);
long bissc_eeprom_read(t_motor *pm, long *read_data);
long bissc_eeprom_write(t_motor *pm, long write_data);

long a_as_pos(t_motor *pm);
long a_as_enc_id(t_motor *pm);
long a_as_eeprom_read(t_motor *pm, long *read_data);
long a_as_eeprom_write(t_motor *pm, long write_data);

long fac_pos(t_motor *pm);
long fac_pos1(t_motor *pm);
long fac_enc_id(t_motor *pm);
long fac_eeprom_read(t_motor *pm, long *read_data);
long fac_eeprom_write(t_motor *pm, long write_data);

extern long hfdsl_pos(t_motor *pm);
extern long hfdsl_enc_id(t_motor *pm);
extern long hfdsl_eeprom_read(t_motor *pm, long *read_data);
extern long hfdsl_eeprom_write(t_motor *pm, long write_data);

#define ERRBIT_31 0x80000000
#define ERRBIT_30 0x40000000
#define ERRBIT_29 0x20000000
#define ERRBIT_28 0x10000000
#define ERRBIT_27 0x08000000
#define ERRBIT_26 0x04000000
#define ERRBIT_25 0x02000000
#define ERRBIT_24 0x01000000
#define ERRBIT_23 0x00800000
#define ERRBIT_22 0x00400000
#define ERRBIT_21 0x00200000
#define ERRBIT_20 0x00100000
#define ERRBIT_19 0x00080000
#define ERRBIT_18 0x00040000
#define ERRBIT_17 0x00020000
#define ERRBIT_16 0x00010000
#define ERRBIT_15 0x00008000
#define ERRBIT_14 0x00004000
#define ERRBIT_13 0x00002000
#define ERRBIT_12 0x00001000
#define ERRBIT_11 0x00000800
#define ERRBIT_10 0x00000400
#define ERRBIT_09 0x00000200
#define ERRBIT_08 0x00000100
#define ERRBIT_07 0x00000080
#define ERRBIT_06 0x00000040
#define ERRBIT_05 0x00000020
#define ERRBIT_04 0x00000010
#define ERRBIT_03 0x00000008
#define ERRBIT_02 0x00000004
#define ERRBIT_01 0x00000002
#define ERRBIT_00 0x00000001


//#define ERROR_MASK_DFLT    0x1E3A0000
#define ERROR_MASK_DFLT    0x163A0000 //no voltage
#define LVOLT_VAL_DFLT    18 // [V]
#define HVOLT_VAL_DFLT    26 // [V]
#define OVC_VAL_DFLT    2 * 10600 // [mA]
#define OVS_VAL_DFLT    6000 // [rpm]
#define WOVS_VAL_DFLT    1000 // [rpm]
#define WOVS_TIME        5000 // [value * 100us]
#define WPOSMAX_VAL_DFLT    2147483647 // [ec]
#define WPOSMIN_VAL_DFLT    -2147483648 // [ec]
#define TC_LIMIT_VAL_DFLT 3500 // [mA]
#define TC_LIMIT_TIME_VAL_DFLT 5000 // [ms]
#define POS_ERROR_LIMIT_VAL_DFLT 5000 // [ec]
#define POS_ERROR_LIMIT_TIME_VAL_DFLT 500 // [ms]

#define WINVOVERTEMP_VAL_DFLT    2000
#define EMP_VAL_DFLT    30

unsigned char ChkPOE(void);
void print_hex2 (t_console *pc, long Value);
void    m_Ereset(t_console *pc, t_motor *pm);
void    m_Emask(t_console *pc, t_motor *pm);
void    m_Elvolt(t_console *pc, t_motor *pm);
void    m_Ehvolt(t_console *pc, t_motor *pm);
void    m_Eovc(t_console *pc, t_motor *pm);
void    m_Eovs(t_console *pc, t_motor *pm);
void    m_Ewovs(t_console *pc, t_motor *pm);
void    m_EwposMax(t_console *pc, t_motor *pm);
void    m_EwposMin(t_console *pc, t_motor *pm);
void    m_Eemp(t_console *pc, t_motor *pm);
void    m_EovTemp(t_console *pc, t_motor *pm);
void    ErrLedDsp( void );
/* RZ/T2 add */
void    m_CtrlMode(t_console *pc, t_motor *pm);
void    m_CommandDirection(t_console *pc, t_motor *pm);
void    m_CommandVelocity(t_console *pc, t_motor *pm);
void    m_CommandTorque(t_console *pc, t_motor *pm);

short   estimate_torque(t_motor *pm);

#define INITIAL_VELOCITY            7158282
#define INITIAL_ACCELERATION        14317
#define INITIAL_DECELERATION        14317

/* motor constant *//* RZ/T2 add */
#define MTR_KT_NUM  (0.033f) /* torque constant [Nm/A] */
//#define MTR_KT_NUM1  (0.026f) /* torque constant [Nm/A] */
#define MTR_KT_NUM1  (0.135f) /* torque constant [Nm/A] */
//#define MTR_KE_NUM  (0.03343949044585987f)  /* back EMF constant[Vpeak/(rad/s)] */ /* TSM3101 */
#define MTR_KE_NUM    (0.0382f)


/* conversion gain */
#define CNVGAIN_SEC_TO_POS_LP_CYC (20000)   /* x[50us] = (1000*1000/50)[50us/s] * y[s]  Base on pos_loop_cycle_time=50[us] */
#define CNVGAIN_RPS_TO_RPM (60)             /* x[rpm] = 60[s/min] * y[rps] */
#define CNVGAIN_NM_TO_UNM (1000*10)       /* x[uNm] = 1000*1000[uNm/Nm] * y[Nm] */
#define CNVGAIN_A_TO_MA (1000)
#define CNVGAIN_VOLTAGE_DIV_VOUT_TO_VIN (121) /* (R222+R223)/R222 = (120k+1k)/1k = 121 */

/* bus board voltage measurement constant */
#define BUS_BOARD_VOLT_COEF 5949.7f
#define BUS_BOARD_VOLT_INTERCEPT 2227.0f
/* The relationship between the value(x) of the bus board power supply voltage divided by R222 and R223 and the value(y) of DSMIF9 was y = 5949.7 * x + 2227.4 */
/* The voltage divided is obtained by subtracting the intercept (2227.4) from the conversion value of DSMIF9 and dividing by the slope value (5949.7) */
/* The power supply voltage is calculated by multiplying the divided voltage by CNVGAIN_VOLTAGE_DIV_VOUT_TO_VIN */

/* Internal conversion of current */
#define CUR_AD_NUM          (40.0f)         /* maximum detection current +/-40[A]*/
#define CUR_AD_DIG_NUM      (2048)          /* 12bit ADC +/-2048[digit] */
#define CUR_BASE_NUM        (37.5)          /* base current[A] */
#define CUR_BASE_DIG_NUM    (32767.0f)      /* digital value of base current[digit] */
#define CUR_DSM_INPUT_VOLTAGE_RANGE (0.32f) /* input voltage range of dsm */

/* Internal conversion of velocity */
#define VEL_BASE_NUM        (1)             /* base velocity[count/pos_loop_cycle_time] */
#define VEL_BASE_DIG_NUM    (4294967296LL)  /* digital value of base velocity[digit] */

#define LIM_INT16_MAX   ( 32767.0f)
#define LIM_INT16_MIN   (-32767.0f)

#define SetSignBit48(a)  ( ( ( (a) & 0x0000800000000000 ) == 0) ? ( (a) & 0x0000FFFFFFFFFFFF ) : ( (a) | 0xFFFF000000000000 ) )

#define LED1 R_PORT_NSR->P_b[0x16].POUT_5
#define LED2 R_PORT_SRS->P_b[0x06].POUT_7
#define LED3 R_PORT_SRS->P_b[0x0].POUT_6
#define LED4 R_PORT_NSR->P_b[0x12].POUT_0
#define LED5 R_PORT_NSR->P_b[0x12].POUT_1
#define SW12_1 R_PORT_NSR->PIN_b[0x23].PIN3
#define SW12_4 R_PORT_NSR->PIN_b[0x23].PIN6


