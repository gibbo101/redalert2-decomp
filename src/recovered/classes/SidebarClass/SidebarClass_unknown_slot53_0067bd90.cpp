// void SidebarClass::unknown_slot53() (0x0067BD90, slot 53)
// Loads the sidebar shapes: a new drawer for the current palette, the
// clock, the sell/repair/tab/scroll button shapes and the sidebar pieces.
#include "shared/sidebar.hpp"
// @ref ?unknown_slot53@PowerClass@@UAEXXZ=0061c560
// @ref ?Unknown_006F45E0@@YAPAVPaletteClass@@XZ=006f45e0
// @ref ?unknown_drawer_8323cc@@3PAVConvertClass@@A=008323cc
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0ConvertClass@@QAE@ABVPaletteClass@@0PAVSurface@@H_N@Z=00483650
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?Unknown_Load_Shape_00495270@@YIPBXPBDAA_N@Z=00495270
// @ref ?Set_Shape@ShapeButtonClass@@UAEXPBXHH@Z=00675130
// @ref ?Set_Allocated@ShapeButtonClass@@QAEX_N@Z=006751d0
// @ref _sprintf=007820f4
// @ref ?unknown_shapes_abcd20@@3PAPBXA=00abcd20
// @ref ?unknown_shapes_allocated_abcd40@@3PA_NA=00abcd40
// @ref ??_C@_09JPCP@ADDON?4SHP?$AA@=007f3dc8
// @ref ??_C@_09LOKN@SIDE3?4SHP?$AA@=007f3dd4
// @ref ??_C@_09BOII@SIDE2?4SHP?$AA@=007f3de0
// @ref ??_C@_09POOH@SIDE1?4SHP?$AA@=007f3dec
// @ref ??_C@_08MPGF@R?9UP?4SHP?$AA@=007f3df8
// @ref ??_C@_08MDGH@R?9DN?4SHP?$AA@=007f3e04
// @ref ??_C@_0M@MIPJ@TAB?$CF02d?4SHP?$AA@=007f3e10
// @ref ??_C@_0L@ENIH@REPAIR?4SHP?$AA@=007f3e1c
// @ref ??_C@_08GFHD@SELL?4SHP?$AA@=007f3e28
// @ref ??_C@_0M@JIPG@GCLOCK2?4SHP?$AA@=007f3e34

void SidebarClass::unknown_slot53()
{
    PowerClass::unknown_slot53();
    PaletteClass palette = *Unknown_006F45E0();
    if (unknown_drawer_8323cc) {
        delete unknown_drawer_8323cc;
        unknown_drawer_8323cc = 0;
    }
    unknown_drawer_8323cc = new ConvertClass(palette, palette, unknown_surface_839950, 1, false);
    unknown_shapes_abcd20[7] = Unknown_Load_Shape_00495270("GCLOCK2.SHP", unknown_shapes_allocated_abcd40[7]);

    bool allocated = false;
    unknown_button_ab96b8.Set_Shape(Unknown_Load_Shape_00495270("SELL.SHP", allocated));
    unknown_button_ab96b8.Set_Allocated(allocated);
    unknown_button_ab96b8.unknown_50 = unknown_drawer_8323cc;

    unknown_button_abcc58.Set_Shape(Unknown_Load_Shape_00495270("REPAIR.SHP", allocated));
    unknown_button_abcc58.Set_Allocated(allocated);
    unknown_button_abcc58.unknown_50 = unknown_drawer_8323cc;

    for (int index = 0; index < 4; index++) {
        char name[256];
        sprintf(name, "TAB%02d.SHP", index);
        unknown_buttons_ab9508[index].Set_Shape(Unknown_Load_Shape_00495270(name, allocated));
        unknown_buttons_ab9508[index].Set_Allocated(allocated);
        unknown_buttons_ab9508[index].unknown_50 = unknown_drawer_8323cc;
    }

    unknown_button_abcbe8.Set_Shape(Unknown_Load_Shape_00495270("R-DN.SHP", allocated));
    unknown_button_abcbe8.Set_Allocated(allocated);
    unknown_button_abcbe8.unknown_50 = unknown_drawer_8323cc;

    unknown_button_abccc0.Set_Shape(Unknown_Load_Shape_00495270("R-UP.SHP", allocated));
    unknown_button_abccc0.Set_Allocated(allocated);
    unknown_button_abccc0.unknown_50 = unknown_drawer_8323cc;

    unknown_shapes_abcd20[0] = Unknown_Load_Shape_00495270("SIDE1.SHP", unknown_shapes_allocated_abcd40[0]);
    unknown_shapes_abcd20[1] = Unknown_Load_Shape_00495270("SIDE2.SHP", unknown_shapes_allocated_abcd40[1]);
    unknown_shapes_abcd20[2] = Unknown_Load_Shape_00495270("SIDE3.SHP", unknown_shapes_allocated_abcd40[2]);
    unknown_shapes_abcd20[3] = Unknown_Load_Shape_00495270("ADDON.SHP", unknown_shapes_allocated_abcd40[3]);
}
