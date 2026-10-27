// LZOPipe::~LZOPipe() (0x0053EBA0)
// Releases both block buffers.
#include "shared/lzo_pipe.hpp"

LZOPipe::~LZOPipe()
{
    delete [] Buffer;
    Buffer = 0;

    delete [] Buffer2;
    Buffer2 = 0;
}
