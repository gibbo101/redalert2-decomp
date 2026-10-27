// bool Wstring::Set_Char(char character, unsigned index) (0x0076EDA0)
// Replaces the character at index; false when index is past the end.
#include "shared/wstring.hpp"

bool Wstring::Set_Char(char character, unsigned index)
{
    if (index >= strlen(Buffer)) {
        return false;
    }
    Buffer[index] = character;
    return true;
}
