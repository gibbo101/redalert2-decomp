// @ref ?unknown_slot24@Tactical@@UAE_NABUCoordStruct@@0H_N@Z=006ac160
// Tactical depth-shaded world line, original006AC160 (374+10).
#include "shared/tactical.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
extern Rect unknown_rect_839630;
// @ref ?unknown_rect_839630@@3VRect@@A=00839630

bool Tactical::unknown_slot24(CoordStruct const &from, CoordStruct const &to, int color, bool write_depth)
{
    Point2D start;
    Coord_To_Pixel(from,start);
    Point2D end;
    Coord_To_Pixel(to,end);
    unknown_surface_83995c->Draw_Depth_Shaded_Line(unknown_rect_839630,start,end,color,
        14-Unknown_006A2970(from.Z),14-Unknown_006A2970(to.Z),write_depth);
    return true;
}
