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
* File Name    : m_interpreter.c
* Version      : 1.0
* Device       : RZ/T2H
* Tool-Chain   : IAR Embedded Workbench for ARM
*                Renesas e2studio
* OS           : Not use
* Description  : Source file of Interpreter.
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <stdlib.h>
#include <ctype.h>

#include "m_common.h"
#include "m_recorder.h"
#include "m_interpreter.h"
#include "m_commands.h"

/******************************************************************************
Global variables
******************************************************************************/

/* exported variables */
extern t_motor m1;
extern t_motor g_st_m[MOTOR_NUM];
extern t_trace trace;
extern short   g_counter;

char sPCT[]   = "PCT";          // Pos Capture Trigger
char sSETUP[] = "SETUP";        // Setup PMAP and HINVERT after alignment of the rotor
char sSIM[]   = "SIM";          // Enable Simulation mode
char sBRAKE[] = "BRAKE";        // 
char sPHASES[]= "PHASES";       // Phase count
char sDATA0[] = "DATA0";        // User data 0
char sDATA1[] = "DATA1";        // User data 1
char sDATA2[] = "DATA2";        // User data 2
char sDATA3[] = "DATA3";        // User data 3
char sDATA4[] = "DATA4";        // User data 4
char sDATA5[] = "DATA5";        // User data 5
char sDATA6[] = "DATA6";        // User data 6
char sDATA7[] = "DATA7";        // User data 7
char sHOFFS[] = "HOFFS";        // Home Offset
char sTYPE[]  = "TYPE";         // Controller type - single axis, dual axis, dual with e-gearing
char sETYPE[] = "ETYPE";        // Encoder type: 0 - incremental, 1 - EnDAT, 2 - BiSS, 3 FA-Coder, 4  - A-Format 
char sHTYPE[] = "HTYPE";        // Hall sensors type: 0 - parallel, 1 - serial 
char sFREQ[]  = "FREQ";         // PWM Carrier frequency
char sSAVE[]  = "SAVE";         // Save parameters to SPI Flash
char sREST[]  = "RESTORE";      // Restore parameters to SPI Flash
char sU[]     = "U";            // Phase U PWM control
char sV[]     = "V";            // Phase V PWM control
char sW[]     = "W";            // Phase W PWM control
char sHSCAN[] = "HSCAN";        // Halls Scanning
char sCYCLE[] = "CYCLE";        // Cycle
char sASTOP[] = "ASTOP";        // Auto stop mode
char sADC1[]  = "ADC1";         // Read ADC 1 value
char sADC2[]  = "ADC2";         // Read ADC 2 value
char sTC[]    = "TC";           // Total Current

char sIDM[]   = "IDM";          // D Current Measured
char sIQM[]   = "IQM";          // Q Current Measured
char sIQERR[] = "IQERR";        // Q Current Error
char sIQCMD[] = "IQCMD";        // IQ Desired (PID Output)
char sIDCMD[] = "IDCMD";        // ID Desired 

char sGO[]       = "GO";        // Update motion and PID parameters
char sALIGN[]    = "ALIGN";     // Start phase alignmen procedure
char sRESET[]    = "RESET";     // Reset
char sSERVOON[]  = "ON";        // Servo on
char sSERVOOFF[] = "OFF";       // Servo off
char sENABLE[]   = "ENABLE";    // Enable Power
char sDISABLE[]  = "DISABLE";   // Enable Power
char sSTOP[]     = "STOP";      // Stop smoothly
char sABORT[]    = "ABORT";     // Stop abruptly
char sHOME[]     = "HOME";      // Home axis
char sPVT[]      = "PVT";       // Reports PVT FIFO buffer occupancy count
char sITIME[]    = "ITIME";     // PVT / VT Interpolation Time [pos loop cycles]

char sEMASK[]    = "EMASK";     // Error Input Mask
char sHMASK[]    = "HMASK";     // Home Input Mask
char sINVERT[]   = "INVERT";    // Input Invert Mask
char sHINVERT[]  = "HINVERT";   // Halls Invert Mask
char sHSHIFT[]   = "HSHIFT";    // Halls Shift Mask
char sHPOS[]     = "HPOS";      // Halls Trnsition position
char sPINVERT[]  = "PINVERT";   // position Invert Mask

char sVER[]   = "VER";          // Firmware Version
char sSTA[]   = "STA";          // Activity status
char sPOS[]   = "POS";          // Actual position
char sERR[]   = "ERR";          // position error
char sIND[]   = "IND";          // Index position
char sINP[]   = "INP";          // Inputs state

char sOUT[]   = "OUT";          // Outputs state
char sOUT1[]  = "OUT1";         // Outputs state
char sOUT2[]  = "OUT2";         // Outputs state

char sPRO[]   = "PRO";          // velocity profile mode
char sABS[]   = "ABS";          // Target position
char sREL[]   = "REL";          // Relative target position
char sVEL[]   = "VEL";          // Target velocity
char sACC[]   = "ACC";          // Target acceleration
char sDEC[]   = "DEC";          // Target deceleration
char sJERK[]  = "JERK";         // acceleration jerk
char sAJERK[] = "AJERK";        // acceleration jerk
char sDJERK[] = "DJERK";        // deceleration jerk

/* FOC Control Loop Gains */ 
char sQKP[]   = "QKP"; 
char sQKI[]   = "QKI"; 

/* position Loop PID Regulator Gains*/
char sKP[]    = "KP"; 
char sKD[]    = "KD"; 
char sKI[]    = "KI"; 
char sIL[]    = "IL"; 
char sDS[]    = "DS";           // Derivative Sample time
char sBP[]    = "BP"; 
char sAFF[]   = "AFF"; 
char sVFF[]   = "VFF";
char sBIAS[]  = "BIAS";         // Motor bias

/* Limits */
char sMLIMIT[]= "MLIMIT";       // PID Control Output Limit 
char sCLIMIT[]= "CLIMIT";       // Continuous Current limit 
char sCTIME[] = "CTIME";        // Continuous Current limit time 
char sPLIMIT[]= "PLIMIT";       // Peak Current - I2t limit 
char sPTIME[] = "PTIME";        // Peak Time - I2t time 
char sMAX[]   = "MAX";          // position error limit
char sETIME[] = "ETIME";        // position error time 
char sPWM[]   = "PWM";
char sQGAIN[] = "QGAIN";        // Current loop set-point scaling 

char sFWD[]   = "FWD";          // Jogging (optionally for a certain time)
char sREV[]   = "REV";

char sPCMODE[]= "PCMODE";       // Phase commutation mode
char sPIMODE[]= "PIMODE";       // Phase init mode
char sPITIME[]= "PITIME";       // Phase init time
char sPIOUT[] = "PIOUT";        // Phase init output
char sPCOUNTS[] = "PCOUNTS";    // Phase counts per electrical cycle
char sPANGLE[]= "PANGLE";       // Phase angle
char sPORIGIN[]="PORIGIN";      // Phase origin
char sPPAIRS[]= "PPAIRS";       // Pole pairs
char sECPR[]  = "ECPR";         // Encoder counts per revolution
char sPSCALE[]= "PSCALE";       // Phase prescale
char sPMAP[]  = "PMAP";         // Phase mapping code (to outputs)
char sPVECTOR[]="PVECTOR";      // Phase vector
char sPIOFFS[] ="PIOFFS";       // Phase-Index Offset
char sCV[]    ="CV";            // Current velocity
char sPADV[]  ="PADV";          // Phase advance 
char sVCOMP[] ="VCOMP";         // Phase velocity feed forward compensation
char sTIMER[] ="TIMER";         // PWM Carrier Interrupt handling time in nanoseconds

char sECP[] = "ECP";            // Max error at Commanded position
char sECV[] = "ECV";            // Max error at Commanded velocity
char sEPO[] = "EPO";            // Max error at position

/* Data Collection Commands */        
char sCH1[]   = "CH1";          // Channel 1 Trace Source
char sCH2[]   = "CH2";          // Channel 2 Trace Source
char sCH3[]   = "CH3";          // Channel 3 Trace Source
char sCH4[]   = "CH4";          // Channel 3 Trace Source
char sPLAY[]  = "PLAY";         // Display Trace Samples
char sTRACE[] = "TRACE";        // Trace Trigger setup
char sTMODE[] = "TMODE";        // Trace Mode
char sTRATE[] = "TRATE";        // Trace Rate
char sTLEVEL[]= "TLEVEL";       // Trigger Level
char sTBSIZE[]= "TBSIZE";       // Trace buffer size (maximum number of records)
char sWMARK[] = "WMARK";         // PVT watermark

char sADDP[]  = "ADDP";         // Add position
char sADDV[]  = "ADDV";         // Add velocity
char sADDR[]  = "ADDR";         // Node address
char sGROUP[] = "GROUP";        // Group address    

enum CommandCode {
    CC_INVALID = 0,
    CC_RW_WORD,
    CC_RW_LONG,
    CC_RO_WORD,
    CC_RO_LONG,
    CC_RW_HEX,
    CC_RO_HEX,
    CC_FUNC,                     // Function with no argument
    CC_FUNC_OA,                  // Function with optional 32bit argument
    CC_RW_INT,
    CC_RO_INT,
    CC_RO_LONG_HEX,
    CC_FUNC_PVT
};

enum ParameterCode {
    PC_NONE,
    PC_WORD,
    PC_LONG,
	PC_LONGLONG
};

typedef void (*FPTR)(t_console *pc, t_motor *cm);

typedef struct {
   unsigned short CmdCode;
   char * pName; 
   union {
      FPTR fptr;
      short *wptr;
      long *lptr;
   } Ptr;
   union {
      FPTR fptr;
      short *wptr;
      long *lptr;
      unsigned short ParCode;
   } Ptr2;
   union {
      FPTR fptr;
      short *wptr;
      long *lptr;
      unsigned short ParCode;
   } Ptr3;
   union {
      FPTR fptr;
      short *wptr;
      long *lptr;
      unsigned short ParCode;
   } Ptr4;
   union {
      FPTR fptr;
      short *wptr;
      long *lptr;
      unsigned short ParCode;
   } Ptr5;
   union {
      FPTR fptr;
      short *wptr;
      long *lptr;
      unsigned short ParCode;
   } Ptr6;
   union {
      FPTR fptr;
      short *wptr;
      long *lptr;
      unsigned short ParCode;
   } Ptr7;
   union {
      FPTR fptr;
      short *wptr;
      long *lptr;
      unsigned short ParCode;
   } Ptr8;
   union {
      FPTR fptr;
      short *wptr;
      long *lptr;
      unsigned short ParCode;
   } Ptr9;
} t_command;

