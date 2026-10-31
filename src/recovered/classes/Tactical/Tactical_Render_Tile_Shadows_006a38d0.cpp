// void Tactical::Render_Tile_Shadows(Rect const &xpanrect, Rect const &ypanrect, bool fullredraw)
// (0x006A38D0): draws the tile shadows (0x006A8240) of the whole view, or of the strips the pan exposed, then of every
// cell flagged for redraw that is in view and of every dirty area, last first
// (TibSun Tactical::Render_Tile_Shadows).
#include "shared/tactical.hpp"
#include "shared/tactical_lists.hpp"
#include "shared/cell.hpp"
#include "shared/display.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?DirtyAreas@TacticalLists@@2V?$DynamicVectorClass@UDirtyAreaStruct@@@@A=00abe5b0
// @ref ?Draw_Tile_Shadows@Tactical@@QAEXABVRect@@0@Z=006a8240

void Tactical::Render_Tile_Shadows(Rect const &xpanrect, Rect const &ypanrect, bool fullredraw)
{
    if (fullredraw) {
        Draw_Tile_Shadows(unknown_rect_839630, unknown_rect_839630);
    } else {
        if (xpanrect.Is_Valid()) {
            Draw_Tile_Shadows(xpanrect, xpanrect);
        }
        if (ypanrect.Is_Valid()) {
            Draw_Tile_Shadows(ypanrect, ypanrect);
        }
    }

    if (unknown_e0 > 0 && !fullredraw) {
        for (int i = 0; i < unknown_e0; i++) {
            CoordStruct coord = Coord_Snap(Cell_Center(unknown_e4[i]->MapCoords));
            Point2D pixel;
            pixel = Coord_To_Pixel_Absolute(coord);
            pixel -= Point2D(unknown_b0.X, unknown_b0.Y);
            Rect rect = Rect(pixel.X - 30, pixel.Y, 60, 30);
            rect.Y += unknown_rect_839630.Y;

            Rect inter = Intersect(unknown_rect_839630, rect);

            if (inter.Is_Valid()) {
                Draw_Tile_Shadows(inter, inter);
            }
        }
    }

    if (TacticalLists::DirtyAreas.Count()) {
        for (int j = TacticalLists::DirtyAreas.Count() - 1; j >= 0; j--) {
            Rect redraw = TacticalLists::DirtyAreas[j].Area;
            redraw.Y += unknown_rect_839630.Y;
            redraw = Intersect(unknown_rect_839630, redraw);

            if (redraw.Is_Valid()) {
                Draw_Tile_Shadows(redraw, redraw);
            }
        }
    }
}
