// CCINIClass::Get_ActionType (0x0046A3A0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?ActionNames@@3PAPBDA=0079d888

int CCINIClass::Get_ActionType(char const *section, char const *entry, int defvalue) const
{
    char buffer[32];
    Get_String(section, entry, ActionNames[defvalue], buffer, sizeof(buffer));
    for (int index = 0; index < 66; index++) {
        if (_stricmp(buffer, ActionNames[index]) == 0) {
            return index;
        }
    }
    return 0;
}
