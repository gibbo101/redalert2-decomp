// Westwood's multi-precision integer library (MPMath.cpp, 0x005A7530+).
//
// Numbers are little-endian arrays of 32-bit digits (two's complement);
// every routine takes the precision (digit count) last. The routines are
// __fastcall (first two arguments in ECX/EDX).
#ifndef RA2_SHARED_MPMATH_HPP
#define RA2_SHARED_MPMATH_HPP

class Straw;

typedef unsigned long digit;

#define UNITSIZE 32
#define UPPER_MOST_BIT 0x80000000UL
#define MAX_UNIT_PRECISION 64


unsigned short const * __fastcall XMP_Fetch_Prime_Table();                          // 0x005A7530
int __fastcall XMP_Fetch_Prime_Size();                                              // 0x005A7540
int __fastcall XMP_Test_Eq_Int(digit const *number, int value, int precision);     // 0x005A7550
int __fastcall XMP_DER_Length_Encode(unsigned long length, unsigned char *output); // 0x005A7590
int __fastcall XMP_DER_Encode(digit const *from, unsigned char *output, int precision);         // 0x005A7610
void __fastcall XMP_DER_Decode(digit *result, unsigned char const *input, int precision);       // 0x005A76D0
unsigned __fastcall XMP_Encode(unsigned char *to, unsigned tobytes, digit const *from, int precision);  // 0x005A7750
int __fastcall XMP_Encode(unsigned char *to, digit const *from, int precision);                // 0x005A77F0
void __fastcall XMP_Signed_Decode(digit *result, unsigned char const *from, int frombytes, int precision);   // 0x005A7860
void __fastcall XMP_Unsigned_Decode(digit *result, unsigned char const *from, int frombytes, int precision); // 0x005A78B0
int __fastcall XMP_Significance(digit const *number, int precision);               // 0x005A78F0
void __fastcall XMP_Inc(digit *number, int precision);                             // 0x005A7910
void __fastcall XMP_Dec(digit *number, int precision);                             // 0x005A7930
void __fastcall XMP_Neg(digit *number, int precision);                             // 0x005A7950
void __fastcall XMP_Abs(digit *number, int precision);                             // 0x005A7980
void __fastcall XMP_Shift_Right_Bits(digit *number, int bits, int precision);      // 0x005A79C0
void __fastcall XMP_Shift_Left_Bits(digit *number, int bits, int precision);       // 0x005A7B00
bool __fastcall XMP_Rotate_Left(digit *number, bool carry, int precision);         // 0x005A7C40
void __fastcall XMP_Not(digit *number, int precision);                             // 0x005A7C80
void __fastcall XMP_Init(digit *number, digit value, int precision);               // 0x005A7CA0
int __fastcall XMP_Count_Bits(digit const *number, int precision);                 // 0x005A7CC0
int __fastcall XMP_Count_Bytes(digit const *number, int precision);                // 0x005A7D00
void __fastcall XMP_Move(digit *dest, digit const *source, int precision);         // 0x005A7D20
int __fastcall XMP_Compare(digit const *left, digit const *right, int precision);  // 0x005A7D40
bool __fastcall XMP_Add(digit *result, digit const *left, digit const *right, bool carry, int precision);           // 0x005A7D90
bool __fastcall XMP_Add_Int(digit *result, digit const *left, digit right, bool carry, int precision);             // 0x005A7E00
bool __fastcall XMP_Sub(digit *result, digit const *left, digit const *right, bool borrow, int precision);         // 0x005A7E60
bool __fastcall XMP_Sub_Int(digit *result, digit const *left, unsigned short right, bool borrow, int precision);   // 0x005A7EC0
int __fastcall XMP_Unsigned_Mult(digit *product, digit const *multiplicand, digit const *multiplier, int precision);  // 0x005A7F20
int __fastcall XMP_Unsigned_Mult_Int(digit *product, digit const *multiplicand, short multiplier, int precision);  // 0x005A80F0
int __fastcall XMP_Signed_Mult_Int(digit *product, digit const *multiplicand, signed short multiplier, int precision);  // 0x005A8130
int __fastcall XMP_Signed_Mult(digit *product, digit const *multiplicand, digit const *multiplier, int precision);  // 0x005A8340
unsigned short __fastcall XMP_Unsigned_Div_Int(digit *quotient, digit const *dividend, unsigned short divisor, int precision); // 0x005A8540
int __fastcall XMP_Unsigned_Div(digit *remainder, digit *quotient, digit const *dividend, digit const *divisor, int precision);  // 0x005A8670
void __fastcall XMP_Signed_Div(digit *remainder, digit *quotient, digit const *dividend, digit const *divisor, int precision);  // 0x005A8880
void __fastcall XMP_Inverse_A_Mod_B(digit *result, digit const *number, digit const *modulus, int precision);       // 0x005A8AA0
int __fastcall XMP_Reciprocal(digit *quotient, digit const *divisor, int precision);                              // 0x005A8CF0
void __fastcall XMP_Decode_ASCII(char const *str, digit *number, int precision);                                  // 0x005A8F00
void __fastcall XMP_Single_Mul(unsigned short *prod, unsigned short const *multiplicand, unsigned short multiplier, int precision);   // 0x005A9110
void __fastcall XMP_Double_Mul(digit *prod, digit const *multiplicand, digit const *multiplier, int precision);  // 0x005A9160
int __fastcall XMP_Prepare_Modulus(digit const *modulus, int precision);                                          // 0x005A9220
int __fastcall XMP_Mod_Mult(digit *prod, digit const *multiplicand, digit const *multiplier, int precision);     // 0x005A9400
void __fastcall XMP_Mod_Mult_Clear(int precision);                                                                // 0x005A9720
unsigned short __fastcall mp_quo_digit(unsigned short const *dividend);                                          // 0x005A97D0
int __fastcall XMP_Exponent_Mod(digit *result, digit const *base, digit const *exponent, digit const *modulus, int precision);   // 0x005A9860
void __fastcall memrev(char *buffer, unsigned int length);                                                         // 0x005A9BD0
int __fastcall pfunc(void const *key, void const *element);                                                       // 0x005A9BF0
bool __fastcall XMP_Is_Small_Prime(digit const *candidate, int precision);                                        // 0x005A9C10
bool __fastcall XMP_Small_Divisors_Test(digit const *candidate, int precision);                                   // 0x005A9C90
bool __fastcall XMP_Fermat_Test(digit const *candidate, unsigned rounds, int precision);                          // 0x005A9CE0
bool __fastcall XMP_Rabin_Miller_Test(Straw &rng, digit const *w, int rounds, int precision);                     // 0x005A9E10
void __fastcall XMP_Randomize(digit *result, Straw &rng, int nbits, int precision);                               // 0x005AA130
void __fastcall XMP_Randomize(digit *result, Straw &rng, digit const *minval, digit const *maxval, int precision);   // 0x005AA1A0
bool __fastcall XMP_Is_Prime(digit const *number, int precision);                   // 0x005AA380

inline digit XMP_Bit_Mask(int bits)
{
    if (bits == 0) {
        return 0;
    }
    return 1L << ((bits - 1) % UNITSIZE);
}

inline bool XMP_Test_Bit(digit const *number, unsigned bit)
{
    return (number[bit >> 5] & (1L << (bit & 31))) != 0;
}

inline void XMP_Set_Bit(digit *number, unsigned bit)
{
    number[bit >> 5] |= 1L << (bit & 31);
}

inline bool XMP_Is_Negative(digit const *number, int precision)
{
    return (signed long)number[precision - 1] < 0;
}

#endif
