// bool Tactical::Coord_To_Pixel(Coord const &, Point2D &) (0x006A29D0).
#include "shared/tactical.hpp"

bool Tactical::Coord_To_Pixel(CoordStruct const &coord, Point2D &pixel)
{
    pixel = Coord_To_Pixel_Absolute(coord);
    pixel -= Point2D(TacPixelX, TacPixelY);

    if (pixel.X < -360) {
        return false;
    }

    if (pixel.X > unknown_rect_abe560.Width + 360) {
        return false;
    }

    if (pixel.Y < -180) {
        return false;
    }

    if (pixel.Y > unknown_rect_abe560.Height + 180) {
        return false;
    }

    return true;
}
