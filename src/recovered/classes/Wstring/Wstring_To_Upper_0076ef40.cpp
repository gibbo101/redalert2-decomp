// void Wstring::To_Upper() (0x0076EF40): uppercases a-z in place.
#include "shared/wstring.hpp"

void Wstring::To_Upper()
{
    for (unsigned index = 0; index < Length(); index++) {
        if (Buffer[index] >= 'a' && Buffer[index] <= 'z') {
            Buffer[index] = (char)toupper(Buffer[index]);
        }
    }
}
