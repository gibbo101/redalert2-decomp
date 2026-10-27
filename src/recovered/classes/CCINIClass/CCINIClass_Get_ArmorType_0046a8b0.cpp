// CCINIClass::Get_ArmorType (0x0046A8B0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?ArmorNames@@3PAPBDA=0079de28
// @ref ?Armor_From_Name@@YI?AW4ArmorType@@PBD@Z=00733a20

ArmorType CCINIClass::Get_ArmorType(char const *section, char const *entry, ArmorType defvalue) const
{
    char buffer[128];
    Get_String(section, entry, ArmorNames[defvalue], buffer, sizeof(buffer));
    return Armor_From_Name(buffer);
}
