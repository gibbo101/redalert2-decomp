// bool Wstring::Remove(int position, int count) (0x0076E310)
// Deletes a clamped window of characters.
#include "shared/wstring.hpp"

bool Wstring::Remove(int position, int count)
{
    int length = strlen(Buffer);
    // As observed: an overlong window moves its start back, not its end.
    if (position + count > length) {
        position = length - count;
    }
    if (position < 0) {
        count += position;
        position = 0;
    }
    if (count <= 0) {
        return false;
    }
    char *result = new char[length - count + 1];
    Buffer[position] = '\0';
    Buffer[position + count - 1] = '\0';
    strcpy(result, Buffer);
    strcat(result, Buffer + position + count);
    delete[] Buffer;
    Buffer = result;
    return true;
}
