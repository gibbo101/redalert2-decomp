// LZO1X block compression (Markus Oberhumer's LZO library, as linked into
// the game).
//
// lzo1x_1_compress (0x0053E420) and lzo1x_decompress (0x0053E970) take the
// input pointer in ECX and the input length in EDX with the remaining
// arguments on the stack, so they are declared __fastcall. Identified library
// code; their bodies are not part of this recovery.
#ifndef RA2_SHARED_LZO_HPP
#define RA2_SHARED_LZO_HPP

// Compresses in_len bytes into out; *out_len receives the compressed size.
// wrkmem is a 64 KB scratch dictionary.
int __fastcall lzo1x_1_compress(unsigned char const *in, unsigned int in_len,
                                unsigned char *out, unsigned int *out_len, void *wrkmem);
// Decompresses in_len bytes into out; *out_len receives the output size.
int __fastcall lzo1x_decompress(unsigned char const *in, unsigned int in_len,
                                unsigned char *out, unsigned int *out_len, void *wrkmem);

#endif
