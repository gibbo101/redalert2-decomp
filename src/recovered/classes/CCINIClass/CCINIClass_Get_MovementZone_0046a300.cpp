// CCINIClass::Get_MovementZone (0x0046A300).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?MovementZoneNames@@3PAPBDA=007d1a68

int CCINIClass::Get_MovementZone(char const *section, char const *entry, int defvalue) const
{
    char buffer[32];
    Get_String(section, entry, MovementZoneNames[defvalue], buffer, sizeof(buffer));
    for (int index = 0; index < 12; index++) {
        if (_stricmp(buffer, MovementZoneNames[index]) == 0) {
            return index;
        }
    }
    return -1;
}
