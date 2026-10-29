// void TeamClass::TMission_unknown_6bb0f0(ScriptMissionClass const &mission, bool unknown) (0x006BB0F0)
// Targets the cell of waypoint Data (when flagged, or while no second target is set and the script line is below 0x65); every Rules minutes lets the leader pick a better target for the team; then runs 0x006B9BB0 when the target has its +0x14 bit 1 set, else 0x006BA1A0.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/cell.hpp"
#include "shared/techno_type.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_6631a0@UnknownIDSource@@QAEPAVCellClass@@H@Z=006631a0
// @ref ?unknown_func_6b79e0@TeamClass@@QAEXPAVAbstractClass@@@Z=006b79e0
// @ref ?Get_Current_Mission@ScriptClass@@QBE?AVScriptMissionClass@@XZ=00668870
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref __ftol=0077f110
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_func_6b9bb0@TeamClass@@QAEXXZ=006b9bb0
// @ref ?unknown_func_6ba1a0@TeamClass@@QAEXXZ=006ba1a0
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_func_6baa60@TeamClass@@QAEPAVFootClass@@XZ=006baa60

void TeamClass::TMission_unknown_6bb0f0(ScriptMissionClass const &mission, bool unknown)
{
    CellClass *cell = unknown_id_source_a3d290->unknown_6631a0(mission.Data);
    if (unknown) {
        unknown_func_6b79e0(cell);
    }
    if (unknown_40 == 0) {
        ScriptMissionClass current = Script->Get_Current_Mission();
        if ((unsigned)current.Data < 0x65) {
            unknown_func_6b79e0(cell);
        }
    }
    if (Frame % (int)(Rules->unknown_e28 * 900.0) == 0) {
        FootClass *leader = unknown_func_6baa60();
        if (leader != 0) {
            AbstractClass *found = leader->unknown_slot219(1, &CoordStruct(leader->Coord), 0);
            if (found != 0) {
                unknown_func_6b79e0(found);
            } else if (unknown_40 != cell) {
                unknown_func_6b79e0(0);
            }
        }
    }
    if (unknown_40 != 0 && unknown_40->unknown_14_bit1) {
        unknown_func_6b9bb0();
    } else {
        unknown_func_6ba1a0();
    }
}
