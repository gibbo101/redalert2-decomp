// void Tactical::Render_Tiles(Rect const &xpanrect, Rect const &ypanrect, bool fullredraw)
// (0x006A3670): draws the iso tiles (0x006A7BA0) of the whole view, or of the strips the pan exposed, then of every
// cell flagged for redraw that is in view and of every dirty area, last first
// (TibSun Tactical::Render_Tiles).
#include "shared/tactical.hpp"
#include "shared/tactical_lists.hpp"
#include "shared/cell.hpp"
#include "shared/display.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?DirtyAreas@TacticalLists@@2V?$DynamicVectorClass@UDirtyAreaStruct@@@@A=00abe5b0
// @ref ?Draw_Tiles@Tactical@@QAEXABVRect@@0@Z=006a7ba0
// @ref ?Draw_Tiles@Tactical@@QAEXABVCell@@ABVRect@@@Z=006a8560

// The cell's map position as a copy (TibSun's CellClass::Fetch_CellID accessor; a CellClass
// member changes another unit's output, so it stays file-local here).
inline Cell Fetch_CellID(CellClass const *cell)
{
    return cell->MapCoords;
}

void Tactical::Render_Tiles(Rect const &xpanrect, Rect const &ypanrect, bool fullredraw)
{
    if (fullredraw) {
        Draw_Tiles(unknown_rect_839630, unknown_rect_839630);
    } else {
        if (xpanrect.Is_Valid()) {
            Draw_Tiles(xpanrect, xpanrect);
        }
        if (ypanrect.Is_Valid()) {
            Draw_Tiles(ypanrect, ypanrect);
        }
    }

    if (unknown_e0 > 0 && !fullredraw) {
        for (int i = 0; i < unknown_e0; i++) {
            CoordStruct coord = Coord_Snap(Cell_Center(unknown_e4[i]->MapCoords));
            Point2D pixel;
            pixel = Unknown_006A27A0(coord);
            pixel -= Point2D(unknown_b0.X, unknown_b0.Y);
            Rect rect = Rect(pixel.X - 30, pixel.Y, 60, 30);
            rect.Y += unknown_rect_839630.Y;

            Rect inter = Intersect(unknown_rect_839630, rect);

            if (inter.Is_Valid()) {
                Draw_Tiles(Fetch_CellID(unknown_e4[i]), rect);
            }
        }
    }

    if (TacticalLists::DirtyAreas.Count() && !fullredraw) {
        for (int j = TacticalLists::DirtyAreas.Count() - 1; j >= 0; j--) {
            Rect redraw = TacticalLists::DirtyAreas[j].Area;
            redraw.Y += unknown_rect_839630.Y;
            redraw = Intersect(unknown_rect_839630, redraw);

            if (redraw.Is_Valid()) {
                Draw_Tiles(redraw, redraw);
            }
        }
    }
}
