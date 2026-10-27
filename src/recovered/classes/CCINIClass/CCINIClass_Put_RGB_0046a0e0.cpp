// CCINIClass::Put_RGB (0x0046A0E0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_RGB(char const *section, char const *entry, RGBClass const &rgb)
{
    char buffer[64];
    sprintf(buffer, "%d,%d,%d", rgb.Red, rgb.Green, rgb.Blue);
    return Put_String(section, entry, buffer);
}
