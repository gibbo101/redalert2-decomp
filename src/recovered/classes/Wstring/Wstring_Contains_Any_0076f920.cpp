// bool Wstring::Contains_Any(char const *characters) const (0x0076F920)
// Whether the text contains any of characters (strcspn stops before the
// end); false for no characters or no text.
#include "shared/wstring.hpp"

bool Wstring::Contains_Any(char const *characters) const
{
    if (characters && Buffer) {
        unsigned length = strlen(Buffer);
        return strcspn(Buffer, characters) < length;
    }
    return false;
}
