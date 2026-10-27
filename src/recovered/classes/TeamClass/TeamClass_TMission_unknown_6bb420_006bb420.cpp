// void TeamClass::TMission_unknown_6bb420(ScriptMissionClass const &mission, int unknown) (0x006BB420)
// Replaces the team's script with a new one of script type Data and starts it.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?Reset@ScriptClass@@QAE_NXZ=00668900
// @ref ??0ScriptClass@@QAE@PAVScriptTypeClass@@@Z=00668730
// @ref ?ScriptTypes@@3V?$DynamicVectorClass@PAVScriptTypeClass@@@@A=00866258

void TeamClass::TMission_unknown_6bb420(ScriptMissionClass const &mission, int unknown)
{
    if (Script != 0) {
        delete Script;
    }
    Script = new ScriptClass(ScriptTypes[mission.Data]);
    Script->Reset();
}
