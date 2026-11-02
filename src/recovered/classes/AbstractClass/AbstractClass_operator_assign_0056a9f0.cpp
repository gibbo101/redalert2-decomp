// AbstractClass::operator=0056A9F0, member-wise copy without vptr writes.
#include "shared/map.hpp"
AbstractClass &AbstractClass::operator=(AbstractClass const &other)
{
    UniqueID = other.UniqueID;
    AbstractFlags = other.AbstractFlags;
    unknown_18 = other.unknown_18;
    RefCount = other.RefCount;
    Dirty = other.Dirty;
    return *this;
}
