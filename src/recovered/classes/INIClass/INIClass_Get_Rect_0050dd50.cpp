// INIClass::Get_Rect (0x0050DD50)
// Reads a "x,y,width,height" rectangle; defvalue when the entry is missing or empty
// (the text is read through Get_String into a 64-byte buffer).
#include "shared/ini_class.hpp"
// @ref ??_C@_07MFIN@0?00?00?00?$AA@=007db4a8

INIRect INIClass::Get_Rect(char const *section, char const *entry, INIRect const &defvalue) const
{
    char buffer[64];

    if (Get_String(section, entry, "0,0,0,0", buffer, sizeof(buffer)) != 0) {
        INIRect value = defvalue;
        sscanf(buffer, "%d,%d,%d,%d", &value.X, &value.Y, &value.Width, &value.Height);
        return value;
    }
    return defvalue;
}
