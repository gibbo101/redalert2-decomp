// void __fastcall Audio_Pool_Free(AudioPool *pool, void *data) -- 0x00407460
// Purpose: puts a block (given by its data) back on the pool's free list.
#include "shared/audio.hpp"

void __fastcall Audio_Pool_Free(AudioPool *pool, void *data)
{
    AudioPoolBlock *block = (AudioPoolBlock *)data - 1;
    block->Next = pool->Free;
    pool->Free = block;
}
