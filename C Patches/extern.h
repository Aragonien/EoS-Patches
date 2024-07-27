#pragma once

#include <pmdsky.h>
#include <cot.h>
//Used for "CheckAnsSaveStylusAroundPosVars","CheckTSBox"
extern uint8_t TSXPosLive;
extern uint8_t TSYPosLive;
extern uint8_t TSXPosLastMitDrag;
extern uint8_t TSYPosLastMitDrag;
extern uint8_t TSPressed;

//Used for "CheckAnsSaveStylusAroundPosVars", "StoreCameraPosition"
extern uint16_t KameraXPos;
extern uint16_t KameraYPos;