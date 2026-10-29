// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
// @ref ?unknown_color_a76158@OwnerDraw@@3HA=00a76158
#include "shared/win32_api.hpp"
#include "shared/surface.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Draws a frame thickness pixels wide around rect, in the owner-draw frame colour by default.
void __fastcall unknown_5fdb20(Surface *surface, Rect const &rect, int thickness, int color)
{
    if (color == -1) {
        color = unknown_5fda40(unknown_color_a76158);
    }
    Rect frame = rect;
    frame.X -= thickness;
    frame.Y -= thickness;
    frame.Width += thickness * 2;
    frame.Height += thickness * 2;
    for (int i = 0; i < thickness; i++) {
        surface->Draw_Line(Point2D(frame.X + i, frame.Y + i), Point2D(frame.X + frame.Width - 2 - i, frame.Y + i), color);
        surface->Draw_Line(Point2D(frame.X + i, frame.Y + frame.Height - 1 - i),
                           Point2D(frame.X + frame.Width - 1 - i, frame.Y + frame.Height - 1 - i), color);
        surface->Draw_Line(Point2D(frame.X + i, frame.Y + i + 1), Point2D(frame.X + i, frame.Y + frame.Height - 1 - i), color);
        surface->Draw_Line(Point2D(frame.X + frame.Width - 1 - i, frame.Y + i),
                           Point2D(frame.X + frame.Width - 1 - i, frame.Y + frame.Height - 2 - i), color);
    }
}

}
