// Wstring::~Wstring() (0x0076D9E0)
// Frees the buffer.
#include "shared/wstring.hpp"

Wstring::~Wstring()
{
    Release();
}
