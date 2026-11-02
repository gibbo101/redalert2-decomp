// void __fastcall Detach_This_From_All(AbstractClass *target, bool all) (0x006ECB90)
// TibSun tracker.cpp: removes every reference to an object that is going away from the
// pending placement, the gas cloud system and each tracker list of its kind (houses,
// animations, objects, types, then the switch on the remaining kinds), and from the
// global owners (Map, Logic, Rules, the tactical view, the bomb and kamikaze trackers).
#define MAP_VIEW_DECLARE_DETACH
#include "shared/map_view.hpp"
#include "shared/object_lists.hpp"
#include "shared/abstract_type.hpp"
#include "shared/particle_system.hpp"
#include "shared/logic.hpp"
#include "shared/rules.hpp"
#include "shared/tactical.hpp"
#include "shared/saveload_lists.hpp"
#include "shared/kamikaze_tracker.hpp"
#include "shared/foot.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_00498F10@DisplayClass@@QAEXPBVCell@@@Z=00498f10
// @ref ?unknown_gas_cloud_system_a40d20@@3PAVParticleSystemClass@@A=00a40d20
// @ref ?Logic@@3VLogicClass@@A=00832470
// @ref ?Detach@LogicClass@@UAEXPBVAbstractClass@@_N@Z=0053e110
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Detach@RulesClass@@QAEXPBVAbstractClass@@_N@Z=00651290
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?BombList@@3VBombListClass@@A=008322e0
// @ref ?Detach@BombListClass@@QAEXPAVAbstractClass@@@Z=00436750
// @ref ?KamikazeTracker@@3VKamikazeTrackerClass@@A=00a6e428
// @ref ?Detach@KamikazeTrackerClass@@QAEXPAVAbstractClass@@@Z=00531880
// @ref ?unknown_tracker_839ea0@@3UUnknownTracker839EA0@@A=00839ea0
// @ref ?Unknown_004131D0@UnknownTracker839EA0@@QAEXPAVAbstractClass@@@Z=004131d0
// @ref ?Unknown_006F7970@@YIXPAX@Z=006f7970
// @ref ?Detach@MapClass@@QAEXPAVAbstractClass@@_N@Z=00559d80
// @ref ___RTDynamicCast=00783ce4
// @ref ??_7type_info@@6B@=007b15e4
// @ref ??_R0?AVAbstractClass@@@8=007ce240
// @ref ??_R0?AVAbstractTypeClass@@@8=007ce260

void __fastcall Unknown_006F7970(void *item);

void __fastcall Detach_This_From_All(AbstractClass *target, bool all)
{
    int rtti = target->Kind_Of();
    int index = 0;

    if (Map.unknown_11a0 == target) {
        Map.unknown_11a0 = 0;
    }

    if (Map.unknown_11a4 == target) {
        Map.unknown_11a4 = 0;
        Map.Unknown_00498F10(0);
    }

    if (rtti == 0x18 && target == unknown_gas_cloud_system_a40d20) {
        unknown_gas_cloud_system_a40d20 = 0;
    }

    if (rtti == 0x0D) {
        for (index = 0; index < unknown_abstracts_ac0d08.Count(); index++) {
            unknown_abstracts_ac0d08[index]->Detach(target, all);
        }
        Logic.Detach(target, all);
        return;
    }

    if (rtti == 0x04) {
        for (index = 0; index < unknown_abstracts_ac0bf8.Count(); index++) {
            unknown_abstracts_ac0bf8[index]->Detach(target, all);
        }
        return;
    }

    bool is_object;
    if (target != 0) {
        is_object = target->AbstractFlags.IsObject;
    }
    if (target != 0 && is_object) {
        for (index = 0; index < unknown_AbstractClass_list_00ac0d60.Count(); index++) {
            unknown_AbstractClass_list_00ac0d60[index]->Detach(target, all);
        }
        BombList.Detach(target);
        KamikazeTracker.Detach(target);
        if (rtti == 0x0F || rtti == 0x01 || rtti == 0x02) {
            unknown_tracker_839ea0.Unknown_004131D0(target);
        }
        Unknown_006F7970(target);
        if (unknown_tactical_83996c != 0) {
            unknown_tactical_83996c->Detach(target, true);
        }
        Logic.Detach(target, all);
        return;
    }

    if (dynamic_cast<AbstractTypeClass *>(target) != 0) {
        for (index = 0; index < unknown_objects_ac0cb0.Count(); index++) {
            unknown_objects_ac0cb0[index]->Detach(target, all);
        }
        Rules->Detach(target, all);
        return;
    }

    switch (rtti) {
    case 0x2C:
        for (index = 0; index < unknown_objects_ac0c58.Count(); index++) {
            unknown_objects_ac0c58[index]->Detach(target, all);
        }
        Map.Detach(target, true);
        Logic.Detach(target, all);
        break;

    case 0x26:
        for (index = 0; index < unknown_AbstractClass_list_00ac0d48.Count(); index++) {
            unknown_AbstractClass_list_00ac0d48[index]->Detach(target, all);
        }
        break;

    case 0x0C:
        for (index = 0; index < unknown_abstracts_ac0c80.Count(); index++) {
            unknown_abstracts_ac0c80[index]->Detach(target, all);
        }
        Map.Detach(target, true);
        break;

    case 0x2F:
    case 0x30:
        for (index = 0; index < unknown_AbstractClass_list_00ac0c98.Count(); index++) {
            unknown_AbstractClass_list_00ac0c98[index]->Detach(target, all);
        }
        break;

    case 0x33:
        for (index = 0; index < unknown_objects_ac0c30.Count(); index++) {
            unknown_objects_ac0c30[index]->Detach(target, all);
        }
        break;

    case 0x22:
        for (index = 0; index < unknown_list_ac0c18.Count(); index++) {
            unknown_list_ac0c18[index]->Detach(target, all);
        }
        break;

    case 0x3C:
        for (index = 0; index < unknown_objects_ac0d30.Count(); index++) {
            unknown_objects_ac0d30[index]->Detach(target, all);
        }
        break;
    }
}
