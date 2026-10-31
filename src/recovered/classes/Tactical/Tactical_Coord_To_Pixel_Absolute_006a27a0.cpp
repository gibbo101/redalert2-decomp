// Point2D Tactical::Unknown_006A27A0(CoordStruct const &coord) (0x006A27A0): the absolute screen pixel of a
// coordinate: its X/Y rotated onto the isometric axes, leptons to pixels (/256), raised by the screen
// height of its Z (0x006A2970) (TibSun Tactical::Coord_To_Pixel_Absolute(Coord const &)).
#include "shared/tactical.hpp"

Point2D Tactical::Unknown_006A27A0(CoordStruct const &coord)
{
    Point2D pixel = Rectangular_To_Isometric(Point2D(coord.X, coord.Y));
    pixel.X /= 256;
    pixel.Y /= 256;
    pixel.Y -= Unknown_006A2970(coord.Z);
    return pixel;
}
