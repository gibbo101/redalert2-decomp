// void __fastcall MultiplayerGameMode::unknown_init_modes_5b8bd0() -- 0x005B8BD0
// Recreates the mode list: deletes the registered modes (0x005B8D40, expanded here) and registers
// the six modes by name with their Initializer<T> (whose Create and scalar deleting destructor
// copies this unit emits).
// @ref ??_C@_06BJJB@Battle?$AA@=007e632c
// @ref ??_C@_09PAOG@ManBattle?$AA@=007e6320
// @ref ??_C@_05COBB@Siege?$AA@=007e6318
// @ref ??_C@_06DAKK@Unholy?$AA@=007e6310
// @ref ??_C@_0L@PICL@FreeForAll?$AA@=007e6304
// @ref ??_C@_0M@CHM@Cooperative?$AA@=007e62f8
// @ref ??0MultiplayerManBattle@@QAE@ABVWideString@@0ABVWstring@@1_NH@Z=005a74b0
// @ref ??0MultiplayerSiege@@QAE@ABVWideString@@0ABVWstring@@1_NH@Z=005ab5a0
// @ref ??0?$DynamicVectorClass@PAVMultiplayerGameMode@@@@QAE@IPBQAVMultiplayerGameMode@@@Z=005b95c0
// @ref ?unknown_register_5b8490@MultiplayerGameMode@@SIXABVWstring@@ABVInitializerBase@1@@Z=005b8490
// @ref ??_7InitializerBase@MultiplayerGameMode@@6B@=007a72b0
// @ref ??_GInitializerBase@MultiplayerGameMode@@UAEPAXI@Z=005b8ec0
// @ref ??_7?$Initializer@VMultiplayerBattle@@@MultiplayerGameMode@@6B@=007a72f8
// @ref ??_7?$Initializer@VMultiplayerManBattle@@@MultiplayerGameMode@@6B@=007a72ec
// @ref ??_7?$Initializer@VMultiplayerSiege@@@MultiplayerGameMode@@6B@=007a72e0
// @ref ??_7?$Initializer@VUnholyAlliance@@@MultiplayerGameMode@@6B@=007a72d4
// @ref ??_7?$Initializer@VFreeForAll@@@MultiplayerGameMode@@6B@=007a72c8
// @ref ??_7?$Initializer@VMPCooperative@@@MultiplayerGameMode@@6B@=007a72bc
#include "shared/multiplayer_game_mode.hpp"

void MultiplayerGameMode::unknown_init_modes_5b8bd0()
{
    unknown_delete_modes_5b8d40();
    Initializer<MultiplayerBattle> battle;
    unknown_register_5b8490("Battle", battle);
    Initializer<MultiplayerManBattle> man_battle;
    unknown_register_5b8490("ManBattle", man_battle);
    Initializer<MultiplayerSiege> siege;
    unknown_register_5b8490("Siege", siege);
    Initializer<UnholyAlliance> unholy;
    unknown_register_5b8490("Unholy", unholy);
    Initializer<FreeForAll> free_for_all;
    unknown_register_5b8490("FreeForAll", free_for_all);
    Initializer<MPCooperative> cooperative;
    unknown_register_5b8490("Cooperative", cooperative);
}
