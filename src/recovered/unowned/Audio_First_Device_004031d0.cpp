// void __fastcall Audio_First_Device(AudioListCursor *cursor) -- 0x004031D0
// Purpose: start a device walk: cursor->Node = the first device of the audio system. No direct callers (inlined).
#include "shared/audio.hpp"

void __fastcall Audio_First_Device(AudioListCursor *cursor)
{
    cursor->Node = Audio_List_First(&Audio_System_Instance->Devices);
}
