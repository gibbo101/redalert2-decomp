// Whether a foot object is a member of the team.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"

bool TeamClass::unknown_func_6ba8b0(FootClass *object)
{
    for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
        if (member == object) {
            return true;
        }
    }
    return false;
}
