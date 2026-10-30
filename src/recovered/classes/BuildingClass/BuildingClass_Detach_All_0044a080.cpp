// 0044A080: notify radio contacts and abandon production when the building is removed.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/factory_class_decl.hpp"
// @ref ?Abandon_Production_004B97C0@FactoryClass@@=004b97c0
// @ref ?Contact@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e10
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
// @ref ?unknown_slot54@ObjectClass@@UAEX_N@Z=005d3c10
void BuildingClass::unknown_slot54(bool removing)
{
    if (removing) {
        if (unknown_41c) {
            static_cast<FactoryClass *>(unknown_41c)->Abandon_Production_004B97C0();
            delete static_cast<FactoryClass *>(unknown_41c);
            unknown_41c=0;
        }
        if (House) {
            if (Type->Factory==7) {
                unknown_44a000((UnknownBuildingFactory *)House->unknown_52e8);
                unknown_44a000((UnknownBuildingFactory *)House->unknown_52ec);
                unknown_44a000((UnknownBuildingFactory *)House->unknown_52f0);
                unknown_44a000((UnknownBuildingFactory *)House->unknown_52f4);
                unknown_44a000((UnknownBuildingFactory *)House->unknown_52f8);
            } else {
                unknown_44a000((UnknownBuildingFactory *)House->unknown_func_4eb580(Type->Factory,Type->Naval,0));
            }
        }
    }
    if (!removing) {
        for (int index=0; index<RadioLinks.Length(); ++index) {
            TechnoClass *contact=Contact(index);
            if (contact && !House->Is_Ally(contact)) unknown_slot150(3,contact);
        }
    }
    else {
        unknown_slot152(3);
    }
    ObjectClass::unknown_slot54(removing);
}
