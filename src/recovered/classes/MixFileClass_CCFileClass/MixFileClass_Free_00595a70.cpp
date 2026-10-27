// void MixFileClass<T>::Free() (0x00595A70)
// Releases the cached data (when owned) and forgets it.
#include "shared/mix_file_class.hpp"

class CCFileClass;

template <class T>
void MixFileClass<T>::Free()
{
    if (Data && IsAllocated) {
        delete[] (char *)Data;
    }
    Data = 0;
    IsAllocated = false;
}
