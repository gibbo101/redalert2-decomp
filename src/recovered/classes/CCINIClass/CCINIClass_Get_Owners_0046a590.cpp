// CCINIClass::Get_Owners (0x0046A590).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Owner_From_Name@@YIHPBD@Z=00482de0

int CCINIClass::Get_Owners(char const *section, char const *entry, int defvalue) const
{
    char buffer[128];
    int bits = defvalue;
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        bits = 0;
        for (char const *name = strtok(buffer, ","); name != 0; name = strtok(0, ",")) {
            bits |= Owner_From_Name(name);
        }
    }
    return bits;
}
