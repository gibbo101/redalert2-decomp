// Wstring::Wstring(Wstring const &other) : (0x0076D980)
// Copy constructor; a null source stays null.
#include "shared/wstring.hpp"

Wstring::Wstring(Wstring const &other) :
    Buffer(0)
{
    if (other.Buffer) {
        Buffer = new char[strlen(other.Buffer) + 1];
        strcpy(Buffer, other.Buffer);
    }
}
