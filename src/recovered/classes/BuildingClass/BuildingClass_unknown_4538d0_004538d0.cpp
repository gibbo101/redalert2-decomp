// bool BuildingClass::unknown_4538d0(ObjectTypeClass *type) (0x004538D0)
// Whether slot 62 answers for the object the type creates for the building's
// house (hypothesis).
#include "shared/building.hpp"

bool BuildingClass::unknown_4538d0(ObjectTypeClass *type)
{
    TechnoClass *object = (TechnoClass *)type->unknown_slot35(House);
    return unknown_slot62(object) != 0 ? true : false;
}
