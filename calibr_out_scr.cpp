extern "C"{
#include "lcd.h"
#include "font.h"
#include "bmps.h"
#include "keyb.h"
#include "timers.h"
#include "variables.h"
#include "screens.h"
#include "pass_controller.h"
};

#include "messages.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calibr_out_scr.h"
#include "usbase.h"

void CalibrOutScreen::Activated(unsigned long * param)
{
  TwoColScr::Activated(param);
  SetIntValueByTag(OUT_CALIBR_FLAG, 1);
};

CalibrOutScreen::~CalibrOutScreen()
{
  SetIntValueByTag(OUT_CALIBR_FLAG, 0);
}
