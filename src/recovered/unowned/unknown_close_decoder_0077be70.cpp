// void __fastcall unknown_close_decoder(UnknownDecoderState *state) -- 0x0077BE70
// Purpose: shuts a decoder state down (owner unknown; the 0x00776xxx-
// 0x0077Cxxx library functions share this 0x7DC-byte state with two
// callbacks at +0x40 and +0x44): finishes pending output when +0x84 bit 0
// and +0xEA bits 0-1 are set (0x00776420; clears +0x7BC bit 30 after
// 0x00412380), frees the buffer at +0x158 (size +0x15C * +0x160) when
// +0x150 bit 5 is set, runs 0x00777190, then signals the callbacks: event
// 4 on +0x40 and events 5 (free, 0x7DC bytes) and 3 on +0x44 for the state.
// Assumptions: layout and event meanings are hypotheses from this function.
// @ref ?unknown_decoder_finish_00776420@@YIXPAUUnknownDecoderState@@@Z=00776420
// @ref ?unknown_decoder_release_00777190@@YIXPAUUnknownDecoderState@@@Z=00777190
// @ref ?unknown_return_one_00412380@@YAHXZ=00412380

struct UnknownDecoderState;
typedef int (*UnknownDecoderCallback)(UnknownDecoderState *state, int event, void *data, int size);

struct UnknownDecoderState {
    char unknown_000[0x40];
    UnknownDecoderCallback Callback40;      // +0x40
    UnknownDecoderCallback Callback44;      // +0x44
    char unknown_048[0x84 - 0x48];
    unsigned char unknown_84;               // +0x84
    char unknown_085[0xEA - 0x85];
    unsigned char unknown_ea;               // +0xEA
    char unknown_0eb[0x150 - 0xEB];
    unsigned char unknown_150;              // +0x150
    char unknown_151[0x158 - 0x151];
    void *Buffer;                           // +0x158
    int BufferWidth;                        // +0x15C
    int BufferHeight;                       // +0x160
    char unknown_164[0x7BC - 0x164];
    unsigned long unknown_7bc;              // +0x7BC
    char unknown_7c0[0x7DC - 0x7C0];
};

void __fastcall unknown_decoder_finish_00776420(UnknownDecoderState *state);
void __fastcall unknown_decoder_release_00777190(UnknownDecoderState *state);
int unknown_return_one_00412380();

void __fastcall unknown_close_decoder(UnknownDecoderState *state)
{
    if ((state->unknown_84 & 1) && (state->unknown_ea & 3)) {
        unknown_decoder_finish_00776420(state);
        if (state->unknown_7bc & 0x40000000) {
            unknown_return_one_00412380();
            state->unknown_7bc &= ~0x40000000;
        }
    }
    if ((state->unknown_150 & 0x20) && state->Buffer != 0) {
        state->Callback44(state, 5, state->Buffer, state->BufferHeight * state->BufferWidth);
        state->Callback44(state, 3, state->Buffer, 0);
    }
    unknown_decoder_release_00777190(state);
    state->Callback40(state, 4, 0, 0);
    state->Callback44(state, 5, state, sizeof(UnknownDecoderState));
    state->Callback44(state, 3, state, 0);
}
