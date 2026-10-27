// int __fastcall unknown_decoder_read_block(UnknownDecoderState_77afa0 *state, int length) -- 0x0077AFA0
// Purpose: takes the first free block of the decoder's pool (+0x164) and
// has the input callback (+0x40, event 5) fill its data, ending at
// +0x768 bytes, with `length` bytes rounded up to even; marks the block
// (+0x0C = 10, +0x10 = start offset), makes it current and, for formats
// below version 3 (+0xE8), puts 0x80 after the data. -4 when the callback
// fails, else -1.
// Assumptions: the decoder state of 0x0077BE70; field meanings are
// hypotheses.

struct UnknownDecoderBlock_77afa0 {
    char *Data;
    UnknownDecoderBlock_77afa0 *Next;     // +0x04
    int unknown_08;
    int unknown_0c;
    int unknown_10;
};
struct UnknownDecoderPool_77afa0 {
    UnknownDecoderBlock_77afa0 *Free;     // +0x00
    UnknownDecoderBlock_77afa0 *Current;  // +0x04
};
struct UnknownDecoderState_77afa0 {
    char unknown_000[0x40];
    int (*Callback)(UnknownDecoderState_77afa0 *state, int code, char *buffer, unsigned size);  // +0x40
    char unknown_044[0xE8 - 0x44];
    unsigned short unknown_e8;          // +0xE8
    char unknown_0ea[0x164 - 0xEA];
    UnknownDecoderPool_77afa0 Pool;                   // +0x164
    char unknown_16c[0x174 - 0x16C];
    int unknown_174;                    // +0x174
    char unknown_178[0x768 - 0x178];
    int unknown_768;                    // +0x768
};

int __fastcall unknown_decoder_read_block(UnknownDecoderState_77afa0 *state, int length)
{
    UnknownDecoderBlock_77afa0 *block = state->Pool.Free;
    unsigned size = (length + 1) & ~1;
    int offset = state->unknown_768 - size;
    char *buffer = block->Data + offset;
    if (state->Callback(state, 5, buffer, size) != 0) {
        return -4;
    }
    state->unknown_174 = 0;
    block->unknown_0c = 10;
    block->unknown_10 = offset;
    UnknownDecoderPool_77afa0 *pool = &state->Pool;
    pool->Current = block;
    pool->Free = block->Next;
    if (state->unknown_e8 < 3) {
        buffer[length + 1] = (char)0x80;
    }
    return -1;
}
