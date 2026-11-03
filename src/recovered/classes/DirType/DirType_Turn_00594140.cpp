#define RA2_DIR_MISSILE_MEMBERS
#include "shared/dir_type.hpp"
#include "shared/crt_memory.hpp"
#pragma intrinsic(abs)

bool DirType::Turn(DirType const &towards, DirType const &by)
{
    if (Is_Complete_Turn(towards, by)) {
        Facing = towards.Facing;
        return true;
    }
    DirType difference(towards - *this);
    if (difference.Facing < 0) {
        *this -= by;
    } else {
        *this += by;
    }
    return false;
}
