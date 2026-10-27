// int __fastcall MissionClass::Mission_From_Name(char const *name) (0x00594FE0): -1 when unknown.
#include "shared/mission.hpp"
// @ref __stricmp=00781f20

extern "C" int __cdecl _stricmp(char const *left, char const *right);

int __fastcall MissionClass::Mission_From_Name(char const *name)
{
    if (name != 0) {
        for (int mission = 0; mission < 30; mission++) {
            if (_stricmp(MissionNames[mission], name) == 0) {
                return mission;
            }
        }
    }
    return -1;
}
