// void __fastcall GScreenClass::Blit(bool mouse, Surface *surface, Rect const *area) (0x004E0C90)
// Westwood's Update_Visible_Surface: copies area (the whole surface when null) of surface to the window's
// client area, offset by the screen shake, moved past a left sidebar, scaled by the tactical zoom, with
// the strips the shake uncovers cleared; mouse draws the cursor over the copy for 50 ms.
#include "shared/gscreen.hpp"
#include "shared/map_view.hpp"
#include "shared/mouse.hpp"
#include "shared/tool_tip.hpp"
#include "shared/win32_api.hpp"
#include "shared/crt_memory.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref __imp__GetClientRect@8=0079a4b8
// @ref __imp__ClientToScreen@8=0079a4ac
// @ref __imp__Sleep@4=0079a1e4
// @ref ?unknown_flag_a40b30@@3_NA=00a40b30
// @ref ?unknown_a40d13@@3_NA=00a40d13
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_int_839648@@3HA=00839648
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref __ftol=0077f110
// @ref ?unknown_flag_a40380@@3_NA=00a40380
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Is_Active@ToolTipManager@@QBE_NXZ=006ebee0
// @ref ?unknown_flag_8373f6@@3_NA=008373f6
// @ref ?unknown_ac11fc@@3PAUUnknownStruct_AC11FC@@A=00ac11fc
// @ref ?unknown_int_a40d34@@3HA=00a40d34
// @ref ?WWMouse@@3PAVMouse@@A=00839c68

void __fastcall GScreenClass::Blit(bool mouse, Surface *surface, Rect const *area)
{
    Rect rect;
    if (area == 0) {
        rect = surface->Get_Rect();
        area = &rect;
    }

    RECT client_rect;
    if (GetClientRect(MainWindow, &client_rect)) {

    POINT screen_pt;
    screen_pt.x = client_rect.left;
    screen_pt.y = client_rect.top;
    if (ClientToScreen(MainWindow, &screen_pt)) {

    Rect dest_rect(screen_pt.x, screen_pt.y, surface->Get_Width(), surface->Get_Height());

    if (Map.ShakeX == 0 && Map.ShakeY == 0) {
    } else {
        if (Map.ShakeX > 0) {
            dest_rect.X += Map.ShakeX;
            dest_rect.Width -= Map.ShakeX;
        } else if (Map.ShakeX < 0) {
            dest_rect.Width += Map.ShakeX;
        }
        if (Map.ShakeY > 0) {
            dest_rect.Y += Map.ShakeY;
            dest_rect.Height -= Map.ShakeY;
        } else if (Map.ShakeY < 0) {
            dest_rect.Height += Map.ShakeY;
        }
    }

    if (!unknown_flag_a40b30 && !unknown_a40d13) {
        dest_rect.X += (((unknown_surface_839948->Get_Width() < unknown_int_839648 - dest_rect.Width) ? unknown_surface_839948->Get_Width() : unknown_int_839648 - dest_rect.Width) > 0)
            ? ((unknown_surface_839948->Get_Width() < unknown_int_839648 - dest_rect.Width) ? unknown_surface_839948->Get_Width() : unknown_int_839648 - dest_rect.Width)
            : 0;
    }

    Rect src_rect = *area;
    if (unknown_tactical_83996c != 0 && unknown_tactical_83996c->unknown_c0 != 1.0) {
        int zoom_surface_width = surface->Get_Width();
        int zoom_surface_height = surface->Get_Height();
        Rect tmp;
        double zoomed_width = (double)zoom_surface_width / unknown_tactical_83996c->unknown_c0;
        tmp.X = (int)(((double)zoom_surface_width - zoomed_width) / 2.0);
        double zoomed_height = (double)zoom_surface_height / unknown_tactical_83996c->unknown_c0;
        tmp.Y = (int)(((double)zoom_surface_height - zoomed_height) / 2.0);
        tmp.Width = (int)zoomed_width;
        tmp.Height = (int)zoomed_height;
        src_rect = tmp;
    } else {
        if (src_rect.Width >= dest_rect.Width) {
            src_rect.Width = dest_rect.Width;
        }
        if (src_rect.Height >= dest_rect.Height) {
            src_rect.Height = dest_rect.Height;
        }
    }

    if (Map.ShakeY < 0) {
        src_rect.Y -= Map.ShakeY;
    }
    if (Map.ShakeX < 0) {
        src_rect.X -= Map.ShakeX;
    }

    if (unknown_flag_a40380) {
        bool active = ToolTips != 0 && ToolTips->Is_Active();
        if (!unknown_flag_8373f6 && Map.ShakeY == 0 && !active) {
            dest_rect.Height -= unknown_ac11fc->unknown_0c;
            src_rect.Height -= unknown_ac11fc->unknown_0c;
        }
    }

    if (Map.ShakeX != 0) {
        Rect fill_rect;
        fill_rect.Set(fill_rect.X, screen_pt.y, abs(Map.ShakeX), surface->Get_Height() - unknown_ac11fc->unknown_0c);
        fill_rect.X = Map.ShakeX < 0 ? dest_rect.X + dest_rect.Width : dest_rect.X - Map.ShakeX;
        unknown_surface_839950->Fill_Rect(unknown_surface_839950->Get_Rect(), fill_rect, 0);
    }
    if (Map.ShakeY != 0) {
        Rect fill_rect;
        fill_rect.Set(screen_pt.x, fill_rect.Y, surface->Get_Width(), abs(Map.ShakeY));
        fill_rect.Y = Map.ShakeY < 0 ? dest_rect.Y + dest_rect.Height : dest_rect.Y - Map.ShakeY;
        unknown_surface_839950->Fill_Rect(unknown_surface_839950->Get_Rect(), fill_rect, 0);
    }

    if (mouse && WWMouse != 0) {
        WWMouse->Draw_Mouse(surface, false);
    }

    unknown_surface_839950->Copy_From(dest_rect, *surface, src_rect, false, unknown_int_a40d34 == 0);

    if (mouse && WWMouse != 0) {
        Sleep(50);
        WWMouse->Erase_Mouse(surface, false);
    }
    }
    }
}
