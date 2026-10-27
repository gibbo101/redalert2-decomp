// CCINIClass::Get_Facing (0x00469BA0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

int CCINIClass::Get_Facing(char const *section, char const *entry, int defvalue) const
{
    char buffer[32];
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        return (atoi(buffer) * 256) / 360;
    }
    return defvalue;
}
