#include "shared/multi_mission.hpp"
#include "shared/crt_string.hpp"
#include "shared/ini_class.hpp"
// Red Alert's MultiMission::Set_Filename.
void MultiMission::Set_Filename(char const *filename)
{
    if (filename) {
        strncpy(unknown_58, filename, sizeof(unknown_58));
        unknown_58[sizeof(unknown_58) - 1] = '\0';
    } else {
        strcpy(unknown_58, "No File Name");
    }
}
// @ref ??_C@_0N@ENPG@No?5File?5Name?$AA@=007f3b60
// @ref _strncpy=007823d0
