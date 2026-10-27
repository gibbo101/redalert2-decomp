// int __fastcall Audio_Copy_Block(AudioChannelBuffer *record, void *destination, int *destination_size,
//                                 void const *source, int *source_size) -- 0x00409CB0
// Purpose: the PCM decoder: copies the smaller of the two sizes from
// source to destination and stores that count into both sizes (nothing
// when it is 0). Always returns 1. The record is not used.
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"

int __fastcall Audio_Copy_Block(AudioChannelBuffer *record, void *destination, int *destination_size,
                                void const *source, int *source_size)
{
    int count = *destination_size;
    if (count > *source_size) {
        count = *source_size;
    }
    if (count != 0) {
        memcpy(destination, source, count);
        *destination_size = count;
        *source_size = count;
    }
    return 1;
}
