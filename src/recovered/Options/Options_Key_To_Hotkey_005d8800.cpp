// unsigned short __fastcall Key_To_Hotkey(unsigned short key) (0x005D8800)
// A key number as a hot key control value (HOTKEYF_ALT, CONTROL and SHIFT in the high
// byte, HOTKEYF_EXT for the 0x1000 bit).
#include "shared/options.hpp"

unsigned short __fastcall Key_To_Hotkey(unsigned short key)
{
    unsigned int flags = 0;
    if (key & 0x400) flags = 4;
    if (key & 0x200) flags |= 2;
    if (key & 0x100) flags |= 1;
    if (key & 0x1000) flags |= 8;
    return (flags << 8) | (key & 0xFF);
}
