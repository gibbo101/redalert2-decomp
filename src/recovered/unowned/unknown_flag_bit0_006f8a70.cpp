// bool __fastcall unknown_flag_bit0(UnknownFlags_006f8a70 const *object) -- 0x006F8A70
// Purpose: bit 0 of the byte at +0x14; false for a null object.
// Assumptions: owner unknown; the bit is a one-bit field.

struct UnknownFlags_006f8a70 {
    char unknown_00[0x14];
    unsigned char unknown_14_bit0 : 1;      // +0x14 bit 0
};

unsigned char __fastcall unknown_flag_bit0(UnknownFlags_006f8a70 const *object)
{
    if (object == 0) {
        return 0;
    }
    return object->unknown_14_bit0;
}
