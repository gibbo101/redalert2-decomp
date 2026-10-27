// MultiplayerSiegeDefenderTeam::MultiplayerSiegeDefenderTeam() -- 0x005ABDC0 (MPSiegeTeam.cpp)
// The siege defenders: team number 1, named by the localized
// "MP:DefenderTeam" string. Class names from RTTI (vtables 0x007A6C54
// defender, 0x007A6C64 attacker, 0x007A7314 MultiplayerTeam).
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/multiplayer_game_mode.hpp"
#include "shared/string_table.hpp"
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??0MultiplayerTeam@@QAE@ABVWideString@@H@Z=005b9b20
// @ref ??_7MultiplayerSiegeDefenderTeam@@6B@=007a6c54
// @ref ??_GMultiplayerSiegeDefenderTeam@@UAEPAXI@Z=005abec0
// @ref ?unknown_slot2@MultiplayerTeam@@UAE_NH@Z=005b9b80
// @ref ??_C@_0BA@NAFP@MP?3DefenderTeam?$AA@=007e5764
// @ref ??_C@_0BH@CFFE@D?3?2Ra2?2MPSiegeTeam?4cpp?$AA@=007e5774

MultiplayerSiegeDefenderTeam::MultiplayerSiegeDefenderTeam() :
    MultiplayerTeam(StringTable::Load_String("MP:DefenderTeam", 0, "D:\\Ra2\\MPSiegeTeam.cpp", 6), 1)
{
}
