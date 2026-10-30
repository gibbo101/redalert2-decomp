// Original004E4090:113body+15padding; inventory004E4094 is inside the first MOV.
// @ref ?Get_Object@FactoryClass@@QBEPAVTechnoClass@@XZ=004b9930
#include "shared/techno.hpp"
#include "shared/factory_class_decl.hpp"

FactoryClass *HouseClass::Factory_Producing_This_004e4090(TechnoTypeClass const *type) const
{
    FactoryClass *factory=0;
    for (int index=0;index<Factories.Count();++index) {
        if (Factories[index]->Get_House_004e4090()==this) {
            if (Factories[index]->Get_Object()!=0 &&
                Factories[index]->Get_Object()->unknown_slot32()==type) {
                factory=Factories[index];
                break;
            }
        }
    }
    return factory;
}
