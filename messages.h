#ifndef MESSAGES_h
#define MESSAGES_h

typedef
struct {
  char Msg;
  unsigned long Param;
} MESSAGE;

#define MAX_MESSAGES 160

#define MSG_NULL                 0

#define MSG_KEYPRESSED           1
#define MSG_L_ENCODER_PRESSED    2
#define MSG_L_ENCODER_CW         3
#define MSG_L_ENCODER_CCW        4
#define MSG_R_ENCODER_PRESSED    5
#define MSG_R_ENCODER_CW         6
#define MSG_R_ENCODER_CCW        7
#define MSG_ANYKEY               8

#define MSG_BTN_OK               9
#define MSG_BTN_CANCEL           10
#define MSG_BTN_DEFAULT          11
#define MSG_BTN_FORWARD          12
#define MSG_BTN_BACKWARD         13
#define MSG_BTN_HOME             14
#define MSG_BTN_MENU             15
#define MSG_BTN_EDIT             16
#define MSG_BTN_MISC             17
#define MSG_BTN_RESERVED4        18
#define MSG_BTN_RESERVED5        19
#define MSG_BTN_RESERVED6        20
#define MSG_BTN_RESERVED7        21
#define MSG_BTN_RESERVED8        22
#define MSG_BTN_RESERVED9        23
#define MSG_BTN_RESERVED10       24

#define MSG_ADC_READY            25

#define MSG_VAR_CHANGED          26

#define MSG_EDITOR_ACTIVATE      27
#define MSG_EDITOR_KEY_UP        28
#define MSG_EDITOR_KEY_DOWN      29

#define MSG_EDITOR_FINISHED      31
#define MSG_EDITOR_CANCELLED     32
#define MSG_EDITOR_DEACTIVATED   33

#define MSG_SCREEN_ACTIVATE      34
#define MSG_SCREEN_OK            35
#define MSG_SCREEN_CANCEL        36

#define MSG_CONTROL_OK           37

#define MSG_CHILD_SCREEN_ACTIVATE    38
#define MSG_CHILD_SCREEN_DEACTIVATED 39

#define MSG_CHECKBOX             40

#define MSG_PASS_WRONG     41
#define MSG_PASS_CANCEL    42
#define MSG_PASS1_OK       43
#define MSG_PASS2_OK       44
#define MSG_PASS3_OK       45
//------------------------------------------------------------------------------
//  UARTS INTERRUPT REQUESTS
//------------------------------------------------------------------------------
#define MSG_UART0READHOLDINGS          49
#define MSG_UART0WRITESINGLEHOLDING    50
#define MSG_UART0WRITEMULTIPLEHOLDINGS 51  
#define MSG_UART0PRINTSCREEN           52

#define MSG_UART1READHOLDINGS          53
#define MSG_UART1WRITESINGLEHOLDING    54
#define MSG_UART1WRITEMULTIPLEHOLDINGS 55  
#define MSG_UART1PRINTSCREEN           56

#define MSG_UART0_RX                   60
#define MSG_UART0_TX                   61
#define MSG_UART1_RX                   62
#define MSG_UART1_TX                   63
//------------------------------------------------------------------------------

//#define MSG_CUR_ACTIVATE   100
//#define MSG_CUR_DEACTIVATE 101

#define MSG_EDITOR_SCREEN_ACTIVATE    100
#define MSG_EDITOR_SCREEN_OK          101
#define MSG_EDITOR_SCREEN_CANCEL      102
#define MSG_EDITOR_SCREEN_DEACTIVATED 103

#define MSG_DEF_WARN_SCREEN_ACTIVATE  110

#define MSG_MESSAGE_SCREEN_ACTIVATE   115
#define MSG_MESSAGE_SCREEN_OK         116
#define MSG_MESSAGE_SCREEN_CANCEL     117

#define MSG_MAIN_SCREEN_ACTIVATE      120
#define MSG_MAIN_SCREEN_DEACTIVATED   121

#define MSG_PARAM_SCREEN_ACTIVATE     122
#define MSG_PARAM_SCREEN_CLOSE        123
#define MSG_PARAM_SCREEN_DEACTIVATED  124

#define MSG_TWOCOL_SCREEN_ACTIVATE    125



#define MSG_CLAPP_SCREEN_ACTIVATE     131
#define MSG_CLAPP_SCREEN_CLOSE        132
#define MSG_CLAPP_SCREEN_DEACTIVATED  133

#define MSG_MENU_SCREEN_ACTIVATE      134
#define MSG_MENU_SCREEN_DEACTIVATED   135

#define MSG_PASSWORD_SCREEN_ACTIVATE  136

#define MSG_ADC_IN_TEST_SCREEN_ACTIVATE       139
#define MSG_ADC_IN_TEST_SCREEN_DEACTIVATED    140

#define MSG_DAC_OUT_TEST_SCREEN_ACTIVATE      141
#define MSG_DAC_OUT_TEST_SCREEN_DEACTIVATED   142

#define MSG_DISCR_IN_TEST_SCREEN_ACTIVATE     143
#define MSG_DISCR_IN_TEST_SCREEN_DEACTIVATED  144

#define MSG_DISCR_OUT_TEST_SCREEN_ACTIVATE    145
#define MSG_DISCR_OUT_TEST_SCREEN_DEACTIVATED 146

#define MSG_PWM_TEST_SCREEN_ACTIVATE          147
#define MSG_PWM_TEST_SCREEN_DEACTIVATED       148

#define MSG_RS232_SCREEN_ACTIVATE             149
#define MSG_RS232_SCREEN_DEACTIVATED          150

#define MSG_RS485_SCREEN_ACTIVATE             151
#define MSG_RS485_SCREEN_DEACTIVATED          152

#define MSG_ETHERNET_SCREEN_ACTIVATE          153
#define MSG_ETHERNET_SCREEN_DEACTIVATED       154

#define MSG_TREND_SCREEN_ACTIVATE             155
#define MSG_TREND_SCREEN_DEACTIVATED          156

#define MSG_MISC_SCREEN_ACTIVATE              157
#define MSG_MISC_SCREEN_DEACTIVATED           158

void InitMessages(void);

void SendParamMessage(int Msg, unsigned long param);
void SendMessage(int Msg);
//void SendIRQMessage(char Msg);

char GetParamMessage(int Msg, unsigned long*param);
char GetMessage(int Msg);

void ProcessMessages(void);
/*
//------------------------------------------------------------------------------
#define MAX_SEMAPHORES 1

#define SIS_SPI_SEMAPHORE 0

void InitSemaphores(void);
void SetSemaphore(char num);
void ClrSemaphore(char num);
char GetSemaphore(char num);
*/
#endif
