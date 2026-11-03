#define RA2_DIR_MISSILE_MEMBERS
#include "shared/dir_type.hpp"

DirType DirType::operator/(int divisor) const
{
    return DirType(Facing / divisor);
}
