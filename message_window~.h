//------------------------------------------------------------------------------
// Модуль реализует окно сообщений
//------------------------------------------------------------------------------
#ifndef MESSAGE_WINDOW_h
#define MESSAGE_WINDOW_h

#define MB_OK     1
#define MB_CANCEL 2

void SetMessageScreenMode(char* message_line1, char* message_line2,
                       char* message_line3, char buttons);

void ProcessMessageWindow(void);

#endif
