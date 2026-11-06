// Table-driven hi-colour VQA decoder, complete original 0x0070B820.
// Uses the existing six-argument cdecl API; movie callback aliases stay unchanged.
#include "shared/unvq_table.hpp"
// @ref ?HicolorTable@@3PAGA=00ad0614

// The real reference helper: fills a sequence of 32-bit pixel pairs.
static inline void Fill_Pixel_Pairs(void *destination, unsigned int value, unsigned int count)
{
    unsigned int *pairs = (unsigned int *)destination;
    for (unsigned int index = 0; index < count; ++index) pairs[index] = value;
}

void __cdecl UnVQ2_4x4_Table(unsigned char *codebook, unsigned char *pointers, unsigned char *buffer,
    unsigned long blocks_per_row, unsigned long rows, unsigned long width)
{
    width *= 2;
    unsigned char *end = buffer + rows * width * 4;
    unsigned char *row_start = buffer;
    unsigned char *row_end = buffer + blocks_per_row * 8;
    unsigned int block_height = width * 4;
    unsigned short *commands = (unsigned short *)pointers;
    unsigned char *out = buffer;
    while (out < end) {
        unsigned short token = *commands++;
        unsigned int value = token;
        unsigned int count = value & 0xffff0fff;
        int opcode = value & 0xf000;
        if (opcode <= 0x3000) {
            if (opcode != 0x3000) {
                if (opcode) {
                    if (opcode != 0x1000) {
                        if (opcode == 0x2000) {
                            unsigned short *block = (unsigned short *)(codebook + *commands++ * 32);
                            unsigned int line_count = 4;
                            while (line_count > 0) {
                                unsigned int low = block[0];
                                unsigned int high = block[1];
                                unsigned int first_pair = low | (high << 16);
                                block += 2;
                                unsigned char *pixel = out;
                                unsigned int repeats = count;
                                while (repeats > 0) {
                                    *(unsigned int *)pixel = first_pair;
                                    pixel += 8;
                                    --repeats;
                                }
                                low = block[0];
                                high = block[1];
                                unsigned int second_pair = low | (high << 16);
                                block += 2;
                                unsigned char *second_pixel = out + 4;
                                unsigned int second_repeats = count;
                                while (second_repeats > 0) {
                                    *(unsigned int *)second_pixel = second_pair;
                                    second_pixel += 8;
                                    --second_repeats;
                                }
                                out += width;
                                --line_count;
                            }
                            out += count * 8 - block_height;
                        }
                    } else {
                        out += count * 8;
                    }
                } else {
                    unsigned int length = 2 * count;
                    unsigned short color = HicolorTable[*commands++];
                    unsigned int pair = color | (color << 16);
                    Fill_Pixel_Pairs(out, pair, length);
                    Fill_Pixel_Pairs(out + width, pair, length);
                    Fill_Pixel_Pairs(out + 2 * width, pair, length);
                    Fill_Pixel_Pairs(out + 2 * width + width, pair, length);
                    out += count * 8;
                }
            } else {
                unsigned short *block = (unsigned short *)(codebook + *commands++ * 32);
                unsigned int line_count = 4;
                while (line_count > 0) {
                    unsigned short *pixel = (unsigned short *)out;
                    unsigned int columns = 4;
                    while (columns > 0) {
                        unsigned short color = *block;
                        if (!(color & 0x8000)) {
                            unsigned short *repeat_pixel = pixel;
                            unsigned int repeats = count;
                            while (repeats > 0) {
                                *repeat_pixel = color;
                                repeat_pixel += 4;
                                --repeats;
                            }
                        }
                        ++pixel;
                        ++block;
                        --columns;
                    }
                    out += width;
                    --line_count;
                }
                out += 8 * count - block_height;
            }
        } else {
            switch (opcode) {
            case 0x5000:
                if (count > 0) {
                    int pitch = 4 * (width >> 2);
                    while (count > 0) {
                        unsigned short color = HicolorTable[*commands];
                        unsigned int pair = color | (color << 16);
                        ++commands;
                        unsigned char *line = out;
                        unsigned int line_count = 4;
                        while (line_count > 0) {
                            *(unsigned int *)line = pair;
                            ((unsigned int *)line)[1] = pair;
                            line += pitch;
                            --line_count;
                        }
                        out += 8;
                        --count;
                    }
                }
                break;
            case 0x6000:
                if (count > 0) {
                    int pitch = 4 * (width >> 2);
                    while (count > 0) {
                        unsigned short *block = (unsigned short *)(codebook + *commands++ * 32);
                        unsigned char *line = out;
                        unsigned int line_count = 4;
                        while (line_count > 0) {
                            unsigned int low = block[0];
                            unsigned int high = block[1];
                            unsigned int first_pair = low | (high << 16);
                            block += 2;
                            *(unsigned int *)line = first_pair;
                            low = block[0];
                            high = block[1];
                            unsigned int second_pair = low | (high << 16);
                            block += 2;
                            ((unsigned int *)line)[1] = second_pair;
                            line += pitch;
                            --line_count;
                        }
                        out += 8;
                        --count;
                    }
                }
                break;
            case 0x7000:
                if (count > 0) {
                    while (count > 0) {
                        unsigned short *block = (unsigned short *)(codebook + *commands++ * 32);
                        unsigned char *line = out;
                        int line_count = 4;
                        while (line_count) {
                            unsigned short *pixel = (unsigned short *)line;
                            unsigned int columns = 4;
                            while (columns > 0) {
                                if (!(*block & 0x8000)) *pixel = *block;
                                ++pixel;
                                ++block;
                                --columns;
                            }
                            --line_count;
                            line += 2 * (width >> 1);
                        }
                        out += 8;
                        --count;
                    }
                }
                break;
            }
        }
        if (out == row_end) {
            row_start += block_height;
            out = row_start;
            row_end = out + blocks_per_row * 8;
        }
    }
}
