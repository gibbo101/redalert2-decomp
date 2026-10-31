// void Tactical::Wipe_Depth(bool fullredraw, int xoff, int yoff, Rect const &cliprect) (0x006A33F0): unless the
// whole view is redrawn, moves every dirty area by the scroll offset and clips it to the view (dropping those
// left empty, clearing the alpha buffer under the rest), then wipes the depth of every cell flagged for redraw
// (TibSun Tactical::Wipe_Depth).
#include "shared/tactical.hpp"
#include "shared/tactical_lists.hpp"
#include "shared/cell.hpp"
#include "shared/display.hpp"
#include "shared/blit.hpp"
#include "shared/win32_window.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?DirtyAreas@TacticalLists@@2V?$DynamicVectorClass@UDirtyAreaStruct@@@@A=00abe5b0
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
// @ref ??GRectPoint2D@@QBE?AU0@ABU0@@Z=0047d040
// @ref ??0Rect@@QAE@ABURectPoint2D@@HH@Z=00453e40
// @ref ?unknown_4754b0@CellClass@@QAEXABUPoint2D@@ABVRect@@@Z=004754b0
// @ref ?unknown_475d60@CellClass@@QBE?AUCoordStruct@@XZ=00475d60
// @ref ?Coord_To_Pixel_Absolute@Tactical@@QAE?AUPoint2D@@ABUCoordStruct@@@Z=006a27a0
// @ref ?Clear_Region_007761C0@ABuffer@@QAEXVRect@@@Z=007761c0
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8

// Point quotient by a scalar, zero giving the origin (TibSun RectPoint2D::operator/; file-local: as a Point2D
// member it changes another unit's output). The sum is rect.hpp's Point2D::operator+.
inline Point2D operator/(Point2D const &point, int value)
{
    if (value == 0) {
        return Point2D(0, 0);
    }
    return Point2D(point.X / value, point.Y / value);
}

// The rectangle moved back by a point and its corner (TibSun TRect::operator- and Top_Left, which this unit
// expands; the other units call their out-of-line copies 0x0047D000 and 0x00435560).
inline RectPoint2D Corner(Rect const &rect)
{
    RectPoint2D point;
    point.Y = rect.Y;
    point.X = rect.X;
    return point;
}

inline Rect Moved_Back(Rect const &rect, RectPoint2D const &point)
{
    return Rect(Corner(rect) - point, rect.Width, rect.Height);
}

void Tactical::Wipe_Depth(bool fullredraw, int xoff, int yoff, Rect const &cliprect)
{
    if (!fullredraw && TacticalLists::DirtyAreas.Count()) {
        for (int i = TacticalLists::DirtyAreas.Count() - 1; i >= 0; i--) {
            Rect redraw = TacticalLists::DirtyAreas[i].Area;
            redraw.X += xoff;
            redraw.Y += yoff;
            redraw = Intersect(Moved_Back(unknown_rect_839630, Corner(unknown_rect_839630)), redraw);
            TacticalLists::DirtyAreas[i].Area = redraw;

            if (!redraw.Is_Valid()) {
                TacticalLists::DirtyAreas.Delete(i);
            } else {
                ABufferPtr->Clear_Region_007761C0(redraw);
            }
        }
    }

    if (unknown_e0 > 0 && !fullredraw) {
        for (int i = 0; i < unknown_e0; i++) {
            CoordStruct coord = unknown_e4[i]->unknown_475d60();
            coord.Z = 0;
            Point2D pixel;
            Coord_To_Pixel(coord, pixel);
            Point2D draw = pixel + Point2D(60, 30) / -2;
            draw = draw + Point2D(unknown_rect_839630.X, unknown_rect_839630.Y);

            if (MainWindow) {
                unknown_e4[i]->unknown_4754b0(draw, cliprect);
            }
        }
    }
}
