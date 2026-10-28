// bool WolRegistryOptions::unknown_004ff2c0() const (0x004FF2C0)
// Bit 1 of Options is clear (the option the WOL login flow tests before saving the nickname).
// Written as the compiler wants it: the dword is loaded, the byte inverted and shifted.
#include "shared/wol_sink.hpp"

bool WolRegistryOptions::unknown_004ff2c0() const
{
    unsigned int options = Options;
    bool result = ((unsigned char)~options >> 1) & 1;
    return result;
}
