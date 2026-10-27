// CCINIClass::Put_Facing (0x00469B50).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_Facing(char const *section, char const *entry, int facing)
{
    char buffer[32];
    sprintf(buffer, "%d", (facing * 360) / 256);
    return Put_String(section, entry, buffer);
}
