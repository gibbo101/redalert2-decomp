// void TabClass::Draw_It(bool complete) (0x006A12D0, slot 16)
// Redraws the command bar when it needs it: when asked to, when one of its
// buttons wants a repaint, when the mouse moved over it or left it, or when
// the surface it last drew on is not the current one. The bar's pieces are
// drawn as shapes (background, caps, tiles, the open bar's tail), the
// buttons that asked for a repaint are drawn again, and the surface is
// remembered (the four most recent). Then the sidebar's drawing.
#include "shared/tab.hpp"
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_drawer_8323cc@@3PAVConvertClass@@A=008323cc
// @ref ?unknown_buffer_ac10f8@@3PAXA=00ac10f8
// @ref ?unknown_buffer_ac1048@@3PAXA=00ac1048
// @ref ?unknown_buffer_ac1098@@3PAXA=00ac1098
// @ref ?unknown_buffer_ac10a4@@3PAXA=00ac10a4
// @ref ?unknown_buffer_ac10b0@@3PAXA=00ac10b0
// @ref ?unknown_int_ac0ff4@@3HA=00ac0ff4
// @ref ?unknown_flag_abcd84@@3_NA=00abcd84
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0
// @ref ?Draw_It@SidebarClass@@UAEX_N@Z=0067cf80
// @ref ?Draw_Me@ShapeButtonClass@@UAEHH@Z=006751e0
// @ref ?Unknown_00494530@UnknownTab4EEC@@QAEX_N@Z=00494530
// @ref _?$S94@?1??Draw_It@TabClass@@UAEX_N@Z@4EA=00abe298
// @ref _?last_spot@?1??Draw_It@TabClass@@UAEX_N@Z@4UUnknownTabSpot@@A=00abe348
// @ref _?mouse_inside@?1??Draw_It@TabClass@@UAEX_N@Z@4_NA=00abe480
// @ref _?drawn_on@?1??Draw_It@TabClass@@UAEX_N@Z@4PAPAVSurface@@A=00abe350
// @ref _?drawn_count@?1??Draw_It@TabClass@@UAEX_N@Z@4HA=00abe484
// @ref _$E95=006a1700

void TabClass::Draw_It(bool complete)
{
    static UnknownTabSpot last_spot;
    static bool mouse_inside;
    static Surface *drawn_on[4];
    static int drawn_count;

    bool redraw = complete || unknown_4f15;
    if (!redraw) {
        for (int slot = 0; slot < 25; slot++) {
            ShapeButtonClass *button = Unknown_006A0600(slot);
            if (button != 0 && button->unknown_54) {
                redraw = true;
                break;
            }
        }
    }
    if (redraw) {
        drawn_count = 0;
    } else {
        Point2D mouse = WWMouse->Get_Mouse_XY();
        if (unknown_rect_ac11fc->Is_Point_Within(mouse)) {
            mouse_inside = true;
            if (mouse.X != last_spot.X || mouse.Y != last_spot.Y) {
                redraw = true;
            }
        } else {
            if (mouse_inside) {
                redraw = true;
            }
            mouse_inside = false;
        }
        last_spot.X = mouse.X;
        last_spot.Y = mouse.Y;
        if (redraw) {
            drawn_count = 0;
        } else {
            int index;
            for (index = 0; index < drawn_count; index++) {
                if (drawn_on[index] == unknown_surface_83995c) {
                    goto drawn;
                }
            }
            redraw = true;
        drawn:;
        }
    }
    if (!unknown_flag_a40d13) {
        Unknown_006A1710();
        unknown_4eec.Unknown_00494530(true);
        if (redraw) {
            Rect view = unknown_surface_83995c->Get_Rect();
            Point2D where(0, 0);
            where.X = unknown_rect_ac11fc->X;
            where.Y = unknown_rect_ac11fc->Y;
            Rect narrow = view;
            narrow.Width = unknown_rect_ac11fc->Width;
            Surface *surface = unknown_surface_83995c;
            CC_Draw_Shape(surface, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_buffer_ac1048, 0,
                          where, narrow, 0, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            if (unknown_4f14) {
                where.X = unknown_rect_ac1204->X;
                where.Y = unknown_rect_ac1204->Y;
            } else {
                where.X = unknown_rect_ac1208->X;
                where.Y = unknown_rect_ac1208->Y;
            }
            CC_Draw_Shape(surface, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_buffer_ac1098, 0,
                          where, view, 0, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            if (unknown_4f14) {
                where.X = unknown_rect_ac120c->X;
                where.Y = unknown_rect_ac11fc->Y;
                for (int tile = 0; tile < unknown_int_ac0ff4; tile++) {
                    CC_Draw_Shape(surface, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_buffer_ac10a4, 0,
                                  where, view, 0, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
                    where.X += unknown_rect_ac120c->Width;
                }
                for (int slot = 0; slot < 25; slot++) {
                    ShapeButtonClass *button = Unknown_006A0600(slot);
                    if (button != 0 && button->Shape != 0) {
                        button->Draw_Me(1);
                        button->unknown_54 = false;
                    }
                }
            }
            where.X = unknown_rect_ac1210->X;
            CC_Draw_Shape(surface, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_buffer_ac10b0, 0,
                          where, view, 0, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            if (unknown_4f14) {
                unknown_button_abe400.Draw_Me(1);
            } else {
                unknown_button_abe390.Draw_Me(1);
            }
            unknown_4f16 = true;
            unknown_4f15 = false;
            if (drawn_count < sizeof(drawn_on) / sizeof(drawn_on[0])) {
                drawn_count++;
            }
            for (int index = drawn_count - 2; index >= 0; index--) {
                drawn_on[index + 1] = drawn_on[index];
            }
            drawn_on[0] = surface;
        } else {
            unknown_4f16 = false;
        }
    }
    SidebarClass::Draw_It(complete);
}
