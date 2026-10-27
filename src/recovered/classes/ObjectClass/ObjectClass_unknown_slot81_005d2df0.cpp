// void ObjectClass::unknown_slot81() (0x005D2DF0)
#include "shared/object_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0049EC40@DisplayClass@@QAEPAVObjectClass@@XZ=0049ec40
// @ref ?Unknown_0049EC60@DisplayClass@@QAEXPAVObjectClass@@@Z=0049ec60
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60

void ObjectClass::unknown_slot81()
{
    if (unknown_77) {
        unknown_objects_a40c60.Delete(this);
        unknown_77 = false;
        if (Map.Unknown_0049EC40() == this) {
            Map.Unknown_0049EC60(0);
        }
    }
}
