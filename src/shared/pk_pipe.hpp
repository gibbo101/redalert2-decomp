// PKPipe: a Pipe that public-key encrypts a stream.
//
// Name from RTTI (vtable 0x007A8184, base Pipe); methods in PKPipe.cpp
// (0x0060FA90+). Encrypting, a random 56-byte Blowfish key is drawn from
// Rand, encrypted with the public key and sent first; the rest of the
// stream is Blowfish encrypted with it. Decrypting reverses this. The pipe
// routes its output through the embedded BlowPipe.
#ifndef RA2_SHARED_PK_PIPE_HPP
#define RA2_SHARED_PK_PIPE_HPP

#include "shared/pipe.hpp"
#include "shared/blow_pipe.hpp"
#include "shared/pkey.hpp"
#include "shared/random_straw.hpp"

class PKPipe : public Pipe {
public:
    // Direction of the data transformation.
    typedef enum CryptControl {
        ENCRYPT,
        DECRYPT
    } CryptControl;

    PKPipe(CryptControl control, RandomStraw &rnd);         // 0x0060FA90
    virtual void Put_To(Pipe *pipe);                        // 0x0060FAF0
    virtual void Put_To(Pipe &pipe) { Put_To(&pipe); }      // 0x0060FDC0
    virtual int Put(void const *source, int length);        // 0x0060FBA0

    // Sets the public (encrypting) or private (decrypting) key.
    void Key(PKey const *key);                              // 0x0060FB40

    enum {
        BLOWFISH_KEY_SIZE = 56,
        MAX_KEY_BLOCK_SIZE = 256
    };

    bool IsGettingKey;          // +0x0C the Blowfish key is still to be sent or read
    RandomStraw &Rand;          // +0x10 source of the Blowfish key
    BlowPipe BF;                // +0x14 Blowfish stage of the output
    CryptControl Control;       // +0x34 encrypting or decrypting
    PKey const *CipherKey;      // +0x38 key (null: pass through)
    char Buffer[256];           // +0x3C encrypted Blowfish key
    int Counter;                // +0x13C encrypted key length
    int BytesLeft;              // +0x140 encrypted key bytes still to read

private:
    int Encrypted_Key_Length() const;                       // 0x0060FD10
    int Plain_Key_Length() const;                           // 0x0060FD40
};

#endif
