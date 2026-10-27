// static void TabClass::Unknown_006A19E0() (0x006A19E0)
// Sets up the two side buttons: ids 0xF0 and 0xF1 at the 0x00AC1204 and
// 0x00AC1208 rectangles with the 0x00AC1098 shape. Init_IO inlines it; this
// is the copy the linker kept.
#include "shared/tab.hpp"
// @ref ?unknown_drawer_8323cc@@3PAVConvertClass@@A=008323cc
// @ref ?unknown_buffer_ac1098@@3PAXA=00ac1098
// @ref ?unknown_rect_ac1204@@3PBVRect@@B=00ac1204
// @ref ?unknown_rect_ac1208@@3PBVRect@@B=00ac1208
// @ref ?unknown_button_abe400@TabClass@@2VShapeButtonClass@@A=00abe400
// @ref ?unknown_button_abe390@TabClass@@2VShapeButtonClass@@A=00abe390
// @ref ?Set_Position@GadgetClass@@UAEXHH@Z=004cf660
// @ref ?Set_Shape@ShapeButtonClass@@UAEXPBXHH@Z=00675130

void TabClass::Unknown_006A19E0()
{
    unknown_button_abe400.ID = 0xF0;
    unknown_button_abe400.unknown_50 = unknown_drawer_8323cc;
    unknown_button_abe400.IsOn = false;
    unknown_button_abe400.ToggleType = 0;
    unknown_button_abe400.Flags = 5;
    void const *shape = unknown_buffer_ac1098;
    Rect area = *unknown_rect_ac1204;
    unknown_button_abe400.Set_Position(area.X, area.Y);
    unknown_button_abe400.Set_Shape(shape, 0, 0);
    unknown_button_abe390.ID = 0xF1;
    unknown_button_abe390.unknown_50 = unknown_drawer_8323cc;
    unknown_button_abe390.IsOn = false;
    unknown_button_abe390.ToggleType = 0;
    unknown_button_abe390.Flags = 5;
    Rect area2 = *unknown_rect_ac1208;
    unknown_button_abe390.Set_Position(area2.X, area2.Y);
    unknown_button_abe390.Set_Shape(shape, 0, 0);
}
