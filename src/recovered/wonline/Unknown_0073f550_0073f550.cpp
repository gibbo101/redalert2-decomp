// WideString __fastcall Unknown_0073f550(Wstring const &filename) (0x0073F550)
// The description of the multiplayer map with this file name: the random-map text for RandMap.Sed,
// empty when the map is not in the session's list.
#include "shared/wol_sink.hpp"
#include "shared/multi_mission.hpp"
#include "shared/crt_string.hpp"
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
// @ref ??_EWstring@@QAEPAXI@Z=0040af40
// @ref ??_C@_0BL@DEKD@TXT_RANDOM_MAP_DESCRIPTION?$AA@=007e14dc
// @ref ??_C@_0M@FDHG@RandMap?4Sed?$AA@=007e16e8
// @ref ??_C@_0BD@IJO@D?3?2Ra2?2wonline?4cpp?$AA@=007fd62c

WideString __fastcall Unknown_0073f550(Wstring const &filename)
{
    if (_stricmp(filename.Peek_Buffer(), "RandMap.Sed") == 0) {
        return WideString(StringTable::Load_String("TXT_RANDOM_MAP_DESCRIPTION", 0, "D:\\Ra2\\wonline.cpp", 2705));
    }
    for (int index = 0; index < unknown_multi_missions_a3d8d8.Count(); index++) {
        MultiMission *mission = unknown_multi_missions_a3d8d8[index];
        if (_stricmp(filename.Peek_Buffer(), mission->unknown_58) == 0) {
            return WideString(mission->Description);
        }
    }
    return WideString(L"");
}
