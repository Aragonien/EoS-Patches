#include <pmdsky.h>
#include <cot.h>
#include "extern.h"
#include "StoreCameraPosition.h"
//Made by Argonien
//Stores the cameras Position for other patches. The Position consists of the cameras grid coordinates in the Skytemple Scene Editor.
//Only supports full numbers.
//Param 1: The Cameras X Position
//Param 2: The Cameras Y Position
//If you use multiple patches that use these variables, comment them out in all but one patch. It won't compile otherwise.
uint16_t KameraXPos;
uint16_t KameraYPos;

void StoreCameraPosition(short arg1, short arg2){
    if (arg1 <= 17){
        KameraXPos = 0;
    }
    if (arg2 <= 12){
        KameraYPos = 0;
    }
    if (arg1 > 17 && arg2 > 12){
        KameraXPos = (arg1-17)*8;
        KameraYPos = (arg2-12)*8;
    }
}