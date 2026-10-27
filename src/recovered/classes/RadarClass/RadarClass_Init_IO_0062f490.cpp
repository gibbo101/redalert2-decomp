// void RadarClass::Init_IO() (0x0062F490, slot 8)
// After the display's controls, sets up the two radar shape buttons (ids
// 0xF2 and 0xF3) at their positions with their shapes.
#include "shared/radar.hpp"
// @ref ?Init_IO@DisplayClass@@UAEXXZ=00498c50
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
// @ref ?unknown_drawer_8323cc@@3PAVConvertClass@@A=008323cc
// @ref ?unknown_button_ab63e8@RadarClass@@2VShapeButtonClass@@A=00ab63e8
// @ref ?unknown_button_ab6380@RadarClass@@2VShapeButtonClass@@A=00ab6380
// @ref ?unknown_shape_ab6350@RadarClass@@2PBXB=00ab6350
// @ref ?unknown_shape_ab6318@RadarClass@@2PBXB=00ab6318
// @ref ?unknown_int_ab6468@@3HA=00ab6468
// @ref ?unknown_int_ab646c@@3HA=00ab646c
// @ref ?unknown_int_ab6338@@3HA=00ab6338
// @ref ?unknown_int_ab633c@@3HA=00ab633c
// @ref ?Set_Position@GadgetClass@@UAEXHH@Z=004cf660
// @ref ?Set_Shape@ShapeButtonClass@@UAEXPBXHH@Z=00675130
// @ref ?Flag_To_Redraw@GadgetClass@@UAEXXZ=004cf5a0

void RadarClass::Init_IO()
{
    DisplayClass::Init_IO();
    if (!unknown_flag_a40d13) {
        unknown_button_ab63e8.ID = 0xF2;
        unknown_button_ab63e8.unknown_4c = true;
        unknown_button_ab63e8.unknown_50 = unknown_drawer_8323cc;
        unknown_button_ab63e8.IsOn = false;
        unknown_button_ab63e8.ToggleType = 0;
        unknown_button_ab63e8.Flags = 5;
        unknown_button_ab63e8.Set_Position(unknown_int_ab6468, unknown_int_ab646c);
        unknown_button_ab63e8.Set_Shape(unknown_shape_ab6350);
        unknown_button_ab63e8.Flag_To_Redraw();

        unknown_button_ab6380.ID = 0xF3;
        unknown_button_ab6380.unknown_4c = true;
        unknown_button_ab6380.unknown_50 = unknown_drawer_8323cc;
        unknown_button_ab6380.IsOn = false;
        unknown_button_ab6380.ToggleType = 0;
        unknown_button_ab6380.Flags = 5;
        unknown_button_ab6380.Set_Position(unknown_int_ab6338, unknown_int_ab633c);
        unknown_button_ab6380.Set_Shape(unknown_shape_ab6318);
        unknown_button_ab6380.Flag_To_Redraw();
    }
}
