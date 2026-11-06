// void Tactical::Draw_Overlays(Rect const &area) (0x006A7350): draws the overlay
// of every cell of the diagonal band under area whose overlay rectangle meets the
// clipped area, then the overlay shadows over the same band (TibSun
// Tactical::Draw_Overlays).
#include "shared/tactical.hpp"
#include "shared/cell.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380
// @ref ?unknown_4749c0@CellClass@@QAEXABUPoint2D@@ABVRect@@@Z=004749c0

void Tactical::Draw_Overlays(Rect const &area)
{
    Point2D leptons = Unknown_006A2900(Point2D(area.X, area.Y) + Point2D(TacPixelX, TacPixelY) - Point2D(unknown_rect_839630.X, unknown_rect_839630.Y));
    CoordStruct lepton(leptons.X, leptons.Y, 0);
    if (lepton.Y < 0) lepton.Y = 0;
    if (lepton.X < 0) lepton.X = 0;

    Cell origin = Map[lepton].MapCoords;
    Cell base = origin;

    int ycount = area.Height / 15 + 20;
    int xcount = area.Width / 60 + 4;

    Rect cliprect = Intersect(unknown_rect_839630, area);
    base += Cell(-4, -2);

    int ix, iy;
    for (iy = ycount + 1; iy >= 0; iy--) {
        Cell step(iy / 2, (iy + 1) / 2);
        Cell cell = base + step;

        for (ix = xcount; ix > 0; ix--) {
            if (Map.Unknown_0054AAB0(cell)) {
                CellClass *cellptr = &Map[cell];
                if (cellptr->OverlayIndex != -1) {
                    Rect render = cellptr->unknown_474eb0();
                    Rect visible = cliprect.Intersect(render);
                    if (visible.Is_Valid()) {
                        Point2D pixel;
                        Coord_To_Pixel(Coord_Snap(Cell_Center(cell)), pixel);
                        pixel.X += -30;
                        cellptr->unknown_4749c0(pixel, cliprect);
                    }
                }
            }
            cell += Cell(1, -1);
        }
    }

    for (iy = ycount + 1; iy >= 0; iy--) {
        Cell step(iy / 2, (iy + 1) / 2);
        Cell cell = base + step;

        for (ix = xcount; ix > 0; ix--) {
            if (Map.Unknown_0054AAB0(cell)) {
                CellClass *cellptr = &Map[cell];
                if (cellptr->OverlayIndex != -1) {
                    Rect shadow = cellptr->unknown_475100();
                    Rect visible = cliprect.Intersect(shadow);
                    if (visible.Is_Valid()) {
                        Point2D pixel;
                        Coord_To_Pixel(Coord_Snap(Cell_Center(cell)), pixel);
                        pixel.X += -30;
                        cellptr->unknown_474830(pixel, cliprect);
                    }
                }
            }
            cell.X++;
            cell.Y--;
        }
    }
}
