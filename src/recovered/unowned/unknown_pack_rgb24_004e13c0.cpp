// void __fastcall unknown_pack_rgb24(unsigned char *pixels, unsigned int width, unsigned int height, unsigned int depth) -- 0x004E13C0
// Packs width * height * depth four-byte pixels in place into three-byte colours (the first byte of every
// pixel is dropped). No direct callers; the three factors of the count and the owner are not identified.
void __fastcall unknown_pack_rgb24_004e13c0(unsigned char *pixels, unsigned int width, unsigned int height, unsigned int depth)
{
    unsigned char *out = pixels;
    unsigned char *in = pixels;
    for (unsigned int count = width * height * depth; count > 0; count--) {
        in += 1;
        *out = *in;
        in++;
        out++;
        *out = *in;
        in++;
        out++;
        *out = *in;
        in++;
        out++;
    }
}
