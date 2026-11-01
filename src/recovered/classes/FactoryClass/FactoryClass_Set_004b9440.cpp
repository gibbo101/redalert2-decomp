// @ref ?Abandon_Production_004B97C0@FactoryClass@@QAE_NXZ=004b97c0
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Is_Build_Limited_004F4F30@HouseClass@@QAE_NPAVTechnoTypeClass@@@Z=004f4f30
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref ?unknown_func_4f52f0@HouseClass@@QAE_NXZ=004f52f0
#include "shared/factory_class.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
bool FactoryClass::unknown_4b9440(TechnoTypeClass *type, HouseClass *house, unsigned char resume)
{
    if (type->Kind_Of()==7) Abandon_Production_004B97C0();
    if (type->Kind_Of()!=7 && ((Rate!=0 && !unknown_6c) || Queue.Count()>0 || (Object && unknown_6c)) && !resume) {
        if (Queue.Count()<Rules->MaximumQueuedObjects && !Owner->Is_Build_Limited_004F4F30(type)) {
            Queue.Add(type);
            return true;
        }
        if (house->Unknown_004F52B0()) Voc_Play(Rules->unknown_620,1.0f,0x2000,0);
        return false;
    }
    unknown_59=true;
    unknown_6c=true;
    Set_Rate(0);
    Stage=0;
    Object=static_cast<TechnoClass *>(type->unknown_slot35(house));
    if (!house->unknown_func_4f52f0() && Object && Object->Kind_Of()==6)
        static_cast<BuildingClass *>(Object)->unknown_59a=true;
    if (Object) {
        Owner=Object->House;
        UnspentCost=type->unknown_slot33((int)Owner);
        Object->unknown_258=UnspentCost;
    }
    return Object!=0;
}
