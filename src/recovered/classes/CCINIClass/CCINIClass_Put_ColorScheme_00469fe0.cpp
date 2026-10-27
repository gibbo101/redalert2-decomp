// CCINIClass::Put_ColorScheme (0x00469FE0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_ColorScheme(char const *section, char const *entry, int scheme)
{
    return Put_String(section, entry, ColorSchemes[scheme]->Name);
}
