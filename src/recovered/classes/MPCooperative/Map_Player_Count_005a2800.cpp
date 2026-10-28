// int __fastcall Map_Player_Count_005a2800(char const *filename) -- 0x005A2800
// The number of players of a map file: its [Waypoints] 0..7 that are set, else
// [RandomMap] NumPlayers; 0 without a file name or when the INI does not load.
#include "shared/multiplayer_game_mode.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ini_class.hpp"
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Load@INIClass@@QAEHAAVFileClass@@_N@Z=0050bbe0
// @ref ?Get_Int@INIClass@@QBEHPBD0H@Z=0050d7f0
// @ref ??1INIClass@@UAE@XZ=0050b8d0
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??0GenericNode@@QAE@XZ=0040e160
// @ref ?Link@GenericNode@@QAEXPAV1@@Z=0040e180
// @ref ??_7INIClass@@6B@=007a2b34
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref _sprintf=007820f4
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
// @ref ??_GINIClass@@UAEPAXI@Z=004deef0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_7GenericNode@@6B@=0079aafc
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_09CKPM@RandomMap?$AA@=007e15dc
// @ref ??_C@_0L@JLOO@NumPlayers?$AA@=007e1690
// @ref ??_C@_09DFBC@Waypoints?$AA@=007e33dc
#include "shared/crt_string.hpp"

int __fastcall Map_Player_Count_005a2800(char const *filename)
{
    if (filename == 0) {
        return 0;
    }
    CCFileClass file(filename);
    INIClass ini;
    if (ini.Load(file, false) == 0) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < 8; i++) {
        char key[32];
        sprintf(key, "%d", i);
        if (ini.Get_Int("Waypoints", key, -1) != -1) {
            count++;
        }
    }
    if (count == 0) {
        count = ini.Get_Int("RandomMap", "NumPlayers", 0);
    }
    return count;
}
