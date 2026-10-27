// int __fastcall unknown_decoder_reset_6d0(UnknownDecoderState_77870 *state) -- 0x00777870
// Purpose: sets the word at +0x6D0 of the decoder state to -1 and returns -1.
// Assumptions: the decoder state of 0x0077BE70; meaning unknown.

struct UnknownDecoderState_77870 {
    char unknown_000[0x6D0];
    int unknown_6d0;                        // +0x6D0
};

int __fastcall unknown_decoder_reset_6d0(UnknownDecoderState_77870 *state)
{
    return state->unknown_6d0 = -1;
}
