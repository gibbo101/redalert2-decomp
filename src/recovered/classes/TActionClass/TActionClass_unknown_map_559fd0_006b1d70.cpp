// bool TActionClass::unknown_map_559fd0(...) (0x006B1D70)
// Calls Map.Unknown_00559FD0; always true.
#include "shared/taction.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_00559FD0@MapClass@@QAEXXZ=00559fd0
// @ref ?Map@@3VMouseClass@@A=008324e0


bool TActionClass::unknown_map_559fd0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Map.Unknown_00559FD0();
    return true;
}
