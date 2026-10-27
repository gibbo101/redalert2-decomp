// lzo1x_1_compress(in, in_len, out, out_len, wrkmem) (0x0053E420)
// LZO1X-1 entry point: inputs of up to 13 bytes are stored as one literal
// run, longer ones are compressed by do_compress (0x0053E490); a successful
// result is terminated with the end-of-stream marker. Returns 0 (LZO_E_OK)
// or the error from do_compress. Identified library code (LZO 1.0x).
// @ref ?do_compress@@YIHPBEIPAEPAIPAX@Z=0053e490
#include "shared/lzo.hpp"

#define LZO_E_OK 0
#define M2_MAX_LEN 8
#define M4_MARKER 16

int __fastcall do_compress(unsigned char const *in, unsigned int in_len,
                           unsigned char *out, unsigned int *out_len, void *wrkmem);

int __fastcall lzo1x_1_compress(unsigned char const *in, unsigned int in_len,
                                unsigned char *out, unsigned int *out_len, void *wrkmem)
{
    unsigned char *op = out;
    int r = LZO_E_OK;

    if (in_len <= 0) {
        *out_len = 0;
    } else if (in_len <= M2_MAX_LEN + 5) {
        *op++ = (unsigned char)(17 + in_len);
        do {
            *op++ = *in++;
        } while (--in_len > 0);
        *out_len = op - out;
    } else {
        r = do_compress(in, in_len, out, out_len, wrkmem);
    }

    if (r == LZO_E_OK) {
        op = out + *out_len;
        *op++ = M4_MARKER | 1;
        *op++ = 0;
        *op++ = 0;
        *out_len += 3;
    }
    return r;
}
