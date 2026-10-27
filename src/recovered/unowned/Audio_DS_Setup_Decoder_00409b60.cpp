// void __fastcall Audio_DS_Setup_Decoder(AudioChannelBuffer *record) -- 0x00409B60
// Purpose: prepares the buffer record's decoder for its channel's source
// format (the device default when the source has none): PCM copies
// (0x00409CB0); IMA ADPCM (type 1) runs the block decoder 0x00409D00 with
// 0x0040A990 and needs a block-sized input buffer and a 4 * block + 0x80
// output buffer; type 2 runs 0x00409D00 alone. Grows the two work buffers
// (+0x7C and +0x90) when they are too small; a failed allocation leaves
// the capacity 0. Does nothing without a source.
// @ref _free=007825e8
// @ref _malloc=00782630
// @ref ?Audio_DS_Decode_Adpcm_Block@@YIHPAUAudioChannelBuffer@@@Z=0040a990
// @ref ?Audio_Copy_Block@@YIHPAUAudioChannelBuffer@@PAXPAHPBX2@Z=00409cb0
// @ref ?Audio_DS_Decode_Blocks@@YIHPAUAudioChannelBuffer@@PAXPAHPBX2@Z=00409d00
#include "shared/audio.hpp"

extern "C" void __cdecl free(void *block);
extern "C" void *__cdecl malloc(unsigned int size);

void __fastcall Audio_DS_Setup_Decoder(AudioChannelBuffer *record)
{
    AudioSource *source = record->Channel->Source;
    if (source == 0) {
        return;
    }
    AudioFormat *format = source->Format;
    if (format == 0) {
        format = &record->Channel->Device->DefaultFormat;
    }
    record->unknown_98 = 0;
    record->unknown_84 = 0;
    record->unknown_80 = 0;
    record->DecodeState = 3;
    record->InputNeeded = 0;
    record->OutputNeeded = 0;
    record->DecodeChannels = format->Channels;
    record->unknown_a8 = 0;
    switch (format->Type) {
    case AUDIO_FORMAT_PCM:
        record->Decode = Audio_Copy_Block;
        break;
    case AUDIO_FORMAT_IMA_ADPCM:
        record->Decode = Audio_DS_Decode_Blocks;
        record->Decode_Block = Audio_DS_Decode_Adpcm_Block;
        record->InputNeeded = format->BlockSize;
        record->BlockSize = format->BlockSize;
        record->OutputNeeded = format->BlockSize * 4 + 0x80;
        break;
    case 2:
        record->Decode = Audio_DS_Decode_Blocks;
        break;
    }
    if (record->InputCapacity < record->InputNeeded) {
        if (record->Input != 0) {
            free(record->Input);
        }
        record->Input = malloc(record->InputNeeded);
        if (record->Input == 0) {
            record->InputCapacity = 0;
        } else {
            record->InputCapacity = record->InputNeeded;
        }
    }
    if (record->OutputCapacity < record->OutputNeeded) {
        if (record->Output != 0) {
            free(record->Output);
        }
        record->Output = malloc(record->OutputNeeded);
        if (record->Output == 0) {
            record->OutputCapacity = 0;
        } else {
            record->OutputCapacity = record->OutputNeeded;
        }
    }
}
