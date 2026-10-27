// char const *CenterTeamCommandClass::Get_Name() const -- 0x0051B460
// The command's key name, "TeamCenter_<n>", formatted into the shared name
// buffer (0x00A4149C).
#include "shared/command.hpp"
// @ref _sprintf=007820f4
// @ref ?unknown_command_name_a4149c@@3PADA=00a4149c
// @ref ??_C@_0O@MPKB@TeamCenter_?$CFd?$AA@=007dcaf0

extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);

char const *CenterTeamCommandClass::Get_Name() const
{
    sprintf(unknown_command_name_a4149c, "TeamCenter_%d", TeamNumber);
    return unknown_command_name_a4149c;
}
