// void TabClass::Unknown_006A0D50() (0x006A0D50)
// Unlinks each of the 25 buttons and adds it to the button list.
#include "shared/tab.hpp"
// @ref ?Buttons@TabClass@@2PAVShapeButtonClass@@A=00abd918

void TabClass::Unknown_006A0D50()
{
    for (int index = 0; index < 25; index++) {
        ShapeButtonClass &button = Buttons[index];
        button.Zap();
        Add_A_Button(button);
    }
}
