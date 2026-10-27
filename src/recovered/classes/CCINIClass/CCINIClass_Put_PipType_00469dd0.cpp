// CCINIClass::Put_PipType (0x00469DD0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_PipType(char const *section, char const *entry, int pip)
{
    if (pip != 0) {
        return Put_String(section, entry, PipNames[pip].Name);
    }
    return false;
}
