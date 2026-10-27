#include "shared/coord.hpp"
// Matches X/Y only; Z intentionally unread as in the original.
int CoordStruct::Equal_XY_004bfb60(CoordStruct const &other) const
{
    if (X==other.X && Y==other.Y) return 1;
    return 0;
}
