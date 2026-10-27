// void TabClass::Unknown_006A0D80() (0x006A0D80)
// Removes the 25 buttons from the button list.
#include "shared/tab.hpp"
// @ref ?Buttons@TabClass@@2PAVShapeButtonClass@@A=00abd918

void TabClass::Unknown_006A0D80()
{
    for (int index = 0; index < 25; index++) {
        Remove_A_Button(Buttons[index]);
    }
}
