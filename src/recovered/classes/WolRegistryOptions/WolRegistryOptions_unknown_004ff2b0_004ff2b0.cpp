// bool WolRegistryOptions::unknown_004ff2b0() const (0x004FF2B0)
// Bit 0 of Options is clear (same form as 0x004FF2C0: the dword loaded, the byte inverted).
#include "shared/wol_sink.hpp"

bool WolRegistryOptions::unknown_004ff2b0() const
{
    unsigned int options = Options;
    bool result = (unsigned char)~options & 1;
    return result;
}
