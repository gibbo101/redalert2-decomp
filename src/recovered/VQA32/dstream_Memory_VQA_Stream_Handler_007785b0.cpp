// int __cdecl Memory_VQA_Stream_Handler(VQAHandle *vqa, int action, int buffer, int nbytes) -- 0x007785B0
// Purpose: the stream handler for a movie held in memory (the loop cache):
// reads copy from LoopCache.Ptr at Offset, seeks move Offset.
#include "shared/vqa_player.hpp"
#include "shared/crt_memory.hpp"

int __cdecl Memory_VQA_Stream_Handler(VQAHandle *vqa, int action, int buffer, int nbytes)
{
    int error = 0;
    int p;
    int bytes;
    VQAHandleP *vqap = (VQAHandleP *)vqa;
    VQALoopCache *cache = &vqap->LoopCache;

    switch (action) {
    case VQACMD_OPEN:
        error = 0;
        break;

    case VQACMD_READ:
        bytes = cache->Bytes;
        p = cache->Offset;
        if (p + nbytes <= bytes) {
            memcpy((void *)buffer, &cache->Ptr[p], nbytes);
            cache->Offset += nbytes;
            error = 0;
            break;
        }
        error = 1;
        break;

    case VQACMD_SEEK:
    case VQACMD_SEEKPEEK:
        switch (buffer) {
        case 1:
            cache->Offset += nbytes;
            error = 0;
            break;

        case 0:
            p = (int)cache->Buffer;
            if (nbytes >= p) {
                cache->Offset = nbytes - p;
                break;
            }

        default:
            error = 1;
            break;
        }
        break;

    case VQACMD_SIZE:
        error = 0;
        break;

    case VQACMD_CLOSE:
        error = 0;
        break;

    case VQACMD_INIT:
    case VQACMD_CLEANUP:
        error = 0;
        break;

    case VQACMD_WRITE:
        error = 1;
        break;

    default:
        break;
    }

    return error;
}
