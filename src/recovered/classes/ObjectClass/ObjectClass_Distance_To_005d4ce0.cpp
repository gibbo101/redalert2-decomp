// Existing ObjectClass direct Aircraft dependency; source spelling is a hypothesis.
#include "shared/techno.hpp"
#include "shared/building_type.hpp"
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?Foundation_Height@BuildingTypeClass@@QBEH_N@Z=00458940
// @ref ?Width@BuildingTypeClass@@QBEHXZ=00458930
static inline Point2D Object_Geometry_Planar_Position_005D4CE0(CoordStruct const &position)
{
    return Point2D(position.X, position.Y);
}
static inline int Object_Geometry_Planar_Distance_005D4CE0(Point2D origin, Point2D destination)
{
    int origin_x = origin.X;
    int origin_y = origin.Y;
    Point2D difference((int)((unsigned int)origin_x - (unsigned int)destination.X),
        (int)((unsigned int)origin_y - (unsigned int)destination.Y));
    double y = difference.Y;
    double x = difference.X;
    return (int)unknown_sqrt_4ba410(x * x + y * y);
}
int ObjectClass::Planar_Distance(AbstractClass const *target) const
{
    if (!target) return 0;
    int distance = Object_Geometry_Planar_Distance_005D4CE0(Object_Geometry_Planar_Position_005D4CE0(Center_Coord()),
        Object_Geometry_Planar_Position_005D4CE0(target->Center_Coord()));
    BuildingClass const *building = target->Kind_Of() == 6 ? static_cast<BuildingClass const *>(target) : 0;
    if (building) {
        Point2D size(building->Type->Width(), building->Type->Foundation_Height(false));
        distance = (int)((unsigned int)distance - ((unsigned int)size.X + (unsigned int)size.Y) * 64U);
        if (distance < 0) distance = 0;
    }
    return distance;
}
