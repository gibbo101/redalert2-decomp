// RawFileClass::Size (0x00639180, virtual slot 11)
// Returns the file length: the bias window length when one is set, otherwise
// the disk size. A closed file is opened temporarily to measure it.
#include "shared/raw_file_class.hpp"

long RawFileClass::Size()
{
    long size = 0;
    if (BiasLength != -1) {
        return BiasLength;
    }
    if (Is_Open()) {
        size = GetFileSize(Handle, 0);
        if (size == -1) {
            Error(GetLastError(), false, Filename);
        }
    } else if (Open()) {
        size = Size();
        Close();
    }
    BiasLength = size - BiasStart;
    return BiasLength;
}
