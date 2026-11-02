// DynamicVectorClass<MultiplayerGameMode *> &MultiplayerGameMode::unknown_modes_5b6c30() -- 0x005B6C30 (MultiplayerGameMode unit)
// The registered game modes: a function-local static list (guard bit 0 of
// 0x00A719E0, storage 0x00A71A10), destroyed at exit by 0x005B6C90.
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_INSERT_AFTER
#define VECTOR_IMPLEMENT_DYNAMIC_INSERT_AFTER
#endif
#include "shared/multiplayer_game_mode.hpp"
#include "shared/ccini_class.hpp"
// @ref ??_7?$DynamicVectorClass@PAVMultiplayerGameMode@@@@6B@=007a7178
// @ref ??_7?$VectorClass@PAVMultiplayerGameMode@@@@6B@=007a7198
// @ref _atexit=0078298a
// @ref _?$S40@?1??unknown_modes_5b6c30@MultiplayerGameMode@@SAAAV?$DynamicVectorClass@PAVMultiplayerGameMode@@@@XZ@4EA=00a719e0
// @ref _?modes@?1??unknown_modes_5b6c30@MultiplayerGameMode@@SAAAV?$DynamicVectorClass@PAVMultiplayerGameMode@@@@XZ@4V3@A=00a71a10
// @ref _$E41=005b6c90

DynamicVectorClass<MultiplayerGameMode *> &MultiplayerGameMode::unknown_modes_5b6c30()
{
    static DynamicVectorClass<MultiplayerGameMode *> modes;
    return modes;
}
