// LCWStraw::~LCWStraw() (0x00535340)
// Releases both block buffers.
#include "shared/lcw_straw.hpp"

LCWStraw::~LCWStraw()
{
    delete [] Buffer;
    Buffer = 0;

    delete [] Buffer2;
    Buffer2 = 0;
}
