// void HouseClass::unknown_func_4f3170(int kind, bool naval, int arg3) (0x004F3170)
// A factory building left (BuildingClass slot 52): the house's factory for
// the type kind drops the queued types it can no longer build; the object in
// production is abandoned when it cannot be built at all, suspended (and the
// player's sidebar strip redrawn) when only the limits forbid it, or resumed
// when it was waiting; an idle empty factory is deleted.
#include "shared/techno.hpp"
#include "shared/factory_class.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Which_Column@SidebarClass@@SIHHH_N@Z=00681940

void HouseClass::unknown_func_4f3170(int kind, bool naval, int arg3)
{
    FactoryClass *factory;
    switch (kind) {
    case 7:
        if (arg3 == 5) {
            factory = unknown_52f8;
        } else {
            factory = unknown_52e8;
        }
        break;
    case 40:
        if (naval) {
            factory = unknown_52e4;
        } else {
            factory = unknown_52e0;
        }
        break;
    case 16:
        factory = unknown_52dc;
        break;
    case 3:
        factory = unknown_52d8;
        break;
    default:
        return;
    }
    if (factory == 0) {
        return;
    }
    for (int index = factory->Queue.Count() - 1; index >= 0; index--) {
        if (factory->Queue[index]->Who_Can_Build_Me(true, false, true, this) == 0) {
            factory->Queue.Delete(index);
        }
    }
    if (factory->Object != 0) {
        if (factory->Object->unknown_slot32()->Who_Can_Build_Me(true, false, true, this) == 0) {
            factory->Abandon_Production_004B97C0();
            factory->Start_Next_Queued_004B9D70();
        } else if (factory->Object->unknown_slot32()->Who_Can_Build_Me(true, true, true, this) == 0) {
            factory->Suspend_004B9630(false);
            if (unknown_player_a35db4 == this) {
                Map.Unknown_0067C2D0(SidebarClass::Which_Column(kind, arg3, naval));
            }
        } else if (factory->unknown_6c && !factory->unknown_6d) {
            factory->Start_Production_004B9670(false);
        }
    }
    if (factory->Object == 0 && factory->Queue.Count() == 0) {
        delete factory;
    }
}
