// RawFileClass::Read (0x00638D90, virtual slot 9)
// Reads up to size bytes, limited to the rest of the bias window. A closed
// file is opened for reading and closed again afterwards. ReadFile failures
// are reported through Error() (retry allowed) unless RawFileReadStopOnError
// asks to stop. Returns the number of bytes read.
#include "shared/raw_file_class.hpp"

long RawFileClass::Read(void *buffer, long size)
{
    long bytes_read = 0;
    int opened = false;

    if (!Is_Open()) {
        if (!Open(FILE_RIGHTS_READ)) {
            return 0;
        }
        opened = true;
    }
    if (BiasLength != -1) {
        long remainder = BiasLength - Seek(0, FILE_SEEK_CURRENT);
        size = size < remainder ? size : remainder;
    }
    long total = 0;
    while (size > 0) {
        bytes_read = 0;
        if (!ReadFile(Handle, buffer, size, (DWORD *)&bytes_read, 0)) {
            buffer = (char *)buffer + bytes_read;
            size -= bytes_read;
            total += bytes_read;
            if (RawFileReadStopOnError) {
                break;
            }
            Error(GetLastError(), true, Filename);
            continue;
        }
        buffer = (char *)buffer + bytes_read;
        size -= bytes_read;
        total += bytes_read;
        if (bytes_read == 0) {
            break;
        }
    }
    bytes_read = total;
    RawFileReadStopOnError = false;
    if (opened) {
        Close();
    }
    return bytes_read;
}
