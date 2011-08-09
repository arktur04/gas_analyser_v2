#include "messages.h"
#include "stdlib.h"

MESSAGE Messages[MAX_MESSAGES];

void InitMessages(void)
{
  for(int i = 0; i < MAX_MESSAGES - 1; i++)
    Messages[i].Msg = 0;
}

void SendParamMessage(int Msg, unsigned long param)
{
  if(Messages[Msg].Msg == 0)
    Messages[Msg].Msg = 1;
  Messages[Msg].Param = param;
}

void SendMessage(int Msg)
{
  SendParamMessage(Msg, 0);
}

/*
void SendIRQMessage(char Msg)
{
  Messages[Msg] = 4;
}
*/

char GetParamMessage(int Msg, unsigned long *param)
{
  if((Messages[Msg].Msg == 2) || (Messages[Msg].Msg == 4))
  {
    Messages[Msg].Msg = 0;
    if(param != NULL)
      *param = Messages[Msg].Param;
    return 1;
  };
  return 0;
};

char GetMessage(int Msg)
{
  return GetParamMessage(Msg, NULL);
}

void ProcessMessages(void)
{
  for(int i = 0; i < MAX_MESSAGES - 1; i++)
  {
    if(Messages[i].Msg == 2) Messages[i].Msg = 0;
    if(Messages[i].Msg == 1) Messages[i].Msg = 2;
  }
}
//------------------------------------------------------------------------------
/*
volatile char semaphores[MAX_SEMAPHORES];

void InitSemaphores(void)
{
  for(char i = 0; i < MAX_SEMAPHORES; i++)
  {
    semaphores[i] = 0;
  };
}

void SetSemaphore(char num)
{
  semaphores[num] = 1;
}

void ClrSemaphore(char num)
{
  semaphores[num] = 0;
}

char GetSemaphore(char num)
{
  return semaphores[num];
}
*/
