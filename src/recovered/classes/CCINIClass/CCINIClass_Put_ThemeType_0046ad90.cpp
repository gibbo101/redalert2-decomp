// CCINIClass::Put_ThemeType (0x0046AD90).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Base_Name@ThemeClass@@QBEPBDH@Z=006e7c40

bool CCINIClass::Put_ThemeType(char const *section, char const *entry, int theme)
{
    return Put_String(section, entry, Theme.Base_Name(theme));
}
