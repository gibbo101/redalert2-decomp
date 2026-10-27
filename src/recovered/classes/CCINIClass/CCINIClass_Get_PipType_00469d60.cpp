// CCINIClass::Get_PipType (0x00469D60).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?PipNames@@3PAUNameValueStruct@@A=007d1970

int CCINIClass::Get_PipType(char const *section, char const *entry, int defvalue) const
{
    char buffer[32];
    Get_String(section, entry, PipNames[defvalue].Name, buffer, sizeof(buffer));
    for (int index = 0; index < 5; index++) {
        if (_stricmp(buffer, PipNames[index].Name) == 0) {
            return PipNames[index].Value;
        }
    }
    return 1;
}
