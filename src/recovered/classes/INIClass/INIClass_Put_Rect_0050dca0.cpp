// INIClass::Put_Rect (0x0050DCA0)
// Stores a rectangle as "x,y,width,height".
#include "shared/ini_class.hpp"

bool INIClass::Put_Rect(char const *section, char const *entry, INIRect const &value)
{
    char buffer[64];

    sprintf(buffer, "%d,%d,%d,%d", value.X, value.Y, value.Width, value.Height);
    return Put_String(section, entry, buffer);
}
