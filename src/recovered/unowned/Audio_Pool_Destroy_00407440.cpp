// void __fastcall Audio_Pool_Destroy(AudioPool *pool) -- 0x00407440
// Purpose: frees a pool made by Audio_Pool_Create.
#include "shared/audio.hpp"

void __cdecl operator delete(void *block);

void __fastcall Audio_Pool_Destroy(AudioPool *pool)
{
    operator delete(pool);
}
