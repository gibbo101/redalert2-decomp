// char *Unknown_00737ad0(char *buffer, int size) (0x00737AD0)
// TS winstub.cpp Build_Number_String: the build number (0x007D8900) as decimal text in buffer;
// size is not read.
#include "shared/win_stub.hpp"
#include "shared/crt_string.hpp"

extern int unknown_build_number_7d8900;         // 0x007D8900 the build number (39)
// @ref ?unknown_build_number_7d8900@@3HA=007d8900
// @ref _sprintf=007820f4
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc

char *__fastcall Unknown_00737ad0(char *buffer, int size)
{
    sprintf(buffer, "%d", unknown_build_number_7d8900);
    return buffer;
}
