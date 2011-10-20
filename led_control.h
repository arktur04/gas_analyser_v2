/***************************************************************************
 **
 **    This file defines the LED control definitions
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyleft
 **
 ***************************************************************************/
#ifndef __LED_CONTROL_H
#define __LED_CONTROL_H

#define OFF   0
#define ON    1
#define BLINK 2
#define FAST_BLINK  3

#define DISP_LED_L_STATE 0     
#define DISP_LED_L_TR1   1
#define DISP_LED_L_TR2   2
#define DISP_LED_L_ENC   3
#define DISP_LED_R_STATE 4
#define DISP_LED_R_TR1   5
#define DISP_LED_R_TR2   6
#define DISP_LED_R_ENC   7

//-------------------------------
#define SYS_TRG_RES_L 0
#define SYS_TRG_RES_R 1
/*
#define SYS_ADC0_CLK  2
#define SYS_ADC1_CLK  3
#define SYS_ADC2_CLK  4
#define SYS_ADC3_CLK  5
#define SYS_ADC_MOSI  6
#define SYS_RES0      7
*/
#define SYS_LED_ADC0  8
#define SYS_LED_ADC1  9
#define SYS_LED_ADC2  10
#define SYS_LED_ADC3  11
#define SYS_OPEN_NET_1  12
#define SYS_OPEN_NET_2  13
#define SYS_SHORT_NET_1 14
#define SYS_SHORT_NET_1 15

#define SYS_LED_DOUT0 16
#define SYS_LED_DOUT1 17
#define SYS_LED_DOUT2 18
#define SYS_LED_DOUT3 19
#define SYS_LED_DOUT4 20
#define SYS_LED_DOUT5 21
#define SYS_RES5      22
#define SYS_RES6      23

#define SYS_LED_RS232TX 24
#define SYS_LED_RS232RX 25
#define SYS_LED_RS485TX 26
#define SYS_LED_RS485RX 27

void SetDispLedState(char led, char state);
void SetSysSpiBusState(char led, char state);
void UpdateSysBus(void);
void ProcessLeds(void);

void SetSysBit(char bit_num);
void ClrSysBit(char bit_num);
void ProcessSysState(void);

#endif /* __LED_CONTROL_H */
