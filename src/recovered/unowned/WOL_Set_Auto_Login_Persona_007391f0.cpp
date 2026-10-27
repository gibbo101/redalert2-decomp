// void __fastcall WOL_Set_Auto_Login_Persona(Wstring const &persona) (0x007391F0): writes
// [DefaultPersona] AutoLogin= to wolinfo.ini, creating the file first. Name is a hypothesis.
// The section and entry literals convert implicitly to Put_String's Wstring overload.
// @ref ??_C@_0M@BGMB@wolinfo?4ini?$AA@=007fd208
// @ref ??_C@_09FGAK@AutoLogin?$AA@=007fd268
// @ref ??_C@_0P@LNNI@DefaultPersona?$AA@=007fd284
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_7INIClass@@6B@=007a2b34
// @ref ??_7CDFileClass@@6B@=0079a658
#include "shared/ini_class.hpp"
#include "shared/cc_file_class.hpp"

void __fastcall WOL_Set_Auto_Login_Persona(Wstring const &persona)
{
    CDFileClass file("wolinfo.ini");
    if (!file.Is_Available()) {
        file.Create();
        file.Close();
        file.Open("wolinfo.ini", 1);
    }
    INIClass ini;
    if (file.Is_Available()) {
        ini.Load(file, false);
        ini.Put_String("DefaultPersona", "AutoLogin", persona);
        ini.Save(file);
    }
}
