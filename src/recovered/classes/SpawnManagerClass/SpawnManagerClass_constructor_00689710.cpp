// SpawnManagerClass::SpawnManagerClass(TechnoClass *owner, AircraftTypeClass *type, int count, int regen, int reload) (0x00689710)
// Creates count units of the type for the owner's house, each in its own
// record, and joins the unit's list.
#include "shared/spawn_manager.hpp"
#include "shared/aircraft.hpp"
#include "shared/rules.hpp"
// @ref ??_7SpawnManagerClass@@6BIPersistStream@@@=007ab8c8
// @ref ??_7SpawnManagerClass@@6BIRTTITypeInfo@@@=007ab8ac
// @ref ??_7SpawnManagerClass@@6BINoticeSink@@@=007ab8a4
// @ref ??_7SpawnManagerClass@@6BINoticeSource@@@=007ab89c
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ?AI@SpawnManagerClass@@UAEXXZ=00689c90
// @ref ??0?$VectorClass@PAUSpawnControl@@@@QAE@IPBQAUSpawnControl@@@Z=0068b0e0
// @ref ??_7?$DynamicVectorClass@PAUSpawnControl@@@@6B@=007ab92c
// @ref ??_7?$VectorClass@PAUSpawnControl@@@@6B@=007ab94c
// @ref ??_G?$DynamicVectorClass@PAUSpawnControl@@@@UAEPAXI@Z=0068aff0
// @ref ??_G?$VectorClass@PAUSpawnControl@@@@UAEPAXI@Z=0068afa0
// @ref ??8?$VectorClass@PAUSpawnControl@@@@UBE_NABV0@@Z=0068aae0
// @ref ?Resize@?$DynamicVectorClass@PAUSpawnControl@@@@UAE_NHPBQAUSpawnControl@@@Z=0068ac60
// @ref ?Resize@?$VectorClass@PAUSpawnControl@@@@UAE_NHPBQAUSpawnControl@@@Z=0068ab20
// @ref ?Clear@?$DynamicVectorClass@PAUSpawnControl@@@@UAEXXZ=0068aa20
// @ref ?Clear@?$VectorClass@PAUSpawnControl@@@@UAEXXZ=0068abd0
// @ref ?ID@?$DynamicVectorClass@PAUSpawnControl@@@@UAEHABQAUSpawnControl@@@Z=0068ad10
// @ref ?ID@?$DynamicVectorClass@PAUSpawnControl@@@@UAEHPBQAUSpawnControl@@@Z=0068aa50
// @ref ?ID@?$VectorClass@PAUSpawnControl@@@@UAEHABQAUSpawnControl@@@Z=0068ac00
// @ref ?ID@?$VectorClass@PAUSpawnControl@@@@UAEHPBQAUSpawnControl@@@Z=0068ac40
// @ref ?Fetch@?$VectorClass@PAUSpawnControl@@@@UBEPAUSpawnControl@@H@Z=0068aa70
// @ref ??2@YAPAXI@Z=00782017
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_SpawnManagerClass_list_00abd028@@3V?$DynamicVectorClass@PAVSpawnManagerClass@@@@A=00abd028

SpawnManagerClass::SpawnManagerClass(TechnoClass *owner, AircraftTypeClass *type, int count, int regen, int reload)
{
    Owner = owner;
    SpawnType = type;
    SpawnCount = count;
    RegenRate = regen;
    ReloadRate = reload;
    for (int i = 0; i < SpawnCount; i++) {
        SpawnControl *node = new SpawnControl;
        if (!node) {
            break;
        }
        node->Unit = (AircraftClass *)SpawnType->unknown_slot35(Owner->Owning_House());
        if (node->Unit) {
            if (SpawnType == Rules->V3Rocket.Type || SpawnType == Rules->DMisl.Type) {
                node->IsMissile = 1;
            } else {
                node->IsMissile = 0;
            }
            node->Unit->unknown_slot52();
            node->Unit->unknown_23c = Owner;
            node->Status = 0;
            node->Timer = 0;
            SpawnedNodes.Add(node);
        }
    }
    unknown_50 = 20;
    Destination = 0;
    Target = 0;
    Status = 0;
    unknown_5c = 0;
    unknown_SpawnManagerClass_list_00abd028.Add(this);
}
