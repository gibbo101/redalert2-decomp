// Wstring __fastcall WOL_Auto_Login_Persona() (0x007390B0): the [DefaultPersona]
// AutoLogin entry of wolinfo.ini; null when the file is absent. Name is a hypothesis.
// Fastcall: the hidden result pointer arrives in ecx (mov esi, ecx), and the Wstring
// temporaries are built before the pushes (implicit conversions).
// @ref ??_C@_0M@BGMB@wolinfo?4ini?$AA@=007fd208
// @ref ??_C@_09FGAK@AutoLogin?$AA@=007fd268
// @ref ??_C@_0P@LNNI@DefaultPersona?$AA@=007fd284
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_7INIClass@@6B@=007a2b34
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_GINIClass@@UAEPAXI@Z=004deef0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
#include "shared/ini_class.hpp"
#include "shared/cc_file_class.hpp"

Wstring __fastcall WOL_Auto_Login_Persona()
{
    CDFileClass file("wolinfo.ini");
    if (!file.Is_Available()) {
        return 0;
    }
    INIClass ini;
    ini.Load(file, false);
    file.Close();
    Wstring persona;
    ini.Get_String("DefaultPersona", "AutoLogin", persona, persona);
    return persona;
}
