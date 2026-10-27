// PKStraw: a Straw that public-key encrypts or decrypts a stream.
//
// Name from RTTI (vtable 0x007A81B8, base Straw); methods in PKStraw.cpp
// (0x0060FE30+). Same format as PKPipe: an encrypted 56-byte Blowfish key,
// then the Blowfish encrypted stream, which is drawn through the embedded
// BlowStraw.
#ifndef RA2_SHARED_PK_STRAW_HPP
#define RA2_SHARED_PK_STRAW_HPP

#include "shared/straw.hpp"
#include "shared/blow_straw.hpp"
#include "shared/pkey.hpp"
#include "shared/random_straw.hpp"

class PKStraw : public Straw {
public:
    // Direction of the data transformation.
    typedef enum CryptControl {
        ENCRYPT,
        DECRYPT
    } CryptControl;

    PKStraw(CryptControl control, RandomStraw &rnd);        // 0x0060FE30
    virtual void Get_From(Straw *straw);                    // 0x0060FEA0
    virtual void Get_From(Straw &straw) { Get_From(&straw); }   // 0x00610140
    virtual int Get(void *buffer, int length);              // 0x0060FF10

    // Sets the public (encrypting) or private (decrypting) key.
    void Key(PKey const *key);                              // 0x0060FEF0

    enum {
        BLOWFISH_KEY_SIZE = 56,
        MAX_KEY_BLOCK_SIZE = 256
    };

    bool IsGettingKey;          // +0x0C the Blowfish key is still to be made or read
    RandomStraw &Rand;          // +0x10 source of the Blowfish key
    BlowStraw BF;               // +0x14 Blowfish stage of the input
    CryptControl Control;       // +0x34 encrypting or decrypting
    PKey const *CipherKey;      // +0x38 key (null: pass through)
    char Buffer[256];           // +0x3C encrypted Blowfish key
    int Counter;                // +0x13C encrypted key length
    int BytesLeft;              // +0x140 encrypted key bytes still to hand out

private:
    int Encrypted_Key_Length() const;                       // 0x006100E0
    int Plain_Key_Length() const;                           // 0x00610110
};

#endif
