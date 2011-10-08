extern "C"{
#include "messages.h"
#include "pass_controller.h"
#include "variables.h"
};
#include "tagvaluelabel.h"
#include "usbase.h"
#include "editor_scr.h"
#include "pass_scr.h"
//------------------------------------------------------------------------------
/*
void usTagValueLabel::Paint(void)
{
  
  usTextButton::Paint();  
}
*/
void usTagValueLabel::Update(void)
{
  const int BUF_SIZE = 10;
  char str[BUF_SIZE];
  
  if(tag != EMPTY_CELL)
  {
    GetStringByTag(tag, ID_CURR_VAL, str, BUF_SIZE);
    text.assign(str);
  };
  setFocusEnabled(getAccessLevel(tag) != ACCESS_0);
  usTextButton::Update();
}

void usTagValueLabel::Click()
{
  if(EditAllowed() || getPasswordEntered())                                                                    //!!!!!!!!!!!!!!
  {
    editor_scr = new EditorScreen(tag);
    SendParamMessage(MSG_EDITOR_SCREEN_ACTIVATE, tag);
  }
  else
  {
    pass_scr = new PassScreen();
  };
}