/* Command table */
t_command Commands[256] = {

    {CC_RO_HEX, sSTA, (FPTR) &(g_st_m[0].act_state), (FPTR) &g_st_m[1].act_state, (FPTR) &g_st_m[2].act_state, (FPTR) &g_st_m[3].act_state, (FPTR) &g_st_m[4].act_state, (FPTR) &g_st_m[5].act_state, (FPTR) &g_st_m[6].act_state, (FPTR) &g_st_m[7].act_state, (FPTR) &g_st_m[8].act_state }, // 0
    {CC_RO_INT, sERR, (FPTR) &(g_st_m[0].pos_error), (FPTR) &g_st_m[1].pos_error, (FPTR) &g_st_m[2].pos_error, (FPTR) &g_st_m[3].pos_error, (FPTR) &g_st_m[4].pos_error, (FPTR) &g_st_m[5].pos_error, (FPTR) &g_st_m[6].pos_error, (FPTR) &g_st_m[7].pos_error, (FPTR) &g_st_m[8].pos_error },
    {CC_RO_INT, sADC1, (FPTR) &(g_st_m[0].adc1_raw), (FPTR) &g_st_m[1].adc1_raw, (FPTR) &g_st_m[2].adc1_raw, (FPTR) &g_st_m[3].adc1_raw, (FPTR) &g_st_m[4].adc1_raw, (FPTR) &g_st_m[5].adc1_raw, (FPTR) &g_st_m[6].adc1_raw, (FPTR) &g_st_m[7].adc1_raw, (FPTR) &g_st_m[8].adc1_raw },
    {CC_RO_INT, sADC2, (FPTR) &(g_st_m[0].adc2_raw), (FPTR) &g_st_m[1].adc2_raw, (FPTR) &g_st_m[2].adc2_raw, (FPTR) &g_st_m[3].adc2_raw, (FPTR) &g_st_m[4].adc2_raw, (FPTR) &g_st_m[5].adc2_raw, (FPTR) &g_st_m[6].adc2_raw, (FPTR) &g_st_m[7].adc2_raw, (FPTR) &g_st_m[8].adc2_raw },
    {CC_RO_LONG, sTC, (FPTR) &(g_st_m[0].total_current), (FPTR) &g_st_m[1].total_current, (FPTR) &g_st_m[2].total_current, (FPTR) &g_st_m[3].total_current, (FPTR) &g_st_m[4].total_current, (FPTR) &g_st_m[5].total_current, (FPTR) &g_st_m[6].total_current, (FPTR) &g_st_m[7].total_current, (FPTR) &g_st_m[8].total_current },
    {CC_RO_LONG, sCV, (FPTR) &(g_st_m[0].crnt_vel), (FPTR) &g_st_m[1].crnt_vel, (FPTR) &g_st_m[2].crnt_vel, (FPTR) &g_st_m[3].crnt_vel, (FPTR) &g_st_m[4].crnt_vel, (FPTR) &g_st_m[5].crnt_vel, (FPTR) &g_st_m[6].crnt_vel, (FPTR) &g_st_m[7].crnt_vel, (FPTR) &g_st_m[8].crnt_vel },
    {CC_RO_WORD, sPVT, (FPTR) &(g_st_m[0].pvt_points), (FPTR) &g_st_m[1].pvt_points, (FPTR) &g_st_m[2].pvt_points, (FPTR) &g_st_m[3].pvt_points, (FPTR) &g_st_m[4].pvt_points, (FPTR) &g_st_m[5].pvt_points, (FPTR) &g_st_m[6].pvt_points, (FPTR) &g_st_m[7].pvt_points, (FPTR) &g_st_m[8].pvt_points },
    {CC_RW_WORD, sITIME, (FPTR) &(g_st_m[0].pvt_period), (FPTR) &g_st_m[1].pvt_period, (FPTR) &g_st_m[2].pvt_period, (FPTR) &g_st_m[3].pvt_period, (FPTR) &g_st_m[4].pvt_period, (FPTR) &g_st_m[5].pvt_period, (FPTR) &g_st_m[6].pvt_period, (FPTR) &g_st_m[7].pvt_period, (FPTR) &g_st_m[8].pvt_period },
    {CC_RW_LONG, sVEL, (FPTR) &(g_st_m[0].buffMotion.velocity), (FPTR) &g_st_m[1].buffMotion.velocity, (FPTR) &g_st_m[2].buffMotion.velocity, (FPTR) &g_st_m[3].buffMotion.velocity, (FPTR) &g_st_m[4].buffMotion.velocity, (FPTR) &g_st_m[5].buffMotion.velocity, (FPTR) &g_st_m[6].buffMotion.velocity, (FPTR) &g_st_m[7].buffMotion.velocity, (FPTR) &g_st_m[8].buffMotion.velocity },
    {CC_RW_LONG, sACC, (FPTR) &(g_st_m[0].buffMotion.acceleration), (FPTR) &g_st_m[1].buffMotion.acceleration, (FPTR) &g_st_m[2].buffMotion.acceleration, (FPTR) &g_st_m[3].buffMotion.acceleration, (FPTR) &g_st_m[4].buffMotion.acceleration, (FPTR) &g_st_m[5].buffMotion.acceleration, (FPTR) &g_st_m[6].buffMotion.acceleration, (FPTR) &g_st_m[7].buffMotion.acceleration, (FPTR) &g_st_m[8].buffMotion.acceleration},
    {CC_RW_LONG, sDEC, (FPTR) &(g_st_m[0].buffMotion.deceleration), (FPTR) &g_st_m[1].buffMotion.deceleration, (FPTR) &g_st_m[2].buffMotion.deceleration, (FPTR) &g_st_m[3].buffMotion.deceleration, (FPTR) &g_st_m[4].buffMotion.deceleration, (FPTR) &g_st_m[5].buffMotion.deceleration, (FPTR) &g_st_m[6].buffMotion.deceleration, (FPTR) &g_st_m[7].buffMotion.deceleration, (FPTR) &g_st_m[8].buffMotion.deceleration}, // 10
    {CC_RW_LONG, sAJERK, (FPTR) &(g_st_m[0].buffMotion.accel_jerk), (FPTR) &g_st_m[1].buffMotion.accel_jerk, (FPTR) &g_st_m[2].buffMotion.accel_jerk, (FPTR) &g_st_m[3].buffMotion.accel_jerk, (FPTR) &g_st_m[4].buffMotion.accel_jerk, (FPTR) &g_st_m[5].buffMotion.accel_jerk, (FPTR) &g_st_m[6].buffMotion.accel_jerk, (FPTR) &g_st_m[7].buffMotion.accel_jerk, (FPTR) &g_st_m[8].buffMotion.accel_jerk},
    {CC_RW_LONG, sDJERK, (FPTR) &(g_st_m[0].buffMotion.decel_jerk), (FPTR) &g_st_m[1].buffMotion.decel_jerk, (FPTR) &g_st_m[2].buffMotion.decel_jerk, (FPTR) &g_st_m[3].buffMotion.decel_jerk, (FPTR) &g_st_m[4].buffMotion.decel_jerk, (FPTR) &g_st_m[5].buffMotion.decel_jerk, (FPTR) &g_st_m[6].buffMotion.decel_jerk, (FPTR) &g_st_m[7].buffMotion.decel_jerk, (FPTR) &g_st_m[8].buffMotion.decel_jerk},
    {CC_RW_WORD, sPRO, (FPTR) &(g_st_m[0].dflt_vgp_mode), (FPTR) &g_st_m[1].dflt_vgp_mode, (FPTR) &g_st_m[2].dflt_vgp_mode, (FPTR) &g_st_m[3].dflt_vgp_mode, (FPTR) &g_st_m[4].dflt_vgp_mode, (FPTR) &g_st_m[5].dflt_vgp_mode, (FPTR) &g_st_m[6].dflt_vgp_mode, (FPTR) &g_st_m[7].dflt_vgp_mode, (FPTR) &g_st_m[8].dflt_vgp_mode},
    {CC_RW_WORD, sKP, (FPTR) &(g_st_m[0].buff_kp), (FPTR) &g_st_m[1].buff_kp, (FPTR) &g_st_m[2].buff_kp, (FPTR) &g_st_m[3].buff_kp, (FPTR) &g_st_m[4].buff_kp, (FPTR) &g_st_m[5].buff_kp, (FPTR) &g_st_m[6].buff_kp, (FPTR) &g_st_m[7].buff_kp, (FPTR) &g_st_m[8].buff_kp},
    {CC_RW_WORD, sKI, (FPTR) &(g_st_m[0].buff_ki), (FPTR) &g_st_m[1].buff_ki, (FPTR) &g_st_m[2].buff_ki, (FPTR) &g_st_m[3].buff_ki, (FPTR) &g_st_m[4].buff_ki, (FPTR) &g_st_m[5].buff_ki, (FPTR) &g_st_m[6].buff_ki, (FPTR) &g_st_m[7].buff_ki, (FPTR) &g_st_m[8].buff_ki},
    {CC_RW_WORD, sKD, (FPTR) &(g_st_m[0].buff_kd), (FPTR) &g_st_m[1].buff_kd, (FPTR) &g_st_m[2].buff_kd, (FPTR) &g_st_m[3].buff_kd, (FPTR) &g_st_m[4].buff_kd, (FPTR) &g_st_m[5].buff_kd, (FPTR) &g_st_m[6].buff_kd, (FPTR) &g_st_m[7].buff_kd, (FPTR) &g_st_m[8].buff_kd},
    {CC_RW_WORD, sIL, (FPTR) &(g_st_m[0].integral_limit16), (FPTR) &g_st_m[1].integral_limit16, (FPTR) &g_st_m[2].integral_limit16, (FPTR) &g_st_m[3].integral_limit16, (FPTR) &g_st_m[4].integral_limit16, (FPTR) &g_st_m[5].integral_limit16, (FPTR) &g_st_m[6].integral_limit16, (FPTR) &g_st_m[7].integral_limit16, (FPTR) &g_st_m[8].integral_limit16},
    {CC_RW_WORD, sVFF, (FPTR) &(g_st_m[0].buff_kvff), (FPTR) &g_st_m[1].buff_kvff, (FPTR) &g_st_m[2].buff_kvff, (FPTR) &g_st_m[3].buff_kvff, (FPTR) &g_st_m[4].buff_kvff, (FPTR) &g_st_m[5].buff_kvff, (FPTR) &g_st_m[6].buff_kvff, (FPTR) &g_st_m[7].buff_kvff, (FPTR) &g_st_m[8].buff_kvff },
    {CC_RW_WORD, sAFF, (FPTR) &(g_st_m[0].buff_kaff), (FPTR) &g_st_m[1].buff_kaff, (FPTR) &g_st_m[2].buff_kaff, (FPTR) &g_st_m[3].buff_kaff, (FPTR) &g_st_m[4].buff_kaff, (FPTR) &g_st_m[5].buff_kaff, (FPTR) &g_st_m[6].buff_kaff, (FPTR) &g_st_m[7].buff_kaff, (FPTR) &g_st_m[8].buff_kaff},
    {CC_RW_WORD, sMAX, (FPTR) &(g_st_m[0].buff_err_limit), (FPTR) &g_st_m[1].buff_err_limit, (FPTR) &g_st_m[2].buff_err_limit, (FPTR) &g_st_m[3].buff_err_limit, (FPTR) &g_st_m[4].buff_err_limit, (FPTR) &g_st_m[5].buff_err_limit, (FPTR) &g_st_m[6].buff_err_limit, (FPTR) &g_st_m[7].buff_err_limit, (FPTR) &g_st_m[8].buff_err_limit}, // 20
    {CC_RW_WORD, sETIME, (FPTR) &(g_st_m[0].pos_error_time), (FPTR) &g_st_m[1].pos_error_time, (FPTR) &g_st_m[2].pos_error_time, (FPTR) &g_st_m[3].pos_error_time, (FPTR) &g_st_m[4].pos_error_time, (FPTR) &g_st_m[5].pos_error_time, (FPTR) &g_st_m[6].pos_error_time, (FPTR) &g_st_m[7].pos_error_time, (FPTR) &g_st_m[8].pos_error_time},
    {CC_RW_WORD, sDS, (FPTR) &(g_st_m[0].crnt_ds), (FPTR) &g_st_m[1].crnt_ds, (FPTR) &g_st_m[2].crnt_ds, (FPTR) &g_st_m[3].crnt_ds, (FPTR) &g_st_m[4].crnt_ds, (FPTR) &g_st_m[5].crnt_ds, (FPTR) &g_st_m[6].crnt_ds, (FPTR) &g_st_m[7].crnt_ds, (FPTR) &g_st_m[8].crnt_ds},
    {CC_RW_WORD, sMLIMIT, (FPTR) &(g_st_m[0].pos_loop_limit), (FPTR) &g_st_m[1].pos_loop_limit, (FPTR) &g_st_m[2].pos_loop_limit, (FPTR) &g_st_m[3].pos_loop_limit, (FPTR) &g_st_m[4].pos_loop_limit, (FPTR) &g_st_m[5].pos_loop_limit, (FPTR) &g_st_m[6].pos_loop_limit, (FPTR) &g_st_m[7].pos_loop_limit, (FPTR) &g_st_m[8].pos_loop_limit},
    {CC_RW_INT, sBIAS, (FPTR) &(g_st_m[0].crnt_bias), (FPTR) &g_st_m[1].crnt_bias, (FPTR) &g_st_m[2].crnt_bias, (FPTR) &g_st_m[3].crnt_bias, (FPTR) &g_st_m[4].crnt_bias, (FPTR) &g_st_m[5].crnt_bias, (FPTR) &g_st_m[6].crnt_bias, (FPTR) &g_st_m[7].crnt_bias, (FPTR) &g_st_m[8].crnt_bias},
    {CC_RW_WORD, sASTOP, (FPTR) &(g_st_m[0].auto_stop_mode), (FPTR) &g_st_m[1].auto_stop_mode, (FPTR) &g_st_m[2].auto_stop_mode, (FPTR) &g_st_m[3].auto_stop_mode, (FPTR) &g_st_m[4].auto_stop_mode, (FPTR) &g_st_m[5].auto_stop_mode, (FPTR) &g_st_m[6].auto_stop_mode, (FPTR) &g_st_m[7].auto_stop_mode, (FPTR) &g_st_m[8].auto_stop_mode},
    {CC_RW_WORD, sPIMODE, (FPTR) &(g_st_m[0].phasing_mode), (FPTR) &g_st_m[1].phasing_mode, (FPTR) &g_st_m[2].phasing_mode, (FPTR) &g_st_m[3].phasing_mode, (FPTR) &g_st_m[4].phasing_mode, (FPTR) &g_st_m[5].phasing_mode, (FPTR) &g_st_m[6].phasing_mode, (FPTR) &g_st_m[7].phasing_mode, (FPTR) &g_st_m[8].phasing_mode},
    {CC_RW_WORD, sPITIME, (FPTR) &(g_st_m[0].phasing_time), (FPTR) &g_st_m[1].phasing_time, (FPTR) &g_st_m[2].phasing_time, (FPTR) &g_st_m[3].phasing_time, (FPTR) &g_st_m[4].phasing_time, (FPTR) &g_st_m[5].phasing_time, (FPTR) &g_st_m[6].phasing_time, (FPTR) &g_st_m[7].phasing_time, (FPTR) &g_st_m[8].phasing_time},
    {CC_RW_WORD, sPIOUT, (FPTR) &(g_st_m[0].phasing_power), (FPTR) &g_st_m[1].phasing_power, (FPTR) &g_st_m[2].phasing_power, (FPTR) &g_st_m[3].phasing_power, (FPTR) &g_st_m[4].phasing_power, (FPTR) &g_st_m[5].phasing_power, (FPTR) &g_st_m[6].phasing_power, (FPTR) &g_st_m[7].phasing_power, (FPTR) &g_st_m[8].phasing_power},
    {CC_RW_WORD, sPMAP, (FPTR) &(g_st_m[0].phase_config), (FPTR) &g_st_m[1].phase_config, (FPTR) &g_st_m[2].phase_config, (FPTR) &g_st_m[3].phase_config, (FPTR) &g_st_m[4].phase_config, (FPTR) &g_st_m[5].phase_config, (FPTR) &g_st_m[6].phase_config, (FPTR) &g_st_m[7].phase_config, (FPTR) &g_st_m[8].phase_config},
    {CC_RW_LONG, sPORIGIN, (FPTR) &(g_st_m[0].phase_origin), (FPTR) &g_st_m[1].phase_origin, (FPTR) &g_st_m[2].phase_origin, (FPTR) &g_st_m[3].phase_origin, (FPTR) &g_st_m[4].phase_origin, (FPTR) &g_st_m[5].phase_origin, (FPTR) &g_st_m[6].phase_origin, (FPTR) &g_st_m[7].phase_origin, (FPTR) &g_st_m[8].phase_origin}, // 30
    {CC_RW_WORD, sPCMODE, (FPTR) &(g_st_m[0].commutation_mode), (FPTR) &g_st_m[1].commutation_mode, (FPTR) &g_st_m[2].commutation_mode, (FPTR) &g_st_m[3].commutation_mode, (FPTR) &g_st_m[4].commutation_mode, (FPTR) &g_st_m[5].commutation_mode, (FPTR) &g_st_m[6].commutation_mode, (FPTR) &g_st_m[7].commutation_mode, (FPTR) &g_st_m[8].commutation_mode},
    {CC_RW_INT, sPVECTOR, (FPTR) &(g_st_m[0].phase_vector), (FPTR) &g_st_m[1].phase_vector, (FPTR) &g_st_m[2].phase_vector, (FPTR) &g_st_m[3].phase_vector, (FPTR) &g_st_m[4].phase_vector, (FPTR) &g_st_m[5].phase_vector, (FPTR) &g_st_m[6].phase_vector, (FPTR) &g_st_m[7].phase_vector, (FPTR) &g_st_m[8].phase_vector},
    {CC_RW_WORD, sPPAIRS, (FPTR) &(g_st_m[0].pole_pairs), (FPTR) &g_st_m[1].pole_pairs, (FPTR) &g_st_m[2].pole_pairs, (FPTR) &g_st_m[3].pole_pairs, (FPTR) &g_st_m[4].pole_pairs, (FPTR) &g_st_m[5].pole_pairs, (FPTR) &g_st_m[6].pole_pairs, (FPTR) &g_st_m[7].pole_pairs, (FPTR) &g_st_m[8].pole_pairs},
    {CC_RW_LONG, sPCOUNTS, (FPTR) &(g_st_m[0].ec_per_ecycle), (FPTR) &g_st_m[1].ec_per_ecycle, (FPTR) &g_st_m[2].ec_per_ecycle, (FPTR) &g_st_m[3].ec_per_ecycle, (FPTR) &g_st_m[4].ec_per_ecycle, (FPTR) &g_st_m[5].ec_per_ecycle, (FPTR) &g_st_m[6].ec_per_ecycle, (FPTR) &g_st_m[7].ec_per_ecycle, (FPTR) &g_st_m[8].ec_per_ecycle},
    {CC_RW_LONG, sECPR, (FPTR) &(g_st_m[0].ec_per_rev), (FPTR) &g_st_m[1].ec_per_rev, (FPTR) &g_st_m[2].ec_per_rev, (FPTR) &g_st_m[3].ec_per_rev, (FPTR) &g_st_m[4].ec_per_rev, (FPTR) &g_st_m[5].ec_per_rev, (FPTR) &g_st_m[6].ec_per_rev, (FPTR) &g_st_m[7].ec_per_rev, (FPTR) &g_st_m[8].ec_per_rev},
    {CC_RW_INT, sPIOFFS, (FPTR) &(g_st_m[0].phase_offset), (FPTR) &g_st_m[1].phase_offset, (FPTR) &g_st_m[2].phase_offset, (FPTR) &g_st_m[3].phase_offset, (FPTR) &g_st_m[4].phase_offset, (FPTR) &g_st_m[5].phase_offset, (FPTR) &g_st_m[6].phase_offset, (FPTR) &g_st_m[7].phase_offset, (FPTR) &g_st_m[8].phase_offset},
    {CC_RO_INT, sPANGLE, (FPTR) &(g_st_m[0].phase_angle), (FPTR) &g_st_m[1].phase_angle, (FPTR) &g_st_m[2].phase_angle, (FPTR) &g_st_m[3].phase_angle, (FPTR) &g_st_m[4].phase_angle, (FPTR) &g_st_m[5].phase_angle, (FPTR) &g_st_m[6].phase_angle, (FPTR) &g_st_m[7].phase_angle, (FPTR) &g_st_m[8].phase_angle},
    {CC_RW_INT, sPADV, (FPTR) &(g_st_m[0].phase_adv_gain), (FPTR) &g_st_m[1].phase_adv_gain, (FPTR) &g_st_m[2].phase_adv_gain, (FPTR) &g_st_m[3].phase_adv_gain, (FPTR) &g_st_m[4].phase_adv_gain, (FPTR) &g_st_m[5].phase_adv_gain, (FPTR) &g_st_m[6].phase_adv_gain, (FPTR) &g_st_m[7].phase_adv_gain, (FPTR) &g_st_m[8].phase_adv_gain},
    {CC_RW_INT, sVCOMP, (FPTR) &(g_st_m[0].phase_vel_comp), (FPTR) &g_st_m[1].phase_vel_comp, (FPTR) &g_st_m[2].phase_vel_comp, (FPTR) &g_st_m[3].phase_vel_comp, (FPTR) &g_st_m[4].phase_vel_comp, (FPTR) &g_st_m[5].phase_vel_comp, (FPTR) &g_st_m[6].phase_vel_comp, (FPTR) &g_st_m[7].phase_vel_comp, (FPTR) &g_st_m[8].phase_vel_comp},
    {CC_FUNC_OA, sCLIMIT, m_CurrentLimit, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD}, // 40
    {CC_RW_WORD, sCTIME, (FPTR) &(g_st_m[0].tc_limit_time), (FPTR) &g_st_m[1].tc_limit_time, (FPTR) &g_st_m[2].tc_limit_time, (FPTR) &g_st_m[3].tc_limit_time, (FPTR) &g_st_m[4].tc_limit_time, (FPTR) &g_st_m[5].tc_limit_time, (FPTR) &g_st_m[6].tc_limit_time, (FPTR) &g_st_m[7].tc_limit_time, (FPTR) &g_st_m[8].tc_limit_time},
    {CC_RO_LONG, sIDM, (FPTR) &(g_st_m[0].foc_id), (FPTR) &g_st_m[1].foc_id, (FPTR) &g_st_m[2].foc_id, (FPTR) &g_st_m[3].foc_id, (FPTR) &g_st_m[4].foc_id, (FPTR) &g_st_m[5].foc_id, (FPTR) &g_st_m[6].foc_id, (FPTR) &g_st_m[7].foc_id, (FPTR) &g_st_m[8].foc_id},
    {CC_RO_LONG, sIQM, (FPTR) &(g_st_m[0].foc_iq), (FPTR) &g_st_m[1].foc_iq, (FPTR) &g_st_m[2].foc_iq, (FPTR) &g_st_m[3].foc_iq, (FPTR) &g_st_m[4].foc_iq, (FPTR) &g_st_m[5].foc_iq, (FPTR) &g_st_m[6].foc_iq, (FPTR) &g_st_m[7].foc_iq, (FPTR) &g_st_m[8].foc_iq},
    {CC_RO_LONG, sIQERR, (FPTR) &(g_st_m[0].foc_iq_err), (FPTR) &g_st_m[1].foc_iq_err, (FPTR) &g_st_m[2].foc_iq_err, (FPTR) &g_st_m[3].foc_iq_err, (FPTR) &g_st_m[4].foc_iq_err, (FPTR) &g_st_m[5].foc_iq_err, (FPTR) &g_st_m[6].foc_iq_err, (FPTR) &g_st_m[7].foc_iq_err, (FPTR) &g_st_m[8].foc_iq_err},
    {CC_RW_WORD, sQKP, (FPTR) &(g_st_m[0].foc_kp), (FPTR) &g_st_m[1].foc_kp, (FPTR) &g_st_m[2].foc_kp, (FPTR) &g_st_m[3].foc_kp, (FPTR) &g_st_m[4].foc_kp, (FPTR) &g_st_m[5].foc_kp, (FPTR) &g_st_m[6].foc_kp, (FPTR) &g_st_m[7].foc_kp, (FPTR) &g_st_m[8].foc_kp},
    {CC_RW_WORD, sQKI, (FPTR) &(g_st_m[0].foc_ki), (FPTR) &g_st_m[1].foc_ki, (FPTR) &g_st_m[2].foc_ki, (FPTR) &g_st_m[3].foc_ki, (FPTR) &g_st_m[4].foc_ki, (FPTR) &g_st_m[5].foc_ki, (FPTR) &g_st_m[6].foc_ki, (FPTR) &g_st_m[7].foc_ki, (FPTR) &g_st_m[8].foc_ki},
    {CC_RW_HEX, sPCT, (FPTR) &(g_st_m[0].pos_capture_mode), (FPTR) &g_st_m[1].pos_capture_mode, (FPTR) &g_st_m[2].pos_capture_mode, (FPTR) &g_st_m[3].pos_capture_mode, (FPTR) &g_st_m[4].pos_capture_mode, (FPTR) &g_st_m[5].pos_capture_mode, (FPTR) &g_st_m[6].pos_capture_mode, (FPTR) &g_st_m[7].pos_capture_mode, (FPTR) &g_st_m[8].pos_capture_mode},
    {CC_RW_HEX, sHMASK, (FPTR) &(g_st_m[0].home_mask), (FPTR) &g_st_m[1].home_mask, (FPTR) &g_st_m[2].home_mask, (FPTR) &g_st_m[3].home_mask, (FPTR) &g_st_m[4].home_mask, (FPTR) &g_st_m[5].home_mask, (FPTR) &g_st_m[6].home_mask, (FPTR) &g_st_m[7].home_mask, (FPTR) &g_st_m[8].home_mask},
    {CC_RW_HEX, sINVERT, (FPTR) &(g_st_m[0].home_inv_mask), (FPTR) &g_st_m[1].home_inv_mask, (FPTR) &g_st_m[2].home_inv_mask, (FPTR) &g_st_m[3].home_inv_mask, (FPTR) &g_st_m[4].home_inv_mask, (FPTR) &g_st_m[5].home_inv_mask, (FPTR) &g_st_m[6].home_inv_mask, (FPTR) &g_st_m[7].home_inv_mask, (FPTR) &g_st_m[8].home_inv_mask},
    {CC_RW_INT, sHINVERT, (FPTR) &(g_st_m[0].hall_inverted), (FPTR) &g_st_m[1].hall_inverted, (FPTR) &g_st_m[2].hall_inverted, (FPTR) &g_st_m[3].hall_inverted, (FPTR) &g_st_m[4].hall_inverted, (FPTR) &g_st_m[5].hall_inverted, (FPTR) &g_st_m[6].hall_inverted, (FPTR) &g_st_m[7].hall_inverted, (FPTR) &g_st_m[8].hall_inverted}, // 50
    {CC_RW_INT, sHSHIFT, (FPTR) &(g_st_m[0].hall_shift), (FPTR) &g_st_m[1].hall_shift, (FPTR) &g_st_m[2].hall_shift, (FPTR) &g_st_m[3].hall_shift, (FPTR) &g_st_m[4].hall_shift, (FPTR) &g_st_m[5].hall_shift, (FPTR) &g_st_m[6].hall_shift, (FPTR) &g_st_m[7].hall_shift, (FPTR) &g_st_m[8].hall_shift},
    {CC_RW_LONG, sHPOS, (FPTR) &(g_st_m[0].hall_change_pos), (FPTR) &g_st_m[1].hall_change_pos, (FPTR) &g_st_m[2].hall_change_pos, (FPTR) &g_st_m[3].hall_change_pos, (FPTR) &g_st_m[4].hall_change_pos, (FPTR) &g_st_m[5].hall_change_pos, (FPTR) &g_st_m[6].hall_change_pos, (FPTR) &g_st_m[7].hall_change_pos, (FPTR) &g_st_m[8].hall_change_pos},
    {CC_RW_HEX, sEMASK, (FPTR) &(g_st_m[0].dinputs_err_mask), (FPTR) &g_st_m[1].dinputs_err_mask, (FPTR) &g_st_m[2].dinputs_err_mask, (FPTR) &g_st_m[3].dinputs_err_mask, (FPTR) &g_st_m[4].dinputs_err_mask, (FPTR) &g_st_m[5].dinputs_err_mask, (FPTR) &g_st_m[6].dinputs_err_mask, (FPTR) &g_st_m[7].dinputs_err_mask, (FPTR) &g_st_m[8].dinputs_err_mask},
    {CC_RW_LONG, sECP, (FPTR) &(g_st_m[0].mecmd_pos), (FPTR) &g_st_m[1].mecmd_pos, (FPTR) &g_st_m[2].mecmd_pos, (FPTR) &g_st_m[3].mecmd_pos, (FPTR) &g_st_m[4].mecmd_pos, (FPTR) &g_st_m[5].mecmd_pos, (FPTR) &g_st_m[6].mecmd_pos, (FPTR) &g_st_m[7].mecmd_pos, (FPTR) &g_st_m[8].mecmd_pos},
    {CC_RW_LONG, sECV, (FPTR) &(g_st_m[0].mecmd_vel), (FPTR) &g_st_m[1].mecmd_vel, (FPTR) &g_st_m[2].mecmd_vel, (FPTR) &g_st_m[3].mecmd_vel, (FPTR) &g_st_m[4].mecmd_vel, (FPTR) &g_st_m[5].mecmd_vel, (FPTR) &g_st_m[6].mecmd_vel, (FPTR) &g_st_m[7].mecmd_vel, (FPTR) &g_st_m[8].mecmd_vel},
    {CC_RW_LONG, sEPO, (FPTR) &(g_st_m[0].mecrnt_pos), (FPTR) &g_st_m[1].mecrnt_pos, (FPTR) &g_st_m[2].mecrnt_pos, (FPTR) &g_st_m[3].mecrnt_pos, (FPTR) &g_st_m[4].mecrnt_pos, (FPTR) &g_st_m[5].mecrnt_pos, (FPTR) &g_st_m[6].mecrnt_pos, (FPTR) &g_st_m[7].mecrnt_pos, (FPTR) &g_st_m[8].mecrnt_pos},
    {CC_RW_INT, sU, (FPTR) &(g_st_m[0].PhaseU), (FPTR) &g_st_m[1].PhaseU, (FPTR) &g_st_m[2].PhaseU, (FPTR) &g_st_m[3].PhaseU, (FPTR) &g_st_m[4].PhaseU, (FPTR) &g_st_m[5].PhaseU, (FPTR) &g_st_m[6].PhaseU, (FPTR) &g_st_m[7].PhaseU, (FPTR) &g_st_m[8].PhaseU},
    {CC_RW_INT, sV, (FPTR) &(g_st_m[0].PhaseV), (FPTR) &g_st_m[1].PhaseV, (FPTR) &g_st_m[2].PhaseV, (FPTR) &g_st_m[3].PhaseV, (FPTR) &g_st_m[4].PhaseV, (FPTR) &g_st_m[5].PhaseV, (FPTR) &g_st_m[6].PhaseV, (FPTR) &g_st_m[7].PhaseV, (FPTR) &g_st_m[8].PhaseV},
    {CC_RW_INT, sW, (FPTR) &(g_st_m[0].PhaseW), (FPTR) &g_st_m[1].PhaseW, (FPTR) &g_st_m[2].PhaseW, (FPTR) &g_st_m[3].PhaseW, (FPTR) &g_st_m[4].PhaseW, (FPTR) &g_st_m[5].PhaseW, (FPTR) &g_st_m[6].PhaseW, (FPTR) &g_st_m[7].PhaseW, (FPTR) &g_st_m[8].PhaseW},
    {CC_RW_WORD, sTYPE, (FPTR) &(g_st_m[0].module_type), (FPTR) &g_st_m[1].module_type, (FPTR) &g_st_m[2].module_type, (FPTR) &g_st_m[3].module_type, (FPTR) &g_st_m[4].module_type, (FPTR) &g_st_m[5].module_type, (FPTR) &g_st_m[6].module_type, (FPTR) &g_st_m[7].module_type, (FPTR) &g_st_m[8].module_type}, // 60
    {CC_RW_WORD, sHTYPE, (FPTR) &(g_st_m[0].halls_type), (FPTR) &g_st_m[1].halls_type, (FPTR) &g_st_m[2].halls_type, (FPTR) &g_st_m[3].halls_type, (FPTR) &g_st_m[4].halls_type, (FPTR) &g_st_m[5].halls_type, (FPTR) &g_st_m[6].halls_type, (FPTR) &g_st_m[7].halls_type, (FPTR) &g_st_m[8].halls_type},
    {CC_RW_LONG, sHOFFS, (FPTR) &(g_st_m[0].home_offset), (FPTR) &g_st_m[1].home_offset, (FPTR) &g_st_m[2].home_offset, (FPTR) &g_st_m[3].home_offset, (FPTR) &g_st_m[4].home_offset, (FPTR) &g_st_m[5].home_offset, (FPTR) &g_st_m[6].home_offset, (FPTR) &g_st_m[7].home_offset, (FPTR) &g_st_m[8].home_offset},
    {CC_RW_LONG, sDATA0, (FPTR) &(g_st_m[0].user_data[0]), (FPTR) &g_st_m[1].user_data[0], (FPTR) &g_st_m[2].user_data[0], (FPTR) &g_st_m[3].user_data[0], (FPTR) &g_st_m[4].user_data[0], (FPTR) &g_st_m[5].user_data[0], (FPTR) &g_st_m[6].user_data[0], (FPTR) &g_st_m[7].user_data[0], (FPTR) &g_st_m[8].user_data[0]},
    {CC_RW_LONG, sDATA1, (FPTR) &(g_st_m[0].user_data[1]), (FPTR) &g_st_m[1].user_data[1], (FPTR) &g_st_m[2].user_data[1], (FPTR) &g_st_m[3].user_data[1], (FPTR) &g_st_m[4].user_data[1], (FPTR) &g_st_m[5].user_data[1], (FPTR) &g_st_m[6].user_data[1], (FPTR) &g_st_m[7].user_data[1], (FPTR) &g_st_m[8].user_data[1]},
    {CC_RW_LONG, sDATA2, (FPTR) &(g_st_m[0].user_data[2]), (FPTR) &g_st_m[1].user_data[2], (FPTR) &g_st_m[2].user_data[2], (FPTR) &g_st_m[3].user_data[2], (FPTR) &g_st_m[4].user_data[2], (FPTR) &g_st_m[5].user_data[2], (FPTR) &g_st_m[6].user_data[2], (FPTR) &g_st_m[7].user_data[2], (FPTR) &g_st_m[8].user_data[2]},
    {CC_RW_LONG, sDATA3, (FPTR) &(g_st_m[0].user_data[3]), (FPTR) &g_st_m[1].user_data[3], (FPTR) &g_st_m[2].user_data[3], (FPTR) &g_st_m[3].user_data[3], (FPTR) &g_st_m[4].user_data[3], (FPTR) &g_st_m[5].user_data[3], (FPTR) &g_st_m[6].user_data[3], (FPTR) &g_st_m[7].user_data[3], (FPTR) &g_st_m[8].user_data[3]},
    {CC_RW_LONG, sDATA4, (FPTR) &(g_st_m[0].user_data[4]), (FPTR) &g_st_m[1].user_data[4], (FPTR) &g_st_m[2].user_data[4], (FPTR) &g_st_m[3].user_data[4], (FPTR) &g_st_m[4].user_data[4], (FPTR) &g_st_m[5].user_data[4], (FPTR) &g_st_m[6].user_data[4], (FPTR) &g_st_m[7].user_data[4], (FPTR) &g_st_m[8].user_data[4]},
    {CC_RW_LONG, sDATA5, (FPTR) &(g_st_m[0].user_data[5]), (FPTR) &g_st_m[1].user_data[5], (FPTR) &g_st_m[2].user_data[5], (FPTR) &g_st_m[3].user_data[5], (FPTR) &g_st_m[4].user_data[5], (FPTR) &g_st_m[5].user_data[5], (FPTR) &g_st_m[6].user_data[5], (FPTR) &g_st_m[7].user_data[5], (FPTR) &g_st_m[8].user_data[5]},
    {CC_RW_LONG, sDATA6, (FPTR) &(g_st_m[0].user_data[6]), (FPTR) &g_st_m[1].user_data[6], (FPTR) &g_st_m[2].user_data[6], (FPTR) &g_st_m[3].user_data[6], (FPTR) &g_st_m[4].user_data[6], (FPTR) &g_st_m[5].user_data[6], (FPTR) &g_st_m[6].user_data[6], (FPTR) &g_st_m[7].user_data[6], (FPTR) &g_st_m[8].user_data[6]},
    {CC_RW_LONG, sDATA7, (FPTR) &(g_st_m[0].user_data[7]), (FPTR) &g_st_m[1].user_data[7], (FPTR) &g_st_m[2].user_data[7], (FPTR) &g_st_m[3].user_data[7], (FPTR) &g_st_m[4].user_data[7], (FPTR) &g_st_m[5].user_data[7], (FPTR) &g_st_m[6].user_data[7], (FPTR) &g_st_m[7].user_data[7], (FPTR) &g_st_m[8].user_data[7]}, // 70
    {CC_RW_WORD, sPHASES, (FPTR) &(g_st_m[0].motor_type), (FPTR) &g_st_m[1].motor_type, (FPTR) &g_st_m[2].motor_type, (FPTR) &g_st_m[3].motor_type, (FPTR) &g_st_m[4].motor_type, (FPTR) &g_st_m[5].motor_type, (FPTR) &g_st_m[6].motor_type, (FPTR) &g_st_m[7].motor_type, (FPTR) &g_st_m[8].motor_type},
    {CC_RW_WORD, sBRAKE, (FPTR) &(g_st_m[0].brake_mode), (FPTR) &g_st_m[1].brake_mode, (FPTR) &g_st_m[2].brake_mode, (FPTR) &g_st_m[3].brake_mode, (FPTR) &g_st_m[4].brake_mode, (FPTR) &g_st_m[5].brake_mode, (FPTR) &g_st_m[6].brake_mode, (FPTR) &g_st_m[7].brake_mode, (FPTR) &g_st_m[8].brake_mode},
    {CC_RW_WORD, sTMODE, (FPTR) &trace.Mode, (FPTR) &trace.Mode, (FPTR) &trace.Mode, (FPTR) &trace.Mode, (FPTR) &trace.Mode, (FPTR) &trace.Mode, (FPTR) &trace.Mode, (FPTR) &trace.Mode, (FPTR) &trace.Mode},
    {CC_RW_WORD, sTRATE, (FPTR) &trace.RateMult, (FPTR) &trace.RateMult, (FPTR) &trace.RateMult, (FPTR) &trace.RateMult, (FPTR) &trace.RateMult, (FPTR) &trace.RateMult, (FPTR) &trace.RateMult, (FPTR) &trace.RateMult, (FPTR) &trace.RateMult},
    {CC_RW_LONG, sTLEVEL, (FPTR) &trace.Level, (FPTR) &trace.Level, (FPTR) &trace.Level, (FPTR) &trace.Level, (FPTR) &trace.Level, (FPTR) &trace.Level, (FPTR) &trace.Level, (FPTR) &trace.Level, (FPTR) &trace.Level},
    {CC_RW_WORD, sSIM, (FPTR) &(g_st_m[0].simulated_mode), (FPTR) &g_st_m[1].simulated_mode, (FPTR) &g_st_m[2].simulated_mode, (FPTR) &g_st_m[3].simulated_mode, (FPTR) &g_st_m[4].simulated_mode, (FPTR) &g_st_m[5].simulated_mode, (FPTR) &g_st_m[6].simulated_mode, (FPTR) &g_st_m[7].simulated_mode, (FPTR) &g_st_m[8].simulated_mode},
    {CC_RW_WORD, sTIMER, (FPTR) &g_counter, (FPTR) &g_counter, (FPTR) &g_counter, (FPTR) &g_counter, (FPTR) &g_counter, (FPTR) &g_counter, (FPTR) &g_counter, (FPTR) &g_counter, (FPTR) &g_counter},
    {CC_FUNC_OA, sADDP, m_AddPos, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC_OA, sADDV, m_AddVel, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC_OA, sABS, m_Abs, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG}, // 80
    {CC_FUNC_OA, sREL, m_Rel, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC_OA, sPOS, m_Position, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC, sINP, m_Inputs, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC, sIND, m_Index, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC_OA, sGO, m_Go,  (FPTR) PC_NONE,  (FPTR) PC_NONE,  (FPTR) PC_NONE,  (FPTR) PC_NONE,  (FPTR) PC_NONE,  (FPTR) PC_NONE,  (FPTR) PC_NONE,  (FPTR) PC_NONE},
    {CC_FUNC_OA, sFWD, m_Forward, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC_OA, sREV, m_Reverse, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC_OA, sRESET, m_Reset, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC, sSERVOON, m_ServoOn, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC, sSERVOOFF, m_ServoOff, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE}, // 90
    {CC_FUNC, sENABLE, m_PowerOn, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC, sDISABLE, m_PowerOff, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC, sSTOP, m_SmoothStop, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC, sABORT, m_AbruptStop, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC, sHOME, m_StartHoming, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC_OA, sALIGN, m_AlignPhase, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC, sVER, m_Version, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG },
    {CC_FUNC_OA, sOUT1, m_Output1, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, sOUT2, m_Output2, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, sPWM, m_PosLoopCmd, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD}, // 100
    {CC_FUNC_OA, sIQCMD, m_OutputIQ, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, sIDCMD, m_OutputID, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, sCH1, m_LogChannel0, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, sCH2, m_LogChannel1, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, sCH3, m_LogChannel2, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, sCH4, m_LogChannel3, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, sTRACE, m_Trace, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, sPLAY, m_Play, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, sPLIMIT, m_PLimit, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, sPTIME, m_PLimitTime, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD}, // 110
    {CC_FUNC_OA, "GEARIN", m_GearIn, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, "GEAROUT", m_GearOut, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, sSETUP, m_Setup, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC_OA, sPINVERT, m_PosInvert, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD },
    {CC_FUNC, sSAVE, m_Save, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC, sREST, m_Restore, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC_OA, sETYPE, m_EncoderType, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, "EID", m_EncReadID, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC_OA, "EADDR", m_EncAddrEEPROM, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, "EDATA", m_EncDataEEPROM, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD}, // 120
    {CC_FUNC_OA, "EBAUDRATE", m_EncBaudrate, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, "ESTATUS", m_EncStatus, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_RW_WORD, sADDR, (FPTR) &(g_st_m[0].module_addr), (FPTR) &g_st_m[1].module_addr, (FPTR) &g_st_m[2].module_addr, (FPTR) &g_st_m[3].module_addr, (FPTR) &g_st_m[4].module_addr, (FPTR) &g_st_m[5].module_addr, (FPTR) &g_st_m[6].module_addr, (FPTR) &g_st_m[7].module_addr, (FPTR) &g_st_m[8].module_addr},
    {CC_RW_WORD, sGROUP, (FPTR) &(g_st_m[0].group_addr), (FPTR) &g_st_m[1].group_addr, (FPTR) &g_st_m[2].group_addr, (FPTR) &g_st_m[3].group_addr, (FPTR) &g_st_m[4].group_addr, (FPTR) &g_st_m[5].group_addr, (FPTR) &g_st_m[6].group_addr, (FPTR) &g_st_m[7].group_addr, (FPTR) &g_st_m[8].group_addr},
    {CC_RO_WORD, sTBSIZE, (FPTR) &trace.buff_size, (FPTR) &trace.buff_size, (FPTR) &trace.buff_size, (FPTR) &trace.buff_size, (FPTR) &trace.buff_size, (FPTR) &trace.buff_size, (FPTR) &trace.buff_size, (FPTR) &trace.buff_size, (FPTR) &trace.buff_size},
    {CC_RW_WORD, sWMARK, (FPTR) &(g_st_m[0].pvt_watermark), (FPTR) &g_st_m[1].pvt_watermark, (FPTR) &g_st_m[2].pvt_watermark, (FPTR) &g_st_m[3].pvt_watermark, (FPTR) &g_st_m[4].pvt_watermark, (FPTR) &g_st_m[5].pvt_watermark, (FPTR) &g_st_m[6].pvt_watermark, (FPTR) &g_st_m[7].pvt_watermark, (FPTR) &g_st_m[8].pvt_watermark},
    {CC_RW_WORD, "QKD", (FPTR) &(g_st_m[0].foc_kd), (FPTR) &g_st_m[1].foc_kd, (FPTR) &g_st_m[2].foc_kd, (FPTR) &g_st_m[3].foc_kd, (FPTR) &g_st_m[4].foc_kd, (FPTR) &g_st_m[5].foc_kd, (FPTR) &g_st_m[6].foc_kd, (FPTR) &g_st_m[7].foc_kd, (FPTR) &g_st_m[8].foc_kd},
    {CC_RW_WORD, "VKP", (FPTR) &(g_st_m[0].buff_kp_vel), (FPTR) &g_st_m[1].buff_kp_vel, (FPTR) &g_st_m[2].buff_kp_vel, (FPTR) &g_st_m[3].buff_kp_vel, (FPTR) &g_st_m[4].buff_kp_vel, (FPTR) &g_st_m[5].buff_kp_vel, (FPTR) &g_st_m[6].buff_kp_vel, (FPTR) &g_st_m[7].buff_kp_vel, (FPTR) &g_st_m[8].buff_kp_vel},
    {CC_RW_WORD, "VKI", (FPTR) &(g_st_m[0].buff_ki_vel), (FPTR) &g_st_m[1].buff_ki_vel, (FPTR) &g_st_m[2].buff_ki_vel, (FPTR) &g_st_m[3].buff_ki_vel, (FPTR) &g_st_m[4].buff_ki_vel, (FPTR) &g_st_m[5].buff_ki_vel, (FPTR) &g_st_m[6].buff_ki_vel, (FPTR) &g_st_m[7].buff_ki_vel, (FPTR) &g_st_m[8].buff_ki_vel},
    {CC_RW_WORD, "VKD", (FPTR) &(g_st_m[0].buff_kd_vel), (FPTR) &g_st_m[1].buff_kd_vel, (FPTR) &g_st_m[2].buff_kd_vel, (FPTR) &g_st_m[3].buff_kd_vel, (FPTR) &g_st_m[4].buff_kd_vel, (FPTR) &g_st_m[5].buff_kd_vel, (FPTR) &g_st_m[6].buff_kd_vel, (FPTR) &g_st_m[7].buff_kd_vel, (FPTR) &g_st_m[8].buff_kd_vel}, // 130
    {CC_FUNC_OA, "ELVOLT", m_Elvolt, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC_OA, "EHVOLT", m_Ehvolt, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC_OA, "EWPOSMIN", m_EwposMin, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC_OA, "EWPOSMAX", m_EwposMax, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC_OA, "EOVS", m_Eovs, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC_OA, "EWOVS", m_Ewovs, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC_OA, "EEMP", m_Eemp, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC_OA, "EOVTEMP", m_EovTemp, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_FUNC_OA, "ERRMASK", m_Emask, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_RO_INT, "EVOLT", (FPTR) &(g_st_m[0].crnt_volt), (FPTR) &g_st_m[1].crnt_volt, (FPTR) &g_st_m[2].crnt_volt, (FPTR) &g_st_m[3].crnt_volt, (FPTR) &g_st_m[4].crnt_volt, (FPTR) &g_st_m[5].crnt_volt, (FPTR) &g_st_m[6].crnt_volt, (FPTR) &g_st_m[7].crnt_volt, (FPTR) &g_st_m[8].crnt_volt}, // 140
    {CC_RO_LONG_HEX, "EQUERY", (FPTR) &(g_st_m[0].ErrSts), (FPTR) &g_st_m[1].ErrSts, (FPTR) &g_st_m[2].ErrSts, (FPTR) &g_st_m[3].ErrSts, (FPTR) &g_st_m[4].ErrSts, (FPTR) &g_st_m[5].ErrSts, (FPTR) &g_st_m[6].ErrSts, (FPTR) &g_st_m[7].ErrSts, (FPTR) &g_st_m[8].ErrSts},
    {CC_FUNC, "ERESET", m_Ereset, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC_OA, "EOVC", m_Eovc, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG, (FPTR) PC_LONG},
    {CC_RO_INT, "ETEMP", (FPTR) &(g_st_m[0].crnt_temp), (FPTR) &g_st_m[1].crnt_temp, (FPTR) &g_st_m[2].crnt_temp, (FPTR) &g_st_m[3].crnt_temp, (FPTR) &g_st_m[4].crnt_temp, (FPTR) &g_st_m[5].crnt_temp, (FPTR) &g_st_m[6].crnt_temp, (FPTR) &g_st_m[7].crnt_temp, (FPTR) &g_st_m[8].crnt_temp},
    {CC_FUNC_OA, "CTRLMODE", m_CtrlMode, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, "COMDIR", m_CommandDirection, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, "COMVEL", m_CommandVelocity, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_FUNC_OA, "COMTRQ", m_CommandTorque, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_RO_WORD, "ESTTRQ", (FPTR) &(g_st_m[0].est_trq), (FPTR) &g_st_m[1].est_trq, (FPTR) &g_st_m[2].est_trq, (FPTR) &g_st_m[3].est_trq, (FPTR) &g_st_m[4].est_trq, (FPTR) &g_st_m[5].est_trq, (FPTR) &g_st_m[6].est_trq, (FPTR) &g_st_m[7].est_trq, (FPTR) &g_st_m[8].est_trq},
    {CC_FUNC, "GPIO", m_Gpio, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE}, // 150
    {CC_FUNC_PVT, "IPVT", m_InitPvt, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC_PVT, "SPVT", m_SetPvt, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE, (FPTR) PC_NONE},
    {CC_FUNC_OA, "RVAL", m_ReadValue, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD, (FPTR) PC_WORD},
    {CC_RW_WORD, 0, 0}
};

