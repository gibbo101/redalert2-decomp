// Buffer::~Buffer (0x00438410)
// Releases an owned block (Reset, inlined).
#include "shared/buffer.hpp"

Buffer::~Buffer()
{
    Reset();
}
