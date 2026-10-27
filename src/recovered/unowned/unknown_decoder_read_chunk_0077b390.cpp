// int __fastcall unknown_decoder_read_chunk(UnknownDecoderState_77b390 *state, unsigned length) -- 0x0077B390
// Purpose: reads a chunk of `length` bytes (rounded up to even) through the
// decoder's input callback (+0x40). Without the buffering flag (+0x84 bit 0)
// or a buffer (+0x78C) the chunk is skipped (event 7). A chunk larger than
// the limit (+0x7B4) is read whole into +0x78C once, marking one byte per
// frame-sized (+0x9C) piece in +0x794; otherwise it is read into +0x7A8 and
// its length kept in +0x7B0. -4 when a read fails, -6 when a skip fails,
// else -1.
// Assumptions: the decoder state of 0x0077AFA0; field meanings are
// hypotheses.

struct UnknownDecoderState_77b390 {
    char unknown_000[0x40];
    int (*Callback)(UnknownDecoderState_77b390 *state, int code, void *buffer, unsigned size);  // +0x40
    char unknown_044[0x84 - 0x44];
    unsigned char unknown_84;           // +0x84
    char unknown_085[0x9C - 0x85];
    unsigned unknown_9c;                // +0x9C
    char unknown_0a0[0x78C - 0xA0];
    void *unknown_78c;                  // +0x78C
    unsigned unknown_790;               // +0x790
    char *unknown_794;                  // +0x794
    char unknown_798[0x7A8 - 0x798];
    void *unknown_7a8;                  // +0x7A8
    char unknown_7ac[0x7B0 - 0x7AC];
    unsigned unknown_7b0;               // +0x7B0
    unsigned unknown_7b4;               // +0x7B4
};

int __fastcall unknown_decoder_read_chunk(UnknownDecoderState_77b390 *state, unsigned length)
{
    unsigned size = (length + 1) & ~1;
    if ((state->unknown_84 & 1) == 0 || state->unknown_78c == 0) {
        return state->Callback(state, 7, (void *)1, size) ? -6 : -1;
    }
    if (size > state->unknown_7b4 && state->unknown_790 == 0) {
        if (state->Callback(state, 5, state->unknown_78c, size) != 0) {
            return -4;
        }
        state->unknown_790 += length;
        for (unsigned i = 0; i < length / state->unknown_9c; i++) {
            state->unknown_794[i] = 1;
        }
        return -1;
    }
    if (state->Callback(state, 5, state->unknown_7a8, size) != 0) {
        return -4;
    }
    state->unknown_7b0 = length;
    return -1;
}
