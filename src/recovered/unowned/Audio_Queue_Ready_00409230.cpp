// int __fastcall Audio_Queue_Ready(AudioQueue *queue) -- 0x00409230
// Purpose: updates the queue (0x004090E0) with a zero limit and returns
// its ready count.
// @ref ?Audio_Queue_Update@@YIHPAUAudioQueue@@H@Z=004090e0
#include "shared/audio.hpp"

int __fastcall Audio_Queue_Ready(AudioQueue *queue)
{
    Audio_Queue_Update(queue, 0);
    return queue->Available;
}
