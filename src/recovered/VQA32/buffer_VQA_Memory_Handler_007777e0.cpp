// int __cdecl VQA_Memory_Handler(VQAHandle *vqa, int action, int buffer, int nbytes) -- 0x007777E0
// Purpose: the default memory handler: VQAMEM_ALLOC mallocs, VQAMEM_FREE
// frees, LOCK and UNLOCK return the buffer, action 6 (loop cache budget
// query) stores -1 (no limit) through the buffer.
#include "shared/vqa_player.hpp"
#include "shared/crt_memory.hpp"

int __cdecl VQA_Memory_Handler(VQAHandle *vqa, int action, int buffer, int nbytes)
{
    int result = 0;
    switch (action) {
    case VQAMEM_ALLOC:
        result = (int)malloc(nbytes);
        break;
    case VQAMEM_FREE:
        free((void *)buffer);
        break;
    case VQAMEM_LOCK:
    case VQAMEM_UNLOCK:
        result = buffer;
        break;
    case 6:
        *(int *)buffer = -1;
        break;
    }
    return result;
}
