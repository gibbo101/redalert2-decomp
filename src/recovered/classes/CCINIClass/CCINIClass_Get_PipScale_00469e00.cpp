// CCINIClass::Get_PipScale (0x00469E00).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?PipScaleNames@@3PAUNameValueStruct@@A=007d1998

int CCINIClass::Get_PipScale(char const *section, char const *entry, int defvalue) const
{
    char buffer[32];
    if (Get_String(section, entry, "", buffer, sizeof(buffer)) > 0) {
        for (int index = 0; index < 4; index++) {
            if (_stricmp(buffer, PipScaleNames[index].Name) == 0) {
                return PipScaleNames[index].Value;
            }
        }
        return 0;
    }
    return defvalue;
}
