// int HouseClass::Abandon_Production(int kind, int index, bool naval) (0x004E64F0)
// RA's Abandon_Production: a type still queued is only removed from the
// queue; otherwise the factory abandons its object (the player's house
// updates the sidebar and drops a pending building) and, with nothing
// queued, is cleared from the house and deleted. 3 without a factory.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
#include "shared/map_view.hpp"
#include "shared/factory_class.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_00681740@SidebarClass@@QAE_NHHPAVFactoryClass@@@Z=00681740

int HouseClass::Abandon_Production(int kind, int index, bool naval)
{
    int buildcat = unknown_func_4eb550(kind, index);
    FactoryClass *factory = unknown_func_4eb580(kind, naval, buildcat);
    if (factory == 0) {
        return 3;
    }
    if (factory->Queue.Count() > 0 && index >= 0 && buildcat == 0 && factory->Delete_Queued_004B9DF0(Unknown_00482C00(kind, index))) {
        Map.Unknown_0067C2D0(Unknown_006818D0(kind, index, 0));
        return 0;
    }
    if (buildcat == 0 && index != -1) {
        if (factory->Object == 0 || index != factory->Object->Class_Of()->unknown_slot16()) {
            return 0;
        }
    }
    if (unknown_player_a35db4 == this) {
        Map.Unknown_00681740(kind, index, factory);
        if (kind == 7 || kind == 6) {
            Map.unknown_11a0 = 0;
            Map.unknown_11a4 = 0;
            Map.unknown_11a8 = -1;
            Map.Unknown_00498F10(0);
        }
    }
    factory->Abandon_Production_004B97C0();
    if (factory->Queue.Count() == 0) {
        Set_Factory(0, kind, naval, buildcat);
        delete factory;
    } else {
        factory->Start_Next_Queued_004B9D70();
    }
    return 0;
}
