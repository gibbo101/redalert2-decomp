// int WorldDominationTour::Map::Territory_At(Point2D const &point) const (0x0072A660): the
// territory index the index surface holds under point (relative to the map origin unknown_44);
// -1 outside the surface.
#include "shared/wdt_map.hpp"

namespace WorldDominationTour {

int Map::Territory_At(Point2D const &point) const
{
    Point2D local = point;
    local.X -= unknown_44.X;
    local.Y -= unknown_44.Y;
    if (local.X >= 0 && local.X < unknown_24->Get_Width() && local.Y >= 0 && local.Y < unknown_24->Get_Height()) {
        return unknown_24->Get_Pixel(local);
    }
    return -1;
}

}
