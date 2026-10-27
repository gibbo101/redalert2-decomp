// bool ScriptClass::Next_Mission() (0x00668920)
// Advances to the next line; true while it exists (unsigned compare).
#include "shared/script.hpp"

bool ScriptClass::Next_Mission()
{
    return (unsigned)++CurrentMission < (unsigned)Class->MissionCount;
}
