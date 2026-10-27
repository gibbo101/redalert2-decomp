// LZOStraw::~LZOStraw() (0x0053F010)
// Releases both block buffers.
#include "shared/lzo_straw.hpp"

LZOStraw::~LZOStraw()
{
    delete [] Buffer;
    Buffer = 0;

    delete [] Buffer2;
    Buffer2 = 0;
}
