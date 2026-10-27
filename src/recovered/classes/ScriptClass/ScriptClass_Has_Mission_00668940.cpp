// bool ScriptClass::Has_Mission() const (0x00668940)
// True while the current line exists (unsigned compare).
#include "shared/script.hpp"

bool ScriptClass::Has_Mission() const
{
    return (unsigned)CurrentMission < (unsigned)Class->MissionCount;
}
