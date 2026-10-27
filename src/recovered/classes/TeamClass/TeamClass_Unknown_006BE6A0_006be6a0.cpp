// How far a member may stray: a rules distance, a different one while the current script line is action 0x35 or 0x36.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?Get_Current_Mission@ScriptClass@@QBE?AVScriptMissionClass@@XZ=00668870
// @ref ?Rules@@3PAVRulesClass@@A=00839848

int TeamClass::Unknown_006BE6A0()
{
    int action = Script->Get_Current_Mission().Mission;
    if (action != 0x36 && action != 0x35) {
        return Rules->unknown_1384;
    }
    return Rules->unknown_1388;
}
