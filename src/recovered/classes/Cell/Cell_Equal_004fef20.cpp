#include "shared/coord.hpp"
// Original tests X before Y and returns a full 32-bit zero or one.
// Cell has the evidenced two-short layout; the public TPoint base spelling remains qualified.
int Cell::Equal_004fef20(Cell const &other) const
{
    if (X==other.X && Y==other.Y) return 1;
    return 0;
}
