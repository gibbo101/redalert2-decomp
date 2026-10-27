// bool __fastcall MixFileClass<T>::Free(char const *filename) (0x00595560)
// Releases the cache of the named registered archive; false when it is not registered.
#include "shared/mix_file_class.hpp"

class CCFileClass;

template <class T>
bool __fastcall MixFileClass<T>::Free(char const *filename)
{
    MixFileClass<T> *ptr = Finder(filename);
    if (ptr) {
        ptr->Free();
        return true;
    }
    return false;
}
