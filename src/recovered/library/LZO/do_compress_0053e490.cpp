// do_compress(in, in_len, out, out_len, wrkmem) (0x0053E490)
// LZO1X-1 compressor core: a hash dictionary (16384 entries of byte
// pointers in wrkmem) finds earlier occurrences of the next three bytes;
// matches are coded as M2/M3/M4 back references and the bytes between them
// as literal runs. Leaves the final literal run and the end marker to
// lzo1x_1_compress. Returns 0 (LZO_E_OK). Identified library code
// (LZO 1.0x, file-static in lzo1x_c; __fastcall like its caller).
#include "shared/lzo.hpp"

#define LZO_E_OK 0
#define M2_MAX_LEN 8
#define M2_MAX_OFFSET 0x0800
#define M3_MAX_OFFSET 0x4000
#define M4_MAX_OFFSET 0xBFFF
#define M4_MAX_LEN 9
#define M3_MARKER 32
#define M4_MARKER 16

// Rolling hash of the three bytes at p, and its dictionary slot.
#define DVAL_FIRST(dv, p) dv = ((((unsigned)(p)[2] << 5) ^ (p)[1]) << 5) ^ (p)[0]
#define DVAL_NEXT(dv, p) dv = ((unsigned)(p)[2] << 10) ^ ((p)[-1] >> 5) ^ (dv >> 5)
#define DINDEX(dv) ((((dv) * 0x9F5F) >> 5) & 0x3FFF)

int __fastcall do_compress(unsigned char const *in, unsigned int in_len,
                           unsigned char *out, unsigned int *out_len, void *wrkmem)
{
    unsigned char const *ip;
    unsigned int dv;
    unsigned char *op;
    unsigned char const * const in_end = in + in_len;
    unsigned char const * const ip_end = in + in_len - 9 - 4;
    unsigned char const *ii;
    unsigned char const ** const dict = (unsigned char const **)wrkmem;

    op = out;
    ip = in;
    ii = ip;

    DVAL_FIRST(dv, ip);
    dict[DINDEX(dv)] = ip;
    ip++;
    DVAL_NEXT(dv, ip);
    dict[DINDEX(dv)] = ip;
    ip++;
    DVAL_NEXT(dv, ip);
    dict[DINDEX(dv)] = ip;
    ip++;
    DVAL_NEXT(dv, ip);
    dict[DINDEX(dv)] = ip;
    ip++;

    for (;;) {
        unsigned char const *m_pos;
        int m_off;
        unsigned int m_len;
        unsigned int dindex;

        dindex = DINDEX(dv);
        m_pos = dict[dindex];
        dict[dindex] = ip;

        if (m_pos < in || (m_off = ip - m_pos) <= 0 || m_off > M4_MAX_OFFSET) {
            goto literal;
        }
        if (m_pos[0] != ip[0] || m_pos[1] != ip[1] || m_pos[2] != ip[2]) {
            goto literal;
        }

        {
            unsigned int lit = ip - ii;
            m_pos += 3;
            if (m_off <= M2_MAX_OFFSET) {
                goto match;
            }
            if (lit == 3) {
                op[-2] |= 3;
                *op++ = *ii++;
                *op++ = *ii++;
                *op++ = *ii++;
                goto code_match;
            }
            if (*m_pos != ip[3]) {
                goto literal;
            }

match:
            // Store the literal run before the match.
            if (lit > 0) {
                unsigned int t = lit;
                if (t <= 3) {
                    op[-2] |= (unsigned char)t;
                } else if (t <= 18) {
                    *op++ = (unsigned char)(t - 3);
                } else {
                    unsigned int tt = t - 18;
                    *op++ = 0;
                    while (tt > 255) {
                        tt -= 255;
                        *op++ = 0;
                    }
                    *op++ = (unsigned char)tt;
                }
                do {
                    *op++ = *ii++;
                } while (--t > 0);
            }
        }

code_match:
        // Extend and code the match.
        ip += 3;
        if (*m_pos++ != *ip++ || *m_pos++ != *ip++ || *m_pos++ != *ip++ ||
            *m_pos++ != *ip++ || *m_pos++ != *ip++ || *m_pos++ != *ip++) {
            --ip;
            m_len = ip - ii;

            if (m_off <= M2_MAX_OFFSET) {
                m_off -= 1;
                *op++ = (unsigned char)(((m_len - 1) << 5) | ((m_off & 7) << 2));
                *op++ = (unsigned char)(m_off >> 3);
            } else if (m_off <= M3_MAX_OFFSET) {
                m_off -= 1;
                *op++ = (unsigned char)(M3_MARKER | (m_len - 2));
                goto m3_m4_offset;
            } else {
                m_off -= 0x4000;
                *op++ = (unsigned char)(M4_MARKER | ((m_off & 0x4000) >> 11) | (m_len - 2));
                goto m3_m4_offset;
            }
        } else {
            while (ip < in_end && *m_pos == *ip) {
                m_pos++;
                ip++;
            }
            m_len = ip - ii;

            if (m_off <= M3_MAX_OFFSET) {
                m_off -= 1;
                if (m_len <= 33) {
                    *op++ = (unsigned char)(M3_MARKER | (m_len - 2));
                } else {
                    m_len -= 33;
                    *op++ = M3_MARKER | 0;
                    goto m3_m4_len;
                }
            } else {
                m_off -= 0x4000;
                if (m_len <= M4_MAX_LEN) {
                    *op++ = (unsigned char)(M4_MARKER | ((m_off & 0x4000) >> 11) | (m_len - 2));
                } else {
                    m_len -= M4_MAX_LEN;
                    *op++ = (unsigned char)(M4_MARKER | ((m_off & 0x4000) >> 11));
m3_m4_len:
                    while (m_len > 255) {
                        m_len -= 255;
                        *op++ = 0;
                    }
                    *op++ = (unsigned char)m_len;
                }
            }

m3_m4_offset:
            *op++ = (unsigned char)((m_off & 63) << 2);
            *op++ = (unsigned char)(m_off >> 6);
        }

        ii = ip;
        if (ip >= ip_end) {
            break;
        }
        DVAL_FIRST(dv, ip);
        continue;

literal:
        ip++;
        if (ip >= ip_end) {
            break;
        }
        DVAL_NEXT(dv, ip);
    }

    // Store the final literal run.
    if (in_end - ii > 0) {
        unsigned int t = in_end - ii;
        if (op == out && t <= 238) {
            *op++ = (unsigned char)(17 + t);
        } else if (t <= 3) {
            op[-2] |= (unsigned char)t;
        } else if (t <= 18) {
            *op++ = (unsigned char)(t - 3);
        } else {
            unsigned int tt = t - 18;
            *op++ = 0;
            while (tt > 255) {
                tt -= 255;
                *op++ = 0;
            }
            *op++ = (unsigned char)tt;
        }
        do {
            *op++ = *ii++;
        } while (--t > 0);
    }

    *out_len = op - out;
    return LZO_E_OK;
}
