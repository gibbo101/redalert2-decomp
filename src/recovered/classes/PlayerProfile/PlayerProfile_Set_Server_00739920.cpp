#include "shared/player_profile.hpp"
void PlayerProfile::Set_Server_00739920(Wstring const &server)
{
    if (!(server == Server)) {
        Server = server;
        unknown_08 = true;
    }
}
