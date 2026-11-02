// bool __fastcall MixFileClass::Cache(char const *filename, Buffer const *buffer) (0x00595770)
// Caches the named registered archive; false when it is not registered.
// @ref ?Cache@MixFileClass@@QAE_NPBVBuffer@@@Z=00595810
#include "shared/mix_file_class.hpp"

class CCFileClass;

bool __fastcall MixFileClass::Cache(char const *filename, Buffer const *buffer)
{
    MixFileClass *ptr = Finder(filename);
    if (ptr) {
        return ptr->Cache(buffer);
    }
    return false;
}
