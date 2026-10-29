// void TeamClass::TMission_unknown_6bb8b0(ScriptMissionClass const &mission, int unknown) (0x006BB8B0; Red Alert's TMission_Deploy)
// Conscripts every member; a live unit whose type deploys into a building stops the step: unless it is
// already unloading (mission 0x10) it is told to deploy where the building fits (else 0x00458B10 for its
// cell and house); simple deployers and deploying infantry get mission 0x10. Completes when no unit deploys.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/infantry_type.hpp"
#include "shared/unit_type.hpp"
#include "shared/techno_type.hpp"
#include "shared/aircraft.hpp"

void TeamClass::TMission_unknown_6bb8b0(ScriptMissionClass const &mission, int unknown)
{
    FootClass *unit = Member;
    bool finished = true;
    while (unit != 0) {
        unknown_func_6ba7d0(unit);
        if (unknown_func_6bdd80(unit) && (unit->unknown_579 || unit->Kind_Of() == 2)) {
            bool mcv = unit->Kind_Of() == 1 && ((UnitClass *)unit)->Type->DeploysInto != 0;
            bool deployer = unit->Kind_Of() == 1 && ((UnitClass *)unit)->Type->IsSimpleDeployer;
            bool infantry = unit->Kind_Of() == 0xF && ((InfantryClass *)unit)->unknown_5090a0();
            if (mcv) {
                finished = false;
                if (unit->unknown_slot91() != 0x10) {
                    unit->unknown_slot71(0);
                    if (!((UnitClass *)unit)->Type->DeploysInto->unknown_slot42(unit->unknown_slot104(), 0)) {
                        ((UnitClass *)unit)->Type->DeploysInto->unknown_458b10(unit->unknown_slot104(), unit->House);
                        unit->unknown_slot71(1);
                    } else {
                        unit->unknown_slot71(1);
                        unit->unknown_slot260(0, 1);
                        unit->unknown_slot220(0);
                        unit->unknown_slot116(0x10, false);
                    }
                }
            } else if ((deployer || infantry) && unit->unknown_slot91() != 0x10) {
                unit->unknown_slot116(0x10, false);
            }
        }
        unit = (FootClass *)unit->unknown_4c8;
    }
    if (finished) {
        StepCompleted = true;
    }
}
