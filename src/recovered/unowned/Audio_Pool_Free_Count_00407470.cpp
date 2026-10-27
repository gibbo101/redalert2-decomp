// int __fastcall Audio_Pool_Free_Count(AudioPool *pool) -- 0x00407470
// Purpose: the number of free blocks in the pool.
#include "shared/audio.hpp"

int __fastcall Audio_Pool_Free_Count(AudioPool *pool)
{
    int count = 0;
    for (AudioPoolBlock *block = pool->Free; block != 0; block = block->Next) {
        count++;
    }
    return count;
}
