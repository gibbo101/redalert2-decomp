// MultiplayerTeam::MultiplayerTeam(WideString const &name, int number) -- 0x005B9B20 (MultiplayerTeam unit)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/multiplayer_game_mode.hpp"
// @ref ??0WideString@@QAE@ABV0@@Z=0076fa10
// @ref ??1WideString@@QAE@XZ=0076fa50
// @ref ??_7MultiplayerTeam@@6B@=007a7314
// @ref ?unknown_players_a3fa7c@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa7c
// @ref ?unknown_text_770430@WideString@@QBEPBGXZ=00770430
// @ref __imp__SendMessageA@16=0079a4a0

WIN32_IMPORT long __stdcall SendMessageA(HWND window, unsigned int message, unsigned int wparam, long lparam);

MultiplayerTeam::MultiplayerTeam(WideString const &name, int number) : Name(name), Number(number)
{
}
