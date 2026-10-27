#define RA2_COORD_EQUAL_MEMBER
// Point2D __fastcall Planning_Coord_Pixel(CoordStruct const &coord) (0x006107A0)
#include "shared/planning.hpp"

Point2D __fastcall Planning_Coord_Pixel(CoordStruct const &coord)
{
    Point2D pixel;
    unknown_tactical_83996c->Unknown_006A29D0(coord, pixel);
    pixel.X += unknown_int_839630;
    pixel.Y += unknown_int_839634;
    return pixel;
}
