// void __fastcall AudioSourceInfo::Init(void *data, int size) -- 0x00408500
// Purpose: makes the piece an unlinked piece of size bytes at data.
#include "shared/audio.hpp"

void __fastcall AudioSourceInfo::Init(void *data, int size)
{
    unknown_10 = size;
    unknown_0c = (int)data;
    Audio_List_Init_Node(this);
    Source = 0;
}
