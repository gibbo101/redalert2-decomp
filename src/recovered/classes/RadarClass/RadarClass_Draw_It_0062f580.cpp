// void RadarClass::Draw_It(bool complete) (0x0062F580, slot 16)
// Draws the radar frame: the background art and the two radar buttons when a
// redraw is due, the radar button's open/close animation (+0x14A8 2 closes,
// 3 opens, one frame per four ticks of +0x14FC), the radar events and image,
// the per-mode button frame (+0x14AC), the two sidebar buttons on a complete
// redraw, and grows the redraw rectangle +0x1208 by the radar buttons that
// need drawing.
#include "shared/radar.hpp"
#include "shared/sidebar.hpp"
#include "shared/palette.hpp"
// @ref ?unknown_buffer_ac0ff0@@3PAXA=00ac0ff0
// @ref ?RadarEventClass_unknown_all_63b910@@YAXXZ=0063b910
// @ref ?Unknown_00633210@RadarClass@@QAEXXZ=00633210
// @ref ?Unknown_00630350@RadarClass@@QAEXXZ=00630350
// @ref ?Unknown_00633D30@RadarClass@@QAEXXZ=00633d30

void RadarClass::Draw_It(bool complete)
{
    bool redraw = false;
    if (unknown_flag_a40d13) {
        unknown_14d6 = false;
        unknown_14d5 = false;
        return;
    }
    unknown_14d6 = (unknown_14d6 == true || complete == true);
    unknown_14d5 = (unknown_14d5 == true || unknown_14d6 == true);
    if (unknown_14d5) {
        ShapeFileStruct const *shape = (ShapeFileStruct const *)unknown_buffer_ac0ff0;
        CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, shape, 0,
                      Point2D(unknown_11e0, unknown_11e4), unknown_surface_839948->Get_Rect(), 0, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
        unknown_button_ab63e8.Draw_Me(true);
        unknown_button_ab6380.Draw_Me(true);
    }

    if (unknown_14a8 != 1) {
        if (unknown_14a8 != 0 && unknown_14fc.Value() == 0) {
            unknown_14fc = 4;
            redraw = true;
            if (unknown_14a8 == 2) {
                if (--unknown_14f8 <= 0) {
                    unknown_14a8 = 0;
                    unknown_14bc.Unknown_00406070();
                    unknown_14f8 = 0;
                }
            } else {
                if (++unknown_14f8 >= 32) {
                    unknown_14bc.Unknown_00406070();
                    unknown_14a8 = 1;
                    unknown_14d6 = true;
                    unknown_14f8 = 32;
                }
            }
        }
        if (unknown_14a8 != 1 && (unknown_14d5 == true || redraw)
            && unknown_14f8 >= 0 && unknown_14f8 < ((ShapeFileStruct const *)RadarButton.unknown_28)->FrameCount) {
            CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, (ShapeFileStruct const *)RadarButton.unknown_28, unknown_14f8,
                          Point2D(unknown_11e0, unknown_11e8), unknown_surface_839948->Get_Rect(), 0, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            unknown_1208 = Rect(unknown_11e0, unknown_11e8, unknown_int_7add80, 110);
        }
    }

    RadarEventClass_unknown_all_63b910();
    Unknown_00633210();
    if (unknown_14a8 == 1) {
        switch (unknown_14ac) {
        case 1:
        case 4:
            break;
        case 2:
            if (unknown_14d5) {
                unknown_14d5 = false;
                if (unknown_14d6) {
                    CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, (ShapeFileStruct const *)RadarButton.unknown_28, 32,
                                  Point2D(unknown_11e0, unknown_11e8), unknown_surface_839948->Get_Rect(), 0, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
                    Unknown_00630350();
                    unknown_1208 = Rect(unknown_11e0, unknown_11e8, unknown_int_7add80, 110);
                } else {
                    Unknown_00630350();
                    unknown_1208 = Rect(unknown_11ec, unknown_11f0, unknown_11fc, unknown_1200);
                }
            }
            break;
        case 3:
            Unknown_00633D30();
            break;
        default:
            if (unknown_14d5) {
                unknown_14d5 = false;
                CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, (ShapeFileStruct const *)RadarButton.unknown_28, 0,
                              Point2D(unknown_11e0, unknown_11e8), unknown_surface_839948->Get_Rect(), 0, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
                unknown_1208 = Rect(unknown_11e0, unknown_11e8, unknown_int_7add80, 110);
            }
            break;
        }
    }

    if (unknown_14d6) {
        unknown_14d6 = false;
        SidebarClass::unknown_button_abcc58.Draw_Me(true);
        SidebarClass::unknown_button_ab96b8.Draw_Me(true);
    }
    if (unknown_button_ab63e8.unknown_54) {
        unknown_1208 = Union(unknown_1208, unknown_rect_ab6468);
        unknown_flag_abcd84 = true;
    }
    if (unknown_button_ab6380.unknown_54) {
        unknown_1208 = Union(unknown_1208, unknown_rect_ab6338);
        unknown_flag_abcd84 = true;
    }
}
