#include "shared/coord.hpp"
// Returned-reference identity is an ABI hypothesis: original EAX=this, ret12.
CoordStruct &CoordStruct::Set_00434820(int x, int y, int z)
{
    X = x;
    Y = y;
    Z = z;
    return *this;
}
