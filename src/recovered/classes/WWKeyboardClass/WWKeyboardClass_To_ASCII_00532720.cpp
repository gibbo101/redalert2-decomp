// char WWKeyboardClass::To_ASCII(KeyNumType key) (0x00532720)
// The character a key produces (ToAscii with the key's own shift, control
// and alt bits in KeyState); 0 for releases and keys without one.
// VK_HOME and VK_END give backspace and backslash.
// The ToAscii buffer is a 10-byte char array (the 12-byte frame).
#include "shared/keyboard.hpp"
// @ref __imp__MapVirtualKeyA@8=0079a3d8
// @ref __imp__ToAscii@20=0079a3a0

extern "C" __declspec(dllimport) unsigned int __stdcall MapVirtualKeyA(unsigned int code, unsigned int type);
extern "C" __declspec(dllimport) int __stdcall ToAscii(unsigned int key, unsigned int scan, unsigned char const *state,
                                                       unsigned short *buffer, unsigned int flags);

char WWKeyboardClass::To_ASCII(KeyNumType key)
{
    if (key & 0x800) {
        return 0;
    }
    if ((key & 0xFF) == 0x24) {
        return 8;
    }
    if ((key & 0xFF) == 0x23) {
        return '\\';
    }

    unsigned short shift = key & 0x100;
    if (shift) {
        KeyState[0x10] = 0x80;
    }
    unsigned short control = key & 0x200;
    if (control) {
        KeyState[0x11] = 0x80;
    }
    unsigned short alt = key & 0x400;
    if (alt) {
        KeyState[0x12] = 0x80;
    }

    char buffer[10];
    int scan = MapVirtualKeyA(key, 0);
    int result = ToAscii(key, scan, KeyState, (unsigned short *)buffer, 0);

    if (shift) {
        KeyState[0x10] = 0;
    }
    if (control) {
        KeyState[0x11] = 0;
    }
    if (alt) {
        KeyState[0x12] = 0;
    }
    if (result != 1) {
        return 0;
    }
    return buffer[0];
}
