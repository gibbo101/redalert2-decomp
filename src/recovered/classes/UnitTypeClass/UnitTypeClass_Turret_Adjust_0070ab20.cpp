// Point2D UnitTypeClass::Turret_Adjust(int dir, Point2D const &xy) const -- 0x0070AB20
// The turret drawing offset for a facing: this class leaves it unchanged.
#include "shared/unit_type.hpp"

Point2D UnitTypeClass::Turret_Adjust(int dir, Point2D const &xy) const
{
    return xy;
}
