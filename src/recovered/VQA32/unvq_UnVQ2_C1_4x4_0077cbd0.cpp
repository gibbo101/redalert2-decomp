// void __cdecl UnVQ2_C1_4x4(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
//                 unsigned long blocksperrow, unsigned long numrows, unsigned long bufwidth) -- 0x0077CBD0
// Purpose: draws a 4x4-block frame into a 16-bit buffer from 16-bit block codes
// (fill, skip, replicated codebook rows, keyed codebook blocks and their single-block
// forms); a block row wraps to the next four pixel rows after blocksperrow blocks.
#include "shared/vqa_player.hpp"

void __cdecl UnVQ2_C1_4x4(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
                          unsigned long blocksperrow, unsigned long numrows, unsigned long bufwidth)
{
    bufwidth *= 2;
    unsigned long rowbytes = bufwidth * 4;
    unsigned char *end = buffer + numrows * bufwidth * 4;
    unsigned char *rowstart = buffer;
    unsigned char *rowend = rowstart + blocksperrow * 8;
    unsigned short *src = (unsigned short *)pointers;
    unsigned char *dst = buffer;

    while (dst < end) {
        unsigned short code = *src;
        int op = code & 0xF000;
        unsigned long count = code;
        count &= 0xFFFF0FFF;
        src++;

        switch (op) {
        case 0x0000: {
            unsigned long n = count * 2;
            unsigned long w = *src;
            unsigned long fill = (w << 16) | w;
            src++;
            {
                unsigned int *p = (unsigned int *)dst;
                unsigned int left = n;
                while (left > 0) { *p++ = fill; left--; }
            }
            {
                unsigned int *p = (unsigned int *)(dst + bufwidth);
                unsigned int left = n;
                while (left > 0) { *p++ = fill; left--; }
            }
            {
                unsigned int *p = (unsigned int *)(dst + bufwidth * 2);
                unsigned int left = n;
                while (left > 0) { *p++ = fill; left--; }
            }
            {
                unsigned int *p = (unsigned int *)(dst + bufwidth * 3);
                unsigned int left = n;
                while (left > 0) { *p++ = fill; left--; }
            }
            dst += count * 8;
        } break;

        case 0x1000:
            dst += count * 8;
            break;

        case 0x2000: {
            unsigned char *cb = codebook + ((unsigned long)*src << 5);
            src++;
            for (unsigned long r = 0; r < 4; r++) {
                unsigned long lo = ((unsigned long)*(unsigned short *)(cb + 2) << 16) | *(unsigned short *)cb;
                cb += 4;
                unsigned long i;
                {
                    unsigned char *p = dst;
                    for (i = 0; i < count; i++) { *(unsigned long *)p = lo; p += 8; }
                }
                unsigned long hi = ((unsigned long)*(unsigned short *)(cb + 2) << 16) | *(unsigned short *)cb;
                cb += 4;
                {
                    unsigned char *p = dst + 4;
                    for (i = 0; i < count; i++) { *(unsigned long *)p = hi; p += 8; }
                }
                dst += bufwidth;
            }
            dst += count * 8 - rowbytes;
        } break;

        case 0x3000: {
            unsigned short index = *src;
            unsigned char *cb = codebook + 32 * (unsigned long)index;
            unsigned long r;
            src++;
            for (r = 0; r < 4; r++) {
                unsigned char *rp = dst;
                unsigned long c;
                for (c = 0; c < 4; c++) {
                    unsigned short px = *(unsigned short *)cb;
                    if ((px & 0x8000) == 0) {
                        unsigned char *p = rp;
                        unsigned long i;
                        for (i = 0; i < count; i++) { *(unsigned short *)p = px; p += 8; }
                    }
                    rp += 2;
                    cb += 2;
                }
                dst += bufwidth;
            }
            dst += count * 8 - rowbytes;
        } break;

        case 0x5000: {
            unsigned long i;
            for (i = 0; i < count; i++) {
                unsigned long step = (bufwidth >> 2) * 4;
                unsigned long j;
                unsigned long fill;
                unsigned long rows = 4;
                unsigned char *p;
                {
                    unsigned long w = *src;
                    fill = (w << 16) | w;
                    src++;
                }
                p = dst;
                for (j = 0; j < rows; j++) {
                    *(unsigned long *)(p + 0) = fill;
                    *(unsigned long *)(p + 4) = fill;
                    p += step;
                }
                dst += 8;
            }
        } break;

        case 0x6000: {
            unsigned long i;
            for (i = 0; i < count; i++) {
                unsigned long step = (bufwidth >> 2) * 4;
                unsigned char *cb = codebook + ((unsigned long)*src << 5);
                src++;
                unsigned char *p = dst;
                for (unsigned long r = 0; r < 4; r++) {
                    unsigned long lo;
                    unsigned long hi;
                    lo = ((unsigned long)*(unsigned short *)(cb + 2) << 16) | *(unsigned short *)cb;
                    cb += 4;
                    *(unsigned long *)(p + 0) = lo;
                    hi = ((unsigned long)*(unsigned short *)(cb + 2) << 16) | *(unsigned short *)cb;
                    cb += 4;
                    *(unsigned long *)(p + 4) = hi;
                    p += step;
                }
                dst += 8;
            }
        } break;

        case 0x7000: {
            unsigned long i;
            for (i = 0; i < count; i++) {
                unsigned short index = *src;
                unsigned char *cb = codebook + 32 * (unsigned long)index;
                src++;
                unsigned char *p = dst;
                for (unsigned long r = 0; r < 4; r++) {
                    unsigned char *q = p;
                    for (unsigned long c = 0; c < 4; c++) {
                        unsigned short px = *(unsigned short *)cb;
                        if ((px & 0x8000) == 0) {
                            *(unsigned short *)q = px;
                        }
                        q += 2;
                        cb += 2;
                    }
                    p += (bufwidth >> 1) * 2;
                }
                dst += 8;
            }
        } break;
        }

        if (dst == rowend) {
            rowstart += rowbytes;
            dst = rowstart;
            rowend = rowstart + blocksperrow * 8;
        }
    }
}
