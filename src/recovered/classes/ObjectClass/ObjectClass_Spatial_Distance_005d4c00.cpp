// ObjectClass existing three-dimensional distance interface, diagnostic only.
#include "shared/techno.hpp"
#include "shared/building_type.hpp"
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?Foundation_Height@BuildingTypeClass@@QBEH_N@Z=00458940
// @ref ?Width@BuildingTypeClass@@QBEHXZ=00458930
static inline int Object_Spatial_Distance_005D4C00(CoordStruct const &origin, CoordStruct const &destination)
{
    CoordStruct difference = origin - destination;
    double y = difference.Y;
    double z = difference.Z;
    double x = difference.X;
    return (int)unknown_sqrt_4ba410(x*x + z*z + y*y);
}
int ObjectClass::unknown_5d4c00(AbstractClass *target)
{
    if (!target) return 0;
    int distance = Object_Spatial_Distance_005D4C00(Center_Coord(), target->Center_Coord());
    BuildingClass *building = target->Kind_Of() == 6 ? static_cast<BuildingClass *>(target) : 0;
    if (building) {
        Point2D size(building->Type->Width(), building->Type->Foundation_Height(false));
        distance = (int)((unsigned int)distance - ((unsigned int)size.X + (unsigned int)size.Y) * 64U);
        if (distance < 0) distance = 0;
    }
    return distance;
}
