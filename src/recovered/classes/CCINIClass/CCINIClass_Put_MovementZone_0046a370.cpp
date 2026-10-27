// CCINIClass::Put_MovementZone (0x0046A370).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_MovementZone(char const *section, char const *entry, int zone)
{
    if (zone != -1) {
        return Put_String(section, entry, MovementZoneNames[zone]);
    }
    return false;
}
