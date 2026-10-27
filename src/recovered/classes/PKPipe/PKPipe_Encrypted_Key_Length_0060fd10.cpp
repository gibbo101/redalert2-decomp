// PKPipe::Encrypted_Key_Length() const (0x0060FD10)
// Size of the Blowfish key once encrypted with the key (0 without a key).
#include "shared/pk_pipe.hpp"

int PKPipe::Encrypted_Key_Length() const
{
    if (CipherKey == 0) {
        return 0;
    }
    return CipherKey->Block_Count(BLOWFISH_KEY_SIZE) * CipherKey->Crypt_Block_Size();
}
