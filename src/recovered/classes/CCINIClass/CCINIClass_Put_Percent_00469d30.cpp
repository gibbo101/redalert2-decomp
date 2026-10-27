// CCINIClass::Put_Percent (0x00469D30).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_Percent(char const *section, char const *entry, int value)
{
    return Put_Int(section, entry, (value * 100) / 256);
}
