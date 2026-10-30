// INIClass::Get_UUID (0x0050DA00)
// Reads a class ID written by Put_UUID ("{...}"): the text is widened and
// parsed with CLSIDFromString; defvalue when the entry is missing or empty or
// the text does not parse.
#include "shared/ini_class.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/com_api.hpp"
#include "shared/win32_api.hpp"
// @ref __imp__MultiByteToWideChar@24=0079a1b8
// @ref __imp__CLSIDFromString@8=0079a5e4

WIN32_IMPORT HRESULT __stdcall CLSIDFromString(unsigned short *text, GUID *clsid);

GUID INIClass::Get_UUID(char const *section, char const *entry, GUID defvalue) const
{
    char buffer[128];

    if (Get_String(section, entry, unknown_string_83c55c, buffer, sizeof(buffer))) {
        unsigned short wide[128];
        GUID value;

        MultiByteToWideChar(0, 1, buffer, -1, wide, 128);
        if (SUCCEEDED(CLSIDFromString(wide, &value))) {
            return value;
        }
    }
    return defvalue;
}
