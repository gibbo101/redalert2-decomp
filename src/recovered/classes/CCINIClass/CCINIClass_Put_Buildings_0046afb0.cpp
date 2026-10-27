// CCINIClass::Put_Buildings (0x0046AFB0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_Buildings(char const *section, char const *entry, int buildings)
{
    char buffer[128] = "";
    int count = BuildingTypes.Count() > 32 ? 32 : BuildingTypes.Count();
    for (int index = 0; index < count; index++) {
        if ((buildings & (1 << index)) != 0) {
            if (buffer[0] != '\0') {
                strcat(buffer, ",");
            }
            strcat(buffer, BuildingTypes[index]->ID);
        }
    }
    return Put_String(section, entry, buffer);
}