/******************************************************************************
Static variables and functions
******************************************************************************/
/* prototype definitions of static functions */


/* static variables */
#define TMP_BUFF_SIZE 36
static char Buff[TMP_BUFF_SIZE];


/******************************************************************************
Global functions
******************************************************************************/



void print_dec (t_console *pc, long value)
{
char* ptr = Buff + TMP_BUFF_SIZE - 1;
char  neg = (value < 0);

    if (pc->tx_count > TX_BUF_SIZE - TMP_BUFF_SIZE - 5)
        return;

    if (pc->cmd_req == PTR_PACKET)      /* Binary Protocol Request */
    {
        *(pc->ptx++) = (char)(value);
        *(pc->ptx++) = (char)(value >> 8);
        pc->tx_count += 2;
        if (pc->data_type == PC_LONG)
        {
            *(pc->ptx++) = (char)(value >> 16);
            *(pc->ptx++) = (char)(value >> 24);
            pc->tx_count += 2;
        }
        return;
    }
    
    if (neg) 
        value = -value;
   
    *ptr-- = 0;
    do 
    {
        *ptr-- = (char)((value % 10) + '0');
        value /= 10;
    } 
    while (value != 0);

    if (neg)
        *ptr-- = '-';

    while (*(++ptr)) 
    {
        *(pc->ptx++) = *ptr;
        pc->tx_count++;
    }
}

