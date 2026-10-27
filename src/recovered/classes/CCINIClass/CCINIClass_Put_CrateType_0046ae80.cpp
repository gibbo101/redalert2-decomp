// CCINIClass::Put_CrateType (0x0046AE80).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?CrateNames@@3PAPBDA=0079de54

bool CCINIClass::Put_CrateType(char const *section, char const *entry, CrateType crate)
{
    return Put_String(section, entry, CrateNames[crate]);
}
