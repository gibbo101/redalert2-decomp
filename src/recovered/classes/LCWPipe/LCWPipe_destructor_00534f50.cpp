// LCWPipe::~LCWPipe() (0x00534F50)
// Releases both block buffers.
#include "shared/lcw_pipe.hpp"

LCWPipe::~LCWPipe()
{
    delete [] Buffer;
    Buffer = 0;

    delete [] Buffer2;
    Buffer2 = 0;
}
