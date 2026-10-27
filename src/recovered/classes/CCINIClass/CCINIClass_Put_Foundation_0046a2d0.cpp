// CCINIClass::Put_Foundation (0x0046A2D0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_Foundation(char const *section, char const *entry, int foundation)
{
    if (foundation != -1) {
        return Put_String(section, entry, FoundationNames[foundation].Name);
    }
    return false;
}
