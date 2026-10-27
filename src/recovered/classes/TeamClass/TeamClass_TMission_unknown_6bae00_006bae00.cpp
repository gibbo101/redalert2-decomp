// void TeamClass::TMission_unknown_6bae00(ScriptMissionClass const &mission, bool unknown) (0x006BAE00)
// When flagged, targets the cell whose coordinates are Data % 128 and Data / 128, then runs 0x006BA1A0.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_func_6b79e0@TeamClass@@QAEXPAVAbstractClass@@@Z=006b79e0
// @ref ?unknown_func_6ba1a0@TeamClass@@QAEXXZ=006ba1a0

void TeamClass::TMission_unknown_6bae00(ScriptMissionClass const &mission, bool unknown)
{
    if (unknown) {
        unknown_func_6b79e0(&Map[Cell((short)(mission.Data % 128), (short)(mission.Data / 128))]);
    }
    unknown_func_6ba1a0();
}
