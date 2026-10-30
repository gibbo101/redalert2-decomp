// void __cdecl UnVQ1_C4_4x4(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
//                 unsigned long blocksperrow, unsigned long numrows, unsigned long bufwidth) -- 0x0077CF70
// Purpose: draws a 4x4-block frame into a 16-bit buffer from 13-bit codebook
// indices (opaque, keyed on 0x8000 pixels, or a one-block skip).
#include "shared/vqa_player.hpp"

void __cdecl UnVQ1_C4_4x4(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
                          unsigned long blocksperrow, unsigned long numrows, unsigned long bufwidth)
{
    bufwidth *= 2;
    unsigned long rowbytes = bufwidth * 4;
    unsigned char *end = buffer + numrows * bufwidth * 4;
    unsigned short *src = (unsigned short *)pointers;
    unsigned char *dst = buffer;
    unsigned char *rowstart = buffer;
    unsigned char *rowend = rowstart + blocksperrow * 8;

    while (dst < end) {
        unsigned long op = *src & 0xE000;
        unsigned short index = *src & 0x1FFF;
        src++;

        switch (op) {
        case 0x0000: {
            unsigned char *cb = codebook + (index << 5);
            for (unsigned long r = 0; r < 4; r++) {
                unsigned long lo;
                unsigned long hi;
                lo = ((unsigned long)*(unsigned short *)(cb + 2) << 16) | *(unsigned short *)cb;
                cb += 4;
                *(unsigned long *)(dst + 0) = lo;
                hi = ((unsigned long)*(unsigned short *)(cb + 2) << 16) | *(unsigned short *)cb;
                cb += 4;
                *(unsigned long *)(dst + 4) = hi;
                dst += bufwidth;
            }
            dst += 8 - rowbytes;
        } break;

        case 0x2000: {
            unsigned char *cb = codebook + (index << 5);
            for (unsigned long r = 0; r < 4; r++) {
                unsigned char *p = dst;
                for (unsigned long c = 0; c < 4; c++) {
                    unsigned short px = *(unsigned short *)cb;
                    if (px != 0x8000) {
                        *(unsigned short *)p = px;
                    }
                    p += 2;
                    cb += 2;
                }
                dst += bufwidth;
            }
            dst += 8 - rowbytes;
        } break;

        case 0x4000:
            dst += 8;
            break;

        default:
            break;
        }

        if (dst == rowend) {
            rowstart += rowbytes;
            dst = rowstart;
            rowend = rowstart + blocksperrow * 8;
        }
    }
}
