// SHAEngine: SHA-1 message digest (Westwood's SHAEngine).
//
// Methods in SHA.cpp (0x00674BF0+). Data is hashed in 64-byte blocks;
// partial blocks are staged in Partial. Result pads a copy of the state, so
// hashing can continue afterwards. Layout from the inline constructor
// (initial accumulator 67452301 EFCDAB89 98BADCFE 10325476 C3D2E1F0).
#ifndef RA2_SHARED_SHA_HPP
#define RA2_SHARED_SHA_HPP

class SHAEngine {
public:
    SHAEngine() : IsCached(false), Length(0), PartialCount(0)
    {
        Acc.Long[0] = SA;
        Acc.Long[1] = SB;
        Acc.Long[2] = SC;
        Acc.Long[3] = SD;
        Acc.Long[4] = SE;
    }

    // Adds length bytes to the digest.
    void Hash(void const *data, long length);       // 0x00674C90
    // Writes the 20-byte digest; returns its size.
    int Result(void *result) const;                 // 0x00674D10

    enum {
        SA = 0x67452301L,
        SB = 0xEFCDAB89L,
        SC = 0x98BADCFEL,
        SD = 0x10325476L,
        SE = 0xC3D2E1F0L,

        K1 = 0x5A827999L,
        K2 = 0x6ED9EBA1L,
        K3 = 0x8F1BBCDCL,
        K4 = 0xCA62C1D6L,

        SRC_BLOCK_SIZE = 16 * sizeof(long),     // source bytes per block
        PROC_BLOCK_SIZE = 80 * sizeof(long)     // expanded block
    };

    typedef union {
        unsigned long Long[5];
        unsigned char Char[20];
    } SHADigest;

    bool IsCached;              // +0x00 FinalResult is current
    SHADigest FinalResult;      // +0x04 cached digest
    SHADigest Acc;              // +0x18 running accumulator
    long Length;                // +0x2C bytes hashed in whole blocks
    int PartialCount;           // +0x30 bytes held in Partial
    char Partial[64];           // +0x34 incomplete source block

private:
    // Moves source bytes into Partial when a block is partly staged or the
    // source is shorter than a block; hashes Partial once full.
    void Process_Partial(void const *&data, long &length);                 // 0x00674BF0
    // Hashes one 64-byte block into acc.
    void Process_Block(void const *source, SHADigest &acc) const;          // 0x00674E60

    // The SHA-1 round constant and round function for step index.
    long Get_Constant(int index) const
    {
        if (index < 20) return K1;
        if (index < 40) return K2;
        if (index < 60) return K3;
        return K4;
    }
    long Function1(long X, long Y, long Z) const { return Z ^ (X & (Y ^ Z)); }
    long Function2(long X, long Y, long Z) const { return X ^ Y ^ Z; }
    long Function3(long X, long Y, long Z) const { return (X & Y) | (Z & (X | Y)); }
    long Function4(long X, long Y, long Z) const { return X ^ Y ^ Z; }
    long Do_Function(int index, long X, long Y, long Z) const
    {
        if (index < 20) return Function1(X, Y, Z);
        if (index < 40) return Function2(X, Y, Z);
        if (index < 60) return Function3(X, Y, Z);
        return Function4(X, Y, Z);
    }
};

#endif
