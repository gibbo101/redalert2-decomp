// RAMFileClass::RAMFileClass(void *buffer, int length) (0x00638310)
// Uses the caller's buffer, or allocates and owns one of length bytes.
#include "shared/ram_file_class.hpp"

RAMFileClass::RAMFileClass(void *buffer, int length) :
    Buffer((char *)buffer),
    MaxLength(length),
    Length(length),
    Offset(0),
    Access(FILE_RIGHTS_READ),
    IsOpen(false),
    IsAllocated(false)
{
    if (buffer == 0 && length > 0) {
        Buffer = new char[length];
        IsAllocated = true;
    }
}
