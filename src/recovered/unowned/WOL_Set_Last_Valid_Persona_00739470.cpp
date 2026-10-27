// void __fastcall WOL_Set_Last_Valid_Persona(Wstring const &persona) (0x00739470): writes
// [DefaultPersona] LastValid= to wolinfo.ini, creating the file first. Name is a hypothesis.
// @ref ??_C@_0M@BGMB@wolinfo?4ini?$AA@=007fd208
// @ref ??_C@_09HMCK@LastValid?$AA@=007fd294
// @ref ??_C@_0P@LNNI@DefaultPersona?$AA@=007fd284
#include "shared/ini_class.hpp"
#include "shared/cc_file_class.hpp"

void __fastcall WOL_Set_Last_Valid_Persona(Wstring const &persona)
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
        ini.Put_String("DefaultPersona", "LastValid", persona);
        ini.Save(file);
    }
}
