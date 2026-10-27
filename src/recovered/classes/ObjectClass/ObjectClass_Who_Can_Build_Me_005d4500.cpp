// BuildingClass *ObjectClass::Who_Can_Build_Me(bool in_theory, bool legal) (0x005D4500, slot 94)
// The owner's building that can produce this object's type.
#include "shared/object_type.hpp"

BuildingClass *ObjectClass::Who_Can_Build_Me(bool in_theory, bool legal)
{
    return Class_Of()->Who_Can_Build_Me(in_theory, legal, false, Owning_House());
}
