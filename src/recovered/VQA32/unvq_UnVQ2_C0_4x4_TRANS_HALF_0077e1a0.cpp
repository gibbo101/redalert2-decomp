// void __cdecl UnVQ2_C0_4x4_TRANS_HALF(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
//                 unsigned long blocksperrow, unsigned long numrows, unsigned long bufwidth) -- 0x0077E1A0
// Purpose: the half-size form of UnVQ2_C0_4x4_TRANS: each 4x4 codebook block is drawn
// as a 2x2 block (every other pixel of its first two rows), skipping zero pixels; a
// block row wraps to the next two pixel rows after blocksperrow blocks.
#include "shared/vqa_player.hpp"

void __cdecl UnVQ2_C0_4x4_TRANS_HALF(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
                                unsigned long blocksperrow, unsigned long numrows, unsigned long bufwidth)
{
    register unsigned short *src = (unsigned short *)pointers;
    unsigned char *dst = buffer;
    unsigned long blocks = 0;
    unsigned long count;
    int r;
    unsigned char *rowstart = buffer;
    unsigned long total = blocksperrow * numrows;

    if (total > 0) {
        while (1) {
            unsigned short code = *src;
            if ((code & 0x8000) != 0) {
                long op = code & 0xF000;
                if (op <= 0xC000) {
                    if (op != 0xC000) {
                        switch (op) {
                        case 0xB000: {
                            count = ((unsigned long)code >> 8) & 0xF;
                            if ((unsigned char)code) {
                                unsigned long n = count * 2;
                                for (r = 0; r < 2; r++) {
                                    for (unsigned long k = 0; k < n; k++) {
                                        *dst++ = (unsigned char)code;
                                    }
                                    dst -= n;
                                    dst += bufwidth;
                                }
                                dst -= bufwidth * 2;
                            }
                            dst += count * 2;
                            blocks += count;
                            src++;
                        } break;

                        case 0xA000: {
                            src++;
                            unsigned short code2 = *src;
                            count = code & 0xFFF;
                            if ((code2 & 0x8000) != 0) {
                                int kind = code2 & 0xC000;
                                switch (kind) {
                                case 0xC000: {
                                    unsigned char *cb = codebook + ((unsigned long)(code2 & 0xFFF) << 4);
                                    for (r = 0; r < 2; r++) {
                                        unsigned long j;
                                        for (j = 0; j < count; j++) {
                                            for (int c = 0; c < 2; c++) {
                                                if (*cb) {
                                                    *dst = *cb;
                                                }
                                                dst++;
                                                cb += 2;
                                            }
                                            cb -= 4;
                                        }
                                        cb += 4;
                                        dst -= count * 2;
                                        dst += bufwidth;
                                    }
                                    dst += count * 2;
                                    dst -= bufwidth * 2;
                                    src++;
                                    blocks += count;
                                } break;

                                case 0x8000: {
                                    if ((unsigned char)code2) {
                                        unsigned long n = count * 2;
                                        for (r = 0; r < 2; r++) {
                                            for (unsigned long k = 0; k < n; k++) {
                                                *dst++ = (unsigned char)code2;
                                            }
                                            dst -= n;
                                            dst += bufwidth;
                                        }
                                        dst -= bufwidth * 2;
                                    }
                                    dst += count * 2;
                                    blocks += count;
                                    src++;
                                } break;
                                }
                            } else {
                                unsigned char *cb = codebook + ((unsigned long)code2 << 4);
                                for (r = 0; r < 2; r++) {
                                    unsigned long j;
                                    for (j = 0; j < count; j++) {
                                        for (int c = 0; c < 2; c++) {
                                            *dst++ = *cb;
                                            cb += 2;
                                        }
                                        cb -= 4;
                                    }
                                    cb += 4;
                                    dst -= count * 2;
                                    dst += bufwidth;
                                }
                                dst += count * 2;
                                dst -= bufwidth * 2;
                                src++;
                                blocks += count;
                            }
                        } break;
                        }
                    } else {
                        count = code & 0xFFF;
                        src++;
                        for (unsigned long pairs = count >> 1; pairs != 0; pairs--) {
                            unsigned short code2 = *src;
                            unsigned char left = (unsigned char)(code2 >> 8);
                            if (left != 0) {
                                for (r = 0; r < 2; r++) {
                                    for (int c = 0; c < 2; c++) {
                                        *dst++ = left;
                                    }
                                    dst -= 2;
                                    dst += bufwidth;
                                }
                                dst -= bufwidth * 2;
                            }
                            dst += 2;
                            if ((unsigned char)code2) {
                                for (r = 0; r < 2; r++) {
                                    for (int c = 0; c < 2; c++) {
                                        *dst++ = (unsigned char)code2;
                                    }
                                    dst -= 2;
                                    dst += bufwidth;
                                }
                                dst -= bufwidth * 2;
                            }
                            dst += 2;
                            src++;
                        }
                        blocks += count;
                    }
                } else {
                    switch (op) {
                    case 0xF000: {
                        if ((unsigned char)code) {
                            for (r = 0; r < 2; r++) {
                                for (int c = 0; c < 2; c++) {
                                    *dst++ = (unsigned char)code;
                                }
                                dst -= 2;
                                dst += bufwidth;
                            }
                            dst -= bufwidth * 2;
                        }
                        dst += 2;
                        src++;
                        blocks += 1;
                    } break;

                    case 0xE000: {
                        unsigned char *cb = codebook + ((unsigned long)(code & 0xFFF) << 4);
                        for (r = 0; r < 2; r++) {
                            for (int c = 0; c < 2; c++) {
                                if (*cb) {
                                    *dst = *cb;
                                }
                                dst++;
                                cb += 2;
                            }
                            dst -= 2;
                            dst += bufwidth;
                        }
                        dst -= bufwidth * 2;
                        dst += 2;
                        src++;
                        blocks += 1;
                    } break;
                    }
                }
            } else {
                unsigned char *cb = codebook + ((unsigned long)*src << 4);
                for (r = 0; r < 2; r++) {
                    for (int c = 0; c < 2; c++) {
                        *dst++ = *cb;
                        cb += 2;
                    }
                    dst -= 2;
                    dst += bufwidth;
                }
                dst -= bufwidth * 2;
                dst += 2;
                src++;
                blocks += 1;
            }

            if (blocks % blocksperrow == 0) {
                dst = rowstart + bufwidth * 2;
                rowstart = dst;
            }
            if (blocks >= total) {
                return;
            }
        }
    }
}
