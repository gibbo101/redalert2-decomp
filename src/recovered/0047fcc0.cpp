// 0x0047FCC0: return the original signed constant -15 and pop the three coordinate words.
// The original body does not read its inputs. Global stdcall and CoordStruct-by-value
// are compatible source spellings; the original owner is not uniquely identified.
#include "shared/coord.hpp"

int __stdcall Unknown_0047FCC0(CoordStruct position)
{
    return -15;
}
