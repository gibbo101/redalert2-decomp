// CCINIClass::Get_ColorScheme (0x00469F50).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8

int CCINIClass::Get_ColorScheme(char const *section, char const *entry, int defvalue) const
{
    char buffer[32];
    Get_String(section, entry, ColorSchemes[defvalue]->Name, buffer, sizeof(buffer));
    for (int index = 0; index < ColorSchemes.Count(); index++) {
        if (_stricmp(ColorSchemes[index]->Name, buffer) == 0 && ColorSchemes[index]->unknown_0x310 != 1) {
            return index;
        }
    }
    return defvalue;
}
