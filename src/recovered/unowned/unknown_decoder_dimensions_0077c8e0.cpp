// int __fastcall unknown_decoder_dimensions(UnknownDecoderState_77c8e0 const *state, unsigned *width, unsigned *height) -- 0x0077C8E0
// Purpose: reports the image size: the explicit size at +0x112/+0x116 when
// set, else the 16-bit header values at +0x02/+0x04. Returns -1.
// Assumptions: the state is the 0x7DC-byte decoder state of 0x0077BE70
// (byte-packed in this area); field meanings are hypotheses.

#pragma pack(push, 1)
struct UnknownDecoderState_77c8e0 {
    short unknown_000;
    unsigned short HeaderWidth;             // +0x002
    unsigned short HeaderHeight;            // +0x004
    char unknown_006[0x112 - 0x6];
    unsigned Width;                         // +0x112
    unsigned Height;                        // +0x116
};
#pragma pack(pop)

int __fastcall unknown_decoder_dimensions(UnknownDecoderState_77c8e0 const *state, unsigned *width, unsigned *height)
{
    if (state->Width > 0) {
        *width = state->Width;
        *height = state->Height;
        return -1;
    }
    *width = state->HeaderWidth;
    *height = state->HeaderHeight;
    return -1;
}
