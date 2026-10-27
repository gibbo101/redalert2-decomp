// void Wstring::Set_Size(int size) (0x0076E650)
// Replaces the contents with `size` zero bytes.
#include "shared/wstring.hpp"

void Wstring::Set_Size(int size)
{
    Release();
    if (size >= 0) {
        Buffer = new char[size];
        memset(Buffer, 0, size);
    }
}
