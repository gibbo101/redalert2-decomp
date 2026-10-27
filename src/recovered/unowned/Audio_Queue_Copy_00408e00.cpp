// int __fastcall Audio_Queue_Copy(AudioQueue *queue, void *buffer, int bytes) -- 0x00408E00
// Purpose: moves up to bytes between buffer and the ring through the queue
// (into the ring for the fill side, out of it for the drain side),
// advancing the queue. Returns the bytes moved.
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"

int __fastcall Audio_Queue_Copy(AudioQueue *queue, void *buffer, int bytes)
{
    int moved = 0;
    char *pointer = (char *)buffer;
    Audio_Queue_Update(queue, 0);
    for (;;) {
        int count = queue->Available;
        if (count > bytes) {
            count = bytes;
        }
        if (count == 0) {
            break;
        }
        if (queue->Index != 0) {
            memcpy(pointer, queue->Pointer, count);
        } else {
            memcpy(queue->Pointer, pointer, count);
        }
        Audio_Queue_Update(queue, count);
        pointer += count;
        bytes -= count;
        moved += count;
        if (bytes == 0) {
            break;
        }
    }
    return moved;
}
