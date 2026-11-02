// bool WolRegistryOptions::unknown_004ff2d0() const (0x004FF2D0)
// Bit 2 of Options is clear (same form as 0x004FF2C0).
#include "shared/wol_sink.hpp"

bool WolRegistryOptions::unknown_004ff2d0() const
{
    unsigned int options = Options;
    bool result = ((unsigned char)~options >> 2) & 1;
    return result;
}
