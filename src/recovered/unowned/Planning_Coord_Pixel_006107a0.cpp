#define RA2_COORD_EQUAL_MEMBER
// Point2D __fastcall Planning_Coord_Pixel(CoordStruct const &coord) (0x006107A0)
#include "shared/planning.hpp"
// The tactical pointer and the screen offset are named locals; this body is big
// enough that callers whose inline allowance runs short call it (Is_At_Pixel,
// Draw_Marker, Draw_All) while Pixel(), Rect(), Outer_Rect() and Fill_Marker
// still expand it, as in the original.

Point2D __fastcall Planning_Coord_Pixel(CoordStruct const &coord)
{
    Point2D pixel;
    Tactical *tactical = unknown_tactical_83996c;
    tactical->Coord_To_Pixel(coord, pixel);
    int x = pixel.X;
    int y = pixel.Y;
    int offset_x = unknown_int_839630;
    int offset_y = unknown_int_839634;
    pixel.X = x + offset_x;
    pixel.Y = y + offset_y;
    return pixel;
}
