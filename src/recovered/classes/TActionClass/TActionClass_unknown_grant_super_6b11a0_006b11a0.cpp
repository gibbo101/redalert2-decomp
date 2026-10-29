// bool TActionClass::unknown_grant_super_6b11a0(...) (0x006B11A0)
// Grants the house's super weapon Data one-time; the player's house adds it to the sidebar and redraws that strip; always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
#include "shared/super.hpp"
#include "shared/map_view.hpp"
// @ref ?Grant@SuperClass@@QAE_N_N00@Z=0069ccf0
// @ref ?Unknown_0067C530@SidebarClass@@QAE_NHH@Z=0067c530

bool TActionClass::unknown_grant_super_6b11a0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    house->Supers[Data]->Grant(true, false, false);
    if (unknown_player_a35db4 == house) {
        Map.Unknown_0067C530(31, Data);
        Map.Unknown_0067C2D0(Unknown_006818D0(31, Data, 0));
    }
    return true;
}
