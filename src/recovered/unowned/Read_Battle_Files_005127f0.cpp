// void __fastcall Read_Battle_Files() -- 0x005127F0
// __fastcall (no parameters): as __cdecl VC6 schedules the object address loads after the argument pushes.
#include "shared/win32_find.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/campaign.hpp"
#include "shared/crt_string.hpp"

// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_7GenericNode@@6B@=0079aafc
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_GCCINIClass@@UAEPAXI@Z=0040e2e0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_C@_0M@LBEG@BATTLE?$CK?4INI?$AA@=007dbab0
// @ref ??_C@_0L@HBHN@BATTLE?4INI?$AA@=007dbaa4

// Reads the [Battles] of every BATTLE*.INI in the game folder (by its short name when it
// has one); BATTLE.INI itself is read from the mixfiles when the folder has none.
void __fastcall Read_Battle_Files()
{
    bool found = false;
    WIN32_FIND_DATA data;
    HANDLE handle = FindFirstFileA("BATTLE*.INI", &data);
    if (handle != INVALID_HANDLE_VALUE) {
        do {
            if ((data.dwFileAttributes & 0x116) == 0) {
                char const *name = data.cAlternateFileName;
                if (strlen(name) == 0) {
                    name = data.cFileName;
                }
                CCFileClass file(name);
                CCINIClass *ini = new CCINIClass;
                ini->Load(file, false, false);
                if (_stricmp(name, "BATTLE.INI") == 0) {
                    found = true;
                }
                CampaignClass::Read_Battles(*ini);
                delete ini;
            }
        } while (FindNextFileA(handle, &data));
        FindClose(handle);
    }
    if (!found) {
        CCFileClass file("BATTLE.INI");
        CCINIClass *ini = new CCINIClass;
        if (ini != 0) {
            ini->Load(file, false, false);
            CampaignClass::Read_Battles(*ini);
            delete ini;
        }
    }
}
