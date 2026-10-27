// CCINIClass::Get_Houses (0x0046A720).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Find_Index@HouseClass@@SIHPBD@Z=004f5b40

int CCINIClass::Get_Houses(char const *section, char const *entry, int defvalue) const
{
    char buffer[128];
    int bits = defvalue;
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        bits = 0;
        for (char const *name = strtok(buffer, ","); name != 0; name = strtok(0, ",")) {
            bits |= 1 << HouseClass::Find_Index(name);
        }
    }
    return bits;
}
