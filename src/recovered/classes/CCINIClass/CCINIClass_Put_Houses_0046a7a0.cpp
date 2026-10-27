// CCINIClass::Put_Houses (0x0046A7A0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298

bool CCINIClass::Put_Houses(char const *section, char const *entry, int houses)
{
    char buffer[128];
    buffer[0] = '\0';
    if (houses != 0) {
        for (int index = 0; index < Houses.Count(); index++) {
            HouseClass *house = Houses[index];
            if ((houses & (1 << house->ArrayIndex)) != 0) {
                if (buffer[0] != '\0') {
                    strcat(buffer, ",");
                }
                strcat(buffer, house->IniName);
            }
        }
        if (buffer[0] != '\0') {
            return Put_String(section, entry, buffer);
        }
    }
    return true;
}
