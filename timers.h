#ifndef TIMERS_h
#define TIMERS_h

#define sec 100
#define minute (60 * sec)
#define hour (60 * min)
#define day (24 * hour)

#define MAX_TIMERS 24

#define KEYB_TIMER           0
//#define LAST_KEY_TIMER     1
#define CURSOR_TIMER         2
#define ADC_CONV_TIMER       3
#define ADC_TIME_OUT         4
#define SCREEN_REFRESH_TIMER 5
#define PASS_TIMER           6
#define BACKLIGHT_TIMER      7
#define TEMP_SENS_TIMER      8
#define LED_BLINK_TIMER      9
#define LED_FAST_BLINK_TIMER 10
#define TREND_REFRESH_TIMER  11

#define TIMER_UART0_TX_LED   12
#define TIMER_UART0_RX_LED   13
#define TIMER_UART1_TX_LED   14
#define TIMER_UART1_RX_LED   15
#define TIMER_ADC_RESET      16

#define DEB_TIMER1           17
#define DEB_TIMER2           18

void InitTimers(void);

void ProcessTimers(void);

unsigned int GetTimer(char Timer);

void ResetTimer(char Timer);

//-----------------------------------------
// PWM interrupt handler
void ProcessTimer1(void);
//------------------------------------------

void ProcessTimer2(void);
void ProcessTimer3(void);

void setTimer1Width(int width, char tpState, char neState, char pwmEnabled);

void setTimer2Width(int width, char tpState, char neState, char pwmEnabled);

char GetHeater0State(void);

char GetHeater1State(void);
/*
char LeftPulsesArePresent(void);

char RightPulsesArePresent(void);

void SetTime1(unsigned int value);

void SetTime2(unsigned int value);

void InitIRQ(void);
*/

//void TMR0_IRQHandler (void);

void SysTick_Handler(void);

void SetProcessingHandler(void (*_processing_handler)(void));

#endif
