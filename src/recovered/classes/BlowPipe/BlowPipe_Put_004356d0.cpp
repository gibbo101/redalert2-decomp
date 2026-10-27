// BlowPipe::Put(void const *source, int length) (0x004356D0, virtual slot 4)
// Encrypts or decrypts whole 8-byte blocks and passes them on, holding any
// remainder until more data arrives. Without an engine the data passes
// through unchanged. Returns the bytes passed down the chain.
// @ref ?Encrypt@BlowfishEngine@@QAEHPBXHPAX@Z=00435630
// @ref ?Decrypt@BlowfishEngine@@QAEHPBXHPAX@Z=00435660
#include "shared/blow_pipe.hpp"
#include "shared/crt_string.hpp"

int BlowPipe::Put(void const *source, int length)
{
    if (source == 0 || length < 1) {
        return Pipe::Put(source, length);
    }

    if (BF == 0) {
        return Pipe::Put(source, length);
    }

    int total = 0;

    // Complete a held partial block first.
    if (Counter) {
        int count = sizeof(Buffer) - Counter;
        count = (count < length) ? count : length;
        memmove(&Buffer[Counter], source, count);
        Counter += count;
        source = (char const *)source + count;
        length -= count;

        if (Counter == sizeof(Buffer)) {
            if (Control == DECRYPT) {
                BF->Decrypt(Buffer, Counter, Buffer);
            } else {
                BF->Encrypt(Buffer, Counter, Buffer);
            }
            total += Pipe::Put(Buffer, sizeof(Buffer));
            Counter = 0;
        }
    }

    // Process whole blocks straight from the source.
    while (length >= sizeof(Buffer)) {
        if (Control == DECRYPT) {
            BF->Decrypt(source, sizeof(Buffer), Buffer);
        } else {
            BF->Encrypt(source, sizeof(Buffer), Buffer);
        }
        total += Pipe::Put(Buffer, sizeof(Buffer));
        source = (char const *)source + sizeof(Buffer);
        length -= sizeof(Buffer);
    }

    // Hold the remainder.
    if (length > 0) {
        memmove(Buffer, source, length);
        Counter = length;
    }

    return total;
}
