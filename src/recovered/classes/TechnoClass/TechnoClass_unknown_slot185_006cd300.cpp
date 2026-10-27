// bool TechnoClass::unknown_slot185() (0x006CD300, slot 185)
#include "shared/techno.hpp"
#include "shared/foot.hpp"

bool TechnoClass::unknown_slot185()
{
    if (this != 0) {
        if (Kind_Of() != 1) {
            return true;
        }
        FootClass *foot = (FootClass *)this;
        if ((foot->unknown_574 >= 0 && foot->unknown_slot284()) || unknown_slot201()) {
            return false;
        }
    }
    return true;
}
