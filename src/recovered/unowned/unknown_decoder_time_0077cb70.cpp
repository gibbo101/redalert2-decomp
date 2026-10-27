// int __fastcall unknown_decoder_time(UnknownDecoderState_77cb70 *state) -- 0x0077CB70
// Purpose: the decoder's base value (+0x148) plus the clock read through its
// callback (+0x50) converted to 1/60ths by the rate at +0x78 (unsigned).
// Assumptions: the decoder state of 0x0077AFA0/0x0077B390; field meanings
// (time base, clock rate) are hypotheses.

struct UnknownDecoderState_77cb70 {
    char unknown_000[0x50];
    int (__cdecl *Clock)(UnknownDecoderState_77cb70 *state);   // +0x50
    char unknown_054[0x78 - 0x54];
    unsigned unknown_78;                // +0x78
    char unknown_07c[0x148 - 0x7C];
    int unknown_148;                    // +0x148
};

int __fastcall unknown_decoder_time(UnknownDecoderState_77cb70 *state)
{
    unsigned ticks = (unsigned)(state->Clock(state) * 60) / state->unknown_78;
    return state->unknown_148 + ticks;
}
