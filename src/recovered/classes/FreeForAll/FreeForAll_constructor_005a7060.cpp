// FreeForAll::FreeForAll(...) -- 0x005A7060 (the FreeForAll unit)
// Forwards its six arguments to the MultiplayerGameMode constructor.
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/multiplayer_game_mode.hpp"
// @ref ??0MultiplayerGameMode@@QAE@ABVWideString@@0ABVWstring@@1_NH@Z=005b6cd0
// @ref ??1MultiplayerGameMode@@UAE@XZ=005b6e20
// @ref ??_7FreeForAll@@6B@=007a6914

FreeForAll::FreeForAll(WideString const &name, WideString const &description, Wstring const &ini_name,
    Wstring const &unknown_4, bool unknown_5, int id) :
    MultiplayerGameMode(name, description, ini_name, unknown_4, unknown_5, id)
{
}
