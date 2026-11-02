// MixFileClass::~MixFileClass() (0x00595620)
// Frees the name, the cache and the index, then leaves the archive list.
// @ref ??_7MixFileClass@@6B@=007a6470
// @ref ??_GMixFileClass@@UAEPAXI@Z=00595c60
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
#include "shared/mix_file_class.hpp"

class CCFileClass;

MixFileClass::~MixFileClass()
{
    if (Filename) {
        free((char *)Filename);
    }
    if (Data && IsAllocated) {
        delete[] (char *)Data;
        IsAllocated = false;
    }
    Data = 0;
    if (HeaderBuffer) {
        delete[] HeaderBuffer;
        HeaderBuffer = 0;
    }
    Unlink();
}