/* RZ/T2 add */
/******************************************************************************
* Function Name: print_dec2
* Description  : Convert a number to a string and set it in the send buffer
* Arguments    : pc : structure of communication(pointer)
*              : value : Numerical value to convert to a string
* Return Value : None
******************************************************************************/
void print_dec2 (t_console *pc, long long value)
{
	char* ptr = Buff + TMP_BUFF_SIZE - 1;
	char  neg = (value < 0);

    if (pc->tx_count > TX_BUF_SIZE - TMP_BUFF_SIZE - 5)
        return;

    if (pc->cmd_req == PTR_PACKET)
    {
        if (pc->data_type == PC_LONGLONG)
        {
            *(pc->ptx++) = (char)(value >>  0);
            *(pc->ptx++) = (char)(value >>  8);
            *(pc->ptx++) = (char)(value >> 16);
            *(pc->ptx++) = (char)(value >> 24);
            *(pc->ptx++) = (char)(value >> 32);
            *(pc->ptx++) = (char)(value >> 40);
            *(pc->ptx++) = (char)(value >> 48);
            *(pc->ptx++) = (char)(value >> 56);
            pc->tx_count += 8;
        }
        return;
    }

    if (neg) value = -value;
   
    *ptr-- = 0;
    do 
    {
        *ptr-- = (char)((value % 10) + '0');
        value /= 10;
    } 
    while (value != 0);

    if (neg)
        *ptr-- = '-';

    while (*(++ptr)) 
    {
        *(pc->ptx++) = *ptr;
        pc->tx_count++;
    }
}
/*******************************************************************************
End of function print_dec2
*******************************************************************************/

