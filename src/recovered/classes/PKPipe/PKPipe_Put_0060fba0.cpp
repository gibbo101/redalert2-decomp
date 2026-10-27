// PKPipe::Put(void const *source, int length) (0x0060FBA0, virtual slot 4)
// Before the first data: encrypting, makes a random Blowfish key, sends it
// encrypted with the public key and keys the Blowfish stage; decrypting,
// gathers the encrypted Blowfish key, decrypts it with the private key and
// keys the Blowfish stage. All other data goes to the Blowfish stage.
// Returns the bytes passed down the chain.
// @ref ?Encrypt@PKey@@QBEHPBXHPAX@Z=0060f520
// @ref ?Decrypt@PKey@@QBEHPBXHPAX@Z=0060f650
// @ref ?Key@BlowPipe@@QAEXPBXH@Z=00435800
#include "shared/pk_pipe.hpp"
#include "shared/crt_string.hpp"

int PKPipe::Put(void const *source, int length)
{
    if (source == 0 || length < 1 || CipherKey == 0) {
        return Pipe::Put(source, length);
    }

    int total = 0;

    if (IsGettingKey) {
        if (Control == ENCRYPT) {
            char buffer[MAX_KEY_BLOCK_SIZE];
            memset(buffer, '\0', sizeof(buffer));
            Rand.Get(buffer, BLOWFISH_KEY_SIZE);
            int didput = CipherKey->Encrypt(buffer, Plain_Key_Length(), Buffer);
            total += Pipe::Put(Buffer, didput);
            BF.Key(buffer, BLOWFISH_KEY_SIZE);
            IsGettingKey = false;
        } else {
            int toget = (BytesLeft < length) ? BytesLeft : length;
            memmove(&Buffer[Counter - BytesLeft], source, toget);
            length -= toget;
            BytesLeft -= toget;
            source = (char const *)source + toget;

            if (BytesLeft == 0) {
                char buffer[MAX_KEY_BLOCK_SIZE];
                CipherKey->Decrypt(Buffer, Counter, buffer);
                BF.Key(buffer, BLOWFISH_KEY_SIZE);
                IsGettingKey = false;
            }
        }
    }

    total += Pipe::Put(source, length);
    return total;
}
