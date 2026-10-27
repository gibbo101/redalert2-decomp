// HRESULT __fastcall Audio_Queue_Error(AudioQueue *queue) -- 0x00409010
// Purpose: the queue's last transfer error.
#include "shared/audio.hpp"

HRESULT __fastcall Audio_Queue_Error(AudioQueue *queue)
{
    return queue->Error;
}
