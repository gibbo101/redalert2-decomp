// Int<PRECISION>: fixed-precision integer over the MPMath routines
// (Westwood's INT.H). Inline members; those the compiler emitted out of line
// are listed with the address of their BigInt (Int<64>) instance.
// Error, Carry, Borrow and Remainder are per-instantiation statics
// (Int<64>: 0x00A417C0, 0x00A417C4, 0x00A417C5, 0x00A416C0).
#ifndef RA2_SHARED_INT_HPP
#define RA2_SHARED_INT_HPP

#include "shared/mpmath.hpp"

template<int PRECISION>
class Int {
public:
    Int() { XMP_Init(&reg[0], 0, PRECISION); }
    Int(unsigned long value) { XMP_Init(&reg[0], value, PRECISION); }

    // Random number in [minval, maxval], made odd.
    void Randomize(Straw &rng, Int const &minval, Int const &maxval)    // 0x0060F850
    {
        XMP_Randomize(&reg[0], rng, minval, maxval, PRECISION);
        reg[0] |= 1;
    }

    operator digit *() { return &reg[0]; }
    operator digit const *() const { return &reg[0]; }

    int BitCount() const { return XMP_Count_Bits(&reg[0], PRECISION); }
    bool IsPrime() const { return XMP_Is_Prime(&reg[0], PRECISION); }

    Int &operator+=(Int const &number)                                  // 0x0060F880
    {
        Carry = XMP_Add(&reg[0], &reg[0], number, 0, PRECISION);
        return *this;
    }

    Int operator+(unsigned short b) const                               // 0x0060F8A0
    {
        Int result;
        Carry = XMP_Add_Int(result, &reg[0], b, 0, PRECISION);
        return result;
    }
    Int operator-(unsigned short b) const                                      // 0x0060F7A0
    {
        Int result;
        Borrow = XMP_Sub_Int(result, &reg[0], b, 0, PRECISION);
        return result;
    }
    Int operator*(unsigned short b) const                               // 0x0060F900
    {
        Int result;
        Error = XMP_Unsigned_Mult_Int(result, &reg[0], b, PRECISION);
        return result;
    }
    Int operator<<(int bits) const                                      // 0x0060F950
    {
        Int result = *this;
        XMP_Shift_Left_Bits(result, bits, PRECISION);
        return result;
    }
    bool operator>(Int const &number) const                             // 0x0060F9A0
    {
        return XMP_Compare(&reg[0], number, PRECISION) > 0;
    }

    // Remainder of division by a small divisor (the quotient goes to
    // Remainder).
    unsigned short operator%(unsigned short divisor) const
    {
        return XMP_Unsigned_Div_Int(Remainder, &reg[0], divisor, PRECISION);
    }

    // Modular exponentiation: this ^ e mod m.
    Int exp_b_mod_c(Int const &e, Int const &m) const
    {
        Int result;
        Error = XMP_Exponent_Mod(result, &reg[0], e, m, PRECISION);
        return result;
    }
    // Multiplicative inverse modulo modulus.
    Int Inverse(Int const &modulus) const                               // 0x0060F800
    {
        Int result;
        XMP_Inverse_A_Mod_B(result, &reg[0], modulus, PRECISION);
        return result;
    }

    static Int Unsigned_Mult(Int const &multiplicand, Int const &multiplier)
    {
        Int product;
        Error = XMP_Unsigned_Mult(&product.reg[0], &multiplicand.reg[0], &multiplier.reg[0], PRECISION);
        return product;
    }

    // Distinguished Encoding Rules form; returns the encoded size.
    int DEREncode(unsigned char *output) const { return XMP_DER_Encode(&reg[0], output, PRECISION); }
    void DERDecode(unsigned char const *input) { XMP_DER_Decode(&reg[0], input, PRECISION); }

    static int Error;           // status of the last multiply/exponentiation
    static bool Carry;          // carry out of the last addition
    static bool Borrow;         // borrow out of the last subtraction
    static Int Remainder;       // remainder of the last division

private:
    digit reg[PRECISION];
};

typedef Int<64> BigInt;

// Remainders of a number modulo each small prime of the MPMath prime table,
// kept up to date while the number is stepped, to sieve prime candidates.
template<class T>
class RemainderTable {
public:
    RemainderTable(T const &p) : HasZeroEntry(false)                    // 0x0060F9C0 (BigInt)
    {
        int primesize = XMP_Fetch_Prime_Size();
        unsigned short const *primetable = XMP_Fetch_Prime_Table();
        for (int index = 0; index < primesize; index++) {
            table[index] = p % primetable[index];
        }
    }

    bool HasZero() const { return HasZeroEntry; }

    void Increment(unsigned short increment = 1)                        // 0x0060FA20 (BigInt)
    {
        int primesize = XMP_Fetch_Prime_Size();
        unsigned short const *primetable = XMP_Fetch_Prime_Table();
        HasZeroEntry = false;
        for (int index = 0; index < primesize; index++) {
            table[index] += increment;
            while (table[index] >= primetable[index]) {
                table[index] -= primetable[index];
            }
            HasZeroEntry = (HasZeroEntry || !table[index]);
        }
    }

private:
    bool HasZeroEntry;
    unsigned short table[3511];
};

// A random prime p = 2q + 1 of pbits bits whose q is also prime.
template<class T>
T Generate_Prime(Straw &rng, int pbits, T const *)
{
    T minQ = (T(1UL) << (unsigned short)(pbits - (unsigned short)2));
    T maxQ = ((T(1UL) << (unsigned short)(pbits - (unsigned short)1)) - (unsigned short)1);

    T q;
    T p;

    do {
        q.Randomize(rng, minQ, maxQ);
        p = (q * 2) + (unsigned short)1;

        RemainderTable<T> rtQ(q);
        RemainderTable<T> rtP(p);

        while (rtQ.HasZero() || rtP.HasZero() || !q.IsPrime() || !p.IsPrime()) {
            q += 2;
            p += 4;
            if (q > maxQ) {
                break;
            }

            rtQ.Increment(2);
            rtP.Increment(4);
        }
    } while (q > maxQ);

    return p;
}

#endif
