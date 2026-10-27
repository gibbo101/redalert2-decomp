// int __fastcall unknown_decoder_field_714(UnknownDecoderState_77c7c0 const *state) -- 0x0077C7C0
// Purpose: the 16-bit value at +0x714 of the decoder state.
// Assumptions: the decoder state of 0x0077BE70; meaning unknown.

struct UnknownDecoderState_77c7c0 {
    char unknown_000[0x714];
    unsigned short unknown_714;             // +0x714
};

int __fastcall unknown_decoder_field_714(UnknownDecoderState_77c7c0 const *state)
{
    return state->unknown_714;
}
