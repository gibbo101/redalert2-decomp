// bool __fastcall Find_Local_Scenario_0066c5b0(char *filename, int length, char *digest, bool official, bool unknown)
// (0x0066C5B0): looks the multiplayer map up by file name (never RandMap.Sed); with `unknown` set it asks for the
// disk the map is on when the file is missing; true (and the file name in the list's spelling) when the file
// has the given length and, unless digest is null or empty, its [Digest] 1 entry equals digest.
#include "shared/lobby.hpp"
#include "shared/session_state.hpp"
#include "shared/multi_mission.hpp"
#include "shared/cd.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ini_class.hpp"
#include "shared/crt_string.hpp"
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Is_Available@CCFileClass@@UAEHH@Z=004691a0
// @ref ?Size@CCFileClass@@UAEJXZ=00469150
// @ref ?Load@INIClass@@QAEHAAVFileClass@@_N@Z=0050bbe0
// @ref ?Get_String@INIClass@@QBEHPBD00PADH@Z=0050e9a0
// @ref ??1INIClass@@UAE@XZ=0050b8d0
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??0GenericList@@QAE@XZ=00490e80
// @ref ??_7INIClass@@6B@=007a2b34
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_7CD@@6B@=0079d868
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_7GenericNode@@6B@=0079aafc
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
// @ref ??_GINIClass@@UAEPAXI@Z=004deef0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_EWstring@@QAEPAXI@Z=0040af40
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
// @ref ?RequiredCD@CD@@2HA=007d20e0
// @ref ?Set_Required_CD@CD@@SIXH@Z=0046e4d0
// @ref ?Unknown_0046E4C0@@YIHH@Z=0046e4c0
// @ref ?Unknown_00671F00@MultiMission@@QAE_NH@Z=00671f00
// @ref ?Unknown_00671F90@MultiMission@@QAEHXZ=00671f90
// @ref ?unknown_counter_a3fabc@@3HA=00a3fabc
// @ref ?unknown_multi_missions_a3d8d8@@3V?$DynamicVectorClass@PAVMultiMission@@@@A=00a3d8d8
// @ref ??_C@_0M@FDHG@RandMap?4Sed?$AA@=007e16e8
// @ref ??_C@_06JBJP@Digest?$AA@=007d1ef0
// @ref ??_C@_01FBAH@1?$AA@=007e6f6c
// @ref ??_C@_0BL@HJFD@No?5digest?5here?5mate?4?5Nope?4?$AA@=007e6f70

bool __fastcall Find_Local_Scenario_0066c5b0(char *filename, int length, char *digest, bool official, bool unknown)
{
    if (_stricmp(filename, "RandMap.Sed") != 0) {
        for (int index = 0; index < unknown_multi_missions_a3d8d8.Count(); index++) {
            if (_stricmp(unknown_multi_missions_a3d8d8[index]->unknown_58, filename) == 0) {
                CCFileClass file(unknown_multi_missions_a3d8d8[index]->unknown_58);
                if (!file.Is_Available() && unknown == true) {
                    MultiMission *mission = unknown_multi_missions_a3d8d8[index];
                    if (!mission->Unknown_00671F00(Unknown_0046E4C0(60))) {
                        CD::Set_Required_CD(mission->Unknown_00671F90());
                    }
                    unknown_counter_a3fabc++;
                    if (!CD().Force_Available(CD::RequiredCD)) {
                        unknown_counter_a3fabc--;
                        return false;
                    }
                    unknown_counter_a3fabc--;
                }
                if (file.Is_Available() && file.Size() == length) {
                    INIClass ini;
                    ini.Load(file, false);
                    char file_digest[32];
                    ini.Get_String("Digest", "1", "No digest here mate. Nope.", file_digest, sizeof(file_digest));
                    if (digest == 0 || *digest == '\0' || strcmp(digest, file_digest) == 0) {
                        strcpy(filename, unknown_multi_missions_a3d8d8[index]->unknown_58);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
