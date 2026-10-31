// void TeamClass::TMission_unknown_6badc0(ScriptMissionClass const &mission, bool unknown) (0x006BADC0)
// When flagged, targets the cell under the team's object (+0x34, else the first member), then runs 0x006BA1A0.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_005629D0@MapClass@@QAEPAVCellClass@@PAVAbstractClass@@@Z=005629d0
// @ref ?unknown_func_6b79e0@TeamClass@@QAEXPAVAbstractClass@@@Z=006b79e0
// @ref ?unknown_func_6ba1a0@TeamClass@@QAEXXZ=006ba1a0

void TeamClass::TMission_unknown_6badc0(ScriptMissionClass const &mission, bool unknown)
{
    if (unknown) {
        if (unknown_34 != 0) {
            unknown_func_6b79e0(Map.Unknown_005629D0(unknown_34));
        } else {
            unknown_func_6b79e0(Map.Unknown_005629D0(Member));
        }
    }
    unknown_func_6ba1a0();
}
