// CCINIClass::Put_ArmorType (0x0046A900).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_ArmorType(char const *section, char const *entry, ArmorType armor)
{
    return Put_String(section, entry, ArmorNames[armor]);
}
