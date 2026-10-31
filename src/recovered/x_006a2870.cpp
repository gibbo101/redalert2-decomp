// Point2D Tactical::Coord_To_Pixel_Absolute(Point2D const &point) (0x006A2870): the absolute screen pixel of a
// flat lepton point: rotated onto the isometric axes, leptons to pixels (/256) (TibSun
// Tactical::Coord_To_Pixel_Absolute(Point2D const &), without its unused height lift).
#include "shared/tactical.hpp"

Point2D Tactical::Coord_To_Pixel_Absolute(Point2D const &point)
{
    Point2D pixel = Rectangular_To_Isometric(point);
    pixel.X /= 256;
    pixel.Y /= 256;
    return pixel;
}
