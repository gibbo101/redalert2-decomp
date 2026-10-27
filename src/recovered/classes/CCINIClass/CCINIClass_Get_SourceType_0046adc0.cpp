// CCINIClass::Get_SourceType (0x0046ADC0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Source_From_Name@@YI?AW4SourceType@@PBD@Z=00482ab0

SourceType CCINIClass::Get_SourceType(char const *section, char const *entry, SourceType defvalue) const
{
    char buffer[128];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        return Source_From_Name(buffer);
    }
    return defvalue;
}
