// AudioPool *__fastcall Audio_Pool_Create(unsigned int count, int size) -- 0x00407400
// Purpose: allocates a pool of count blocks of size bytes (each behind an
// 8-byte link) and chains them all into its free list. Returns 0 when the
// allocation fails.
#include "shared/audio.hpp"

void *__cdecl operator new(unsigned int size);

AudioPool *__fastcall Audio_Pool_Create(unsigned int count, int size)
{
    AudioPool *pool = (AudioPool *)operator new((size + 8) * count + 8);
    if (pool != 0) {
        AudioPoolBlock *block = (AudioPoolBlock *)(pool + 1);
        pool->Free = block;
        for (unsigned int left = count - 1; left > 0; left--) {
            AudioPoolBlock *next = (AudioPoolBlock *)(size + 8 + (char *)block);
            block->Next = next;
            block = next;
        }
        block->Next = 0;
    }
    return pool;
}
