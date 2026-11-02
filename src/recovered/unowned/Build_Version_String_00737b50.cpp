#include "shared/crt_string.hpp"
extern "C" char *__cdecl strchr(char const *, int);
extern int unknown_build_number_7d8900;
extern "C" char s_gsmallwoo_007d8904[];
// @ref ?unknown_build_number_7d8900@@3HA=007d8900
// @ref _s_gsmallwoo_007d8904=007d8904
// @ref _sprintf=007820f4
// @ref _strchr=00784130
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_05BAJN@?$CFs?9?$CFs?$AA@=007fd1b8
char *__fastcall Build_Version_String_00737b50(char *buffer, int length)
{
    char number[128];
    char initials[128];
    sprintf(number, "%d", unknown_build_number_7d8900);
    initials[0] = s_gsmallwoo_007d8904[0];
    initials[1] = 0;
    initials[2] = 0;
    char const *separator = strchr(s_gsmallwoo_007d8904, '_');
    if (separator)
        initials[1] = separator[1];
    sprintf(buffer, "%s-%s", initials, number);
    return buffer;
}
