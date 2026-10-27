// CCINIClass::Get_Foundation (0x0046A260).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?FoundationNames@@3PAUNameValueStruct@@A=007d19b8

int CCINIClass::Get_Foundation(char const *section, char const *entry, int defvalue) const
{
    char buffer[32];
    Get_String(section, entry, FoundationNames[defvalue].Name, buffer, sizeof(buffer));
    for (int index = 0; index < 22; index++) {
        if (_stricmp(buffer, FoundationNames[index].Name) == 0) {
            return FoundationNames[index].Value;
        }
    }
    return 0;
}
