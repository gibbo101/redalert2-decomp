// AudioStreamPlayer *__fastcall Audio_Stream_Create(AudioDevice *device, __int64 buffer_time) -- 0x00407790
// Purpose: makes a stream on the device buffering buffer_time milliseconds
// (at least 7000): a zero-filled player named "Audio Stream" with its own
// channel (0x004036C0, 0x1000) whose callbacks feed it from the ring
// (0x00408710). Links it into the stream list and returns it, or returns 0
// without a device, channel or ring.
// @ref ??_C@_0N@KBAM@Audio?5Stream?$AA@=007ccd8c
#include "shared/crt_string.hpp"
#include "shared/audio.hpp"

void *__cdecl operator new(unsigned int size);

AudioStreamPlayer *__fastcall Audio_Stream_Create(AudioDevice *device, __int64 buffer_time)
{
    if (device == 0) {
        return 0;
    }
    if ((unsigned __int64)buffer_time <= 0 || (unsigned __int64)buffer_time < 7000) {
        buffer_time = 7000;
    }
    AudioStreamPlayer *stream = (AudioStreamPlayer *)operator new(sizeof(AudioStreamPlayer));
    memset(stream, 0, sizeof(AudioStreamPlayer));
    Audio_List_Init_Node(stream);
    stream->unknown_10 = (int)device;
    stream->Channel = Audio_Device_Create_Channel(device, 0x1000);
    stream->Channel->unknown_levels_94 = 0;
    stream->Channel->unknown_levels_90 = 0;
    stream->Channel->unknown_levels_98 = 0;
    stream->Channel->unknown_levels_9c = 0;
    stream->BufferTime = buffer_time;
    Audio_Source_Reset(&stream->Source);
    Audio_Format_Init(&stream->Format);
    stream->PauseCount = 0;
    stream->HoldCount = 0;
    strcpy(stream->Name, "Audio Stream");
    AudioStream *ring;
    if (stream->Channel == 0) {
        goto fail;
    }
    stream->Channel->Owner = stream;
    stream->Channel->unknown_next_b0 = Audio_Stream_Next_Block;
    stream->Channel->unknown_done_b8 = Audio_Stream_Channel_Done;
    stream->Channel->unknown_end_callback_bc = Audio_Stream_Channel_End;
    ring = Audio_Ring_Create();
    stream->Ring = ring;
    if (ring == 0) {
fail:
        Audio_Stream_Destroy(stream);
        return 0;
    }
    EnterCriticalSection(&Audio_Stream_Lock);
    Audio_List_Add_Head(&Audio_Stream_List, stream);
    LeaveCriticalSection(&Audio_Stream_Lock);
    return stream;
}
