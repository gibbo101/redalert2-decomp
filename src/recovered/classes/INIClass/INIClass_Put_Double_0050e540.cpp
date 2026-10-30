// INIClass::Put_Double (0x0050E540)
// Stores a number with "%f" (six decimals). The value passes through a
// float conversion that /O2 keeps in the FPU (fld/fstp qword, no rounding);
// a plain double argument is copied as two dwords instead.
#include "shared/ini_class.hpp"

bool INIClass::Put_Double(char const *section, char const *entry, double number)
{
    char buffer[512];

    sprintf(buffer, "%f", (float)number);
    return Put_String(section, entry, buffer);
}
