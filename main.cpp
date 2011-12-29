/*************************************************************************
*    Main.cpp
**************************************************************************/
#define INIT_WDT 
#define _DEBUG_PIN

extern "C"{
#include <intrinsics.h>
#include <stdio.h>
#include <nxp/iolpc1768.h>
#include <assert.h>
  
#include "type.h"
//#include "uart.h"
#include "irq.h"
#include "board.h"  
    
#include "LPC_Uart.h"
#include "timers.h"
//#include "target.h"
#include "lcd.h"
#include "font.h"
#include "lcd_low_level.h"
#include "keyb.h"
#include "bmps.h"
#include "checkbox.h"
#include "adc_fsm.h"
#include "dict.h"
#include "variables.h"
//#include "message_window.h"
//#include "password_screen.h"
#include "pass_controller.h"
#include "messages.h"
#include "led_control.h"
#include "relay_control.h"
#include "modbus.h"
#include "disconnect.h"
#include "lcd_control.h"
#include "power_control.h"
#include "current_outs.h"
};
#include <math.h>

#include "usbase.h"
#include "main_scr.h"
#include "menu_scr.h"
#include "param_scr.h"
#include "lut_scr.h"
#include "do_test.h"
#include "ao_test.h"
#include "ai_test.h"
#include "pwm_test.h"
#include "rs232_scr.h"
#include "rs485_scr.h"
#include "ethernet_scr.h"
#include "trend_scr.h"
#include "misc_scr.h"
#include "twocolscr.h"
#include "calibr_out_scr.h"
#include "msg_scr.h"
#include "pass_scr.h"
#include "editor_scr.h"
#include "processing.h"

//*************************************************************************
// * Function Name: TMR0_IRQHandler
// * Parameters: none
// *
// * Return: none
// *
// * Description: Timer 0 interrupt handler
// *
// *************************************************************************

extern "C" void TMR0_IRQHandler (void)
{
  ProcessTimers();
  //clear interrupt 
  T0IR_bit.MR0INT = 1;

  NVIC_ClrPend(NVIC_TIMER0);
}

/*************************************************************************
 * Function Name: TMR1_IRQHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: Timer 1 interrupt handler
 *
 *************************************************************************/
extern "C" void TMR1_IRQHandler (void)
{
  /* Toggle LED1 */
 // LED1_FIO ^= LED1_MASK;
  ProcessTimer1();
  /*clear interrupt */
  T1IR_bit.MR0INT = 1;
  /**/
  NVIC_ClrPend(NVIC_TIMER1);
}

/*************************************************************************
 * Function Name: TMR2_IRQHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: Timer 2 interrupt handler
 *
 *************************************************************************/
extern "C" void TMR2_IRQHandler (void)
{
  /* Toggle LED1 */
  //LED1_FIO ^= LED1_MASK;
  ProcessTimer2();
  /*clear interrupt */
  T2IR_bit.MR0INT = 1;
  /**/
  NVIC_ClrPend(NVIC_TIMER2);
}
/*************************************************************************
 * Function Name: TMR3_IRQHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: Timer 2 interrupt handler
 *
 *************************************************************************/
/*
extern "C" void TMR3_IRQHandler (void)
{
  // Toggle LED1 
  //LED1_FIO ^= LED1_MASK;
  ProcessTimer3();
  //clear interrupt 
  T3IR_bit.MR0INT = 1;
  
  NVIC_ClrPend(NVIC_TIMER3);
}
*/
unsigned long * pSHPR3 = (unsigned long *)0xE000ED20;

//  Modbus messages 

union DATAADDR{
  WRITEMULTIPLEDATA*modbus_data;
  unsigned long param;
};

void onMsgReadHoldings(unsigned long param, char uartNum)
{
  unsigned long start_addr, num;
  unsigned short * preadholdingdata; 
  
  start_addr = (param & 0xFFFF0000) >> 16;
  num = (param & 0x0000FFFFUL);
  
  preadholdingdata = new unsigned short[num];
  for(int i = 0; i < num; i++)
    GetDataByModbusAddr(start_addr + i, &preadholdingdata[i]);
  
  ReadMultipleHoldingsAnswer(start_addr, num, preadholdingdata, uartNum);
  delete[] preadholdingdata;
}

void onMsgWriteSingleHolding(unsigned long param, char uartNum)
{
  unsigned long  start_addr;
  unsigned short value;
  
  start_addr = (param & 0xFFFF0000) >> 16;
  value = (param & 0xFFFF);
  
  SetDataByModbusAddr(start_addr, value);
  WriteSingleRegisterAnswer(start_addr, value, uartNum);
}

void onMsgWriteMultipleHoldings(unsigned long param, char uartNum)
{
  unsigned short start_addr, num;
  char data_len;
  DATAADDR data_addr;
  
  data_addr.param = param;
  start_addr = data_addr.modbus_data->start_addr;
  num = data_addr.modbus_data->num;
  data_len = data_addr.modbus_data->data_len;
  
  if(data_len)
    for(int i = 0; i < num; i++)
      SetDataByModbusAddr(start_addr + i, 
                          data_addr.modbus_data->data[i]);// % data_len]);
  
  WriteMultipleHoldingsAnswer(start_addr, num, uartNum);
  DataUnlock();
}

