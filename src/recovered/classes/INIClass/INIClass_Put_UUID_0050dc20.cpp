// INIClass::Put_UUID (0x0050DC20)
// Stores a class ID as its registry text ("{...}"): StringFromCLSID, then
// narrowed with WideCharToMultiByte; the wide text is released with
// SysFreeString.
#include "shared/ini_class.hpp"
#include "shared/com_api.hpp"
#include "shared/win32_api.hpp"
// @ref __imp__StringFromCLSID@8=0079a5e0
// @ref __imp__WideCharToMultiByte@32=0079a23c
// @ref __imp__GetLastError@0=0079a1f4
// @ref __imp__SysFreeString@4=0079a35c

WIN32_IMPORT HRESULT __stdcall StringFromCLSID(GUID const &clsid, unsigned short **text);
WIN32_IMPORT int __stdcall WideCharToMultiByte(unsigned int codepage, unsigned long flags, unsigned short const *wide, int wide_length,
                                              char *narrow, int narrow_length, char const *default_char, int *used_default);
WIN32_IMPORT void __stdcall SysFreeString(unsigned short *string);

bool INIClass::Put_UUID(char const *section, char const *entry, GUID const &value)
{
    unsigned short *wide = 0;
    char buffer[128];

    StringFromCLSID(value, &wide);
    if (!WideCharToMultiByte(0, 0, wide, -1, buffer, sizeof(buffer), 0, 0)) {
        GetLastError();
    }
    SysFreeString(wide);
    return Put_String(section, entry, buffer);
}
