// CCINIClass::Put_Integers (0x0046C950).
// Layout and behaviour: shared/ccini_class.hpp.
// @ref ??_C@_08POMI@?$CFd?0?$CFd?0?$CFd?$AA@=007cf360

bool CCINIClass::Put_Integers(char const *section, char const *entry, int first, int second, int third)
{
    char buffer[512] = "";
    sprintf(buffer, "%d,%d,%d", first, second, third);
    return Put_String(section, entry, buffer);
}
