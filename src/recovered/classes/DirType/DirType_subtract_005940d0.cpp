#define RA2_DIR_MISSILE_MEMBERS
#include "shared/dir_type.hpp"

DirType DirType::operator-(DirType const &other) const
{
    return DirType(Facing - other.Facing);
}
