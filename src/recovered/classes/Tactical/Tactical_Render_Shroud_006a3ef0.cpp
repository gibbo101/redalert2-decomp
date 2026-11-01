// void Tactical::Render_Shroud(Rect const &xpanrect, Rect const &ypanrect, Rect const &cliprect, bool fullredraw)
// (0x006A3EF0): redraws the shroud and fog of every cell flagged for redraw (then the alpha shapes over it), or
// of the whole view, then of the strips the pan exposed and of every dirty area that refreshes the shroud,
// clearing the depth buffer there first (TibSun Tactical::Render_Shroud).
#include "shared/tactical.hpp"
#include "shared/tactical_lists.hpp"
#include "shared/cell.hpp"
#include "shared/display.hpp"
#include "shared/alpha_shape.hpp"
#include "shared/blit.hpp"
#include "shared/win32_window.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?DirtyAreas@TacticalLists@@2V?$DynamicVectorClass@UDirtyAreaStruct@@@@A=00abe5b0
// @ref ?Draw_Shroud@Tactical@@QAEXABVRect@@@Z=006a7820
// @ref ?Draw_In_Area@AlphaShapeClass@@SIXABUPoint2D@@ABVRect@@@Z=0041f1c0
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
// @ref ?Draw_Shroud_And_Fog@CellClass@@QAEXABUPoint2D@@ABVRect@@@Z=00475520
// @ref ?unknown_475d60@CellClass@@QBE?AUCoordStruct@@XZ=00475d60
// @ref ?Clear_Region_004110B0@ZBuffer@@QAEXVRect@@@Z=004110b0
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8

void Tactical::Render_Shroud(Rect const &xpanrect, Rect const &ypanrect, Rect const &cliprect, bool fullredraw)
{
    if (unknown_e0 > 0 && !fullredraw) {
        for (int i = 0; i < unknown_e0; i++) {
            CoordStruct coord = unknown_e4[i]->unknown_475d60();
            coord.Z = 0;
            Point2D pixel;
            Coord_To_Pixel(coord, pixel);
            Point2D draw = pixel + Point2D(60, 30) / -2 + Point2D(unknown_rect_839630.X, unknown_rect_839630.Y);

            if (MainWindow) {
                unknown_e4[i]->Draw_Shroud_And_Fog(draw, cliprect);
            }
            AlphaShapeClass::Draw_In_Area(draw, cliprect);
        }
    } else if (fullredraw) {
        Draw_Shroud(unknown_rect_839630);
    }

    if (xpanrect.Is_Valid() && !fullredraw) {
        Draw_Shroud(xpanrect);
    }
    if (ypanrect.Is_Valid() && !fullredraw) {
        Draw_Shroud(ypanrect);
    }

    for (int j = 0; j < TacticalLists::DirtyAreas.Count(); j++) {
        Point2D corner = Point2D(TacticalLists::DirtyAreas[j].Area.X, TacticalLists::DirtyAreas[j].Area.Y) + Point2D(unknown_rect_839630.X, unknown_rect_839630.Y);
        Rect redraw = Rect(corner.X, corner.Y, TacticalLists::DirtyAreas[j].Area.Width, TacticalLists::DirtyAreas[j].Area.Height);
        Rect inter = Intersect(redraw, cliprect);

        if (TacticalLists::DirtyAreas[j].unknown_10) {
            ZBufferPtr->Clear_Region_004110B0(inter);
            Draw_Shroud(inter);
        }
    }
}
