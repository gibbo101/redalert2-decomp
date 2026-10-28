// Cell const *FoggedObjectClass::unknown_4c1f00() const (0x004C1F00): the
// cells a fogged building covers (its type's slot 36 list); null for objects
// of other kinds.
#include "shared/fogged_object.hpp"
#include "shared/object_type.hpp"

Cell const *FoggedObjectClass::unknown_4c1f00() const
{
    if (unknown_30 == 6) {
        return DrawRecords[0].Type->unknown_slot36(0);
    }
    return 0;
}
