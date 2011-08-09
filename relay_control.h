/***************************************************************************
 **
 **    This file defines the Relay control definitions
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyleft
 **
 ***************************************************************************/
#ifndef __RELAY_CONTROL_H
#define __RELAY_CONTROL_H

#define OFF   0
#define ON    1

#define RELAY_0 0
#define RELAY_1 1
#define RELAY_2 2
#define RELAY_3 3
#define RELAY_4 4
#define RELAY_5 5

void SetRelayState(char relay, char state);

#endif /* __RELAY_CONTROL_H */