static char toasciii (char cTemp)
{
   cTemp &= 15;
   if (cTemp < 10)
      cTemp += '0';
   else
      cTemp += 'A' - 10;
   return cTemp;
}

void print_hex (t_console *pc, short value) 
{
    if (pc->tx_count > TX_BUF_SIZE - TMP_BUFF_SIZE - 5)
        return;
   
    if (pc->cmd_req == PTR_ASCII)           /* ASCII Protocol Request */
    {
        *(pc->ptx++) = toasciii ((char)(value >> 12));
        *(pc->ptx++) = toasciii ((char)(value >> 8));
        *(pc->ptx++) = toasciii ((char)(value >> 4));
        *(pc->ptx++) = toasciii ((char)(value));
        pc->tx_count += 4;
    }
    else if (pc->cmd_req == PTR_PACKET)      /* Binary Protocol Request */
    {
        *(pc->ptx++) = (char)(value);
        *(pc->ptx++) = (char)(value >> 8);
        pc->tx_count += 2;
    }
}

void print_hex2 (t_console *pc, long value)
{
    if (pc->tx_count > TX_BUF_SIZE - TMP_BUFF_SIZE - 9)
        return;
   
    if (pc->cmd_req == PTR_ASCII)           /* ASCII Protocol Request */
    {
        *(pc->ptx++) = toasciii ((char)(value >> 28));
        *(pc->ptx++) = toasciii ((char)(value >> 24));
        *(pc->ptx++) = toasciii ((char)(value >> 20));
        *(pc->ptx++) = toasciii ((char)(value >> 16));
        *(pc->ptx++) = toasciii ((char)(value >> 12));
        *(pc->ptx++) = toasciii ((char)(value >> 8));
        *(pc->ptx++) = toasciii ((char)(value >> 4));
        *(pc->ptx++) = toasciii ((char)(value));
        pc->tx_count += 8;
    }
    else if (pc->cmd_req == PTR_PACKET)      /* Binary Protocol Request */
    {
        *(pc->ptx++) = (char)(value);
        *(pc->ptx++) = (char)(value >> 8);
        *(pc->ptx++) = (char)(value >> 16);
        *(pc->ptx++) = (char)(value >> 24);
        pc->tx_count += 4;
    }
}

