// CCINIClass::Get_LandType (0x0046A970).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Name_From_Land@@YIPBDW4LandType@@@Z=00482f00
// @ref ?Land_From_Name@@YI?AW4LandType@@PBD@Z=00482eb0

LandType CCINIClass::Get_LandType(char const *section, char const *entry, LandType defvalue) const
{
    char buffer[128];
    if (Get_String(section, entry, Name_From_Land(defvalue), buffer, sizeof(buffer))) {
        return Land_From_Name(buffer);
    }
    return defvalue;
}
