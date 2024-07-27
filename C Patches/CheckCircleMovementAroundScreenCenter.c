#include <pmdsky.h>
#include <cot.h>
#include "extern.h"
#include "CheckCircleMovementAroundScreenCenter.h"
//If you use multiple patches that use these variables, comment them out in all but one patch. It won't compile otherwise.
uint8_t KreisCounter;

//Made by Argonien
//This patch checks for circular motion around the screen scenter. Check area is the whole screen.
//arg1: 1-> checks for clockwise movement, 2-> checks for counter clockwise movement
//This patch writes the amount of circles completed into Index 1 of $SCENARIO_SUB8
//Returns: 
//  1 when a full circle is completed
//  2 when a portion check is hit
//  3 when holding the touchscreen in check area
//  4 when completing the circular motion fails, e.g. when the check area is left or the movement goes against the checked direction
//  5 when the screen is pressed, but no check area is being hit
//  254 when arg1 is invalid
//  255 when the screen is not pressed
int checkCircleScreenCenter(short arg1){
    int TSX = TSXPosLive;
    int TSY = TSYPosLive;
    int TSP = TSPressed;
    int Counter = LoadScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 1);
    if (TSP == 0){
    KreisCounter = 0;
    SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 0, 0);
    return 255;
    }
    switch (arg1){
    case 1:
        if (KreisCounter == 5){
            KreisCounter = 1;
            Counter++;
            SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 1, Counter);
            return 1;
        }
        if (TSX > 0 && TSX < 128 && TSY > 0 && TSY < 96){
            if(KreisCounter == 0 || KreisCounter == 4){
                KreisCounter++;
                return 2;
            }
            else if (KreisCounter == 1){
                return 3;
            }
                KreisCounter = 0;
                SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 0, 0);
                return 4;
        }
        else if (TSX > 128-2 && TSX < 256 && TSY > 0 && TSY < 96){
            if (KreisCounter == 1){
                KreisCounter++;
                return 2;
            }
            else if (KreisCounter == 2){
                return 3;
            }
            KreisCounter = 0;
            SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 0, 0);
            return 4;
        }
        else if (TSX > 128-2 && TSX < 256 && TSY > 96-2 && TSY < 192){
            if (KreisCounter == 2){
                KreisCounter++;
                
                return 2;
            }
            else if (KreisCounter == 3){
                return 3;
            }
            KreisCounter = 0;
            SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 0, 0);
            return 4;
        }
        else if (TSX > 0 && TSX < 128 && TSY > 96-2 && TSY < 192){
            if (KreisCounter == 3){
                KreisCounter++;
                
                return 2;
            }
            else if (KreisCounter == 4){
                return 3;
            }
            KreisCounter = 0;
            SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 0, 0);
            return 4;
        }
        return 5;   
    case 2:
        if (KreisCounter == 5){
            KreisCounter = 1;
            Counter++;
            SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 1, Counter);
            
            return 1;
        }
        if (TSX > 0 && TSX < 128 && TSY > 0 && TSY < 96){
            if(KreisCounter == 0 || KreisCounter == 4){
                KreisCounter++;
                
                return 2;
            }
            else if (KreisCounter == 1){
                return 3;
            }
                KreisCounter = 0;
                SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 0, 0);
                return 4;
        }
        else if (TSX > 0 && TSX < 128 && TSY > 96-2 && TSY < 192){
            if (KreisCounter == 1){
                KreisCounter++;
                
                return 2;
            }
            else if (KreisCounter == 2){
                return 3;
            }
            KreisCounter = 0;
            SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 0, 0);
            return 4;
        }
        else if (TSX > 128-2 && TSX < 256 && TSY > 96-2 && TSY < 192){
            if (KreisCounter == 2){
                KreisCounter++;
                
                return 2;
            }
            else if (KreisCounter == 3){
                return 3;
            }
            KreisCounter = 0;
            SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 0, 0);
            return 4;
        }
        else if (TSX > 128-2 && TSX < 256 && TSY > 0 && TSY < 96){
            if (KreisCounter == 3){
                KreisCounter++;
                
                return 2;
            }
            else if (KreisCounter == 4){
                return 3;
            }
            KreisCounter = 0;
            SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 0, 0);
            return 4;
        }
        return 5;  
    default:
    return 254;
    }
}