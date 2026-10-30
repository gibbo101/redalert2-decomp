// Point2D Tactical::Clamp_Pixel_To_Tactical(Point2D const &pixel) (0x006A8B10): the
// pixel clamped to the view (0x006A8C80) unless the map editor flag 0x00A40D13
// is set (TibSun Tactical::Clamp_Pixel_To_Tactical).
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"

Point2D Tactical::Clamp_Pixel_To_Tactical(Point2D const &pixel)
{
    Point2D clamped = pixel;
    if (Unknown_006A8C80(&clamped) && !unknown_flag_a40d13) {
        return clamped;
    } else {
        return pixel;
    }
}
