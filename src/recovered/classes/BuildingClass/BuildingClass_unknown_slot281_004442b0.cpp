// int BuildingClass::unknown_slot281(ObjectClass *object) (0x004442B0, slot 281)
// The distance in leptons from the object's center to its dock coordinate
// here (slot 41), through the inline Coord_Distance (shared/building.hpp).
#include "shared/building.hpp"
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __ftol=0077f110

int BuildingClass::unknown_slot281(ObjectClass *object)
{
    return Coord_Distance(unknown_slot41((int)object), object->Center_Coord());
}
