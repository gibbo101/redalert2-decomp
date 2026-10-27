// BlowStraw: a Straw that Blowfish encrypts or decrypts the data drawn
// through it.
//
// Name from RTTI (vtable 0x007A6460, base Straw); methods in BlowStraw.cpp
// (0x00435840+). Data is processed in 8-byte blocks; a short final block is
// passed through unchanged, as is everything without a key. The constructor
// and destructor are inline: the scalar deleting destructor the linker kept
// (0x00595BF0) was compiled with MixFileClass.
#ifndef RA2_SHARED_BLOW_STRAW_HPP
#define RA2_SHARED_BLOW_STRAW_HPP

#include "shared/straw.hpp"
#include "shared/blowfish_engine.hpp"

class BlowStraw : public Straw {
public:
    // Direction of the data transformation.
    typedef enum CryptControl {
        ENCRYPT,
        DECRYPT
    } CryptControl;

    BlowStraw(CryptControl control) : BF(0), Counter(0), Control(control) {}
    virtual ~BlowStraw() { delete BF; BF = 0; }
    virtual int Get(void *buffer, int length);              // 0x00435840

    // Creates the engine if needed and sets the key.
    void Key(void const *key, int length);                  // 0x00435930

    BlowfishEngine *BF;     // +0x0C cipher engine (null: pass through)
    char Buffer[8];         // +0x10 processed block, consumed from the end
    int Counter;            // +0x18 bytes of Buffer still to hand out
    CryptControl Control;   // +0x1C encrypting or decrypting
};

#endif
