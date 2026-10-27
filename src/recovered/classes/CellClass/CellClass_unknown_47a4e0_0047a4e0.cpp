// void CellClass::unknown_47a4e0() (0x0047A4E0): redraws the cell's screen
// area: the pixel of the cell's corner coordinate, moved left by 30 and down
// by the screen offset at 0x00839634 less the cell level (+0x11B, 15 pixels
// each) and 15, as a 60x30 rectangle (Tactical::Unknown_006A3020).
#include "shared/cell.hpp"
#include "shared/tactical.hpp"
// @ref ?unknown_int_839634@@3HA=00839634

void CellClass::unknown_47a4e0()
{
    CoordStruct corner = Coord_Snap(CoordStruct(MapCoords.X * 256 + 128, MapCoords.Y * 256 + 128, 0));
    Point2D pixel;
    unknown_tactical_83996c->Unknown_006A29D0(corner, pixel);
    pixel.Y += unknown_int_839634 - unknown_11b * 15;
    pixel.X -= 30;
    pixel.Y -= 15;
    unknown_tactical_83996c->Unknown_006A3020(Rect(pixel.X, pixel.Y, 60, 30), 0);
}
