// Whether an object is a building (Kind_Of 6), and the object as one: the
// inline tests the sidebar strips apply to their factories' objects.
#ifndef RA2_SHARED_SIDEBAR_BUILDING_HPP
#define RA2_SHARED_SIDEBAR_BUILDING_HPP

#include "shared/object.hpp"

class BuildingClass;

inline bool Is_Building(ObjectClass *object)
{
    return object && object->Kind_Of() == 6;
}

inline BuildingClass *As_Building(ObjectClass *object)
{
    if (!object) {
        return 0;
    }
    return object->Kind_Of() == 6 ? (BuildingClass *)object : 0;
}

#endif
