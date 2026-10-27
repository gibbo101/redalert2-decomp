// BlowPipe: a Pipe that Blowfish encrypts or decrypts the data put into it.
//
// Name from RTTI (vtable 0x007A81A0, base Pipe); methods in BlowPipe.cpp
// (0x00435690+). Data is processed in 8-byte blocks; without a key (no
// engine) it passes through unchanged. The constructor and destructor are
// inline: the scalar deleting destructor the linker kept (0x0060FD70) was
// compiled with PKPipe.
#ifndef RA2_SHARED_BLOW_PIPE_HPP
#define RA2_SHARED_BLOW_PIPE_HPP

#include "shared/pipe.hpp"
#include "shared/blowfish_engine.hpp"

class BlowPipe : public Pipe {
public:
    // Direction of the data transformation.
    typedef enum CryptControl {
        ENCRYPT,
        DECRYPT
    } CryptControl;

    BlowPipe(CryptControl control) : BF(0), Counter(0), Control(control) {}
    virtual ~BlowPipe() { delete BF; BF = 0; }
    virtual int Flush();                                    // 0x00435690
    virtual int Put(void const *source, int length);        // 0x004356D0

    // Creates the engine if needed and sets the key.
    void Key(void const *key, int length);                  // 0x00435800

    BlowfishEngine *BF;     // +0x0C cipher engine (null: pass through)
    char Buffer[8];         // +0x10 partial block
    int Counter;            // +0x18 bytes held in Buffer
    CryptControl Control;   // +0x1C encrypting or decrypting
};

#endif