static void m_report(t_console *pc, t_motor *pm)
{
    short req = pc->rx_buf[0] + (pc->rx_buf[1] << 8);
    
    if (req & 0x0001)    /* Position */
    {
        pc->data_type = PC_LONG;
        print_dec(pc, pm->crnt_pos);
    }
    if (req & 0x0002)    /* Status */
    {
        print_hex(pc, pm->act_state);
    }
    if (req & 0x0004)    /* Position Error */
    {
        print_hex(pc, pm->pos_error);
    }
    if (req & 0x0008)    /* Current Id*//* RZ/T2 change */
    {
        print_hex2(pc, pm->foc_id);
    }
    if (req & 0x0010)    /* Current Iq *//* RZ/T2 change */
    {
        print_hex2(pc, pm->foc_iq);
    }
    if (req & 0x0020)    /* Digital Inputs */
    {
        *(pc->ptx++) = (unsigned char)pm->dinputs;
        pc->tx_count++;
    }
    if (req & 0x0040)    /* PVT FIFO Depth */
    {
        *(pc->ptx++) = (unsigned char)pm->pvt_points;
        pc->tx_count++;
    }
    if (req & 0x0080)    /* Scan FIFO Depth */
    {
        *(pc->ptx++) = 0;
        pc->tx_count++;
    }
    if (req & 0x0100)    /* Buss voltage */
    {
        print_hex(pc, pm->crnt_volt);
    }
    if (req & 0x0200)    /* Inverter temperature */
    {
        print_hex(pc, pm->crnt_temp);
    }
    if (req & 0x0400)    /* Torque Estimate *//* RZ/T2 add */
    {
        print_hex(pc, pm->est_trq);
    }
    if (req & 0x0800)    /* Current Velocity *//* RZ/T2 add */
    {
        pc->data_type = PC_LONG;
        print_dec(pc, pm->crnt_vel);
    }
}

