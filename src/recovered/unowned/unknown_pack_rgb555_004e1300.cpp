// void __fastcall unknown_pack_rgb555(unsigned char *pixels, unsigned int width, unsigned int height, unsigned int depth) -- 0x004E1300
// Packs width * height * depth three-byte colours (red, green, blue) in place into 16-bit 5-5-5 values
// (the three low bits of red and green are dropped, blue is shifted down). No direct callers; the three
// factors of the count and the owner are not identified.
void __fastcall unknown_pack_rgb555_004e1300(unsigned char *pixels, unsigned int width, unsigned int height, unsigned int depth)
{
    unsigned short *out = (unsigned short *)pixels;
    unsigned char *in = pixels;
    for (unsigned int count = width * height * depth; count > 0; count--) {
        unsigned short red = in[0] & 0xf8;
        unsigned short green = in[1] & 0xf8;
        unsigned short blue = in[2] >> 3;
        *out++ = (unsigned short)(((red << 5 | green) << 2) | blue);
        in += 3;
    }
}
