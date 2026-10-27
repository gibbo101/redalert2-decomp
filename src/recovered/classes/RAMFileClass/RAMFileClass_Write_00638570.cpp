// long RAMFileClass::Write(void const *buffer, long size) (0x00638570, slot 12)
// Copies up to size bytes at the current position (within the capacity),
// opening (and closing again) a closed file; 0 when not writable.
#include "shared/ram_file_class.hpp"
#include "shared/crt_string.hpp"

long RAMFileClass::Write(void const *buffer, long size)
{
    if (Buffer == 0 || buffer == 0 || size == 0) {
        return 0;
    }
    bool hasopened = false;
    if (!Is_Open()) {
        Open(FILE_RIGHTS_WRITE);
        hasopened = true;
    } else {
        if ((Access & FILE_RIGHTS_WRITE) == 0) {
            return 0;
        }
    }
    int maxwrite = MaxLength - Offset;
    int towrite = (size < maxwrite) ? size : maxwrite;
    memmove(&Buffer[Offset], buffer, towrite);
    Offset += towrite;
    if (Offset > Length) {
        Length = Offset;
    }
    if (hasopened) {
        Close();
    }
    return towrite;
}
