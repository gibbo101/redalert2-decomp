// ObjectTypeClass *UnitClass::Class_Of() const (0x00705020, slot 33)
// The unit type.
#include "shared/unit.hpp"

ObjectTypeClass *UnitClass::Class_Of() const
{
    return Type;
}
