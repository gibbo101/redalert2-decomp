// int HouseClass::Which_Zone(ObjectClass const *object) const (0x004EAEB0)
// The base zone of an object (-1 for none).
#include "shared/techno.hpp"

int HouseClass::Which_Zone(ObjectClass const *object) const
{
    if (object == 0) {
        return -1;
    }
    return Which_Zone(object->Center_Coord());
}
