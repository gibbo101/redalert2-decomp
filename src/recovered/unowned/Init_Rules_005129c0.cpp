// bool __fastcall Init_Rules() -- 0x005129C0
// Body 0x005129C0-0x00513070 (1713 bytes, ret at 0x00513070, nop padding to 0x00513080). Drafted by
// Init181 (then 45.98: the INIClass constructor 0x0051AD50 was not yet a row of this unit).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_ADD_HEAD
#include "shared/vector_class.hpp"
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/win32_find.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/session_state.hpp"

// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_7GenericNode@@6B@=0079aafc
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_GCCINIClass@@UAEPAXI@Z=0040e2e0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ?Unknown_00513080@@YGHPAUHWND__@@IIJ@Z=00513080
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_06HOCE@AI?4INI?$AA@=007dbb24
// @ref ??_C@_07DCPE@ART?4INI?$AA@=007dbb58
// @ref ??_C@_0N@MIIG@LANGRULE?4INI?$AA@=007dbb2c
// @ref ??_C@_09HNGH@RULE?$CK?4INI?$AA@=007dbb6c
// @ref ??_C@_09NDMD@RULES?4INI?$AA@=007dbb60
// @ref ??_C@_0BJ@DEGF@Failed?5to?5load?5ART?4INI?$CB?6?$AA@=007dbb3c
// @ref ??0?$VectorClass@PAVCCINIClass@@@@QAE@IPBQAVCCINIClass@@@Z=0051e710
// @ref ??_7?$DynamicVectorClass@PAVCCINIClass@@@@6B@=007a3c24
// @ref ??_7?$VectorClass@PAVCCINIClass@@@@6B@=007a3c04
// The VectorClass<CCINIClass *> / DynamicVectorClass<CCINIClass *> members this unit emits (the vtables
// 0x007A3C04 / 0x007A3C24 instantiate them) are the original's rows at 0x0051E0A0-0x0051E710:
// @ref ??_G?$VectorClass@PAVCCINIClass@@@@UAEPAXI@Z=0051e670
// @ref ??_G?$DynamicVectorClass@PAVCCINIClass@@@@UAEPAXI@Z=0051e6c0
// @ref ??8?$VectorClass@PAVCCINIClass@@@@UBE_NABV0@@Z=0051e100
// @ref ?Resize@?$VectorClass@PAVCCINIClass@@@@UAE_NHPBQAVCCINIClass@@@Z=0051e140
// @ref ?Clear@?$VectorClass@PAVCCINIClass@@@@UAEXXZ=0051e1f0
// @ref ?ID@?$VectorClass@PAVCCINIClass@@@@UAEHABQAVCCINIClass@@@Z=0051e220
// @ref ?ID@?$VectorClass@PAVCCINIClass@@@@UAEHPBQAVCCINIClass@@@Z=0051e260
// @ref ?Fetch@?$VectorClass@PAVCCINIClass@@@@UBEPAVCCINIClass@@H@Z=0051e0f0
// @ref ?Resize@?$DynamicVectorClass@PAVCCINIClass@@@@UAE_NHPBQAVCCINIClass@@@Z=0051e280
// @ref ?Clear@?$DynamicVectorClass@PAVCCINIClass@@@@UAEXXZ=0051e0a0
// @ref ?ID@?$DynamicVectorClass@PAVCCINIClass@@@@UAEHABQAVCCINIClass@@@Z=0051e330
// @ref ?ID@?$DynamicVectorClass@PAVCCINIClass@@@@UAEHPBQAVCCINIClass@@@Z=0051e0d0

