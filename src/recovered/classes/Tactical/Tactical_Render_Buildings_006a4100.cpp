// void Tactical::Render_Buildings(Rect const &xpanrect, Rect const &ypanrect, bool fullredraw)
// (0x006A4100): redraws the buildings (0x006A9F60) of every cell flagged
// for redraw, of every dirty area (last first), then of the whole view or of
// the strips the pan exposed (TibSun Tactical::Render_Buildings).
#include "shared/tactical.hpp"
#include "shared/tactical_lists.hpp"
#include "shared/cell.hpp"
#include "shared/display.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?DirtyAreas@TacticalLists@@2V?$DynamicVectorClass@UDirtyAreaStruct@@@@A=00abe5b0

void Tactical::Render_Buildings(Rect const &xpanrect, Rect const &ypanrect, bool fullredraw)
{
    int i;

    if (unknown_e0 > 0) {
        for (i = 0; i < unknown_e0; i++) {
            CoordStruct coord = Coord_Snap(Cell_Center(unknown_e4[i]->MapCoords));
            Point2D pixel;
            Coord_To_Pixel(coord, pixel);

            Rect rect = Rect(pixel.X - 30, pixel.Y, 60, 30);
            rect.Y += unknown_rect_839630.Y;
            Rect cliprect = rect;

            Unknown_006A9F60(true, rect, cliprect);
        }
    }

    if (TacticalLists::DirtyAreas.Count()) {
        for (i = TacticalLists::DirtyAreas.Count() - 1; i >= 0; i--) {
            Rect redraw = TacticalLists::DirtyAreas[i].Area;
            redraw.Y += unknown_rect_839630.Y;
            redraw = Intersect(unknown_rect_839630, redraw);

            if (redraw.Is_Valid()) {
                Rect cliprect = redraw;
                Unknown_006A9F60(true, redraw, cliprect);
            }
        }
    }

    if (fullredraw) {
        Unknown_006A9F60(true, unknown_rect_839630, unknown_rect_839630);
    } else {
        if (xpanrect.Is_Valid()) {
            Unknown_006A9F60(true, xpanrect, xpanrect);
        }
        if (ypanrect.Is_Valid()) {
            Unknown_006A9F60(true, ypanrect, ypanrect);
        }
    }
}
