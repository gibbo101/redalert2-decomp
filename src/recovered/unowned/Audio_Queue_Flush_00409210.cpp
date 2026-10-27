// HRESULT __fastcall Audio_Queue_Flush(AudioQueue *queue) -- 0x00409210
// Purpose: updates the queue (0x004090E0) with a zero limit, then once more
// limited to its ready count when that is non-zero. Returns 0x80040000.
// @ref ?Audio_Queue_Update@@YIHPAUAudioQueue@@H@Z=004090e0
#include "shared/audio.hpp"

HRESULT __fastcall Audio_Queue_Flush(AudioQueue *queue)
{
    Audio_Queue_Update(queue, 0);
    if (queue->Available != 0) {
        Audio_Queue_Update(queue, queue->Available);
    }
    return 0x80040000;
}
