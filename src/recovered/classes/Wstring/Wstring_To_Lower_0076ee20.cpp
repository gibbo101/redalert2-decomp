// void Wstring::To_Lower() (0x0076EE20): lowercases A-Z in place.
#include "shared/wstring.hpp"

void Wstring::To_Lower()
{
    for (unsigned index = 0; index < Length(); index++) {
        if (Buffer[index] >= 'A' && Buffer[index] <= 'Z') {
            Buffer[index] = (char)tolower(Buffer[index]);
        }
    }
}
