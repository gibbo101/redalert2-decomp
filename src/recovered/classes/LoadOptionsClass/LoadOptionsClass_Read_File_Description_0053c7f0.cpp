// bool LoadOptionsClass::Read_File_Description(FileEntryClass *entry, WIN32_FIND_DATA const *find) (0x0053C7F0)
// The base class's slot 4: reads the saved game summary of a *.SAV file (not SAVEGAME.NET) into the list entry:
// description, player name, game type, file name and write time. A game whose first summary value differs from
// 0x007F1B18 is flagged NeedsDescription.
#include "shared/load_dlg.hpp"
#include "shared/crt_string.hpp"
// @ref ?Get_Savefile_Info@@YI_NPBDAAVSavegameInformation@@@Z=00657fa0
// @ref ??0SavegameInformation@@QAE@XZ=00659240
// @ref ?Get_unknown_00@SavegameInformation@@QBEHXZ=006592e0
// @ref ?Get_Description@SavegameInformation@@QBEPBGXZ=00659310
// @ref ?Get_unknown_18c@SavegameInformation@@QBEHXZ=00659390
// @ref ?Get_unknown_188@SavegameInformation@@QBEHXZ=00659370
// @ref ?Get_Game_Type@SavegameInformation@@QBEHXZ=00659520
// @ref ?Get_Player_Name@SavegameInformation@@QBEPBGXZ=00659350
// @ref ?unknown_savegame_version_7f1b18@@3HA=007f1b18
// @ref _wcscpy=00783689
// @ref __stricmp=00781f20
// @ref ??_C@_0N@JPFB@SAVEGAME?4NET?$AA@=007d6a4c

extern "C" wchar_t *__cdecl wcscpy(wchar_t *dest, wchar_t const *source);
extern "C" unsigned int __cdecl strlen(char const *text);
#pragma intrinsic(strlen, strcpy)

bool LoadOptionsClass::Read_File_Description(FileEntryClass *entry, WIN32_FIND_DATA const *find)
{
    if (entry || find) {
        char const *filename = find->cFileName;
        if (_stricmp(filename, "SAVEGAME.NET") != 0) {
            SavegameInformation info;
            bool valid = Get_Savefile_Info(filename, info);
            if (valid) {
                if (info.Get_unknown_00() != unknown_savegame_version_7f1b18) {
                    wcscpy(entry->Description, info.Get_Description());
                    entry->NeedsDescription = true;
                } else {
                    wcscpy(entry->Description, info.Get_Description());
                    entry->NeedsDescription = false;
                }
                entry->HasDescription = valid;
                entry->unknown_120 = info.Get_unknown_18c();
                entry->unknown_1a8 = info.Get_unknown_188();
                entry->unknown_1b8 = info.Get_Game_Type();
                strcpy(entry->Filename, filename);
                wcscpy((wchar_t *)entry->unknown_128, info.Get_Player_Name());
                if (strlen(entry->Filename) == 0) {
                    strcpy(entry->Filename, find->cAlternateFileName);
                }
                entry->LastWriteTime.dwHighDateTime = find->ftLastWriteTime.dwHighDateTime;
                entry->LastWriteTime.dwLowDateTime = find->ftLastWriteTime.dwLowDateTime;
                return true;
            }
        }
    }
    return false;
}
