// bool ScriptClass::Set_Mission(int mission) (0x00668910)
#include "shared/script.hpp"

bool ScriptClass::Set_Mission(int mission)
{
    CurrentMission = mission;
    return true;
}
