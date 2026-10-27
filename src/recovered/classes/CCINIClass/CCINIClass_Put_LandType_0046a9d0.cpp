// CCINIClass::Put_LandType (0x0046A9D0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_LandType(char const *section, char const *entry, LandType land)
{
    return Put_String(section, entry, Name_From_Land(land));
}
