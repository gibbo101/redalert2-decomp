// lzo1x_decompress(in, in_len, out, out_len, wrkmem) (0x0053E970)
// LZO1X decompressor (no bounds checking): literal runs and back
// references until the end-of-stream marker; *out_len receives the output
// size. Returns 0 (LZO_E_OK) when exactly in_len bytes were consumed, else
// -1 (LZO_E_ERROR). wrkmem is unused. Identified library code (LZO 1.0x).
#include "shared/lzo.hpp"

#define LZO_E_OK 0
#define LZO_E_ERROR (-1)
#define M2_MAX_OFFSET 0x0800

int __fastcall lzo1x_decompress(unsigned char const *in, unsigned int in_len,
                                unsigned char *out, unsigned int *out_len, void *wrkmem)
{
    unsigned char *op;
    unsigned char const *ip;
    unsigned int t;
    unsigned char const *m_pos;
    unsigned char const * const ip_end = in + in_len;

    *out_len = 0;
    op = out;
    ip = in;

    if (*ip > 17) {
        t = *ip++ - 17;
        goto first_literal_run;
    }

    for (;;) {
        t = *ip++;
        if (t >= 16) {
            goto match;
        }

        // A literal run.
        if (t == 0) {
            t = 15;
            while (*ip == 0) {
                t += 255;
                ip++;
            }
            t += *ip++;
        }
        *op++ = *ip++;
        *op++ = *ip++;
        *op++ = *ip++;
first_literal_run:
        do {
            *op++ = *ip++;
        } while (--t > 0);

        t = *ip++;
        if (t >= 16) {
            goto match;
        }
        m_pos = op - (1 + M2_MAX_OFFSET);
        m_pos -= t >> 2;
        m_pos -= *ip++ << 2;
        *op++ = *m_pos++;
        *op++ = *m_pos++;
        *op++ = *m_pos;
        goto match_done;

        // Back references (short M1 matches first), each followed by up to
        // three literals.
        for (;;) {
            if (t < 16) {
                m_pos = op - 1;
                m_pos -= t >> 2;
                m_pos -= *ip++ << 2;
                *op++ = *m_pos++;
                *op++ = *m_pos;
                goto match_done;
            }
match:
            if (t >= 64) {
                m_pos = op - 1;
                m_pos -= (t >> 2) & 7;
                m_pos -= *ip++ << 3;
                t = (t >> 5) - 1;
                goto copy_match;
            } else if (t >= 32) {
                t &= 31;
                if (t == 0) {
                    t = 31;
                    while (*ip == 0) {
                        t += 255;
                        ip++;
                    }
                    t += *ip++;
                }
                m_pos = op - 1;
                m_pos -= *ip++ >> 2;
                m_pos -= *ip++ << 6;
            } else {
                m_pos = op;
                m_pos -= (t & 8) << 11;
                t &= 7;
                if (t == 0) {
                    t = 7;
                    while (*ip == 0) {
                        t += 255;
                        ip++;
                    }
                    t += *ip++;
                }
                m_pos -= *ip++ >> 2;
                m_pos -= *ip++ << 6;
                if (m_pos == op) {
                    goto eof_found;
                }
                m_pos -= 0x4000;
            }

copy_match:
            *op++ = *m_pos++;
            *op++ = *m_pos++;
            do {
                *op++ = *m_pos++;
            } while (--t > 0);

match_done:
            t = ip[-2] & 3;
            if (t == 0) {
                break;
            }

            do {
                *op++ = *ip++;
            } while (--t > 0);
            t = *ip++;
        }
    }

eof_found:
    *out_len = op - out;
    return (ip == ip_end) ? LZO_E_OK : LZO_E_ERROR;
}
