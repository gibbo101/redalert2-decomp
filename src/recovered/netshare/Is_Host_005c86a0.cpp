// int Is_Host_005c86a0() (0x005C86A0)
#include "shared/lobby.hpp"

int Is_Host_005c86a0()
{
    wchar_t *name = Unknown_006FA180(unknown_name_a3d3a0);
    return Compare_Wide_007837d3(name, unknown_host_name_a3f618) == 0;
}
