// void RadarClass::Unknown_0062F2D0(bool add) (0x0062F2D0)
// Adds the two radar shape buttons to the button list, or removes them.
#include "shared/radar.hpp"
// @ref ?unknown_button_ab63e8@RadarClass@@2VShapeButtonClass@@A=00ab63e8
// @ref ?unknown_button_ab6380@RadarClass@@2VShapeButtonClass@@A=00ab6380

void RadarClass::Unknown_0062F2D0(bool add)
{
    if (add) {
        Add_A_Button(unknown_button_ab63e8);
        Add_A_Button(unknown_button_ab6380);
    } else {
        Remove_A_Button(unknown_button_ab63e8);
        Remove_A_Button(unknown_button_ab6380);
    }
}
