// RAMFileClass::~RAMFileClass() (0x00638360): closes and frees an owned buffer.
#include "shared/ram_file_class.hpp"

RAMFileClass::~RAMFileClass()
{
    Close();
    if (IsAllocated) {
        delete [] Buffer;
        Buffer = 0;
        IsAllocated = false;
    }
}
