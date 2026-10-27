// int __fastcall Audio_Queue_File(AudioQueue *queue, FileClass *file, int bytes, int *done) -- 0x00408EA0
// Purpose: moves up to bytes between file and the ring through the queue
// (reading the file for the fill side, writing it for the drain side),
// adding the bytes moved to *done. Returns 1 when all moved or the queue
// has no room, 2 at the end of the file, 0 on an error (a negative result
// also sets the queue's error).
#include "shared/raw_file_class.hpp"
#include "shared/audio.hpp"

int __fastcall Audio_Queue_File(AudioQueue *queue, FileClass *file, int bytes, int *done)
{
    int ignored;
    Audio_Queue_Update(queue, 0);
    if (done == 0) {
        done = &ignored;
    }
    *done = 0;
    for (;;) {
        int count = queue->Available;
        if (count > bytes) {
            count = bytes;
        }
        if (count == 0) {
            return 1;
        }
        int moved;
        if (queue->Index != 0) {
            moved = file->Write(queue->Pointer, count);
            if (moved < 0) {
                queue->Error = 0x80040000;
            }
        } else {
            moved = file->Read(queue->Pointer, count);
            if (moved < 0) {
                queue->Error = 0x80040000;
            }
        }
        if (moved == 0) {
            return 2;
        }
        if (moved == -1) {
            return 0;
        }
        Audio_Queue_Update(queue, moved);
        bytes -= moved;
        *done += moved;
        if (bytes == 0) {
            return 1;
        }
    }
}
