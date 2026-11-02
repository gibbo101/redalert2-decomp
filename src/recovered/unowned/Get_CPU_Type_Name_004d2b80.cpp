// char const *__fastcall Get_CPU_Type_Name() (0x004D2B80): the display name of Get_CPU_Type's
// index ("486" ... "Cyrix", the table 0x007D8838), "Unknown" outside 0-8. A separate unit from
// Get_CPU_Type (one translation unit would inline it).
#include "shared/cpu_info.hpp"

// @ref ?Get_CPU_Type@@YAHXZ=004d2a60
// @ref ?unknown_cpu_type_names_7d8838@@3PAPBDA=007d8838
// @ref ??_C@_07PCHH@Unknown?$AA@=007d88cc

extern char const *unknown_cpu_type_names_7d8838[];

char const *__fastcall Get_CPU_Type_Name()
{
    int type = Get_CPU_Type();
    if (type > -1 && type < 9) {
        return unknown_cpu_type_names_7d8838[type];
    }
    return "Unknown";
}
