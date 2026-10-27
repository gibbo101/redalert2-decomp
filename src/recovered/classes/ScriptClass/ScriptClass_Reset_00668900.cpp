// bool ScriptClass::Reset() (0x00668900)
#include "shared/script.hpp"

bool ScriptClass::Reset()
{
    CurrentMission = -1;
    return true;
}
