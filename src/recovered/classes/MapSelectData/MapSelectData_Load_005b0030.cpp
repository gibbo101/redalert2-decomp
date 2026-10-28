// bool MapSelectData::Load(Wstring const &section) (0x005B0030)
// Reads MAPSEL.INI: the stages listed as 1..100 under the section, then
// the section's Anims list (with TextRect and Palette), then its Sounds.
// Assumption: CCFileClass::Open(char const *, int) is an inline member of
// the original header (below; evidence: the Set_Name/Open calls on the local
// file are virtual, and its kept copy 0x00401980 sits among the inline
// header members of the first object file). Expanding it here is also what
// leaves GenericList::GenericList (0x00490E80) out of line in this function.
#include "shared/ms_choice.hpp"
#include "shared/cc_file_class.hpp"
// @ref ??0MapStage@@QAE@AAVINIClass@@ABVWstring@@@Z=005b0a20
// @ref ??_C@_05IAFM@Anims?$AA@=007e5a74
// @ref ??_C@_06MEDA@Sounds?$AA@=007e5a44
// @ref ??_C@_07NBFD@Palette?$AA@=007d9e2c
// @ref ??_C@_08MIOO@TextRect?$AA@=007e5a68
// @ref ??_C@_0BK@CFCJ@Failed?5to?5create?5anim?5?$CFs?6?$AA@=007e5a4c
// @ref ??_C@_0BL@FGF@Failed?5to?5load?5MAPSEL?4INI?6?$AA@=007e5ac8
// @ref ??_C@_0CE@BMKM@MapSelect?3?5There?5isn?8t?5any?5stage@=007e5a7c
// @ref ??_C@_0CG@GLBJ@MapSelect?3?5Failed?5to?5create?5stag@=007e5aa0
// @ref ??_C@_0L@NANM@MAPSEL?4INI?$AA@=007e5ae4
// @ref ?Get_String@INIClass@@QBEHABVWstring@@00AAV2@@Z=0050eb40
// @ref ?Int_To_Wstring@@YI?AVWstring@@H@Z=0076f580
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?Open@CCFileClass@@UAEHPBDH@Z=00401980
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
// @ref ??_7INIClass@@6B@=007a2b34
// @ref ??_GINIClass@@UAEPAXI@Z=004deef0
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??0GenericList@@QAE@XZ=00490e80
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_7GenericNode@@6B@=0079aafc
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0

// CCFileClass::Open(char const *, int) (0x00401980): an inline header member
// in the original; the unqualified Set_Name/Open calls inside it stay virtual
// when it is expanded. Defined here until shared/cc_file_class.hpp carries it.
inline int CCFileClass::Open(char const *filename, int rights)
{
    Set_Name(filename);
    return Open(rights);
}

bool MapSelectData::Load(Wstring const &section)
{
    CCFileClass file;
    INIClass ini;
    Wstring anims;
    Wstring value;

    Clear();
    file.Open("MAPSEL.INI", 1);
    if (ini.Load(file, false) == 0) {
        Debug_Printf("Failed to load MAPSEL.INI\n");
        return false;
    }

    int index;
    for (index = 1; index <= 100; index++) {
        if (ini.Get_String(section, Int_To_Wstring(index), (char const *)0, value) == 0) {
            break;
        }
        MapStage *stage = new MapStage(ini, value);
        if (stage == 0) {
            Debug_Printf("MapSelect: Failed to create stage %s\n", value);
            return false;
        }
        Stages.Add(stage);
    }
    if (Stages.Count() == 0) {
        Debug_Printf("MapSelect: There isn't any stages!\n");
        return false;
    }

    if (ini.Get_String(section, "Anims", (char const *)0, anims) > 0) {
        if (ini.Get_String(anims, "TextRect", (char const *)0, value) > 0) {
            Wstring token;
            int position = value.Get_Token(0, ",", token);
            if (token.Length() > 0) {
                TextRect.X = token.As_Integer();
            }
            position = value.Get_Token(position, ",", token);
            if (token.Length() > 0) {
                TextRect.Y = token.As_Integer();
            }
            position = value.Get_Token(position, ",", token);
            if (token.Length() > 0) {
                TextRect.Width = token.As_Integer();
            }
            value.Get_Token(position, ",", token);
            if (token.Length() > 0) {
                TextRect.Height = token.As_Integer();
            }
        }
        if (ini.Get_String(anims, "Palette", (char const *)0, value) > 0) {
            Palette = value;
        }
        for (index = 1; index <= 100; index++) {
            if (ini.Get_String(anims, Int_To_Wstring(index), (char const *)0, value) == 0) {
                break;
            }
            MSAnimEntry *anim = new MSAnimEntry(value);
            if (anim == 0) {
                Debug_Printf("Failed to create anim %s\n", value);
                return false;
            }
            Anims.Add(anim);
        }
    }

    if (unknown_check_406f30()) {
        Wstring entry;
        if (ini.Get_String(section, "Sounds", (char const *)0, anims) > 0) {
            for (index = 0; index < ini.Entry_Count(anims); index++) {
                entry = ini.Get_Entry(anims, index);
                if (entry != 0 && ini.Get_String(anims, entry, (char const *)0, value) > 0) {
                    MSSfxEntry *sound = new MSSfxEntry(entry, value);
                    if (sound->Name == 0) {
                        delete sound;
                    } else if (sound != 0) {
                        Sounds.Add(sound);
                    }
                }
            }
        }
    }
    return true;
}
