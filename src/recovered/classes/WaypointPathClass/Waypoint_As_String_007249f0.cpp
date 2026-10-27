// Waypoint As String (0x7249F0)
#include "shared/waypoint_path.hpp"
// @ref _?name@?1??Waypoint_As_String@@YIPBDH@Z@4PADA=00b255d0
// @ref ??_C@_02JBML@?$CFc?$AA@=007fb49c
// @ref ??_C@_04LKNH@?$CFc?$CFc?$AA@=007fb494

char const *__fastcall Waypoint_As_String(int index)
{
    static char name[8];
    if (index == -1) {
        name[0] = '\0';
        return name;
    }
    if (index < 26) {
        wsprintfA(name, "%c", index + 'A');
        return name;
    }
    wsprintfA(name, "%c%c", index / 26 + '@', index % 26 + 'A');
    return name;
}

