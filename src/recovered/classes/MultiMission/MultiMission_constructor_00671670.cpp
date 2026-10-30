#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/multi_mission.hpp"
#include "shared/ccini_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/buffer_straw.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/debug_printf.hpp"
#include "shared/ini_class.hpp"
#include "shared/lobby.hpp"
MultiMission::MultiMission(INIClass &ini, char const *section)
{
    Description[0] = 0;
    unknown_58[sizeof(unknown_58) - 1] = '\0';
    strcpy(unknown_15c, "No Digest");
    unknown_17c = true;
    unknown_180 = 2;
    unknown_184 = 4;
    DiskIDs.Clear();
    if (!section) {
        return;
    }
    strcpy(unknown_58, section);
    strcat(unknown_58, ".MAP");
    if (ini.Is_Present(section, "DescriptionText")) {
        char text[0x2C];
        ini.Get_String(section, "DescriptionText", "", text, 0x2C);
        Unknown_006FA0C0(Description, text, -1);
    } else {
        ini.Get_Wide_String(section, "Description", Description, 0x2C);
    }
    unknown_180 = ini.Get_Int(section, "MinPlayers", unknown_180);
    unknown_184 = ini.Get_Int(section, "MaxPlayers", unknown_184);
    char disks[0x80];
    if (ini.Get_String(section, "CD", "", disks, 0x80)) {
        char *token = strtok(disks, ",");
        while (token && *token) {
            DiskIDs.Add((DiskID)atoi(token));
            token = strtok(0, ",");
        }
    }
    Wstring modes;
    bool found = ini.Get_String(section, "GameMode", "", modes) > 0;
    if (found) {
        Wstring token;
        int position = modes.Get_Token(0, ",", token);
        while (position != -1) {
            token.Trim_Leading(" ");
            token.Trim_Trailing(" ");
            GameModes.Add(token);
            position = modes.Get_Token(position, ",", token);
        }
    }
    CCFileClass file(unknown_58);
    if (!file.Is_Available()) {
        Debug_Printf("Unable to locate scenario %s - No digest info will be loaded\n", unknown_58);
    } else {
        if (!file.Open(FILE_RIGHTS_READ)) {
            return;
        }
        file.Seek(-100, 2);
        char tail[0x80];
        memset(tail, 0, sizeof(tail));
        file.Read(tail, 0x64);
        file.Close();
        if (strstr(tail, "[Digest]")) {
            CCINIClass digest_ini;
            BufferStraw straw(tail, 0x64);
            digest_ini.Load(straw, false, false);
            digest_ini.Get_String("Digest", "1", 0, tail, 0x80);
            if (tail) {
                strncpy(unknown_15c, tail, 0x20);
                unknown_15c[0x1F] = '\0';
            } else {
                strcpy(unknown_15c, "No Digest");
            }
        }
    }
}
// @ref ??_C@_0BA@DPIH@DescriptionText?$AA@=007f3b50
// @ref ??_C@_0L@OMDI@MinPlayers?$AA@=007f3904
// @ref ??_C@_0L@MMHH@MaxPlayers?$AA@=007f38f8
// @ref ??_C@_08MPBJ@?$FLDigest?$FN?$AA@=007f3948
// @ref ??_C@_09PJBL@No?5Digest?$AA@=007f38ec
// @ref ??_C@_04OANC@?4MAP?$AA@=007e375c
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_0M@DKEL@Description?$AA@=007d1444
// @ref ??_C@_02JOMG@CD?$AA@=007d1474
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_08MAFF@GameMode?$AA@=007f34d8
// @ref ??_C@_01FCOA@?5?$AA@=007e613c
// @ref ??_C@_01FBAH@1?$AA@=007e6f6c
// @ref ??_C@_06JBJP@Digest?$AA@=007d1ef0
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??0GenericList@@QAE@XZ=00490e80
// @ref ??0?$List@PAUINISection@INIClass@@@@QAE@XZ=00490ff0
// @ref ??0?$IndexClass@HPAUINISection@INIClass@@@@QAE@XZ=004910c0
// @ref ??_C@_0DO@BANC@Unable?5to?5locate?5scenario?5?$CFs?5?9?5N@=007f3b10
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_GCCINIClass@@UAEPAXI@Z=0040e2e0
