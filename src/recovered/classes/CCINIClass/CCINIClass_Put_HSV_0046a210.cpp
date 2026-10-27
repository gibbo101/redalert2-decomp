// CCINIClass::Put_HSV (0x0046A210).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_HSV(char const *section, char const *entry, HSVClass const &hsv)
{
    char buffer[64];
    sprintf(buffer, "%d,%d,%d", hsv.Hue, hsv.Saturation, hsv.Value);
    return Put_String(section, entry, buffer);
}
