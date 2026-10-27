// UnholyAlliance::UnholyAlliance(...) -- 0x005AC330 (the UnholyAlliance unit)
// Forwards its six arguments to the MultiplayerGameMode constructor.
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/multiplayer_game_mode.hpp"
// @ref ??0MultiplayerGameMode@@QAE@PBXHHHHH@Z=005b6cd0
// @ref ??1MultiplayerGameMode@@UAE@XZ=005b6e20
// @ref ??_7UnholyAlliance@@6B@=007a6c84
// @ref ?unknown_flag_a3d2b8@@3_NA=00a3d2b8

// A game option the Unholy Alliance mode switches on (0x00A3D2B8; its
// meaning is not identified).
extern bool unknown_flag_a3d2b8;

UnholyAlliance::UnholyAlliance(void const *unknown_1, int unknown_2, int unknown_3, int unknown_4, int unknown_5,
                               int unknown_6) :
    MultiplayerGameMode(unknown_1, unknown_2, unknown_3, unknown_4, unknown_5, unknown_6)
{
}
