// PKStraw::Get(void *buffer, int length) (0x0060FF10, virtual slot 2)
// Before the first data: decrypting, reads the encrypted Blowfish key,
// decrypts it with the private key and keys the Blowfish stage;
// encrypting, makes a random Blowfish key, encrypts it with the public key
// for output and keys the Blowfish stage. The encrypted key is handed out
// first, then data drawn through the Blowfish stage. Returns the bytes
// delivered (0 if the encrypted key could not be read).
// @ref ?Encrypt@PKey@@QBEHPBXHPAX@Z=0060f520
// @ref ?Decrypt@PKey@@QBEHPBXHPAX@Z=0060f650
// @ref ?Key@BlowStraw@@QAEXPBXH@Z=00435930
#include "shared/pk_straw.hpp"
#include "shared/crt_string.hpp"

int PKStraw::Get(void *buffer, int length)
{
    if (buffer == 0 || length < 1 || CipherKey == 0) {
        return Straw::Get(buffer, length);
    }

    int total = 0;

    if (IsGettingKey) {
        if (Control == DECRYPT) {
            char cbuffer[MAX_KEY_BLOCK_SIZE];
            int got = Straw::Get(cbuffer, Encrypted_Key_Length());
            if (got != Encrypted_Key_Length()) {
                return 0;
            }

            CipherKey->Decrypt(cbuffer, got, Buffer);
            BF.Key(Buffer, BLOWFISH_KEY_SIZE);
        } else {
            char cbuffer[MAX_KEY_BLOCK_SIZE];
            memset(cbuffer, '\0', sizeof(cbuffer));
            Rand.Get(cbuffer, BLOWFISH_KEY_SIZE);

            Counter = BytesLeft = CipherKey->Encrypt(cbuffer, Plain_Key_Length(), Buffer);
            BF.Key(cbuffer, BLOWFISH_KEY_SIZE);
        }
        IsGettingKey = false;
    }

    if (BytesLeft > 0) {
        int count = (length < BytesLeft) ? length : BytesLeft;
        memmove(buffer, &Buffer[Counter - BytesLeft], count);
        buffer = (char *)buffer + count;
        BytesLeft -= count;
        length -= count;
        total += count;
    }

    total += Straw::Get(buffer, length);
    return total;
}
