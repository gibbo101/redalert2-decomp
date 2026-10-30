// @ref ?unknown_draw_edge_glow_5fd290@OwnerDraw@@YI_NPAVSurface@@ABUPoint2D@@1HH@Z=005fd290
#include "shared/win32_api.hpp"
#include "shared/surface.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Draws an edge glow line from start to end over surface (0x005FD290, not yet recovered).
bool __fastcall unknown_draw_edge_glow_5fd290(Surface *surface, Point2D const &start, Point2D const &end, int color,
                                              int alpha);

// Draws count nested raised (or sunken) glow frames inward from rect, one blend strength per edge.
void __fastcall unknown_draw_edge_glows_5fd810(Surface *surface, Rect const &rect, int raised, int count,
                                               int left_alpha, int top_alpha, int right_alpha, int bottom_alpha)
{
    int light = 0xffff;
    int dark = 0;
    if (!raised) {
        dark = 0xffff;
        light = 0;
    }
    for (int i = 0; i < count; i++) {
        unknown_draw_edge_glow_5fd290(surface, Point2D(rect.X + i, rect.Y + i), Point2D(rect.X + rect.Width - 2 - i, rect.Y + i), light, top_alpha);
        unknown_draw_edge_glow_5fd290(surface, Point2D(rect.X + i, rect.Y + rect.Height - 1 - i),
                                      Point2D(rect.X + rect.Width - 1 - i, rect.Y + rect.Height - 1 - i), dark, bottom_alpha);
        unknown_draw_edge_glow_5fd290(surface, Point2D(rect.X + i, rect.Y + i + 1), Point2D(rect.X + i, rect.Y + rect.Height - 1 - i), light,
                                      left_alpha);
        unknown_draw_edge_glow_5fd290(surface, Point2D(rect.X + rect.Width - 1 - i, rect.Y + i),
                                      Point2D(rect.X + rect.Width - 1 - i, rect.Y + rect.Height - 2 - i), dark, right_alpha);
    }
}

}
