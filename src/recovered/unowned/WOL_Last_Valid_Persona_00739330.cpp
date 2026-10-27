// Wstring __fastcall WOL_Last_Valid_Persona() (0x00739330): the [DefaultPersona]
// LastValid entry of wolinfo.ini; null when the file is absent. Name is a hypothesis.
// @ref ??_C@_0M@BGMB@wolinfo?4ini?$AA@=007fd208
// @ref ??_C@_09HMCK@LastValid?$AA@=007fd294
// @ref ??_C@_0P@LNNI@DefaultPersona?$AA@=007fd284
#include "shared/ini_class.hpp"
#include "shared/cc_file_class.hpp"

Wstring __fastcall WOL_Last_Valid_Persona()
{
    CDFileClass file("wolinfo.ini");
    if (!file.Is_Available()) {
        return 0;
    }
    INIClass ini;
    ini.Load(file, false);
    file.Close();
    Wstring persona;
    ini.Get_String("DefaultPersona", "LastValid", persona, persona);
    return persona;
}
