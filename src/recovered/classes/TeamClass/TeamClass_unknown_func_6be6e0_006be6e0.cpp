// Whether any member has unlimited ammo or still has some.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/techno_type.hpp"

bool TeamClass::unknown_func_6be6e0()
{
    bool result = false;
    for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
        if (member->unknown_slot32()->Ammo <= 0 || member->unknown_254 > 0) {
            result = true;
            break;
        }
    }
    return result;
}
