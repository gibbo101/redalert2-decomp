// UnholyAlliance::UnholyAlliance(...) -- 0x005AC330 (the UnholyAlliance unit)
// Forwards its six arguments to the MultiplayerGameMode constructor.
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/multiplayer_game_mode.hpp"
// @ref ??0MultiplayerGameMode@@QAE@ABVWideString@@0ABVWstring@@1_NH@Z=005b6cd0
// @ref ??1MultiplayerGameMode@@UAE@XZ=005b6e20
// @ref ??_7UnholyAlliance@@6B@=007a6c84
// @ref ?unknown_flag_a3d2b8@@3_NA=00a3d2b8

// A game option the Unholy Alliance mode switches on (0x00A3D2B8; its
// meaning is not identified).
extern bool unknown_flag_a3d2b8;

UnholyAlliance::UnholyAlliance(WideString const &name, WideString const &description, Wstring const &ini_name,
    Wstring const &unknown_4, bool unknown_5, int id) :
    MultiplayerGameMode(name, description, ini_name, unknown_4, unknown_5, id)
{
}
