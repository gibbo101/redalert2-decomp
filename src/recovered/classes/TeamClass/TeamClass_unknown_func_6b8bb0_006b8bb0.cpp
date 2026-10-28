// bool TeamClass::unknown_func_6b8bb0() (0x006B8BB0)
// Recomputes the strength flags from the member count against the task
// force's total; a team that never had members is deleted when its last
// member is gone.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"
#include "shared/tag.hpp"
// @ref ?Total_Amount@TaskForceClass@@QBEHXZ=006b6b30
// @ref ?Spring@TagClass@@QAE_NHPAVObjectClass@@VCell@@_NH@Z=006b3df0
// @ref ?unknown_tags_866160@@3V?$DynamicVectorClass@PAVTagClass@@@@A=00866160
// @ref ?unknown_cell_ac0050@@3VCell@@A=00ac0050

extern DynamicVectorClass<TagClass *> unknown_tags_866160;      // 0x00866160
extern Cell unknown_cell_ac0050;

bool TeamClass::unknown_func_6b8bb0()
{
    bool was_under_strength = IsUnderStrength;
    int total = Class->TaskForce->Total_Amount();
    if (unknown_48 > 0) {
        IsFullStrength = unknown_48 == total;
        if (IsFullStrength) {
            IsHasBeen = true;
        }
        if (Class->Reinforce) {
            if (total > 2) {
                IsUnderStrength = unknown_48 <= total / 3;
            } else {
                IsUnderStrength = unknown_48 < total;
            }
        } else {
            IsUnderStrength = !IsHasBeen;
        }
        if (Class->GuardSlower) {
            if (IsUnderStrength) {
                GuardSlowerIsNotUnderStrength = false;
            } else {
                GuardSlowerIsNotUnderStrength = true;
            }
        }
        JustDisappeared = false;
        NeedsToDisappear = false;
    } else {
        GuardSlowerIsNotUnderStrength = false;
        IsUnderStrength = true;
        IsFullStrength = false;
        unknown_34 = 0;
        if (IsHasBeen) {
            if (TargetNotAssigned) {
                for (int index = unknown_tags_866160.Count() - 1; index >= 0; index--) {
                    TagClass *tag = unknown_tags_866160[index];
                    if (tag->Spring(0x17, 0, unknown_cell_ac0050, 0, 0) && unknown_tags_866160.Count() == 0) {
                        break;
                    }
                }
            }
            delete this;
            return false;
        }
    }
    if (was_under_strength != IsUnderStrength) {
        IsReforming = true;
    }
    return true;
}

