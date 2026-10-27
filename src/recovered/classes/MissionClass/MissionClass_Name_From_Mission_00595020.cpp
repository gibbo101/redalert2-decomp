// char const *__fastcall MissionClass::Name_From_Mission(int mission) (0x00595020)
#include "shared/mission.hpp"

char const *__fastcall MissionClass::Name_From_Mission(int mission)
{
    if (mission != -1) {
        return MissionNames[mission];
    }
    return "<none>";
}
