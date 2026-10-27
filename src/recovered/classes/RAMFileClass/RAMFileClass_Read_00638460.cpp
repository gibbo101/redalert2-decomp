// long RAMFileClass::Read(void *buffer, long size) (0x00638460, slot 9)
// Copies up to size bytes from the current position, opening (and closing
// again) a closed file; 0 when not readable.
#include "shared/ram_file_class.hpp"
#include "shared/crt_string.hpp"

long RAMFileClass::Read(void *buffer, long size)
{
    if (Buffer == 0 || buffer == 0 || size == 0) {
        return 0;
    }
    bool hasopened = false;
    if (!Is_Open()) {
        Open(FILE_RIGHTS_READ);
        hasopened = true;
    } else {
        if ((Access & FILE_RIGHTS_READ) == 0) {
            return 0;
        }
    }
    int tocopy = (size < (Length - Offset)) ? size : (Length - Offset);
    memmove(buffer, &Buffer[Offset], tocopy);
    Offset += tocopy;
    if (hasopened) {
        Close();
    }
    return tocopy;
}
