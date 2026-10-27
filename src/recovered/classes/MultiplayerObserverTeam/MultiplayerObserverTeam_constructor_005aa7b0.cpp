// MultiplayerObserverTeam::MultiplayerObserverTeam() -- 0x005AA7B0 (MPObserver.cpp)
// The observers' team: a MultiplayerTeam named by the localized
// "MP:ObserverTeam" string (converted implicitly to a WideString), with
// team number -1. Class names from RTTI (vtables 0x007A6B5C, MultiplayerTeam
// 0x007A7314).
#include "shared/multiplayer_game_mode.hpp"
#include "shared/string_table.hpp"
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??0MultiplayerTeam@@QAE@ABVWideString@@H@Z=005b9b20
// @ref ??_7MultiplayerObserverTeam@@6B@=007a6b5c
// @ref ??_GMultiplayerObserverTeam@@UAEPAXI@Z=005aa810
// @ref ?unknown_slot1@MultiplayerObserverTeam@@UAE_NH@Z=005aa800
// @ref ?unknown_slot2@MultiplayerTeam@@UAE_NH@Z=005b9b80
// @ref ??_C@_0BA@IHCC@MP?3ObserverTeam?$AA@=007e54f0
// @ref ??_C@_0BG@EDON@D?3?2Ra2?2MPObserver?4cpp?$AA@=007e5500

MultiplayerObserverTeam::MultiplayerObserverTeam() :
    MultiplayerTeam(StringTable::Load_String("MP:ObserverTeam", 0, "D:\\Ra2\\MPObserver.cpp", 5), -1)
{
}