int __stdcall Unknown_00513080(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

// Reads RULES.INI (or lets the player choose among the RULE*.INI files in the game folder,
// RULES.INI first), ART.INI, LANGRULE.INI and AI.INI, and copies the multiplayer dialog
// defaults into the session.
bool __fastcall Init_Rules()
{
    DynamicVectorClass<CCINIClass *> files;
    bool found = false;
    WIN32_FIND_DATA data;
    HANDLE handle = FindFirstFileA("RULE*.INI", &data);
    if (handle != INVALID_HANDLE_VALUE) {
        do {
            if ((data.dwFileAttributes & 0x116) == 0) {
                char const *name = data.cAlternateFileName;
                if (data.cAlternateFileName[0] == 0) {
                    name = data.cFileName;
                }
                CCFileClass file(name);
                CCINIClass *ini = new CCINIClass;
                ini->Load(file, false, false);
                if (_stricmp(name, "RULES.INI") == 0) {
                    found = true;
                    files.Add_Head(ini);
                } else {
                    files.Add(ini);
                }
            }
        } while (FindNextFileA(handle, &data));
        FindClose(handle);
        if (found) {
            goto have_rules;
        }
    }
    {
        CCFileClass file("RULES.INI");
        CCINIClass *ini = new CCINIClass;
        ini->Load(file, false, false);
        files.Add_Head(ini);
    }
have_rules:
    if (files.Count() <= 0) {
        return false;
    }

    CCFileClass artfile("ART.INI");
    if (ArtINI.Load(artfile, false, false) == 0) {
        Debug_Printf("Failed to load ART.INI!\n");
        return false;
    }

    CCINIClass *rules;
    if (files.Count() == 1) {
        rules = files[0];
    } else {
        int choice = DialogBoxParamA(ProgramInstance, MAKEINTRESOURCEA(0x93), MainWindow, Unknown_00513080, (LPARAM)&files);
        if (choice == -1) {
            choice = 0;
        }
        rules = files[choice];
    }
    unknown_ini_8396d0 = rules;
    Rules->Colors(*rules);
    Rules->Movies(ArtINI);
    Rules->Audio_Visual(*unknown_ini_8396d0);
    Rules->MPlayer(*unknown_ini_8396d0);

    unknown_session_a3d298.unknown_24 = Rules->Money;
    unknown_session_a3d298.UnitCount = Rules->UnitCount;
    unknown_house_setting_7d88d8 = Rules->TechLevel;
    unknown_session_a3d298.GameSpeed_30 = Rules->GameSpeed;
    unknown_session_a3d298.unknown_difficulty_40 = Rules->AIDifficulty;
    unknown_session_a3d298.AICount = Rules->AIPlayers;
    unknown_session_a3d298.unknown_28 = Rules->BridgeDestruction;
    unknown_session_a3d298.unknown_bases_20 = Rules->Bases;
    unknown_session_a3d298.unknown_crates_29 = Rules->Crates;
    unknown_session_a3d298.unknown_a6 = Rules->CaptureTheFlag;
    unknown_session_a3d298.unknown_a5 = Rules->HarvesterTruce;
    unknown_session_a3d298.unknown_34 = Rules->MultiEngineer;
    unknown_session_a3d298.unknown_a4 = Rules->unknown_111d;
    unknown_session_a3d298.unknown_2a = Rules->ShortGame;
    unknown_session_a3d298.unknown_2b = Rules->SuperWeaponsAllowed;
    unknown_session_a3d298.unknown_2c = Rules->BuildOffAlly;
    unknown_session_a3d298.unknown_fog_a7 = Rules->FogOfWar;
    unknown_session_a3d298.unknown_a8 = Rules->MCVRedeploys;

    CCFileClass langfile("LANGRULE.INI");
    if (langfile.Is_Available() == true) {
        CCINIClass lang;
        if (lang.Load(langfile, true, false) > 1) {
            return false;
        }
        Rules->Addition(lang);
    }

    for (int index = 0; index < files.Count(); index++) {
        if (files[index] != unknown_ini_8396d0) {
            delete files[index];
        }
    }

    CCFileClass aifile("AI.INI");
    unknown_ini_8397a0.Load(aifile, true, false);
    return true;
}
