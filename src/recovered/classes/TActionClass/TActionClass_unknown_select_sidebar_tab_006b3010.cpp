// bool TActionClass::unknown_select_sidebar_tab(...) (0x006B3010)
// Selects sidebar tab Data.Value (0..3) when its strip has buildables; true then.
#include "shared/taction.hpp"
#include "shared/map_view.hpp"

bool TActionClass::unknown_select_sidebar_tab(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    int tab = Data.Value;
    if (tab < 4 && tab >= 0 && Map.Column[tab].Unknown_00681730()) {
        Map.Select_Tab(tab);
        return true;
    }
    return false;
}


