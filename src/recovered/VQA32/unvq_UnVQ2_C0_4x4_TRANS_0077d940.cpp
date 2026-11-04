// void __cdecl UnVQ2_C0_4x4_TRANS(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
//                 unsigned long blocksperrow, unsigned long numrows, unsigned long bufwidth) -- 0x0077D940
// Purpose: unpacks 4x4 blocks (16-byte codebook entries, four pixel
// rows per block), skipping zero pixels of fills and codebook blocks.
#include "shared/vqa_player.hpp"

void __cdecl UnVQ2_C0_4x4_TRANS(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
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
                                unsigned long n = count * 4;
                                for (r = 0; r < 4; r++) {
                                    for (unsigned long k = 0; k < n; k++) {
                                        *dst++ = (unsigned char)code;
                                    }
                                    dst -= n;
                                    dst += bufwidth;
                                }
                                dst -= bufwidth * 4;
                            }
                            dst += count * 4;
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
                                    for (r = 0; r < 4; r++) {
                                        unsigned long j;
                                        for (j = 0; j < count; j++) {
                                            for (int c = 0; c < 4; c++) {
                                                if (*cb) {
                                                    *dst = *cb;
                                                }
                                                dst++;
                                                cb++;
                                            }
                                            cb -= 4;
                                        }
                                        cb += 4;
                                        dst -= count * 4;
                                        dst += bufwidth;
                                    }
                                    dst += count * 4;
                                    dst -= bufwidth * 4;
                                    src++;
                                    blocks += count;
                                } break;

                                case 0x8000: {
                                    if ((unsigned char)code2) {
                                        unsigned long n = count * 4;
                                        for (r = 0; r < 4; r++) {
                                            for (unsigned long k = 0; k < n; k++) {
                                                *dst++ = (unsigned char)code2;
                                            }
                                            dst -= n;
                                            dst += bufwidth;
                                        }
                                        dst -= bufwidth * 4;
                                    }
                                    dst += count * 4;
                                    blocks += count;
                                    src++;
                                } break;
                                }
                            } else {
                                unsigned char *cb = codebook + ((unsigned long)code2 << 4);
                                for (r = 0; r < 4; r++) {
                                    unsigned long j;
                                    for (j = 0; j < count; j++) {
                                        for (int c = 0; c < 4; c++) {
                                            *dst++ = *cb++;
                                        }
                                        cb -= 4;
                                    }
                                    cb += 4;
                                    dst -= count * 4;
                                    dst += bufwidth;
                                }
                                dst += count * 4;
                                dst -= bufwidth * 4;
                                src++;
                                blocks += count;
                            }
                        } break;
                        }
                    } else {
                        count = code & 0xFFF;
                        src++;
                        for (unsigned long pair=0; pair<(count>>1); ++pair) {
                            unsigned short code2 = *src;
                            unsigned char left = (unsigned char)(code2 >> 8);
                            if (left != 0) {
                                for (r = 0; r < 4; r++) {
                                    for (int c = 0; c < 4; c++) {
                                        *dst++ = left;
                                    }
                                    dst -= 4;
                                    dst += bufwidth;
                                }
                                dst -= bufwidth * 4;
                            }
                            dst += 4;
                            if ((unsigned char)code2) {
                                for (r = 0; r < 4; r++) {
                                    for (int c = 0; c < 4; c++) {
                                        *dst++ = (unsigned char)code2;
                                    }
                                    dst -= 4;
                                    dst += bufwidth;
                                }
                                dst -= bufwidth * 4;
                            }
                            dst += 4;
                            src++;
                        }
                        blocks += count;
                    }
                } else {
                    switch (op) {
                    case 0xF000: {
                        if ((unsigned char)code) {
                            for (r = 0; r < 4; r++) {
                                for (int c = 0; c < 4; c++) {
                                    *dst++ = (unsigned char)code;
                                }
                                dst -= 4;
                                dst += bufwidth;
                            }
                            dst -= bufwidth * 4;
                        }
                        dst += 4;
                        src++;
                        blocks += 1;
                    } break;

                    case 0xE000: {
                        unsigned char *cb = codebook + ((unsigned long)(code & 0xFFF) << 4);
                        for (r = 0; r < 4; r++) {
                            for (int c = 0; c < 4; c++) {
                                if (*cb) {
                                    *dst = *cb;
                                }
                                dst++;
                                cb++;
                            }
                            dst -= 4;
                            dst += bufwidth;
                        }
                        dst -= bufwidth * 4;
                        dst += 4;
                        src++;
                        blocks += 1;
                    } break;
                    }
                }
            } else {
                unsigned char *cb = codebook + ((unsigned long)*src << 4);
                for (r = 0; r < 4; r++) {
                    for (int c = 0; c < 4; c++) {
                        *dst++ = *cb++;
                    }
                    dst -= 4;
                    dst += bufwidth;
                }
                dst -= bufwidth * 4;
                dst += 4;
                src++;
                blocks += 1;
            }

            if (blocks % blocksperrow == 0) {
                dst = rowstart + bufwidth * 4;
                rowstart = dst;
            }
            if (blocks >= total) {
                return;
            }
        }
    }
}
