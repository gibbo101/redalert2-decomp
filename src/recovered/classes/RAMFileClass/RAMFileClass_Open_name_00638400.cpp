// int RAMFileClass::Open(char const *filename, int access) (0x00638400, slot 8): the name is ignored.
#include "shared/ram_file_class.hpp"

int RAMFileClass::Open(char const *, int access)
{
    return Open(access);
}
