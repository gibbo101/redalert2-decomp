// bool Tactical::Unknown_006A29D0(CoordStruct const &coord, Point2D &pixel) (0x006A29D0): the screen pixel of a
// coordinate (the absolute pixel, 0x006A27A0, less the view position); false when it lies more than six tiles
// (360 x 180 pixels) outside the view rectangle (TibSun Tactical::Coord_To_Pixel).
#include "shared/tactical.hpp"

bool Tactical::Unknown_006A29D0(CoordStruct const &coord, Point2D &pixel)
{
    pixel = Unknown_006A27A0(coord);
    pixel -= Point2D(unknown_b0.X, unknown_b0.Y);

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
