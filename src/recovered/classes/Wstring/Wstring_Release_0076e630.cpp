// void Wstring::Release() (0x0076E630)
// Frees the buffer and leaves the string null.
#include "shared/wstring.hpp"

void Wstring::Release()
{
    if (Buffer) {
        delete[] Buffer;
    }
    Buffer = 0;
}
