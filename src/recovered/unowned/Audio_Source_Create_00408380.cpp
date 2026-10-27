// AudioSource *__fastcall Audio_Source_Create(int size) -- 0x00408380
// Purpose: makes a zero-filled source owning a data buffer of size bytes.
// Returns 0 (freeing the source) when the buffer cannot be allocated.
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

AudioSource *__fastcall Audio_Source_Create(int size)
{
    AudioSource *source = (AudioSource *)operator new(sizeof(AudioSource));
    memset(source, 0, sizeof(AudioSource));
    source->unknown_00 = 0;
    source->unknown_04 = 0;
    source->Format = 0;
    source->unknown_18 = 0;
    Audio_List_Init(&source->Pieces);
    source->unknown_04 = size;
    source->unknown_00 = (int)operator new(size);
    if (source->unknown_00 == 0) {
        if (source != 0) {
            operator delete(source);
        }
        return 0;
    }
    return source;
}
