#include "shared/win32_api.hpp"
#include "shared/surface.hpp"
#include "shared/hicolor.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Draws a bevelled button frame thickness pixels wide around rect, one green shade per edge.
void __fastcall unknown_draw_button_frame_5fdcb0(Surface *surface, Rect const &rect, int thickness)
{
    Rect frame = rect;
    int top_color = Build_Hicolor_Pixel(0x27, 0xf8, 0x74);
    int bottom_color = Build_Hicolor_Pixel(0x13, 0x7b, 0x39);
    int left_color = Build_Hicolor_Pixel(0x1e, 0xba, 0x57);
    int right_color = Build_Hicolor_Pixel(0x18, 0x99, 0x47);
    frame.X += -1 - thickness;
    frame.Y += -1 - thickness;
    frame.Width += 2 * thickness + 2;
    frame.Height += 2 * thickness + 2;
    for (int i = 0; i < thickness; i++) {
        surface->Draw_Line(Point2D(frame.X + i, frame.Y + i), Point2D(frame.X + frame.Width - 2 - i, frame.Y + i), top_color);
        surface->Draw_Line(Point2D(frame.X + i, frame.Y + frame.Height - 1 - i),
                           Point2D(frame.X + frame.Width - 1 - i, frame.Y + frame.Height - 1 - i), bottom_color);
        surface->Draw_Line(Point2D(frame.X + i, frame.Y + i + 1), Point2D(frame.X + i, frame.Y + frame.Height - 1 - i), left_color);
        surface->Draw_Line(Point2D(frame.X + frame.Width - 1 - i, frame.Y + i),
                           Point2D(frame.X + frame.Width - 1 - i, frame.Y + frame.Height - 2 - i), right_color);
    }
}

}
