// PKPipe::Plain_Key_Length() const (0x0060FD40)
// Size of the Blowfish key padded to whole plaintext blocks of the key
// (0 without a key).
#include "shared/pk_pipe.hpp"

int PKPipe::Plain_Key_Length() const
{
    if (CipherKey == 0) {
        return 0;
    }
    return CipherKey->Block_Count(BLOWFISH_KEY_SIZE) * CipherKey->Plain_Block_Size();
}
