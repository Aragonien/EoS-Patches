#include <pmdsky.h>
#include <cot.h>
#include "extern.h"
#include "CheckAndSaveStylusPosAroundPosVars.h"

static void ChangePressBit(){
  //Changes VAR_SIDE06_ROOM for the main function
  
  int check = LoadScriptVariableValue(NULL, VAR_SIDE06_ROOM);
  if (check == 0){
  SaveScriptVariableValue(NULL, VAR_SIDE06_ROOM, 1);// 1= write, 0 = check
  }
  else if(check == 1){
    SaveScriptVariableValue(NULL, VAR_SIDE06_ROOM, 0);
  }
}
//Made by Argonien
int CheckIfTouchscreenValuesAreInABoxAroundPositionVariables(short arg1){
  //This Special Process Checks if the stylus position is in a 20x40 pixel box around all 3 Indexes of the POSITION_X and POSITION_Y Variables
  //If that process returns a true value, the second part of the process runs, which writes the stylus position values into the POSITION_X and POSITION_Y Variables
  //This second part of the process runs until the touchscreen isn't pressed anymore
  //To determine which part of the process should run, the C code uses VAR_SIDE06_ROOM, which is used as 0=checking and 1=writing
  //Param 1 is used for the Index of the POSITION_X and POSITION_Y Variables you want to write to. For example, if Param1 is 1, then the stylus position values will be written to Index 1 of POSITION_X and POSITION_Y
  //Regarding the Size of the Y value, it appears that the Y value written into POSITION_Y with SavePosition(x); is, for sprites, at the base of the sprite and for objects in the middle of the object
  //So if you are checking for sprites, you should extend the Y Box upwards a bit (like currently) and if you are checking for objects, then the Y Box should have equal lenght in both directions
  //IMPORTANT! When checking for Actor/Object positions, the camera has to be on the top left (default position), else the Actor/Object positions are outside the max. touchscreen values
  int TSX = TSXPosLive;
  int TSY = TSYPosLive;
  int TSP = TSPressed;
  TSX = TSX*256;//The game multiplies the touchscreen pixel value with 256 for the POSITION_X and POSITION_Y Variables
  TSY = TSY*256;
  int TSBitcheck = LoadScriptVariableValue(NULL, VAR_SIDE06_ROOM);
  if (TSBitcheck == 0){//Checking which part of the process should run
  if (TSP == 0){
    return 255;//if the touchscreen isn't pressed return 255
  }
  //Checking Index 0 of POSITION_X and POSITION_Y
  int XInd = LoadScriptVariableValueAtIndex(NULL, VAR_POSITION_X, 0);
  int YInd = LoadScriptVariableValueAtIndex(NULL, VAR_POSITION_Y, 0);
  if (TSX < XInd+2560 && TSX > XInd-2560 && TSY < YInd+2560 && TSY > YInd-5120){
    ChangePressBit();//Changes VAR_SIDE06_ROOM to 1
    return 0;//returns 0 if the the stylus position values are around the Index 0 Values of POSITION_X and POSITION_Y
  }
  //Checking Index 1 of POSITION_X and POSITION_Y
  XInd = LoadScriptVariableValueAtIndex(NULL, VAR_POSITION_X, 1);
  YInd= LoadScriptVariableValueAtIndex(NULL, VAR_POSITION_Y, 1);
  if (TSX < XInd+2560 && TSX > XInd-2560 && TSY < YInd+2560 && TSY > YInd-5120){
    ChangePressBit();//Changes VAR_SIDE06_ROOM to 1
    return 1;//returns 1 if the the stylus position values are around the Index 0 Values of POSITION_X and POSITION_Y
  }
  //Checking Index 2 of POSITION_X and POSITION_Y
  XInd = LoadScriptVariableValueAtIndex(NULL, VAR_POSITION_X, 2);
  YInd= LoadScriptVariableValueAtIndex(NULL, VAR_POSITION_Y, 2);
  if (TSX < XInd+2560 && TSX > XInd-2560 && TSY < YInd+2560 && TSY > YInd-5120){
    ChangePressBit();//Changes VAR_SIDE06_ROOM to 1
    return 2;//returns 2 if the the stylus position values are around the Index 0 Values of POSITION_X and POSITION_Y
  }
  return 254;//returns 254 is the stylus position is pressed, but no defined space is hit
  }
  //The second part of the process, responsible for writing the stylus position values to POSITION_X and POSITION_Y
  else{
    if (TSP == 0){//Check if the touchscreen is still being pressed
      //This Block saves the last stylus position to the Index of POSITION_X and POSITION_Y defined with Param 1
      int TSXLast = TSXPosLastMitDrag;
      int TSYLast = TSYPosLastMitDrag;
      TSXLast = TSXLast*256;
      TSYLast = TSYLast*256;
      switch (arg1){
        case 0:
        SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_X, 0, TSXLast);
        SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_Y, 0, TSYLast);
        ChangePressBit();//Changes VAR_SIDE06_ROOM to 0
        return 2;//Returns 2 when the touchscreen is released and the last writing of the stylus position is done
        case 1:
        SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_X, 1, TSXLast);
        SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_Y, 1, TSYLast);
        ChangePressBit();//Changes VAR_SIDE06_ROOM to 0
        return 2;//Returns 2 when the touchscreen is released and the last writing of the stylus position is done
        case 2:
        SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_X, 2, TSXLast);
        SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_Y, 2, TSYLast);
        ChangePressBit();//Changes VAR_SIDE06_ROOM to 0
        return 2;//Returns 2 when the touchscreen is released and the last writing of the stylus position is done
      }
      return 2;
    }
    //This block runs while the touchscreen is still being pressed and write the current stylus position into the with Param 1 definded Index of POSITION_X and POSITION_Y
    switch (arg1){
      case 0:
      SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_X, 0, TSX);
      SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_Y, 0, TSY);
      return 1;//Returns 1 while writing the position
      case 1:
      SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_X, 1, TSX);
      SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_Y, 1, TSY);
      return 1;//Returns 1 while writing the position
      case 2:
      SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_X, 2, TSX);
      SaveScriptVariableValueAtIndex(NULL, VAR_POSITION_Y, 2, TSY);
      return 1;//Returns 1 while writing the position
    }
  return 128;
  }
}
