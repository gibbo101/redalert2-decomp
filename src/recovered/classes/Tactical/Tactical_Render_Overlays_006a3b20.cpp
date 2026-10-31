// void Tactical::Render_Overlays(Rect const &xpanrect, Rect const &ypanrect, bool fullredraw)
// (0x006A3B20): draws the overlays (0x006A7350) of the whole view, or of the
// strips the pan exposed, then of every cell flagged for redraw and of every
// dirty area, last first (TibSun Tactical::Render_Overlays).
#include "shared/tactical.hpp"
#include "shared/tactical_lists.hpp"
#include "shared/cell.hpp"
#include "shared/display.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?DirtyAreas@TacticalLists@@2V?$DynamicVectorClass@UDirtyAreaStruct@@@@A=00abe5b0
// @ref ?Draw_Overlays@Tactical@@QAEXABVRect@@@Z=006a7350

void Tactical::Render_Overlays(Rect const &xpanrect, Rect const &ypanrect, bool fullredraw)
{
    if (fullredraw) {
        Draw_Overlays(unknown_rect_839630);
    } else {
        if (xpanrect.Is_Valid()) {
            Draw_Overlays(xpanrect);
        }
        if (ypanrect.Is_Valid()) {
            Draw_Overlays(ypanrect);
        }
    }

    if (unknown_e0 > 0 && !fullredraw) {
        for (int i = 0; i < unknown_e0; i++) {
            CoordStruct coord = Coord_Snap(Cell_Center(unknown_e4[i]->MapCoords));
            Point2D pixel = Coord_To_Pixel_Absolute(coord);
            Point2D view = unknown_b0;
            pixel -= view;
            Rect rect = Rect(pixel.X - 30, pixel.Y, 60, 30);
            rect.Y += unknown_rect_839630.Y;

            Draw_Overlays(rect);
        }
    }

    if (TacticalLists::DirtyAreas.Count()) {
        for (int i = TacticalLists::DirtyAreas.Count() - 1; i >= 0; i--) {
            Rect redraw = TacticalLists::DirtyAreas[i].Area;
            redraw.Y += unknown_rect_839630.Y;
            redraw = Intersect(unknown_rect_839630, redraw);

            if (redraw.Is_Valid()) {
                Draw_Overlays(redraw);
            }
        }
    }
}
