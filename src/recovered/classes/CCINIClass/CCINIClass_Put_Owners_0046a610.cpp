// CCINIClass::Put_Owners (0x0046A610).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_Owners(char const *section, char const *entry, int owners)
{
    char buffer[128];
    buffer[0] = '\0';
    if (owners != 0) {
        for (int index = 0; index < HouseTypes.Count(); index++) {
            HouseTypeClass *house = HouseTypes[index];
            if ((owners & (1 << house->House)) != 0) {
                if (buffer[0] != '\0') {
                    strcat(buffer, ",");
                }
                strcat(buffer, house->ID);
            }
        }
        if (buffer[0] != '\0') {
            return Put_String(section, entry, buffer);
        }
    }
    return true;
}
