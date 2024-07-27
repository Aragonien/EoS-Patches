#include <pmdsky.h>
#include <cot.h>
#include "extern.h"
#include "CheckCircleMovementAroundPosVar.h"
//If you use multiple patches that use these variables, comment them out in all but one patch. It won't compile otherwise.
uint8_t KreisCounter;
uint16_t KameraXPos;
uint16_t KameraYPos;

//Made by Argonien
//This patch checks for circular motion on the touchscreen around Index 0 of the Position Variables.
//IMPORTANT! This process on it's own only works correctly at the top left of the screen. If you want the process to work anywhere, please use the "StoreCameraPosition" process beforehand.
//arg1: 1-> checks for clockwise movement, 2-> checks for counter clockwise movement
//arg2: circle radius in pixels 
//This patch writes the amount of circles completed into Index 1 of $SCENARIO_SUB8
//Returns: 
//  1 when a full circle is completed
//  2 when a portion check is hit
//  3 when holding the touchscreen in check area
//  4 when completing the circular motion fails, e.g. when the check area is left or the movement goes against the checked direction
//  5 when the screen is pressed, but no check area is being hit
//  254 when arg1 is invalid
//  255 when the screen is not pressed
int checkCircleAroundPositionVariable(short arg1, short arg2){
    int TSX = TSXPosLive;
    int TSY = TSYPosLive;
    int TSP = TSPressed; 
    int XPOSACTOR = LoadScriptVariableValueAtIndex(NULL, VAR_POSITION_X, 0);
    int YPOSACTOR = LoadScriptVariableValueAtIndex(NULL, VAR_POSITION_Y, 0);
    XPOSACTOR = XPOSACTOR/256-KameraXPos;
    YPOSACTOR = YPOSACTOR/256-KameraYPos;
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
        if (TSX > XPOSACTOR-arg2 && TSX < XPOSACTOR && TSY > YPOSACTOR-arg2 && TSY < YPOSACTOR){
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
        else if (TSX > XPOSACTOR-2 && TSX < XPOSACTOR+arg2 && TSY > YPOSACTOR-arg2 && TSY < YPOSACTOR){
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
        else if (TSX > XPOSACTOR-2 && TSX < XPOSACTOR+arg2 && TSY > YPOSACTOR-2 && TSY < YPOSACTOR+arg2){
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
        else if (TSX > XPOSACTOR-arg2 && TSX < XPOSACTOR && TSY > YPOSACTOR-2 && TSY < YPOSACTOR+arg2){
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
        KreisCounter = 0;
        SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 0, 0);
        return 5;   
    case 2:
        if (KreisCounter == 5){
            KreisCounter = 1;
            Counter++;
            SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 1, Counter);          
            return 1;
        }
        if (TSX > XPOSACTOR-arg2 && TSX < XPOSACTOR && TSY > YPOSACTOR-arg2 && TSY < YPOSACTOR){
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
        else if (TSX > XPOSACTOR-arg2 && TSX < XPOSACTOR && TSY > YPOSACTOR-2 && TSY < YPOSACTOR+arg2){
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
        else if (TSX > XPOSACTOR-2 && TSX < XPOSACTOR+arg2 && TSY > YPOSACTOR-2 && TSY < YPOSACTOR+arg2){
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
        else if (TSX > XPOSACTOR-2 && TSX < XPOSACTOR+arg2 && YPOSACTOR-arg2&& TSY < YPOSACTOR){
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
        KreisCounter = 0;
        SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB8, 0, 0);
        return 5;  
        
    default:
    return 254;
    }
    return 99;
}