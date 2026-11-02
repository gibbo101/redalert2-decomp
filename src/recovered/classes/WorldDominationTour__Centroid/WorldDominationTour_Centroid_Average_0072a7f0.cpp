// Point2D WorldDominationTour::Centroid::Average() const (0x0072A7F0): the mean of the added points,
// (0, 0) when none was added.
#include "shared/vector_elements.hpp"

namespace WorldDominationTour {

Point2D Centroid::Average() const
{
    return unknown_08 > 0 ? Point2D(unknown_00 / unknown_08, unknown_04 / unknown_08) : Point2D(0, 0);
}

}
