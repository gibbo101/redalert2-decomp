// PKPipe::Key(PKey const *key) (0x0060FB40)
// Sets the key and restarts the key exchange; a null key flushes the pipe
// and turns encryption off. Decrypting, the encrypted Blowfish key length
// is expected first.
#include "shared/pk_pipe.hpp"

void PKPipe::Key(PKey const *key)
{
    if (key == 0) {
        Flush();
        IsGettingKey = false;
    }
    CipherKey = key;

    if (CipherKey != 0) {
        IsGettingKey = true;
        if (Control == DECRYPT) {
            Counter = BytesLeft = Encrypted_Key_Length();
        }
    }
}
