// bool ObjectClass::operator<(ObjectClass const &other) const (0x005D4AB0)
#include "shared/object_type.hpp"

bool ObjectClass::operator<(ObjectClass const &other) const
{
    return unknown_slot45() < other.unknown_slot45();
}
