// MultiplayerBattle::MultiplayerBattle(...) -- 0x005A2320 (the MultiplayerBattle unit)
// Forwards its six arguments to the MultiplayerGameMode constructor
// (0x005B6CD0). This unit also emits (and the link kept) the
// MultiplayerGameMode inline virtuals 0x005A2380-0x005A24F0.
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/multiplayer_game_mode.hpp"
// @ref ??0MultiplayerGameMode@@QAE@PBXHHHHH@Z=005b6cd0
// @ref ??1MultiplayerGameMode@@UAE@XZ=005b6e20
// @ref ??_7MultiplayerBattle@@6B@=007a66b4

MultiplayerBattle::MultiplayerBattle(void const *unknown_1, int unknown_2, int unknown_3, int unknown_4,
                                     int unknown_5, int unknown_6) :
    MultiplayerGameMode(unknown_1, unknown_2, unknown_3, unknown_4, unknown_5, unknown_6)
{
}
