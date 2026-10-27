// void __fastcall unknown_clear_low_color_bits(unsigned char *palette, unsigned int count) -- 0x004E12B0
// Purpose: clears the three low bits of every component of `count` RGB
// triples. No direct callers. Owner not identified.
void __fastcall unknown_clear_low_color_bits_004e12b0(unsigned char *palette, unsigned int count)
{
    for (unsigned int index = count * 3; index > 0; index--) {
        *palette++ &= 0xf8;
    }
}
