// void TabClass::Init_IO() (0x006A0C50, slot 8)
// After the sidebar's, when the game is not reloading and the shell art is
// loaded: 0x006A1880, then sets up the two side buttons (ids 0xF0 and 0xF1)
// at the 0x00AC1204 and 0x00AC1208 rectangles with the 0x00AC1098 shape.
#include "shared/tab.hpp"
// @ref ?Init_IO@SidebarClass@@UAEXXZ=0067bad0
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
// @ref ?Unknown_Get_Art_006f4590@@YI_NXZ=006f4590
// @ref ?Unknown_006A1880@TabClass@@QAEXXZ=006a1880
// @ref ?unknown_drawer_8323cc@@3PAVConvertClass@@A=008323cc
// @ref ?unknown_buffer_ac1098@@3PAXA=00ac1098
// @ref ?unknown_rect_ac1204@@3PBVRect@@B=00ac1204
// @ref ?unknown_rect_ac1208@@3PBVRect@@B=00ac1208
// @ref ?unknown_button_abe400@TabClass@@2VShapeButtonClass@@A=00abe400
// @ref ?unknown_button_abe390@TabClass@@2VShapeButtonClass@@A=00abe390
// @ref ?Set_Position@GadgetClass@@UAEXHH@Z=004cf660
// @ref ?Set_Shape@ShapeButtonClass@@UAEXPBXHH@Z=00675130

void TabClass::Init_IO()
{
    SidebarClass::Init_IO();
    if (!unknown_flag_a40d13 && Unknown_Get_Art_006f4590()) {
        Unknown_006A1880();
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
}
