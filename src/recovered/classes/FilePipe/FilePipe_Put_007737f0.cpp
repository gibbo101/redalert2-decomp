// FilePipe::Put (0x007737F0, virtual slot 4)
// Writes to the file, opening it for writing first if it is closed (and
// remembering to close it later). Returns the bytes written, 0 on failure.
#include "shared/file_pipe.hpp"

int FilePipe::Put(void const *source, int length)
{
    if (Valid_File() && source && length > 0) {
        if (!File->Is_Open()) {
            HasOpened = true;
            File->Open(FILE_RIGHTS_WRITE);
        }
        return File->Write(source, length);
    }
    return 0;
}
