// void *__fastcall Audio_Pool_Alloc(AudioPool *pool) -- 0x00407450
// Purpose: takes a block off the pool's free list and returns its data, or
// 0 when the pool is exhausted.
#include "shared/audio.hpp"

void *__fastcall Audio_Pool_Alloc(AudioPool *pool)
{
    AudioPoolBlock *block = pool->Free;
    if (block == 0) {
        return 0;
    }
    pool->Free = block->Next;
    return block + 1;
}
