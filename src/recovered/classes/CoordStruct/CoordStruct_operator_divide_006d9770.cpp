// CoordStruct CoordStruct::operator/(int divisor) const (0x006D9770)
// Member-wise quotient; a zero divisor gives (0, 0, 0).
#include "shared/techno.hpp"

CoordStruct CoordStruct::operator/(int divisor) const
{
    if (divisor == 0) {
        return CoordStruct(0, 0, 0);
    }
    return CoordStruct(X / divisor, Y / divisor, Z / divisor);
}
