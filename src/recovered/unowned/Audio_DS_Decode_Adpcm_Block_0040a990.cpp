// int __fastcall Audio_DS_Decode_Adpcm_Block(AudioChannelBuffer *record) -- 0x0040A990
// Purpose: decodes one IMA ADPCM block from the input buffer into the
// output buffer. Each channel's 4-byte header (sample, step index, zero)
// seeds its decoder state and is the first output sample; the rest are
// 4-byte groups of eight nibbles, low nibble first, interleaved by channel
// for stereo. +0x94 counts the output bytes. Returns 1 when the block
// was consumed exactly, 0 for a short block or a bad header.
// @ref ?Audio_Adpcm_Decode@@YIFEPAUAudioAdpcmState@@@Z=0040abf0
#include "shared/audio.hpp"

int __fastcall Audio_DS_Decode_Adpcm_Block(AudioChannelBuffer *record)
{
    short *output = (short *)record->Output;
    int remaining = record->unknown_80 - record->unknown_84;
    unsigned char const *input = (unsigned char const *)record->Input;
    record->unknown_94 = 0;
    if (remaining < record->DecodeChannels * 4) {
        return 0;
    }
    for (int channel = 0; channel < record->DecodeChannels; channel++) {
        AudioAdpcmState *state = &record->Adpcm[channel];
        state->Sample = input[0] + (input[1] << 8);
        if (state->Sample & 0x8000) {
            state->Sample -= 0x10000;
        }
        state->Index = input[2];
        if (state->Index > 88 || input[3] != 0) {
            return 0;
        }
        *output++ = (short)state->Sample;
        input += 4;
        remaining -= 4;
        record->unknown_94 += 2;
    }
    if (record->DecodeChannels == 1) {
        if (remaining > 0) {
            int groups = (unsigned int)(remaining + 3) >> 2;
            remaining -= groups * 4;
            do {
                short *out = (short *)((char *)record->Output + record->unknown_94);
                for (int count = 4; count != 0; count--) {
                    unsigned char code = *input++;
                    *out++ = Audio_Adpcm_Decode(code & 0xf, &record->Adpcm[0]);
                    *out++ = Audio_Adpcm_Decode(code >> 4, &record->Adpcm[0]);
                }
                record->unknown_94 += 0x10;
            } while (--groups != 0);
        }
    } else if (remaining > 0) {
        do {
            for (int channel = 0; channel < record->DecodeChannels; channel++) {
                AudioAdpcmState *state = &record->Adpcm[channel];
                short *out = (short *)((char *)record->Output + record->unknown_94) + channel;
                for (int count = 4; count != 0; count--) {
                    unsigned char code = *input++;
                    *out = Audio_Adpcm_Decode(code & 0xf, state);
                    out += record->DecodeChannels;
                    *out = Audio_Adpcm_Decode(code >> 4, state);
                    out += record->DecodeChannels;
                }
            }
            record->unknown_94 += record->DecodeChannels << 4;
            remaining -= record->DecodeChannels << 2;
        } while (remaining > 0);
    }
    return remaining == 0;
}
