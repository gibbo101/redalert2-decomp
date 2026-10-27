// int __fastcall Audio_DS_Decode_Blocks(AudioChannelBuffer *record, void *destination, int *destination_size,
//                                       void const *source, int *source_size) -- 0x00409D00
// Purpose: the block decoder: a state machine that gathers BlockSize
// source bytes into the input block, decodes it (the record's block
// function, +0xB0) into the output block and copies the decoded bytes to
// destination, until the source or the destination space runs out. Both
// sizes are updated to the bytes consumed and produced. Returns 1, or 0
// without work buffers or when a block fails to decode.
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"

int __fastcall Audio_DS_Decode_Blocks(AudioChannelBuffer *record, void *destination, int *destination_size,
                                      void const *source, int *source_size)
{
    int source_left = 0;
    int destination_left = 0;
    int consumed = 0;
    int produced = 0;
    if (record->Output == 0 || record->Input == 0) {
        return 0;
    }
    if (source_size != 0) {
        source_left = *source_size;
    }
    if (destination_size != 0) {
        destination_left = *destination_size;
    }
    char const *from = (char const *)source;
    for (;;) {
        int count;
        switch (record->DecodeState) {
        case AUDIO_DECODE_READ:
            if (record->unknown_84 == 0 || from == 0) {
                record->unknown_84 = 0;
                record->DecodeState = record->NextDecodeState;
                break;
            }
            count = record->unknown_84;
            if (count > source_left) {
                count = source_left;
            }
            if (count == 0) {
                goto done;
            }
            memcpy((char *)record->Input + record->unknown_80 - record->unknown_84, from, count);
            from += count;
            consumed += count;
            source_left -= count;
            record->unknown_84 -= count;
            record->unknown_a8 = 1;
            break;
        case AUDIO_DECODE_WRITE:
            if (record->unknown_98 == 0) {
                record->unknown_a8 = 0;
                record->DecodeState = record->NextDecodeState;
                break;
            }
            count = record->unknown_98;
            if (count > destination_left) {
                count = destination_left;
            }
            if (count == 0) {
                goto done;
            }
            memcpy(destination, (char *)record->Output + record->unknown_94 - record->unknown_98, count);
            destination = (char *)destination + count;
            produced += count;
            destination_left -= count;
            record->unknown_98 -= count;
            break;
        case AUDIO_DECODE_BLOCK:
            if (!record->Decode_Block(record)) {
                return 0;
            }
            record->DecodeState = AUDIO_DECODE_WRITE;
            record->unknown_98 = record->unknown_94;
            record->NextDecodeState = AUDIO_DECODE_START;
            break;
        case AUDIO_DECODE_START:
            if (from == 0) {
                goto done;
            }
            record->DecodeState = AUDIO_DECODE_READ;
            record->unknown_80 = record->BlockSize;
            record->unknown_84 = record->BlockSize;
            record->NextDecodeState = AUDIO_DECODE_BLOCK;
            break;
        }
    }
done:
    if (source_size != 0) {
        *source_size = consumed;
    }
    if (destination_size != 0) {
        *destination_size = produced;
    }
    return 1;
}
