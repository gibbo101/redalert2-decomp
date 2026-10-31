// void TeamClass::unknown_func_6bd990(int value) (0x006BD990): stores value in every member (+0xD8).
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"

void TeamClass::unknown_func_6bd990(int value)
{
    for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
        member->unknown_d8 = value;
    }
}
