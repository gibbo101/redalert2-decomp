// PKey: an RSA public/private key (Westwood's PKey).
//
// Methods in PK.cpp (0x0060ED40+). A key is a modulus and an exponent;
// data is processed in blocks one byte shorter than the modulus
// (Plain_Block_Size) that encrypt to Crypt_Block_Size bytes.
#ifndef RA2_SHARED_PKEY_HPP
#define RA2_SHARED_PKEY_HPP

#include "shared/int.hpp"

class Straw;

class PKey {
public:
    PKey() : Modulus(0), Exponent(0), BitPrecision(0) {}
    PKey(void const *exponent, void const *modulus);                    // 0x0060ED40

    // Encrypt or decrypt length bytes block by block; return the bytes
    // written to dest. Partial blocks are ignored.
    int Encrypt(void const *source, int length, void *dest) const;     // 0x0060F520
    int Decrypt(void const *source, int length, void *dest) const;     // 0x0060F650

    // Creates a key pair of the given modulus size from random data.
    static void __fastcall Generate(Straw &random, int bits, PKey &fastkey, PKey &slowkey);  // 0x0060EE30

    // DER encodings of the key parts; return the bytes written (0 without
    // a buffer).
    int Encode_Modulus(void *buffer) const;                             // 0x0060EDA0
    int Encode_Exponent(void *buffer) const;                            // 0x0060EDC0
    void Decode_Modulus(void *buffer);                                  // 0x0060EDE0
    void Decode_Exponent(void *buffer);                                 // 0x0060EE10

    // Plaintext bytes per block (one byte less than the modulus holds).
    int Plain_Block_Size() const { return (BitPrecision - 1) / 8; }
    // Cyphertext bytes per block.
    int Crypt_Block_Size() const { return Plain_Block_Size() + 1; }
    // Blocks needed for length bytes of plaintext.
    int Block_Count(int length) const { return ((length - 1) / Plain_Block_Size()) + 1; }

    BigInt Modulus;         // +0x000
    BigInt Exponent;        // +0x100
    int BitPrecision;       // +0x200 significant bits of the modulus
};

#endif
