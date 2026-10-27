// RawFileClass::Write (0x00638E80, virtual slot 12)
// Writes size bytes at the current position. A closed file is opened for
// writing and closed again afterwards. Writing past the end of a bias window
// extends the window. Returns the number of bytes written.
#include "shared/raw_file_class.hpp"

long RawFileClass::Write(void const *buffer, long size)
{
    DWORD bytes_written = 0;
    int opened = false;

    if (!Is_Open()) {
        if (!Open(FILE_RIGHTS_WRITE)) {
            return 0;
        }
        opened = true;
    }
    if (!WriteFile(Handle, buffer, size, &bytes_written, 0)) {
        Error(GetLastError(), false, Filename);
    }
    if (BiasLength != -1) {
        if (Raw_Seek(0) > BiasStart + BiasLength) {
            BiasLength = Raw_Seek(0) - BiasStart;
        }
    }
    if (opened) {
        Close();
    }
    return bytes_written;
}
