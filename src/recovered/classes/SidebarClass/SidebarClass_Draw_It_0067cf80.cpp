// void SidebarClass::Draw_It(bool complete) (0x0067CF80, slot 16)
// Draws the sidebar onto its surface: the frame pieces (SIDE1, a SIDE2 per
// icon row, SIDE3, ADDON), the buttons, the overlay at 0xABCD30-0xABCD38,
// the active strip and the power bar; then notes repaints.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
#include "shared/tool_tip.hpp"
// @ref ?unknown_mouse_8324e0@@3VMouseClass@@A=008324e0
// @ref ?unknown_rect_ab9688@StripClass@SidebarClass@@2VRect@@A=00ab9688
// @ref ?unknown_rect_8336e8@@3VRect@@A=008336e8
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948
// @ref ?unknown_drawer_8323cc@@3PAVConvertClass@@A=008323cc
// @ref ?unknown_shapes_abcd20@@3PAPBXA=00abcd20
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
// @ref ?unknown_flag_abcd84@@3_NA=00abcd84
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Refresh@CCToolTip@@UAEX_N@Z=0046e230
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0
// @ref ?Draw_It@PowerClass@@UAEX_N@Z=0061c8c0
// @ref ?Draw_Me@ShapeButtonClass@@UAEHH@Z=006751e0
// @ref ?Unknown_0067F800@StripClass@SidebarClass@@QAEX_N@Z=0067f800
// @ref ?Unknown_0067D420@SidebarClass@@QAEX_N@Z=0067d420
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64

void SidebarClass::Draw_It(bool complete)
{
    unknown_rect_8336e8 = StripClass::unknown_rect_ab9688;
    Surface *old = unknown_surface_83995c;
    unknown_surface_83995c = unknown_surface_839948;
    bool drawn = false;
    Rect window(0, 0, unknown_surface_839948->Get_Width(), unknown_surface_839948->Get_Height());
    complete = complete || unknown_4ee2 || unknown_4ee3;

    if (unknown_4ee1 && complete && !unknown_flag_a40d13) {
        if (unknown_4ee3) {
            drawn = true;
            CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_shapes_abcd20[0], 0,
                Point2D(0, unknown_int_839624), window, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            int y = unknown_abcd64;
            int row = 0;
            while (true) {
                if (row >= StripClass::Max_Visible_Rows()) {
                    break;
                }
                CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_shapes_abcd20[1], 0,
                    Point2D(0, y), window, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
                y += ((ShapeFileStruct const *)unknown_shapes_abcd20[1])->Height;
                row++;
            }
            CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_shapes_abcd20[2], 0,
                Point2D(0, y), window, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_shapes_abcd20[3], 0,
                Point2D(0, y + ((ShapeFileStruct const *)unknown_shapes_abcd20[2])->Height), window, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
        }
        unknown_button_ab96b8.Draw_Me(drawn);
        unknown_button_abcc58.Draw_Me(drawn);
        for (int index = 0; index < 4; index++) {
            unknown_buttons_ab9508[index].Draw_Me(true);
        }
        unknown_button_abcbe8.Draw_Me(drawn);
        unknown_button_abccc0.Draw_Me(drawn);
        if (unknown_4ed4) {
            CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_shapes_abcd20[4], unknown_4ed0,
                Point2D(0, unknown_abcd64), window, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_shapes_abcd20[5], unknown_4ed0,
                Point2D(0, unknown_abcd64), window, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_shapes_abcd20[6], unknown_4ed0,
                Point2D(0, unknown_abcd64), window, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
        }
        unknown_flag_abcd84 = true;
    }
    Column[unknown_4ed8].Unknown_0067F800(unknown_4ee3);
    PowerClass::Draw_It(complete || drawn);
    if (unknown_button_ab96b8.unknown_54) {
        unknown_button_ab96b8.unknown_54 = false;
        unknown_flag_abcd84 = true;
    }
    if (unknown_button_abcc58.unknown_54) {
        unknown_button_abcc58.unknown_54 = false;
        unknown_flag_abcd84 = true;
    }
    for (int tab = 0; tab < 4; tab++) {
        if (unknown_buttons_ab9508[tab].unknown_54) {
            unknown_flag_abcd84 = true;
            unknown_buttons_ab9508[tab].unknown_54 = false;
        }
    }
    if (unknown_button_abcbe8.unknown_54) {
        unknown_button_abcbe8.unknown_54 = false;
        unknown_flag_abcd84 = true;
    }
    if (unknown_button_abccc0.unknown_54) {
        unknown_button_abccc0.unknown_54 = false;
        unknown_flag_abcd84 = true;
    }
    if (ToolTips) {
        ToolTips->Refresh(true);
    }
    Unknown_0067D420(unknown_flag_abcd84 || unknown_4ee3);
    unknown_4ee2 = false;
    unknown_4ee3 = false;
    unknown_surface_83995c = old;
}
