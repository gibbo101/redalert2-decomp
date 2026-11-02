// MixFileClass *__fastcall MixFileClass::Finder(char const *filename) (0x005956E0)
// First registered archive whose name and extension equal filename (case-insensitive).
// @ref __splitpath=00784873
// @ref __makepath=007831f0
// @ref __stricmp=00781f20
// @ref ?MixList@MixFileClass@@2V?$List@PAVMixFileClass@@@@A=00a70cc0
#include "shared/mix_file_class.hpp"

class CCFileClass;

MixFileClass *__fastcall MixFileClass::Finder(char const *filename)
{
    MixFileClass *ptr = MixList.First();
    while (ptr->Is_Valid()) {
        char path[260];
        char name[256];
        char extension[256];
        _splitpath(ptr->Filename, 0, 0, name, extension);
        _makepath(path, 0, 0, name, extension);
        if (_stricmp(path, filename) == 0) {
            return ptr;
        }
        ptr = ptr->Next();
    }
    return 0;
}
