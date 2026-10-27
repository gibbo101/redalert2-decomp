// CCINIClass::Get_TheaterType (0x0046ACB0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Theater_From_Name@@YI?AW4TheaterType@@PBD@Z=00482b10

TheaterType CCINIClass::Get_TheaterType(char const *section, char const *entry, TheaterType defvalue) const
{
    char buffer[128];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        return Theater_From_Name(buffer);
    }
    return defvalue;
}
