// AI factory production, completed-object placement and stalled production refunds.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/factory_class_decl.hpp"
#include "shared/sound_play.hpp"
// @ref ?Is_Complete_004B9900@FactoryClass@@=004b9900
// @ref ?Get_Object@FactoryClass@@=004b9930
// @ref ?Abandon_Production_004B97C0@FactoryClass@@=004b97c0
// @ref ?Release_Completed_004B9970@FactoryClass@@=004b9970
// @ref ??0FactoryClass@@=004b90a0
// @ref ?unknown_4b9440@FactoryClass@@=004b9440
// @ref ?Start_Production_004B9670@FactoryClass@@=004b9670
// @ref ?unknown_func_4e74c0@HouseClass@@=004e74c0
// @ref ?Just_Built@HouseClass@@=004e6f10
// @ref ?unknown_4ea7f0@HouseClass@@=004ea7f0
// @ref ?Voc_Static_Add@@=00714290
void BuildingClass::Factory_AI_0044b480()
{
    if (unknown_41c && static_cast<FactoryClass *>(unknown_41c)->Is_Complete_004B9900() && unknown_448.Value() == 0) {
        TechnoClass *product = static_cast<FactoryClass *>(unknown_41c)->Get_Object();
        switch (unknown_slot62(product)) {
        case 0:
            if (product->Kind_Of() == 6 && static_cast<BuildingClass *>(product)->Type->Naval) {
                product->Owning_House()->unknown_138 = false;
            }
            static_cast<FactoryClass *>(unknown_41c)->Abandon_Production_004B97C0();
            delete static_cast<FactoryClass *>(unknown_41c);
            unknown_41c = 0;
            break;
        case 1:
            unknown_448 = (int)(Rules->PlacementDelay * 900);
            break;
        case 2: {
            CoordStruct location(Coord);
            Voc_Static_Add(Type->CreateUnitSound, location, 0);
            House->Just_Built(product);
            static_cast<FactoryClass *>(unknown_41c)->Release_Completed_004B9970();
            delete static_cast<FactoryClass *>(unknown_41c);
            unknown_41c = 0;
            break;
        }
        }
    }
    if (House->unknown_136 && unknown_slot91() != 18 && unknown_slot91() != 19 && Type->Factory != 0) {
        if (unknown_41c) {
            if (unknown_448.Value() == 0) {
                FactoryClass *factory = static_cast<FactoryClass *>(unknown_41c);
                if (factory->Rate != 0 && !factory->unknown_6c) return;
                factory->Abandon_Production_004B97C0();
                delete static_cast<FactoryClass *>(unknown_41c);
                unknown_41c = 0;
            }
        } else {
            if (House->unknown_136 && House->Available_Money() > 10) {
                TechnoTypeClass *type = House->unknown_func_4e74c0(Type->Factory, false);
                if (type) {
                    if (type->Kind_Of() == 40) {
                        if (Type->Naval && !type->Naval) return;
                        if (type->Naval && !Type->Naval) return;
                    }
                    unknown_41c = new FactoryClass;
                    if (unknown_41c) {
                        if (!static_cast<FactoryClass *>(unknown_41c)->unknown_4b9440(type, House, 0)) {
                            delete static_cast<FactoryClass *>(unknown_41c);
                            unknown_41c = 0;
                        } else {
                            House->unknown_4ea7f0(static_cast<FactoryClass *>(unknown_41c)->Get_Object());
                            static_cast<FactoryClass *>(unknown_41c)->Start_Production_004B9670(false);
                        }
                    }
                }
            }
        }
    }
}
