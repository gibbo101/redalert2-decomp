#define RA2_DIR_MISSILE_MEMBERS
#include "shared/dir_type.hpp"
#include "shared/crt_memory.hpp"
#pragma intrinsic(abs)

bool DirType::Is_Complete_Turn(DirType const &towards, DirType const &by)
{
    DirType difference(*this - towards);
    if (abs(by.Facing) >= abs(difference.Facing)) {
        return true;
    }
    return false;
}
