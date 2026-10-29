// TeamClass::~TeamClass() (0x006B7770)
// Reports the team's outcome to the AI trigger types that use its type,
// releases its members and tag, leaves the lists and deletes a transient
// team type.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/house.hpp"
#include "shared/tag.hpp"
#include "shared/ai_trigger_type.hpp"
// @ref ?Register_Success@AITriggerTypeClass@@QAEXXZ=0041dfb0
// @ref ?Register_Failure@AITriggerTypeClass@@QAEXXZ=0041e070
// @ref ?Unknown_006B8FB0@TeamClass@@QAE_NPAVFootClass@@H_N@Z=006b8fb0
// @ref ?unknown_func_6b3cc0@TagClass@@QAEXXZ=006b3cc0
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ??1AbstractClass@@UAE@XZ=0040ff90
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?Teams@@3V?$DynamicVectorClass@PAVTeamClass@@@@A=00866178
// @ref ?unknown_objects_ac0d30@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0d30

extern bool unknown_flag_a40958;            // 0x00A40958
extern DynamicVectorClass<AbstractClass *> unknown_objects_ac0cb0;
extern DynamicVectorClass<AbstractClass *> unknown_objects_ac0d30;

TeamClass::~TeamClass()
{
    for (int index = 0; index < AITriggerTypes.Count(); index++) {
        if (AITriggerTypes[index]->unknown_dc == Class) {
            if (IsSuspended) {
                AITriggerTypes[index]->Register_Success();
            } else {
                AITriggerTypes[index]->Register_Failure();
            }
        }
    }
    if (Owner != 0 && Class != 0 && Class->IsBaseDefense) {
        Owner->unknown_555c--;
    }
    if (unknown_flag_a40958 && Class != 0) {
        while (Member != 0) {
            Unknown_006B8FB0(Member, -1, 0);
        }
        Class->unknown_d4--;
        if (Tag != 0) {
            if (Tag->unknown_2c == 0) {
                Tag->unknown_func_6b3cc0();
            }
            Tag = 0;
        }
    }
    Unknown_006ECB90(this, true);
    unknown_objects_ac0d30.Delete(this);
    unknown_AbstractClass_list_00ac0d60.Delete(this);
    unknown_objects_ac0cb0.Delete(this);
    unknown_objects_ac0c58.Delete(this);
    Teams.Delete(this);
    if (IsTransient && Class != 0) {
        delete Class;
    }
}
