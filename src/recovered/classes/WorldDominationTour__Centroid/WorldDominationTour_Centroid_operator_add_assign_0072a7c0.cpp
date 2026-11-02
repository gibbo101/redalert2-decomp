// WorldDominationTour::Centroid &WorldDominationTour::Centroid::operator+=(Point2D const &point) (0x0072A7C0):
// adds the point to the coordinate sums and counts it.
#include "shared/vector_elements.hpp"

namespace WorldDominationTour {

Centroid &Centroid::operator+=(Point2D const &point)
{
    unknown_00 += point.X;
    unknown_04 += point.Y;
    unknown_08++;
    return *this;
}

}
