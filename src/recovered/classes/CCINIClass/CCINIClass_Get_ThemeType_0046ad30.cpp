// CCINIClass::Get_ThemeType (0x0046AD30).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?From_Name@ThemeClass@@QBEHPBD@Z=006e8510
// @ref ?Theme@@3VThemeClass@@A=00a35d78

int CCINIClass::Get_ThemeType(char const *section, char const *entry, int defvalue) const
{
    char buffer[128];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        return Theme.From_Name(buffer);
    }
    return defvalue;
}
