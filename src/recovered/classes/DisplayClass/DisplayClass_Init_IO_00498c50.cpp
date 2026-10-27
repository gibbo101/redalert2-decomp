// void DisplayClass::Init_IO() (0x00498C50, slot 8)
// Resets the button list and, unless 0x00A40D13 is set, adds the tactical
// area's button to it.
#include "shared/display.hpp"
// @ref ?Init_IO@GScreenClass@@UAEXXZ=004e0990
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
// @ref ?TacButton@DisplayClass@@2VTacticalClass@1@A=00852910
// @ref ?Zap@LinkClass@@UAEXXZ=00538ff0

void DisplayClass::Init_IO()
{
    GScreenClass::Init_IO();
    if (!unknown_flag_a40d13) {
        TacButton.Zap();
        Add_A_Button(TacButton);
    }
}
