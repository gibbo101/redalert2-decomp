// CCINIClass::Get_CrateType (0x0046AE30).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Crate_From_Name@@YI?AW4CrateType@@PBD@Z=00482da0

CrateType CCINIClass::Get_CrateType(char const *section, char const *entry, CrateType defvalue) const
{
    char buffer[128];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        return Crate_From_Name(buffer);
    }
    return defvalue;
}
