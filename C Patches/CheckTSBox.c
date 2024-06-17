
extern uint8_t TSXPosLive;
extern uint8_t TSYPosLive;
extern uint8_t TSXPosLastMitDrag;
extern uint8_t TSYPosLastMitDrag;
extern uint8_t TSPressed;
//Made by Argonien
static int CheckIfTouchscreenIsPressedInDefinedBox(){
  int TSX = TSXPosLive;
  int TSY = TSYPosLive;
  int TSP = TSPressed;
  if (TSP == 0){//Checks if the touchscreen is being pressed, returns 0 if not
    return 0;
  }
  if (TSX >= 114 && TSX <= 142 && TSY >= 86 && TSY <= 106){//Checks for a 20x20 Box in the middle of the screen and returns 1 if the box is hit
        return 1;
    }
  //To add more checks add more else-if blocks:
  /*
  else if (TSX >= LowerXBorder && TSX <= UpperXBorder && TSY >= LowerYBorder && TSY <= UpperYBorder){
        return X;
      }
  */
 return 255;//returns 255 if the touchscreen is pressed, but no Box is being hit
}