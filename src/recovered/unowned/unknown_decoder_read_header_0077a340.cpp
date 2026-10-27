// int __fastcall unknown_decoder_read_header(UnknownDecoderState_77a340 *state, int length) -- 0x0077A340
// Purpose: has the input callback (+0x40, event 5) fill the area at
// +0x112 with `length` bytes rounded up to even; -4 when the callback
// fails, else -1.
// Assumptions: the state is the decoder state of 0x0077BE70; event and
// result meanings are hypotheses.

struct UnknownDecoderState_77a340;
typedef int (*UnknownDecoderCallback_77a340)(UnknownDecoderState_77a340 *state, int event, void *data, int size);
struct UnknownDecoderState_77a340 {
    char unknown_000[0x40];
    UnknownDecoderCallback_77a340 Callback40;   // +0x40
    char unknown_044[0x112 - 0x44];
    char unknown_112[1];                        // +0x112
};

int __fastcall unknown_decoder_read_header(UnknownDecoderState_77a340 *state, int length)
{
    return state->Callback40(state, 5, state->unknown_112, (length + 1) & ~1) != 0 ? -4 : -1;
}
