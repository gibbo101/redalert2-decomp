// void ObjectClass::unknown_slot75() (0x005D36E0)
#include "shared/object_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

void ObjectClass::unknown_slot75()
{
    if (!unknown_75) {
        unknown_75 = true;
        Map.Flag_To_Redraw(0);
    }
}
