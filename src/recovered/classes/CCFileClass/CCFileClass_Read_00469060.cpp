// CCFileClass::Read (0x00469060, virtual slot 9)
// Reads from memory when the file is resident, otherwise from disk. A
// closed file is opened (and closed again) around the read.
#include "shared/cc_file_class.hpp"
#include "shared/crt_string.hpp"

long CCFileClass::Read(void *buffer, long size)
{
    bool opened = false;
    if (!Is_Open()) {
        if (Open()) {
            opened = true;
        }
    }
    if (Data.Get_Buffer() != 0) {
        long maximum = Data.Get_Size() - Position;
        if (maximum < size) {
            size = maximum;
        }
        if (size) {
            memmove(buffer, (char *)Data.Get_Buffer() + Position, size);
            Position += size;
        }
        if (opened) {
            Close();
        }
        return size;
    }
    size = CDFileClass::Read(buffer, size);
    if (opened) {
        Close();
    }
    return size;
}
