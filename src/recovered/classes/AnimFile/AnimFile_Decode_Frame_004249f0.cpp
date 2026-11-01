// bool AnimFile::Decode_Frame(void *source, int size, void *dest, int destsize) (0x004249F0):
// lays one frame record over dest. The record starts with its body type (short): 0 is an
// uncompressed copy (refused unless it fills dest exactly), 1 a run/skip/dump stream that
// must end in the stop code 80 00 00; any other type is refused. An empty record is no change.
#include "shared/anim_file.hpp"
#include "shared/crt_memory.hpp"

bool AnimFile::Decode_Frame(void *source, int size, void *dest, int destsize)
{
    int body;
    unsigned char *dst;
    bool decoded;

    if (size == 0) {
        return true;
    }

    unsigned char *src;
    signed char count;
    int word_count;
    int pixel;

    body = *(short *)source;
    size -= sizeof(short);
    source = (unsigned char *)source + sizeof(short);
    dst = (unsigned char *)dest;

    if (size == 0) {
        return true;
    }

    decoded = true;

    switch (body) {
        case 0:
            if (size != destsize) {
                decoded = false;
            } else {
                memcpy(dst, source, size);
            }
            break;

        case 1:
            src = (unsigned char *)source + size - 3;
            if (size < 3 || src[0] != 0x80 || src[1] != 0 || src[2] != 0) {
                decoded = false;
                break;
            }

            src = (unsigned char *)source;
            {
            next_op:
                count = *src++;
                if (count > 0) {
                    goto short_dump;
                }
                if (count == 0) {
                    goto short_run;
                }
                count -= (signed char)0x80;
                if (count == 0) {
                    goto long_op;
                }

                // short skip
                dst += count;
                goto next_op;

            short_dump:
                memcpy(dst, src, count);
                dst += count;
                src += count;
                goto next_op;

            short_run:
                word_count = *(unsigned char *)src;
                src += sizeof(unsigned char);
                pixel = *src;
                src += sizeof(unsigned char);
                memset(dst, pixel, word_count);
                dst += word_count;
                goto next_op;

            long_op:
                word_count = *(unsigned short *)src;
                src += sizeof(unsigned short);
                if ((signed short)word_count <= 0) {
                    goto not_long_skip;
                }

                // long skip
                dst += word_count;
                goto next_op;

            not_long_skip:
                if (word_count == 0) {
                    goto stop;
                }
                word_count -= 0x8000;
                if (word_count >= 0x4000) {
                    goto long_run;
                }

                // long dump
                memcpy(dst, src, word_count);
                dst += word_count;
                src += word_count;
                goto next_op;

            long_run:
                word_count -= 0x4000;
                pixel = *src;
                src += sizeof(unsigned char);
                memset(dst, pixel, word_count);
                dst += word_count;
                goto next_op;

            stop:
                ;
            }
            break;

        default:
            decoded = false;
            break;
    }

    return decoded;
}
