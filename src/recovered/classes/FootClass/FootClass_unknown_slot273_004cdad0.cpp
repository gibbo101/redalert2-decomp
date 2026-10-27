// CoordStruct FootClass::unknown_slot273() (0x004CDAD0)
// The coordinate of the pending order's object (+0x4B8, else +0x4BC), or
// (-1, -1, -1).
#include "shared/foot.hpp"

CoordStruct FootClass::unknown_slot273()
{
    if (unknown_4b8 != 0) {
        return unknown_4b8->Center_Coord();
    }
    if (unknown_4bc != 0) {
        return unknown_4bc->Center_Coord();
    }
    return CoordStruct(-1, -1, -1);
}
