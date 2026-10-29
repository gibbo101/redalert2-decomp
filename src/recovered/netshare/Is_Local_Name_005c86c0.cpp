// int __fastcall Is_Local_Name_005c86c0(wchar_t const *name) (0x005C86C0)
#include "shared/lobby.hpp"

int __fastcall Is_Local_Name_005c86c0(wchar_t const *name)
{
    return Compare_Wide_007837d3(name, Unknown_006FA180(unknown_name_a3d3a0)) == 0;
}
