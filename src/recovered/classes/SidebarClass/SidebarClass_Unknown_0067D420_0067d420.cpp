// void SidebarClass::Unknown_0067D420(bool complete) (0x0067D420)
// Blits the sidebar surface to the screen: everything when complete or a
// full redraw was requested, else only the changed rectangle (or the credits
// strip when that alone changed).
#include "shared/sidebar.hpp"
#include "shared/mouse.hpp"
#include "shared/win32_window.hpp"
extern bool unknown_session_a40d04;     // 0x00A40D04

void SidebarClass::Unknown_0067D420(bool complete)
{
    if (unknown_4ee1 && unknown_flag_a40958 && unknown_session_a40d04) {
        RECT crect;
        GetClientRect(MainWindow, &crect);
        POINT scrnpt;
        scrnpt.x = crect.left;
        scrnpt.y = crect.top;
        ClientToScreen(MainWindow, &scrnpt);

        if (!unknown_flag_abcd84 && !complete) {
            unknown_flag_abcd84 = false;
            if (unknown_rect_8336e8 == StripClass::unknown_rect_ab9688) {
                if (unknown_4ee4) {
                    WWMouse->Draw_Mouse(unknown_surface_839948, true);
                    unknown_surface_839950->Copy_From(
                        Rect(scrnpt.x + (unknown_flag_a40b30 ? unknown_int_839638 : 0), scrnpt.y, unknown_int_839628, 16),
                        *unknown_surface_839948, Rect(0, 0, unknown_int_839628, 16), false, true);
                    unknown_4ee4 = false;
                    unknown_flag_abcd85 = true;
                }
                unknown_flag_abcd84 = false;
                return;
            }
        } else {
            unknown_flag_abcd84 = true;
        }

        WWMouse->Draw_Mouse(unknown_surface_839948, true);
        if (unknown_rect_8336e8 == StripClass::unknown_rect_ab9688 && !complete) {
            if (unknown_4ee4) {
                unknown_surface_839950->Copy_From(
                    Rect(scrnpt.x + (unknown_flag_a40b30 ? unknown_int_839638 : 0), scrnpt.y, unknown_int_839628, 16),
                    *unknown_surface_839948, Rect(0, 0, unknown_int_839628, 16), false, true);
                unknown_4ee4 = false;
            }
            unknown_surface_839950->Copy_From(
                Rect(scrnpt.x + (unknown_flag_a40b30 ? unknown_int_839638 : 0), scrnpt.y + unknown_int_839624,
                     unknown_int_839628, unknown_surface_839948->Get_Height() - unknown_int_839624),
                *unknown_surface_839948, Rect(0, unknown_int_839624, unknown_int_839628, unknown_int_83962c), false, true);
        } else if (unknown_flag_abcd84) {
            Rect sb_rect = unknown_surface_839948->Get_Rect();
            unknown_surface_839950->Copy_From(
                Rect(scrnpt.x + (unknown_flag_a40b30 ? unknown_int_839638 : 0), scrnpt.y, sb_rect.Width, sb_rect.Height),
                *unknown_surface_839948, Rect(0, 0, sb_rect.Width, sb_rect.Height), false, true);
        } else {
            unknown_surface_839950->Copy_From(
                Rect(scrnpt.x + unknown_rect_8336e8.X + (unknown_flag_a40b30 ? unknown_int_839638 : 0),
                     scrnpt.y + unknown_rect_8336e8.Y, unknown_rect_8336e8.Width, unknown_rect_8336e8.Height),
                *unknown_surface_839948, unknown_rect_8336e8, false, true);
        }
        unknown_flag_abcd85 = true;
    }
    unknown_flag_abcd84 = false;
}
