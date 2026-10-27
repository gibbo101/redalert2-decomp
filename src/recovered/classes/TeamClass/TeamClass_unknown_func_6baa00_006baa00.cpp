// Whether every member has its +0x32D flag set.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"

bool TeamClass::unknown_func_6baa00()
{
    bool all = true;
    for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
        if (!member->unknown_32d) {
            all = false;
            break;
        }
    }
    return all;
}