static void protocol_packet(t_console *pc, t_motor *pm)
{
t_command * pcmd; 

    pc->set = (pc->pkt_code == PC_SET_PAR) ? 1 : 0;
    pc->err = PE_OK;
    
    /* Set status byte */
    pc->tx_buf[0] = PE_OK;
    pc->ptx = &pc->tx_buf[1];
    pc->tx_count = 1;
    
    /* Decode packet */
    switch(pc->pkt_code)
    {
    case PC_REPORT:         /* Report status information as requested */
        m_report(pc, pm);
        break;
        
    case PC_INIT_PVT:       /* Initia;ize PVT Stream */
        /* Make sure the controller is not running PVT stream */
        if (pm->vpg_state != VPG_MotionCompleted)
        {
            pc->tx_buf[0] = PE_INVALID_STATE;
            break;
        }
        if (pc->rx_buf[0] == 0)
        {
            pc->tx_buf[0] = PE_INVALID_VALUE;
            break;
        }
        pm->pvt_points = 0;
        pm->pvt_push = &pm->pvt_pointsFIFO[0];
        pm->pvt_period = pc->rx_buf[0];
        pm->pvt_watermark = pc->rx_buf[1];
        break;
        
    case PC_SET_PVT:        /* Consume PVT Stream */
        {
            int points = (int)((pc->rx_count - 5) >> 3);  /* 5 bytes header & checksum + 8 bytes per point (4 pos + 4 vel) */
            long *pl = (long *)(pc->rx_buf);
            
            if (pm->pvt_points + points >= PVT_BUFF_SIZE)
            {
                pc->tx_buf[0] = PE_BUFFER_OVF;
                break;
            }
            while (points-- >= 0)
            {
                pm->pvt_push->position = *pl++;
                pm->pvt_push->velocity = *pl++;
                pm->pvt_points++;
                pm->pvt_push++;
                if (pm->pvt_push >= &pm->pvt_pointsFIFO[PVT_BUFF_SIZE])
                    pm->pvt_push = &pm->pvt_pointsFIFO[0];     
            }
            if (pm->pvt_points >= pm->pvt_watermark)
                pm->act_state &= ~ACT_PVTWatermark;        
        }
        break;
          
    case PC_GET_TRACE:      /* Return trace buffer content */
        /* Send reply body */
        m_Play(pc, pm);
        /* Make sure there is no data to transmit */
        pc->tx_count = 0;   
        /* Exit directly because checksum is calculated and sent in m_Play()*/
        return;
        
    case PC_FUNCTION:        /* Execute command */
        pcmd = &Commands[pc->rx_buf[0]];
        if ((pcmd->CmdCode == CC_FUNC || pcmd->CmdCode == CC_FUNC_OA) && pcmd->Ptr.fptr != NULL)
        {
            (pcmd->Ptr.fptr)(pc, pm);
            pc->tx_buf[0] = pc->err;
        }
        break;
        
    case PC_SET_PAR:        /* Set 16 or 32 bit parameter */
    case PC_GET_PAR:        /* Get 16 or 32 bit parameter */
    {
        /* Get command/parameter code */
        pcmd = &Commands[pc->rx_buf[0]];
        short *parg_s = pm == &m1 ? pcmd->Ptr.wptr : pcmd->Ptr2.wptr;
        long  *parg_l = (long *)parg_s;
            
        switch (pcmd->CmdCode)
        {
        case CC_RO_WORD: 
        case CC_RO_HEX:
        case CC_RO_INT: 
        case CC_RO_LONG: 
        case CC_RO_LONG_HEX:
            if (pc->set)
            {
                /* Error - attempt to set Read-Only parameter */
                pc->tx_buf[0] = PE_INVALID_ACCESS;
                break;
            }
        case CC_RW_WORD: 
        case CC_RW_HEX:
        case CC_RW_INT: 
        case CC_RW_LONG: 
            if (pc->set)
            {
                if (pcmd->CmdCode == CC_RW_LONG)
                {
                    if (pc->rx_count != 6)
                    {
                        pc->tx_buf[0] = PE_INVALID_FORMAT;
                        break;
                    }
                    *parg_l = *(long *)(&pc->rx_buf[1]);
                }
                else 
                {
                    if (pc->rx_count != 4)
                    {
                        pc->tx_buf[0] = PE_INVALID_FORMAT;
                        break;
                    }
                    *parg_s = *(short *)(&pc->rx_buf[1]);
                }
            }
            else
            {
                if (pcmd->CmdCode == CC_RW_LONG || pcmd->CmdCode == CC_RO_LONG || pcmd->CmdCode == CC_RO_LONG_HEX)
                {
                    pc->data_type = PC_LONG;
                    print_dec (pc, *parg_l);
                }
                else
                {
                    pc->data_type = PC_WORD;
                    print_hex (pc, *parg_s);
                }
            }
            break;

        case CC_FUNC: 
        case CC_FUNC_OA: 
            pc->data_type = pcmd->Ptr2.ParCode;
            if (pc->set)
            {
                if (pc->data_type == PC_WORD)
                {
                    if (pc->rx_count != 4)
                    {
                        pc->tx_buf[0] = PE_INVALID_FORMAT;
                        break;
                    }
                    pc->arg = (long)*(short *)(&pc->rx_buf[1]);
                }
                else if (pc->data_type == PC_LONG)
                {
                    if (pc->rx_count != 6)
                    {
                        pc->tx_buf[0] = PE_INVALID_FORMAT;
                        break;
                    }
                    pc->arg = *(long *)(&pc->rx_buf[1]); 
                }
                else
                {
                    pc->arg = 0;
                }
            }
            if (pcmd->Ptr.fptr != NULL)
            {
                /* RZ/T2 add */
                if (pc->rx_buf[0] == 153)   // CC_FUNC_OA, "RVAL" command only
                {
                    pc->arg = *(long *)(&pc->rx_buf[1]);
                }
                (pcmd->Ptr.fptr)(pc, pm); 
                pc->tx_buf[0] = pc->err;
            }
            else  
            {   
                /* Error - invalid function pointer */
                pc->tx_buf[0] = PE_INVALID_PARAM;
            } 
            break;
            
        default:
            pc->tx_buf[0] = PE_INVALID_PARAM;
            break;
        }
        break;
    }
    case PC_MODULEID:
        *pc->ptx++ = 3;         /* Protocol Version */
        *pc->ptx++ = 0x20;      /* Module Type - Dual Axis Servo Controller */
        *pc->ptx++ =  00;        /* Firmware Version (Minor) */
        *pc->ptx++ = 4;         /* Firmware Version (Major) */
        pc->tx_count += 4;
        break;
        
    case PC_BAUDRATE:
        if (!set_baud_rate(pc->pSCI0, pc->rx_buf[0]))
            pc->tx_buf[0] = PE_INVALID_VALUE;
        break;
        
    default:
        pc->tx_buf[0] = PE_INVALID_CODE;
        break;
    }
    /* If the packet is sent to broadcast address - suppress reply */
//    if (pc->pkt_addr == '\xff' || pc->pkt_addr == pm->group_addr)
    if ( (pc->pkt_addr == 0xFFu) || (pc->pkt_addr == pm->group_addr))
    {
        pc->tx_count = 0;
    }
    else
    {
    /* Calculate packet checksum byte */
        int i;
        unsigned char cs = 0;
        
        for (i = 0; i < pc->tx_count; i++)
            cs += pc->tx_buf[i];
        *pc->ptx = cs;
        pc->tx_count++;
    }
}

