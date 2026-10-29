#include "shared/multi_mission.hpp"
#include "shared/crt_string.hpp"
#include "shared/ini_class.hpp"
void MultiMission::Set_Digest(char const *digest)
{
    if (digest) {
        strncpy(unknown_15c, digest, sizeof(unknown_15c));
        unknown_15c[sizeof(unknown_15c) - 1] = '\0';
    } else {
        strcpy(unknown_15c, "No Digest");
    }
}
// @ref ??_C@_09PJBL@No?5Digest?$AA@=007f38ec
// @ref _strncpy=007823d0