void onMsgPrintScreen(char uartNum)
{
  WritePrintScreenAnswer(GetVideoBuff(), uartNum);
}
/*************************************************************************
 * Function Name: main
 * Parameters: none
 *
 * Return: none
 *
 * Description: main
 *
 *************************************************************************/
 int main(void)
{
  TargetResetInit();
  //InitSemaphores();
  ProcessInit();
  NVIC_IntPri(NVIC_RIT, 1 << 3);                //changed from 4 << 3
  *(pSHPR3 + 3) = 0;
  NVIC_IntPri(NVIC_TIMER0, 2 << 3);
  NVIC_IntPri(NVIC_TIMER1, 3 << 3);
  NVIC_IntPri(NVIC_TIMER2, 3 << 3);
  NVIC_IntPri(NVIC_UART0, 5 << 3);
  NVIC_IntPri(NVIC_UART1, 5 << 3);
  
  InitSysTick();          //Key, pr = 0
  InitRepetitiveTimer();  //DSP, pr = 1
  
  InitTimer0();           //sys tick, pr = 2

  InitTimer1();  //left pwm, pr = 3
  InitTimer2();  //right pwm, pr = 3
  
  Uart0Init();
  Uart1Init();
  
  SetUart0RxHandler(ModbusRxHandler0);
  SetUart1RxHandler(ModbusRxHandler1);
  
#ifdef DEBUG_PIN
  initDebugPin();
#endif
  
  __enable_interrupt();

//  TargetResetInit();

  LcdInitPio();
  BoardInit();
  SysSpiInitPio();
  DacInitPio();
  AdcInitPio();
  PwmInitPio();

//  DebugInitPio();

  LcdInitModule();
  
  LcdClear();
  LcdDraw();

 // OutputSet(LCD_LED);

  InitMessages();
  initKeyb();
 // InitCursor();
  initAdcFsm();
  
  InitDisconn();
  InitPowerControl();

  //SendMessage(MSG_MAIN_SCREEN_ACTIVATE);      
 
  LoadValuesFromFram();
  SetIntValueByTag(DAC_TEST_FLAG, FALSE);

  unsigned long param;
  int btn_num;
  
  usSystemInit(); //usLib init
  
      //     SendMessage(MSG_VAR_CHANGED);                                          //test purpouse only!
  
  MainScreen* mainscreen = new MainScreen();       
  EditorScreen* editorscreen = NULL;
 
  MenuScreen* menuscreen;
    
  ParamScreen* paramscreen;
  LutScreen* lutscreen;
  
  Rs232Screen*rs232_screen;
  Rs485Screen*rs485_screen;
  EthernetScreen*ethernet_screen;
  
  DoTestScreen*do_testcreen;
  AiTestScreen*ai_testscreen;
  AoTestScreen*ao_testscreen;
  PwmTestScreen*pwm_testscreen;
  CalibrOutScreen*calibr_out_screen;
    
  TrendScreen*trend_screen;
  
  MessageWindow*def_warn_scr;
  PassScreen*pass_screen;
  
  MiscScreen*misc_screen;
  
  TwoColScr*calibr_screen;// = new TwoColScr(22, SCR_TC_CALIBR_L);                                                         //temp
  
 // ai_testscreen = new AiTestScreen();                                                 //only for test
 // def_warn_scr = new MessageWindow(OK_CANCEL_MSW);
 // pass_screen = new PassScreen();
  
 // SetDefaultValues();                                                                //debug
  SetFloatValueByTag(T_CL_E, ReadTemp());
  
 // UART_PutStringByPolling(UART0, "foobar\n\r");                                       //debug
  
    //Enable NVIC TMR0 Interrupt
  NVIC_IntEnable(NVIC_TIMER0);
  NVIC_IntEnable(NVIC_RIT);
    //Enable NVIC TMR0 Interrupt
  NVIC_IntEnable(NVIC_TIMER1);
    //Enable NVIC TMR0 Interrupt
  NVIC_IntEnable(NVIC_TIMER2);
    //Enable NVIC TMR0 Interrupt
 // NVIC_IntEnable(NVIC_TIMER3);
#ifdef INIT_WDT
  InitWdt();   
#endif
  while(1)
  {
    ProcessPassController();
    /*
    if(GetMessage(MSG_PASSWORD_SCREEN_ACTIVATE))
    {
      pass_screen = new PassScreen();
    };*/
    
    // relay test mode
    
    if(GetIntValueByTag(RELAY_OUT_TEST_FLAG))
    {
      SetRelayState(RELAY_0, GetIntValueByTag(RELAY_OUT_0)?ON:OFF);  
      SetRelayState(RELAY_1, GetIntValueByTag(RELAY_OUT_1)?ON:OFF);
      SetRelayState(RELAY_2, GetIntValueByTag(RELAY_OUT_2)?ON:OFF);
      SetRelayState(RELAY_3, GetIntValueByTag(RELAY_OUT_3)?ON:OFF);
      SetRelayState(RELAY_4, GetIntValueByTag(RELAY_OUT_4)?ON:OFF);
      SetRelayState(RELAY_5, GetIntValueByTag(RELAY_OUT_5)?ON:OFF);
    }
    else
    {
      SetRelayState(RELAY_0, GetIntValueByTag(FLT_GA_L)?ON:OFF);
      SetRelayState(RELAY_1, GetIntValueByTag(FTH_O2_L)?ON:OFF);
      SetRelayState(RELAY_2, GetIntValueByTag(FTH_H_L)?ON:OFF);    
      SetRelayState(RELAY_3, GetIntValueByTag(FLT_GA_R)?ON:OFF);
      SetRelayState(RELAY_4, GetIntValueByTag(FTH_O2_R)?ON:OFF);
      SetRelayState(RELAY_5, GetIntValueByTag(FTH_H_R)?ON:OFF);        
    };  
    LoadProcessingVariables();
    // pwm test mode
    
    {
      unsigned int pwmWidthLeft, pwmWidthRight;
      if(GetIntValueByTag(PWM_OUT_TEST_FLAG))
      {
        pwmWidthLeft = GetIntValueByTag(PWM_1);
        pwmWidthRight = GetIntValueByTag(PWM_2);
      }
      else
      {
        pwmWidthLeft = GetIntValueByTag(CLC_LI_T_L);
        pwmWidthRight = GetIntValueByTag(CLC_LI_T_R);
      };
      
      setTimer1Width(pwmWidthLeft,
                     GetIntValueByTag(FLT_TP_L),
                     GetIntValueByTag(FLT_NE_L),
                     GetIntValueByTag(PWM0_ON)?TRUE:FALSE
                     );
      setTimer2Width(pwmWidthRight,
                     GetIntValueByTag(FLT_TP_R),
                     GetIntValueByTag(FLT_NE_R),
                     GetIntValueByTag(PWM1_ON)?TRUE:FALSE);                     
     
//     setTimer1Width(GetIntValueByTag(PWM2),
//                     (char)(GetIntValueByTag(FLT_TP_R) != 0),
//                     (char)(GetIntValueByTag(FLT_NE_R) != 0);
//    }
//    else
//    {
//      SetTimer1Width(GetIntValueByTag(CLC_LI_T_L));                                                               //debug
//      SetTimer2Width(GetIntValueByTag(CLC_LI_T_R));                                                               //debug
//    };
    };
    //---------------------------------------

    for(char i = 0; i < 4; i++)
      ProcessDisconn(i);
    
    SetSysSpiBusState(SYS_LED_ADC0, GetIntValueByTag(FLT_TP_L)?ON:OFF);
    SetSysSpiBusState(SYS_LED_ADC1, GetIntValueByTag(FLT_CH_L)?ON:OFF);
    SetSysSpiBusState(SYS_LED_ADC2, GetIntValueByTag(FLT_TP_R)?ON:OFF);
    SetSysSpiBusState(SYS_LED_ADC3, GetIntValueByTag(FLT_CH_R)?ON:OFF);
    
    SetSysSpiBusState(SYS_OPEN_NET_1, GetIntValueByTag(FLT_NE_L)?ON:OFF);
    SetSysSpiBusState(SYS_OPEN_NET_2, GetIntValueByTag(FLT_NE_R)?ON:OFF);
     
    //--------------------------------------------------------------------------
    if(GetTimer(TEMP_SENS_TIMER) > 50)
    {
      SetFloatValueByTag(T_CL_E, ReadTemp());
      ResetTimer(TEMP_SENS_TIMER);
    };
    
   // ProcessMessageWindow();                                                            //temp del
   // ProcessPassController();                                                           //temp del
  //  ProcessCursor();
    processKeyb();
    //----------------------------------------
    if(GetMessage(MSG_L_ENCODER_PRESSED))  //key substitution
    {
      SendParamMessage(MSG_KEYPRESSED, KEY_ENTER);
    };
    //----------------------------------------
    ProcessLeds();
    ProcessLcdControl();
    //-----------------------------------
    (getSystemCursor())->Process();
                                          ProcessSysState();
 //   mainscreen->Process();

  //  (GetProcessing())->Process(); 
    
    if(GetParamMessage(MSG_BTN_MENU, &param))
    {
      btn_num = param & 0x0F;
      switch((param & 0xF0) >> 4)
      {
      case 0:
        switch(btn_num)
        {
        case 0:
          paramscreen = new ParamScreen(0, SCR_THERM_L_0);
          break;
        case 1:
          paramscreen = new ParamScreen(3, SCR_THERM_R_0);
          break;
        case 2:
          paramscreen = new ParamScreen(6, SCR_O2_L_0);
          break;
        case 3:
          paramscreen = new ParamScreen(9, SCR_O2_R_0);
          break;
        case 4:
          paramscreen = new ParamScreen(12, SCR_HN_L_0);
          break;
        case 5:
          paramscreen = new ParamScreen(16, SCR_HN_R_0);
          break;
        case 6:
          paramscreen = new ParamScreen(20, SCR_TH_L);
          break;
        case 7:
          paramscreen = new ParamScreen(21, SCR_TH_R);
          break;          
        case 8:
          if(!EditAllowed() || getPasswordEntered())                                                                    //!!!!!!!!!!!!!!
          {
            pass_screen = new PassScreen();
          };
          break;                
        case 9:
          break;
        };
        break;
      case 1:
        switch(btn_num)
        {
        case 0:
          do_testcreen = new DoTestScreen();//(0, SCR_RS232);
          break;
        case 1:
          ai_testscreen = new AiTestScreen();
          break;
        case 2:
          ao_testscreen = new AoTestScreen();
          break;
        case 3:
          pwm_testscreen = new PwmTestScreen();
          break;
        };
        break;        
      case 2:
        {
          switch(btn_num)
          {
          case 0:
            calibr_screen =  new TwoColScr(24, SCR_TC_CALIBR_L);
            break;
          case 1:
            calibr_screen = new TwoColScr(25, SCR_TC_CALIBR_R);
            break;
          case 2:
            calibr_screen = new TwoColScr(26, SCR_CH_CALIBR_L);
            break;
          case 3:
            calibr_screen = new TwoColScr(27, SCR_CH_CALIBR_R);
            break;
          case 4:
            calibr_out_screen = new CalibrOutScreen();// TwoColScr(26, SCR_OUT_CALIBR);
            break;
          };
        };
        break;
      case 3:
        switch(btn_num)
        {
        case 0:
          rs232_screen = new Rs232Screen();//(0, SCR_RS232);
          break;
        case 1:
          rs485_screen = new Rs485Screen();
          break;
        case 2:
          ethernet_screen = new EthernetScreen();
          break;
        };
        break;
      case 4:
        switch(btn_num)
        {
        case 0:
          def_warn_scr = new MessageWindow(OK_CANCEL_MSW, 
                                           "Внимание!", 
                                           "Все переменные", 
                                           "будут сброшены", 
                                           "в начальное состояние");
          break;
        case 1:
          paramscreen = new ParamScreen(22, SCR_RES_THR_0);
          break;
//        case 2:
//          trend_screen = new TrendScreen(DEBUG_1, 500.0, 800.0, SCR_TREND_L);//(0, SCR_RS232);  //check the tag!
//          break;
//        case 3:
//          trend_screen = new TrendScreen(DEBUG_2, 500.0, 800.0, SCR_TREND_R);                   //check the tag!
//          break;
        case 2:                                // changed from: case 4:         
          misc_screen = new MiscScreen();
          break;
        }
        break;
      };
    };
    
    if(GetMessage(MSG_MAIN_SCREEN_DEACTIVATED))
    {
      menuscreen = new MenuScreen(0, SCR_MENU_0);
    };
    
    if(GetParamMessage(MSG_BTN_FORWARD, &param))
    {
      switch(param){
        //case SCR_MAIN   
      case SCR_MENU_0:
         menuscreen = new MenuScreen(1, SCR_MENU_1);
        break;
      case SCR_MENU_1:
        menuscreen = new MenuScreen(2, SCR_MENU_2);
        break;
      case SCR_MENU_2:
        menuscreen = new MenuScreen(3, SCR_MENU_3);
        break;
      case SCR_MENU_3:
        menuscreen = new MenuScreen(4, SCR_MENU_4);
        break;        
      case SCR_MENU_4:
        paramscreen = new ParamScreen(0, SCR_THERM_L_0);
        break;
        
      case SCR_THERM_L_0:
        paramscreen = new ParamScreen(1, SCR_THERM_L_1);
        break;
      case SCR_THERM_L_1:
        paramscreen = new ParamScreen(2, SCR_THERM_L_2);
        break;
      case SCR_THERM_L_2:
        paramscreen = new ParamScreen(3, SCR_THERM_R_0);
        break;
        
      case SCR_THERM_R_0:
        paramscreen = new ParamScreen(4, SCR_THERM_R_1);
        break;
      case SCR_THERM_R_1:
        paramscreen = new ParamScreen(5, SCR_THERM_R_2);
        break;
      case SCR_THERM_R_2:
        paramscreen = new ParamScreen(6, SCR_O2_L_0);
        break;
        
      case SCR_O2_L_0:
        lutscreen = new LutScreen(7, SCR_O2_L_1);
        break;
      case SCR_O2_L_1:
        paramscreen = new ParamScreen(8, SCR_O2_L_2);
        break;
      case SCR_O2_L_2:
        paramscreen = new ParamScreen(9, SCR_O2_R_0);
        break;
        
      case SCR_O2_R_0:
        lutscreen = new LutScreen(10, SCR_O2_R_1);
        break;
      case SCR_O2_R_1:
        paramscreen = new ParamScreen(11, SCR_O2_R_2);
        break;
      case SCR_O2_R_2:
        paramscreen = new ParamScreen(12, SCR_HN_L_0);
        break;
        
      case SCR_HN_L_0:
        paramscreen = new ParamScreen(13, SCR_HN_L_1);
        break;
      case SCR_HN_L_1:
        lutscreen = new LutScreen(14, SCR_HN_L_2);
        break;
      case SCR_HN_L_2:
        paramscreen = new ParamScreen(15, SCR_HN_L_3);
        break;
      case SCR_HN_L_3:
        paramscreen = new ParamScreen(16, SCR_HN_R_0);
        break;
        
      case SCR_HN_R_0:
        paramscreen = new ParamScreen(17, SCR_HN_R_1);
        break;
      case SCR_HN_R_1:
        lutscreen = new LutScreen(18, SCR_HN_R_2);
        break;
      case SCR_HN_R_2:
        paramscreen = new ParamScreen(19, SCR_HN_R_3);
        break;
      case SCR_HN_R_3:
        paramscreen = new ParamScreen(20, SCR_TH_L);
        break;
        
      case SCR_TH_L:
        paramscreen = new ParamScreen(21, SCR_TH_R);
        break;
      case SCR_TH_R:
        rs232_screen = new Rs232Screen();
        break;
      case SCR_RS232:
        rs485_screen = new Rs485Screen();
        break;
      case SCR_RS485:
        ethernet_screen = new EthernetScreen();
        break;
      case SCR_ETHERNET:
        do_testcreen = new DoTestScreen();
        break;
      case SCR_DO_TEST:
        ai_testscreen = new AiTestScreen();
        break;
      case SCR_AI_TEST:
        ao_testscreen = new AoTestScreen();
        break;
      case SCR_AO_TEST:
        pwm_testscreen = new PwmTestScreen();
        break;
      case SCR_PWM_TEST:
        calibr_screen =  new TwoColScr(24, SCR_TC_CALIBR_L);
        break;
      case SCR_TC_CALIBR_L:
        calibr_screen =  new TwoColScr(25, SCR_TC_CALIBR_R);
        break;
      case SCR_TC_CALIBR_R:
         calibr_screen =  new TwoColScr(26, SCR_CH_CALIBR_L);
        break;
      case SCR_CH_CALIBR_L:
         calibr_screen =  new TwoColScr(27, SCR_CH_CALIBR_R);
        break;
      case SCR_CH_CALIBR_R:
        calibr_out_screen = new CalibrOutScreen(); //TwoColScr(26, SCR_OUT_CALIBR);
        break;
      case SCR_OUT_CALIBR:
        paramscreen = new ParamScreen(22, SCR_RES_THR_0);
        break;
      case SCR_RES_THR_0:
        paramscreen = new ParamScreen(23, SCR_RES_THR_1);
        break;
        //----------------------------------------------------------------------
      case SCR_RES_THR_1:  // new variant
        misc_screen = new MiscScreen();
        break;  
//        //  old variant
//      case SCR_RES_THR_1:
//        trend_screen = new TrendScreen(DEBUG_1, 500.0, 800.0, SCR_TREND_L);
//        break;
//      case SCR_TREND_L:
//        trend_screen = new TrendScreen(DEBUG_2, 500.0, 800.0, SCR_TREND_R);
//        break;
//      case SCR_TREND_R:
//        misc_screen = new MiscScreen();
//        break;
//        
      };
    };
    if(GetParamMessage(MSG_BTN_HOME, &param))
    {
      mainscreen = new MainScreen();
    };
    
    if(GetParamMessage(MSG_BTN_BACKWARD, &param))
    {
      switch(param){
      case SCR_MENU_0:
        mainscreen = new MainScreen();
        break;
      case SCR_MENU_1:
        menuscreen = new MenuScreen(0, SCR_MENU_0);
        menuscreen->SetFocus(2);
        break;
      case SCR_MENU_2:
        menuscreen = new MenuScreen(1, SCR_MENU_1);
        menuscreen->SetFocus(2);
        break;
      case SCR_MENU_3:
        menuscreen = new MenuScreen(2, SCR_MENU_2);
        menuscreen->SetFocus(2);
        break;
      case SCR_MENU_4:
        menuscreen = new MenuScreen(3, SCR_MENU_3);
        menuscreen->SetFocus(2);
        break;        
      case SCR_THERM_L_0:
        menuscreen = new MenuScreen(4, SCR_MENU_4);
        menuscreen->SetFocus(2);
        break;
      case SCR_THERM_L_1:
        paramscreen = new ParamScreen(0, SCR_THERM_L_0);
        paramscreen->SetFocus(2);
        break;
      case SCR_THERM_L_2:
        paramscreen = new ParamScreen(1, SCR_THERM_L_1);
        paramscreen->SetFocus(2);
        break;
        
      case SCR_THERM_R_0:
        paramscreen = new ParamScreen(2, SCR_THERM_L_2);
        paramscreen->SetFocus(2);
        break;
      case SCR_THERM_R_1:
        paramscreen = new ParamScreen(3, SCR_THERM_R_0);
        paramscreen->SetFocus(2);
        break;
      case SCR_THERM_R_2:
        paramscreen = new ParamScreen(4, SCR_THERM_R_1);
        paramscreen->SetFocus(2);
        break;
        
      case SCR_O2_L_0:
        paramscreen = new ParamScreen(5, SCR_THERM_R_2);
        paramscreen->SetFocus(2);
        break;
      case SCR_O2_L_1:
        paramscreen = new ParamScreen(6, SCR_O2_L_0);
        paramscreen->SetFocus(2);
        break;
      case SCR_O2_L_2:
        lutscreen = new LutScreen(7, SCR_O2_L_1);
        lutscreen->SetFocus(2);
        break;
        
      case SCR_O2_R_0:
        paramscreen = new ParamScreen(8, SCR_O2_L_2);
        paramscreen->SetFocus(2);
        break;
      case SCR_O2_R_1:
        paramscreen = new ParamScreen(9, SCR_O2_R_0);
        paramscreen->SetFocus(2);
        break;
      case SCR_O2_R_2:
        lutscreen = new LutScreen(10, SCR_O2_R_1);
        lutscreen->SetFocus(2);
        break;        
        
      case SCR_HN_L_0:
        paramscreen = new ParamScreen(11, SCR_O2_R_2);
        paramscreen->SetFocus(2);
        break;
      case SCR_HN_L_1:
        paramscreen = new ParamScreen(12, SCR_HN_L_0);
        paramscreen->SetFocus(2);
        break;
      case SCR_HN_L_2:
        paramscreen = new ParamScreen(13, SCR_HN_L_1);
        paramscreen->SetFocus(2);
        break;
      case SCR_HN_L_3:
        lutscreen = new LutScreen(14, SCR_HN_L_2);
        lutscreen->SetFocus(2);
        break;
        
      case SCR_HN_R_0:
        paramscreen = new ParamScreen(15, SCR_HN_L_3);
        paramscreen->SetFocus(2);
        break;
      case SCR_HN_R_1:
        paramscreen = new ParamScreen(16, SCR_HN_R_0);
        paramscreen->SetFocus(2);
        break;
      case SCR_HN_R_2:
        paramscreen = new ParamScreen(17, SCR_HN_R_1);
        paramscreen->SetFocus(2);
        break;
      case SCR_HN_R_3:
        lutscreen = new LutScreen(18, SCR_HN_R_2);
        lutscreen->SetFocus(2);
        break;        
        
      case SCR_TH_L:
        paramscreen = new ParamScreen(19, SCR_HN_R_3);
        paramscreen->SetFocus(2);
        break;
      case SCR_TH_R:
        paramscreen = new ParamScreen(20, SCR_TH_L);
        paramscreen->SetFocus(2);
        break; 
      case SCR_RS232:
        paramscreen = new ParamScreen(21, SCR_TH_R);
        paramscreen->SetFocus(2);
        break;
      case SCR_RS485:
        rs232_screen = new Rs232Screen();
        rs232_screen->SetFocus(2);
        break;
      case SCR_ETHERNET:
        rs485_screen = new Rs485Screen();
        rs485_screen->SetFocus(2);
        break;
      case SCR_DO_TEST:
        ethernet_screen = new EthernetScreen();
        ethernet_screen->SetFocus(2);
        break;
      case SCR_AI_TEST:
        do_testcreen = new DoTestScreen();
        do_testcreen->SetFocus(2);
        break;
      case SCR_AO_TEST:
        ai_testscreen = new AiTestScreen();
        ai_testscreen->SetFocus(2);
        break;
      case SCR_PWM_TEST: 
        ao_testscreen = new AoTestScreen();
        ao_testscreen->SetFocus(2);
        break;
      case SCR_TC_CALIBR_L:
        pwm_testscreen = new PwmTestScreen();
        pwm_testscreen->SetFocus(2);
        break;
      case SCR_TC_CALIBR_R:
        calibr_screen =  new TwoColScr(24, SCR_TC_CALIBR_L);       
        calibr_screen->SetFocus(2); 
        break;
      case SCR_CH_CALIBR_L:
        calibr_screen =  new TwoColScr(25, SCR_TC_CALIBR_R);       
        calibr_screen->SetFocus(2);
        break;
      case SCR_CH_CALIBR_R:
        calibr_screen =  new TwoColScr(26, SCR_CH_CALIBR_L); 
        calibr_screen->SetFocus(2);
        break;
      case SCR_OUT_CALIBR:
        calibr_screen =  new TwoColScr(27, SCR_CH_CALIBR_R);
        calibr_screen->SetFocus(2);
        break;        
      case SCR_RES_THR_0:
        calibr_out_screen =  new CalibrOutScreen();//TwoColScr(26, SCR_OUT_CALIBR);
        calibr_out_screen->SetFocus(2);
        break;
      case SCR_RES_THR_1:
        paramscreen = new ParamScreen(22, SCR_RES_THR_0);
        paramscreen->SetFocus(2);
        break;  
      case SCR_MISC:
        paramscreen = new ParamScreen(23, SCR_RES_THR_1);
        paramscreen->SetFocus(2);
        break; 
//        
//      case SCR_TREND_L:
//        paramscreen = new ParamScreen(20, SCR_RES_THR_1);
//        paramscreen->SetFocus(2);
//        break;
//      case SCR_TREND_R:
//        trend_screen = new TrendScreen(DEBUG_1, 500.0, 800.0, SCR_TREND_L);
//        trend_screen->SetFocus(2);
//        break;
//      case SCR_MISC:
//        trend_screen = new TrendScreen(DEBUG_2, 500.0, 800.0, SCR_TREND_R);
//        trend_screen->SetFocus(2);
//        break; 
      };
    };                                                                                                            

    if(GetParamMessage(MSG_BTN_EDIT, &param))
    {
      if(EditAllowed() || getPasswordEntered())                                                                    //!!!!!!!!!!!!!!
      {
        editorscreen = new EditorScreen(param);
        SendParamMessage(MSG_EDITOR_SCREEN_ACTIVATE, param);
      }
      else
      {
        pass_screen = new PassScreen();
      };
    };
                                                                                                     
    if(GetParamMessage(MSG_CHECKBOX, &param))                                                                     
    {
      switch(param & 0xFFFFUL)
      {
      case RS_232_EVEN:
        break;
      case RS_232_ODD:
        break;

      case RS_485_EVEN:
        break;
      case RS_485_ODD:
        break;

      case RELAY_OUT_0:
      case RELAY_OUT_1:
      case RELAY_OUT_2:
      case RELAY_OUT_3:
      case RELAY_OUT_4:
      case RELAY_OUT_5:
        SetIntValueByTag(param & 0xFFFFUL, param & 0xFFFF0000);
        do_testcreen->Update();
        break;
      case PWM0_ON:
        SetIntValueByTag(PWM0_ON, param & 0xFFFF0000);
        break;
      case PWM1_ON:
        SetIntValueByTag(PWM1_ON, param & 0xFFFF0000);
        break;
      };
    };

    getScreenList()->Process();                                                   //temp
//------------------------------------------------------------------------------
//                         Modbus command
//------------------------------------------------------------------------------  
                                                                                                          
  if(GetParamMessage(MSG_UART0READHOLDINGS, &param))                                                          
    onMsgReadHoldings(param, 0);
  if(GetParamMessage(MSG_UART1READHOLDINGS, &param))
    onMsgReadHoldings(param, 1);
  if(GetParamMessage(MSG_UART0WRITESINGLEHOLDING, &param))
    onMsgWriteSingleHolding(param, 0);
  if(GetParamMessage(MSG_UART1WRITESINGLEHOLDING, &param))
    onMsgWriteSingleHolding(param, 1);  
  if(GetParamMessage(MSG_UART0WRITEMULTIPLEHOLDINGS, &param))
    onMsgWriteMultipleHoldings(param, 0);
  if(GetParamMessage(MSG_UART0WRITEMULTIPLEHOLDINGS, &param))
    onMsgWriteMultipleHoldings(param, 1); 
  if(GetParamMessage(MSG_UART0PRINTSCREEN, &param))
    onMsgPrintScreen(0);
  if(GetParamMessage(MSG_UART1PRINTSCREEN, &param))
    onMsgPrintScreen(1);                                                                                                        
//    unsigned long param;
//    unsigned short start_addr, num, value;
//    char data_len;
//    
//    union DATAADDR{
//      WRITEMULTIPLEDATA*modbus_data;
//      unsigned long param;
//    };
//    DATAADDR data_addr;
//    
//    unsigned short* preadholdingdata;
//    
//    if(GetParamMessage(MSG_UART0READHOLDINGS, &param))
//    {
//      start_addr = (param & 0xFFFF0000) >> 16;
//      num = (param & 0x0000FFFFUL);
//      
//      preadholdingdata = new unsigned short[num];
//      for(int i = 0; i < num; i++)
//        GetDataByModbusAddr(start_addr + i, &preadholdingdata[i]);
//        
//      ReadMultipleHoldingsAnswer(start_addr, num, preadholdingdata);
//      delete[] preadholdingdata;
//    };
//    
//    if(GetParamMessage(MSG_UART0WRITESINGLEHOLDING, &param))
//    {
//      start_addr = (param & 0xFFFF0000) >> 16;
//      value = (param & 0xFFFF);
//      
//      SetDataByModbusAddr(start_addr, value);
//      WriteSingleRegisterAnswer(start_addr, value);
//    };
//
//    if(GetParamMessage(MSG_UART0WRITEMULTIPLEREGS, &data_addr.param))
//    {   
//       //unsigned short start_addr;
//       // unsigned short num;
//       // char data_len;
//       // char* data[DATABUFSIZE];
//       
//      start_addr = data_addr.modbus_data->start_addr;
//      num = data_addr.modbus_data->num;
//      data_len = data_addr.modbus_data->data_len;
//      
//      if(data_len)
//        for(int i = 0; i < num; i++)
//          SetDataByModbusAddr(start_addr + i, 
//                              data_addr.modbus_data->data[i]);// % data_len]);
//
//      WriteMultipleHoldingsAnswer(start_addr, num);
//      DataUnlock();
//    };
//    
//    if(GetMessage(MSG_UART0PRINTSCREEN)) 
//    {
//      WritePrintScreenAnswer(GetVideoBuff());
//    };
//------------------------------------------------------------------------------                                                    
//  uarts led control logic
//------------------------------------------------------------------------------
                                                                                                                                  
    if(GetMessage(MSG_UART0_RX))                                                                                       
    {
      ResetTimer(TIMER_UART0_RX_LED);
      SetSysSpiBusState(SYS_LED_RS232RX, ON);
    };
    if(GetMessage(MSG_UART0_TX))
    {
      ResetTimer(TIMER_UART0_TX_LED);
      SetSysSpiBusState(SYS_LED_RS232TX, ON);
    };
    if(GetMessage(MSG_UART1_RX))
    {
      ResetTimer(TIMER_UART1_RX_LED);
      SetSysSpiBusState(SYS_LED_RS485RX, ON);
    };
    if(GetMessage(MSG_UART1_TX))                   
    {
      ResetTimer(TIMER_UART1_TX_LED);
      SetSysSpiBusState(SYS_LED_RS485TX, ON);
    };

    if(GetTimer(TIMER_UART0_RX_LED) > 50)
    {
      SetSysSpiBusState(SYS_LED_RS232RX, OFF);
    };    
    if(GetTimer(TIMER_UART0_TX_LED) > 50)
    {
      SetSysSpiBusState(SYS_LED_RS232TX, OFF);
    };
    if(GetTimer(TIMER_UART1_RX_LED) > 50)
    {
      SetSysSpiBusState(SYS_LED_RS485RX, OFF);
    };
    if(GetTimer(TIMER_UART1_TX_LED) > 50)
    {
      SetSysSpiBusState(SYS_LED_RS485TX, OFF);
    };                                                                                                                             
//------------------------------------------------------------------------------
//  threshold logic
//------------------------------------------------------------------------------
//  
//#define FTH_H_L   650  //left hn treshold output
//#define FTH_H_R   651  //right hn treshold output
//#define FTH_O2_L  652  //left o2 treshold output
//#define FTH_O2_R  653  //right o2 treshold output 
//    
//    
//#define THR_H_L   600  //left hn threshold 
//#define THR_H_R   601  //right hn threshold 
//#define THR_O_L   602  //left o2 threshold 
//#define THR_O_R   603  //right o2 threshold 
//#define G_TH_H_L  604  //left hn hysteresis 
//#define G_TH_H_R  605  //right hn hysteresis
//#define G_TH_O_L  606  //left o2 hysteresis
//#define G_TH_O_R  607  //right o2 hysteresis
//
//#define C_KL_O_L   180  //o2 left
//#define C_KL_O_R   181  //o2 right
//#define C_KL_HN_L  182  //hn right
//#define C_KL_HN_R  183  //hn right
//
                                                                                                                         
    if(!GetIntValueByTag(FTH_O2_L))
    {
      if(GetFloatValueByTag(C_KL_O_L) < 
         (GetFloatValueByTag(THR_O_L) - GetFloatValueByTag(G_TH_O_L)))
        SetIntValueByTag(FTH_O2_L, 1);
    }
    else
    {
      if(GetFloatValueByTag(C_KL_O_L) > GetFloatValueByTag(THR_O_L))
        SetIntValueByTag(FTH_O2_L, 0);
    };
    
    if(!GetIntValueByTag(FTH_O2_R))
    {
      if(GetFloatValueByTag(C_KL_O_R) < 
         (GetFloatValueByTag(THR_O_R) - GetFloatValueByTag(G_TH_O_R)))
        SetIntValueByTag(FTH_O2_R, 1);
    }
    else
    {
      if(GetFloatValueByTag(C_KL_O_R) > GetFloatValueByTag(THR_O_R))                    
        SetIntValueByTag(FTH_O2_R, 0);
    };

    if(!GetIntValueByTag(FTH_H_L))
    {
      if(GetFloatValueByTag(C_KL_HN_L) > 
         (GetFloatValueByTag(THR_H_L) + GetFloatValueByTag(G_TH_O_L)))
        SetIntValueByTag(FTH_H_L, 1);
    }
    else
    {
      if(GetFloatValueByTag(C_KL_HN_L) < GetFloatValueByTag(THR_H_L))
        SetIntValueByTag(FTH_H_L, 0);
    };

    if(!GetIntValueByTag(FTH_H_R))
    {
      if(GetFloatValueByTag(C_KL_HN_R) > 
         (GetFloatValueByTag(THR_H_R) + GetFloatValueByTag(G_TH_O_R)))
        SetIntValueByTag(FTH_H_R, 1);
    }
    else
    {
      if(GetFloatValueByTag(C_KL_HN_R) < GetFloatValueByTag(THR_H_R))
        SetIntValueByTag(FTH_H_R, 0);
    };  
    //------------------------------------------------------------------------------
    //  fault logic
    //------------------------------------------------------------------------------
    SetIntValueByTag(FLT_NE_L, GetHeater0State());
    SetIntValueByTag(FLT_NE_R, GetHeater1State());
    
    SetIntValueByTag(FLT_GA_L,
                     GetIntValueByTag(FLT_CH_L) ||
                     GetIntValueByTag(FLT_TP_L) || 
                     GetIntValueByTag(FLT_NE_L));
    
    SetIntValueByTag(FLT_GA_R, 
                     GetIntValueByTag(FLT_CH_R) || 
                     GetIntValueByTag(FLT_TP_R) || 
                     GetIntValueByTag(FLT_NE_R));
    //------------------------------------------------------------------------------
    //  channel control logic
    //------------------------------------------------------------------------------
    /*
    if(GetIntValueByTag(LEFT_CH_ON))
    {
      if(GetIntValueByTag(FLT_GA_L))
      {
        SetIntValueByTag(CHANNEL_STATE_L, 2);
      }
      else
      {
        SetIntValueByTag(CHANNEL_STATE_L, 1);
      };
    }
    else
      SetIntValueByTag(CHANNEL_STATE_L, 0);
    
    if(GetIntValueByTag(RIGHT_CH_ON))
    {
      if(GetIntValueByTag(FLT_GA_R))
      {
        SetIntValueByTag(CHANNEL_STATE_R, 2);
      }
      else
      {
        SetIntValueByTag(CHANNEL_STATE_R, 1);
      };
    }
    else
      SetIntValueByTag(CHANNEL_STATE_R, 0);
    */
    //--------------------------------------------------------------------------
    // LЁD
    //--------------------------------------------------------------------------
    //    o +-------------------+
    //      |                   |
    //    о |      backlight    | o  - channel on
    //    o |                   | o  - fault
    //    o +-------------------+ o  - HN threshold
    //    O    [1] [2] [3] [4]    O  
    //    o    [5] [6] [7] [8]    o  - encoder`s lights
    //--------------------------------------------------------------------------
    //  The "channel on" lёds have an following meaning:
    //  0 - heater is turn off
    //  1 - normal state, heater has a normal temperature
    //  2 - normal blink - heater is warming, the temperature is not reached
    //  3 - fast blink - heater is overheated;
    
    SetDispLedState(DISP_LED_L_STATE, GetIntValueByTag(PWM0_ON)?
                    (GetFloatValueByTag(CEL_F_T_L) > 
                     GetFloatValueByTag(ADJ_S_T_L) + 
                     GetFloatValueByTag(DELTA_T_PLUS_L))?FAST_BLINK:
                      (GetFloatValueByTag(CEL_F_T_L) < 
                       GetFloatValueByTag(ADJ_S_T_L) -
                       GetFloatValueByTag(DELTA_T_MINUS_L))?BLINK:ON:
                        OFF);
   // SetDispLedState(DISP_LED_R_STATE, GetIntValueByTag(PWM1_ON)?ON:OFF);
    SetDispLedState(DISP_LED_R_STATE, GetIntValueByTag(PWM1_ON)?
                    (GetFloatValueByTag(CEL_F_T_R) > 
                     GetFloatValueByTag(ADJ_S_T_R) + 
                     GetFloatValueByTag(DELTA_T_PLUS_R))?FAST_BLINK:
                      (GetFloatValueByTag(CEL_F_T_R) < 
                       GetFloatValueByTag(ADJ_S_T_R) - 
                       GetFloatValueByTag(DELTA_T_MINUS_R))?BLINK:ON:
                        OFF);

    SetDispLedState(DISP_LED_L_TR1, (GetIntValueByTag(FLT_GA_L)?ON:OFF)); //GetIntValueByTag(FTH_O2_L)?ON:OFF); 
    SetDispLedState(DISP_LED_L_TR2, 
                    (GetIntValueByTag(FTH_O2_L) || 
                     GetIntValueByTag(FTH_H_L))?ON:OFF);
    
    SetDispLedState(DISP_LED_R_TR1, 
                    (GetIntValueByTag(FLT_GA_R)?ON:OFF)); //GetIntValueByTag(FTH_O2_R)?ON:OFF);
    SetDispLedState(DISP_LED_R_TR2,
                    (GetIntValueByTag(FTH_O2_R) || 
                     GetIntValueByTag(FTH_H_R))?ON:OFF);
    
    // SetDispLedState(DISP_LED_L_ENC, ON);                                                  //temp
    // SetDispLedState(DISP_LED_R_ENC, OFF);                                                 //temp
    
    //--------------------------------------------------------------------------
    //  OutputSet(LCD_LED);
    //--------------------------------------------------------------------------
    processCurrOuts();
    ProcessLeftPowerControl();
    ProcessRightPowerControl();                                                                                              
    ProcessMessages();
    ResetWdt();
  }
}
