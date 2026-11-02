// int __fastcall Hotkey_To_Key(int hotkey) (0x005D87D0)
// A hot key control value as a key number: the virtual key with the Alt, Ctrl and Shift
// bits; an extended key gives 0. First source of Options.CPP: its keyboard dialog expands
// the IndexClass and vector accessors inline (the defines must precede the first include).
#define INDEX_DECLARE_FETCH_ID_BY_POSITION
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/options.hpp"

int __fastcall Hotkey_To_Key(int hotkey)
{
    int key = hotkey & 0xFF;
    int flags = (hotkey >> 8) & 0xFF;
    if (flags & 4) key |= 0x400;
    if (flags & 2) key |= 0x200;
    if (flags & 1) key |= 0x100;
    if (flags & 8) key = 0;
    return key;
}
