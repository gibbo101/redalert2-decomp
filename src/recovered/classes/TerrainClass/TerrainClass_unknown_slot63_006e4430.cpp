// bool TerrainClass::unknown_slot63(Rect *bounds, bool forced, bool extras_only) (0x006E4430; TibSun
// terrain.cpp Render): when the object is to be drawn (debug map, no main window, or forced/needing
// a redraw while down and not in limbo), clips bounds to the tactical rectangle and, when the
// drawn area (slot 73, moved to the tactical origin) overlaps it, draws the object at its pixel
// position adjusted to the clipped origin (slot 67).
#include "shared/terrain.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_b263d8@@3HA=00b263d8
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
// @ref ?Coord_To_Pixel@Tactical@@QAE_NABUCoordStruct@@AAUPoint2D@@@Z=006a29d0
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c

bool TerrainClass::unknown_slot63(Rect *bounds, bool forced, bool extras_only)
{
    if (unknown_flag_a40d13 || !unknown_b263d8 || ((forced || unknown_75) && unknown_74 && !unknown_76)) {
        unknown_75 = false;

        Point2D point;

        *bounds = Intersect(*bounds, unknown_rect_839630);

        Rect rect = unknown_slot73() + unknown_rect_839630.Top_Left();

        if (bounds->Is_Overlapping(rect)) {
            unknown_tactical_83996c->Coord_To_Pixel(unknown_slot42(), point);

            if (bounds->X > unknown_rect_839630.X) {
                point.X += unknown_rect_839630.X - bounds->X;
            }
            if (bounds->Y > unknown_rect_839630.Y) {
                point.Y += unknown_rect_839630.Y - bounds->Y;
            }

            unknown_slot67((int)&point, (int)bounds);
            return true;
        }
    }
    return false;
}
