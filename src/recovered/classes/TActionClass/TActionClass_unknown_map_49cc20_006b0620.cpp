// bool TActionClass::unknown_map_49cc20(...) (0x006B0620)
// Calls DisplayClass::Unknown_0049CC20 on the map; always true.
#include "shared/taction.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

bool TActionClass::unknown_map_49cc20(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Map.Unknown_0049CC20();
    return true;
}


