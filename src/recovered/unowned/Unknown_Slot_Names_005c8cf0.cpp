// void __fastcall Unknown_Slot_Names_005c8cf0(wchar_t *list) (0x005C8CF0)
// Writes the name of each of the eight slots' entries into list, each followed by a comma.
#include "shared/lobby.hpp"
#include "shared/wide_string.hpp"
// @ref ?Wstring_To_Wide@@YI?AVWideString@@ABVWstring@@@Z=007711c0
// @ref ??_C@_13JKDK@?$AA?0?$AA?$AA@=007e5c64
// @ref ?unknown_player_slots_a3fa98@@3PAPAUNodeNameType@@A=00a3fa98
// @ref ?unknown_player_a72d44@@3PAUNodeNameType@@A=00a72d44
// @ref ?unknown_lobby_entries_a72d2c@@3PAPAUNodeNameType@@A=00a72d2c
// @ref ??0WideString@@QAE@XZ=0076f9b0
// @ref ??1WideString@@QAE@XZ=0076fa50
// @ref ??1Wstring@@QAE@XZ=0076d9e0
// @ref ??4WideString@@QAEAAV0@ABV0@@Z=0076fbd0
// @ref ??4WideString@@QAEAAV0@PBG@Z=0076fb70
// @ref ?Get@WideString@@QBEPBGXZ=007703f0
// @ref _wcscat=0078365f

extern "C" unsigned short *__cdecl wcscat(unsigned short *dest, unsigned short const *source);

void __fastcall Unknown_Slot_Names_005c8cf0(wchar_t *list)
{
    *list = 0;
    for (int i = 0; i < 8; i++) {
        NodeNameType *entry = unknown_player_slots_a3fa98[i];
        WideString name;
        if (entry == 0 || entry == unknown_lobby_entries_a72d2c[0] || entry == unknown_lobby_entries_a72d2c[1] ||
            entry == unknown_lobby_entries_a72d2c[5] || entry == unknown_player_a72d44 ||
            entry == unknown_lobby_entries_a72d2c[2] || entry == unknown_lobby_entries_a72d2c[3] ||
            entry == unknown_lobby_entries_a72d2c[4]) {
            Wstring text = Unknown_Lobby_Entry_Name_005cd0e0(entry);
            name = Wstring_To_Wide(text);
        } else {
            name = entry->Name;
        }
        wcscat(list, name.Get());
        wcscat(list, L",");
    }
}
