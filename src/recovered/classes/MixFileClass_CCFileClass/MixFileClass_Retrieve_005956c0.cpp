// void const *__fastcall MixFileClass::Retrieve(char const *filename) (0x005956C0)
// Pointer to a member inside a cached archive, or null.
// Compiled alone: the original calls Offset out of line, which VC6 inlines
// when Offset is defined in the same translation unit.
// @ref ?Offset@MixFileClass@@SI_NPBDPAPAXPAPAV1@PAJ3@Z=00595aa0
#include "shared/mix_file_class.hpp"

class CCFileClass;

void const *__fastcall MixFileClass::Retrieve(char const *filename)
{
    void *ptr = 0;
    Offset(filename, &ptr);
    return ptr;
}

