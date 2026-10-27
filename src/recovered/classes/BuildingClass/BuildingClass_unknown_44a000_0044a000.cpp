// void BuildingClass::unknown_44a000(UnknownBuildingFactory *factory) (0x0044A000)
// With +0x76 set meanwhile, abandons the production of the factory's object
// when no building of the house can build its type any more.
#include "shared/building.hpp"
#include "shared/house.hpp"
// @ref ?Get_Object@UnknownBuildingFactory@@QAEPAVTechnoClass@@XZ=004b9930
// @ref ?unknown_func_4e64f0@HouseClass@@QAEXHHH@Z=004e64f0

void BuildingClass::unknown_44a000(UnknownBuildingFactory *factory)
{
    if (factory) {
        TechnoClass *object = factory->Get_Object();
        bool saved = unknown_76;
        unknown_76 = true;
        if (object) {
            if (!object->unknown_slot32()->Who_Can_Build_Me(true, false, false, House)) {
                House->unknown_func_4e64f0(Type->Factory, object->unknown_slot32()->unknown_slot16(), 0);
            }
        }
        unknown_76 = saved;
    }
}
