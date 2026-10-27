// int __fastcall Audio_Queue_Stdio(AudioQueue *queue, void *file, int bytes, int *done) -- 0x00408F50
// Purpose: Audio_Queue_File for a C stdio file (fread/fwrite).
// @ref _fread=007826bc
// @ref _fwrite=007827d3
#include "shared/audio.hpp"

extern "C" unsigned int __cdecl fread(void *buffer, unsigned int size, unsigned int count, void *file);
extern "C" unsigned int __cdecl fwrite(void const *buffer, unsigned int size, unsigned int count, void *file);

int __fastcall Audio_Queue_Stdio(AudioQueue *queue, void *file, int bytes, int *done)
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
            moved = fwrite(queue->Pointer, 1, count, file);
            if (moved < 0) {
                queue->Error = 0x80040000;
            }
        } else {
            moved = fread(queue->Pointer, 1, count, file);
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
