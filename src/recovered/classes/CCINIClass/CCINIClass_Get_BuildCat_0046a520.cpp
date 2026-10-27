// CCINIClass::Get_BuildCat (0x0046A520).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Name_From_BuildCat@@YIPBDW4BuildCat@@@Z=00457a50
// @ref ?BuildCat_From_Name@@YI?AW4BuildCat@@PBD@Z=00457a80

BuildCat CCINIClass::Get_BuildCat(char const *section, char const *entry, BuildCat defvalue) const
{
    char buffer[32];
    Get_String(section, entry, Name_From_BuildCat(defvalue), buffer, sizeof(buffer));
    return BuildCat_From_Name(buffer);
}
