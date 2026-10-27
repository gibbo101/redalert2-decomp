// short __fastcall Audio_Adpcm_Decode(unsigned char code, AudioAdpcmState *state) -- 0x0040ABF0
// Purpose: IMA ADPCM decoding of one 4-bit code: adds the step-scaled
// difference to the predicted sample, clamps it to 16 bits, advances the
// step index (clamped to 0..88) and returns the new sample.
// @ref ?Audio_Adpcm_Index@@3QBHB=007ccfe0
// @ref ?Audio_Adpcm_Steps@@3QBHB=007cd020
#include "shared/audio.hpp"

short __fastcall Audio_Adpcm_Decode(unsigned char code, AudioAdpcmState *state)
{
    int step = Audio_Adpcm_Steps[state->Index];
    int difference = step >> 3;
    if (code & 1) {
        difference += step >> 2;
    }
    if (code & 2) {
        difference += step >> 1;
    }
    if (code & 4) {
        difference += step;
    }
    if (code & 8) {
        difference = -difference;
    }
    state->Sample += difference;
    if (state->Sample > 32767) {
        state->Sample = 32767;
    } else if (state->Sample < -32768) {
        state->Sample = -32768;
    }
    state->Index += Audio_Adpcm_Index[code];
    if (state->Index < 0) {
        state->Index = 0;
    } else if (state->Index > 88) {
        state->Index = 88;
    }
    return (short)state->Sample;
}
