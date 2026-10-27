// BlowStraw::Get(void *buffer, int length) (0x00435840, virtual slot 2)
// Hands out processed bytes, refilling 8-byte blocks from the chained straw.
// A full block is encrypted or decrypted in place; a short final block is
// moved to the end of Buffer unprocessed. Without an engine the data passes
// through unchanged. Returns the bytes delivered.
// @ref ?Encrypt@BlowfishEngine@@QAEHPBXHPAX@Z=00435630
// @ref ?Decrypt@BlowfishEngine@@QAEHPBXHPAX@Z=00435660
#include "shared/blow_straw.hpp"
#include "shared/crt_string.hpp"

int BlowStraw::Get(void *buffer, int length)
{
    if (buffer == 0 || length <= 0) {
        return 0;
    }

    if (BF == 0) {
        return Straw::Get(buffer, length);
    }

    int total = 0;
    while (length > 0) {
        if (Counter > 0) {
            int count = (length < Counter) ? length : Counter;
            memmove(buffer, &Buffer[sizeof(Buffer) - Counter], count);
            Counter -= count;
            buffer = (char *)buffer + count;
            length -= count;
            total += count;
        }
        if (length == 0) {
            break;
        }

        int incount = Straw::Get(Buffer, sizeof(Buffer));
        if (incount == 0) {
            break;
        }

        if (incount == sizeof(Buffer)) {
            if (Control == DECRYPT) {
                BF->Decrypt(Buffer, incount, Buffer);
            } else {
                BF->Encrypt(Buffer, incount, Buffer);
            }
        } else {
            memmove(&Buffer[sizeof(Buffer) - incount], Buffer, incount);
        }
        Counter = incount;
    }
    return total;
}