static void protocol_ascii(t_console *pc)
{
    t_command * CmdTable = Commands;
    unsigned char *pArg;
    unsigned char *pBuff = pc->rx_buf;
    char end = 0;
    char channel = pc->channel;
    int i;

    pc->err = PE_INVALID_VALUE;
    
    /* Skip white space */
    while (*pBuff == ' ' || *pBuff == '\t')               
    {
        pBuff++;
    }
      
    /* Check for an optional explicit channel specifier as a first character */
    if (*pBuff == '1') 
    {
        channel = '1';
        if (*(pBuff + 1) == 0)
        {
            pc->channel = '1';
        }
        pBuff++;
    } 
    else if (*pBuff == '2') 
    {
        channel = '2';
        if (*(pBuff + 1) == 0)
        {
            pc->channel = '2';
        }
        pBuff++;
    }
    else if (*pBuff == '3')
    {
        channel = '3';
        if (*(pBuff + 1) == 0)
        {
            pc->channel = '3';
        }
        pBuff++;
    }
    else if (*pBuff == '4')
    {
        channel = '4';
        if (*(pBuff + 1) == 0)
        {
            pc->channel = '4';
        }
        pBuff++;
    }
    else if (*pBuff == '5')
    {
        channel = '5';
        if (*(pBuff + 1) == 0)
        {
            pc->channel = '5';
        }
        pBuff++;
    }
    else if (*pBuff == '6')
    {
        channel = '6';
        if (*(pBuff + 1) == 0)
        {
            pc->channel = '6';
        }
        pBuff++;
    }
    else if (*pBuff == '7')
    {
        channel = '7';
        if (*(pBuff + 1) == 0)
        {
            pc->channel = '7';
        }
        pBuff++;
    }
    else if (*pBuff == '8')
    {
        channel = '8';
        if (*(pBuff + 1) == 0)
        {
            pc->channel = '8';
        }
        pBuff++;
    }
    else if (*pBuff == '9')
    {
        channel = '9';
        if (*(pBuff + 1) == 0)
        {
            pc->channel = '9';
        }
        pBuff++;
    }
	else
	{
	    /* Do nothing */
	}

    if (*pBuff == '\0') 
    {
        pc->err = 0;
    }
    else
    {
        while (CmdTable->Ptr.wptr != 0 && end == 0) 
        {
            for (i = 0, pArg = pBuff; 1; pArg++, i++) 
            {
                if (CmdTable->pName[i] == '\0' && (*pArg == ' ' || *pArg == '\0')) 
                {
                    pc->err = 0;
                    end = 1;		/* Command is found */
                    while (*pArg == ' ' || *pArg == '=') 
                        pArg++; 
                
                    if (*pArg == '\0') 
                    {   /* Command with no argument */
                        switch (CmdTable->CmdCode)
                        {
                        case CC_RW_WORD: 
                        case CC_RO_WORD: 
                            switch(channel)
                            {
                                case '1':
                                    print_dec(pc, (long)(unsigned short)*CmdTable->Ptr.wptr);
                                    break;
                                case '2':
                                    print_dec(pc, (long)(unsigned short)*CmdTable->Ptr2.wptr);
                                    break;
                                case '3':
                                    print_dec(pc, (long)(unsigned short)*CmdTable->Ptr3.wptr);
                                    break;
                                case '4':
                                    print_dec(pc, (long)(unsigned short)*CmdTable->Ptr4.wptr);
                                    break;
                                case '5':
                                    print_dec(pc, (long)(unsigned short)*CmdTable->Ptr5.wptr);
                                    break;
                                case '6':
                                    print_dec(pc, (long)(unsigned short)*CmdTable->Ptr6.wptr);
                                    break;
                                case '7':
                                    print_dec(pc, (long)(unsigned short)*CmdTable->Ptr7.wptr);
                                    break;
                                case '8':
                                    print_dec(pc, (long)(unsigned short)*CmdTable->Ptr8.wptr);
                                    break;
                                case '9':
                                    print_dec(pc, (long)(unsigned short)*CmdTable->Ptr9.wptr);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case CC_RW_INT: 
                        case CC_RO_INT: 
                            switch(channel)
                            {
                                case '1':
                                    print_dec(pc, (long) *CmdTable->Ptr.wptr);
                                    break;
                                case '2':
                                    print_dec(pc, (long) *CmdTable->Ptr2.wptr);
                                    break;
                                case '3':
                                    print_dec(pc, (long) *CmdTable->Ptr3.wptr);
                                    break;
                                case '4':
                                    print_dec(pc, (long) *CmdTable->Ptr4.wptr);
                                    break;
                                case '5':
                                    print_dec(pc, (long) *CmdTable->Ptr5.wptr);
                                    break;
                                case '6':
                                    print_dec(pc, (long) *CmdTable->Ptr6.wptr);
                                    break;
                                case '7':
                                    print_dec(pc, (long) *CmdTable->Ptr7.wptr);
                                    break;
                                case '8':
                                    print_dec(pc, (long) *CmdTable->Ptr8.wptr);
                                    break;
                                case '9':
                                    print_dec(pc, (long) *CmdTable->Ptr9.wptr);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case CC_RW_LONG: 
                        case CC_RO_LONG: 
                            switch(channel)
                            {
                                case '1':
                                    print_dec(pc, *CmdTable->Ptr.lptr);
                                    break;
                                case '2':
                                    print_dec(pc, *CmdTable->Ptr2.lptr);
                                    break;
                                case '3':
                                    print_dec(pc, *CmdTable->Ptr3.lptr);
                                    break;
                                case '4':
                                    print_dec(pc, *CmdTable->Ptr4.lptr);
                                    break;
                                case '5':
                                    print_dec(pc, *CmdTable->Ptr5.lptr);
                                    break;
                                case '6':
                                    print_dec(pc, *CmdTable->Ptr6.lptr);
                                    break;
                                case '7':
                                    print_dec(pc, *CmdTable->Ptr7.lptr);
                                    break;
                                case '8':
                                    print_dec(pc, *CmdTable->Ptr8.lptr);
                                    break;
                                case '9':
                                    print_dec(pc, *CmdTable->Ptr9.lptr);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case CC_FUNC: 
                        case CC_FUNC_OA: 
                            pc->set = 0;
                            switch(channel)
                            {
                                case '1':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[0]);
                                    break;
                                case '2':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[1]);
                                    break;
                                case '3':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[2]);
                                    break;
                                case '4':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[3]);
                                    break;
                                case '5':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[4]);
                                    break;
                                case '6':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[5]);
                                    break;
                                case '7':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[6]);
                                    break;
                                case '8':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[7]);
                                    break;
                                case '9':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[8]);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case CC_RO_HEX:
                        case CC_RW_HEX:
                            switch(channel)
                            {
                                case '1':
                                    print_hex(pc, *CmdTable->Ptr.wptr);
                                    break;
                                case '2':
                                    print_hex(pc, *CmdTable->Ptr2.wptr);
                                    break;
                                case '3':
                                    print_hex(pc, *CmdTable->Ptr3.wptr);
                                    break;
                                case '4':
                                    print_hex(pc, *CmdTable->Ptr4.wptr);
                                    break;
                                case '5':
                                    print_hex(pc, *CmdTable->Ptr5.wptr);
                                    break;
                                case '6':
                                    print_hex(pc, *CmdTable->Ptr6.wptr);
                                    break;
                                case '7':
                                    print_hex(pc, *CmdTable->Ptr7.wptr);
                                    break;
                                case '8':
                                    print_hex(pc, *CmdTable->Ptr8.wptr);
                                    break;
                                case '9':
                                    print_hex(pc, *CmdTable->Ptr9.wptr);
                                    break;
                                default:
                                    break;
                            }
                            break;   
                        case CC_RO_LONG_HEX:
                            switch(channel)
                            {
                                case '1':
                                    print_hex2(pc, *CmdTable->Ptr.lptr);
                                    break;
                                case '2':
                                    print_hex2(pc, *CmdTable->Ptr2.lptr);
                                    break;
                                case '3':
                                    print_hex2(pc, *CmdTable->Ptr3.lptr);
                                    break;
                                case '4':
                                    print_hex2(pc, *CmdTable->Ptr4.lptr);
                                    break;
                                case '5':
                                    print_hex2(pc, *CmdTable->Ptr5.lptr);
                                    break;
                                case '6':
                                    print_hex2(pc, *CmdTable->Ptr6.lptr);
                                    break;
                                case '7':
                                    print_hex2(pc, *CmdTable->Ptr7.lptr);
                                    break;
                                case '8':
                                    print_hex2(pc, *CmdTable->Ptr8.lptr);
                                    break;
                                case '9':
                                    print_hex2(pc, *CmdTable->Ptr9.lptr);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        default:
                            break;
                        }
                    } 
                    else 
                    {   /* Command with argument */
                        long v = strtol((const char *)pArg, NULL, 0);
                        switch (CmdTable->CmdCode) 
                        {
                        case CC_RW_INT: 
                        case CC_RW_WORD: 
                        case CC_RW_HEX:
                            switch(channel)
                            {
                                case '1':
                                    *CmdTable->Ptr.wptr = (unsigned short) v;
                                    break;
                                case '2':
                                    *CmdTable->Ptr2.wptr = (unsigned short) v;
                                    break;
                                case '3':
                                    *CmdTable->Ptr3.wptr = (unsigned short) v;
                                    break;
                                case '4':
                                    *CmdTable->Ptr4.wptr = (unsigned short) v;
                                    break;
                                case '5':
                                    *CmdTable->Ptr5.wptr = (unsigned short) v;
                                    break;
                                case '6':
                                    *CmdTable->Ptr6.wptr = (unsigned short) v;
                                    break;
                                case '7':
                                    *CmdTable->Ptr7.wptr = (unsigned short) v;
                                    break;
                                case '8':
                                    *CmdTable->Ptr8.wptr = (unsigned short) v;
                                    break;
                                case '9':
                                    *CmdTable->Ptr9.wptr = (unsigned short) v;
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case CC_RW_LONG: 
                            switch(channel)
                            {
                                case '1':
                                    *CmdTable->Ptr.lptr = v;
                                    break;
                                case '2':
                                    *CmdTable->Ptr2.lptr = v;
                                    break;
                                case '3':
                                    *CmdTable->Ptr3.lptr = v;
                                    break;
                                case '4':
                                    *CmdTable->Ptr4.lptr = v;
                                    break;
                                case '5':
                                    *CmdTable->Ptr5.lptr = v;
                                    break;
                                case '6':
                                    *CmdTable->Ptr6.lptr = v;
                                    break;
                                case '7':
                                    *CmdTable->Ptr7.lptr = v;
                                    break;
                                case '8':
                                    *CmdTable->Ptr8.lptr = v;
                                    break;
                                case '9':
                                    *CmdTable->Ptr9.lptr = v;
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case CC_FUNC_OA: 
                            pc->set = 1;
                            pc->arg = v;
                            switch(channel)
                            {
                                case '1':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[0]);
                                    break;
                                case '2':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[1]);
                                    break;
                                case '3':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[2]);
                                    break;
                                case '4':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[3]);
                                    break;
                                case '5':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[4]);
                                    break;
                                case '6':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[5]);
                                    break;
                                case '7':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[6]);
                                    break;
                                case '8':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[7]);
                                    break;
                                case '9':
                                    (CmdTable->Ptr.fptr)(pc, &g_st_m[8]);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case CC_FUNC_PVT:             /* RZ/T2 add */
                            pc->set = 1;
                            switch(channel)
                            {
                                case '1':
                                    (CmdTable->Ptr.fptr)(pc,&g_st_m[0]);
                                    break;
                                case '2':
                                    (CmdTable->Ptr.fptr)(pc,&g_st_m[1]);
                                    break;
                                case '3':
                                    (CmdTable->Ptr.fptr)(pc,&g_st_m[2]);
                                    break;
                                case '4':
                                    (CmdTable->Ptr.fptr)(pc,&g_st_m[3]);
                                    break;
                                case '5':
                                    (CmdTable->Ptr.fptr)(pc,&g_st_m[4]);
                                    break;
                                case '6':
                                    (CmdTable->Ptr.fptr)(pc,&g_st_m[5]);
                                    break;
                                case '7':
                                    (CmdTable->Ptr.fptr)(pc,&g_st_m[6]);
                                    break;
                                case '8':
                                    (CmdTable->Ptr.fptr)(pc,&g_st_m[7]);
                                    break;
                                case '9':
                                    (CmdTable->Ptr.fptr)(pc,&g_st_m[8]);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                }
                if (toupper (*pArg) != CmdTable->pName[i])
                    break;   
            }
            CmdTable++;
        }
    }
    /* Print Prompt */
    *(pc->ptx++) = 13;
    *(pc->ptx++) = 10;
    *(pc->ptx++) = pc->channel;
    *(pc->ptx++) = pc->err == 0 ? '>' : '?';
    pc->tx_count += 4;
}

void m_interpreter(t_console *pc)
{
    /* Setup output buffer */
    pc->ptx = pc->tx_buf;
    pc->tx_count = 0;
    
    /* Parse Command and Invoke Command Handler */
    if (pc->cmd_req == PTR_PACKET)       /* Binary / Packet Based Protocol */
    {
        /* Do Nothing */
    }
    else if (pc->cmd_req == PTR_ASCII)  /* ASCII Based Protocol */
    {
        protocol_ascii(pc);
    }
    else                                /* Invalid protocol type */
    {
        return;
    }
    
    print_buff(pc);
    
    /* Clear Receive Buffer and Command Request flag */
    pc->prx = pc->rx_buf;
    pc->rx_count = 0;
    pc->cmd_req = PTR_NONE;
    pc->pkt_state = PS_IDLE;
}

