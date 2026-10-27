// BufferIOFileClass::Read (0x0042FA80, virtual slot 9)
// Reads through the buffer. An empty buffer is filled first: the whole file
// when it fits, otherwise the buffer-sized window at the current position.
// Data is copied out of the window; when the window is exhausted, changes
// are committed and the next window is read if more data is wanted. A
// closed file is opened (and later closed) around the read.
#include "shared/buffer_io_file_class.hpp"
#include "shared/crt_string.hpp"

long BufferIOFileClass::Read(void *buffer, long size)
{
    int opened = false;

    if (!Is_Open()) {
        if (Open(FILE_RIGHTS_READ)) {
            TrueFileStart = RawFileClass::Seek(0, FILE_SEEK_CURRENT);
            opened = true;
        }
    }
    if (UseBuffer) {
        long total = 0;
        if (BufferRights != FILE_RIGHTS_WRITE) {
            while (size) {
                long chunk = (size >= BufferSize - BufferPos) ? BufferSize - BufferPos : size;
                if (!IsCached) {
                    long fill;
                    if (FileSize < BufferSize) {
                        fill = FileSize;
                        BufferFilePos = 0;
                    } else {
                        fill = BufferSize;
                        BufferFilePos = FilePos;
                    }
                    if (TrueFileStart) {
                        UseBuffer = false;
                        Seek(FilePos, FILE_SEEK_START);
                        Read(Buffer, BufferSize);
                        Seek(FilePos, FILE_SEEK_START);
                        UseBuffer = true;
                    } else {
                        RawFileClass::Seek(BufferFilePos, FILE_SEEK_START);
                        RawFileClass::Read(Buffer, fill);
                    }
                    BufferPos = 0;
                    BufferChangeBeg = -1;
                    BufferChangeEnd = -1;
                    IsCached = true;
                }
                memmove((char *)buffer + total, Buffer + BufferPos, chunk);
                total += chunk;
                size -= chunk;
                BufferPos += chunk;
                FilePos = BufferFilePos + BufferPos;
                if (BufferPos == BufferSize) {
                    Commit();
                    BufferPos = 0;
                    BufferFilePos = FilePos;
                    BufferChangeBeg = -1;
                    BufferChangeEnd = -1;
                    if (size && FileSize > FilePos) {
                        if (TrueFileStart) {
                            UseBuffer = false;
                            Seek(FilePos, FILE_SEEK_START);
                            Read(Buffer, BufferSize);
                            Seek(FilePos, FILE_SEEK_START);
                            UseBuffer = true;
                        } else {
                            RawFileClass::Seek(FilePos, FILE_SEEK_START);
                            RawFileClass::Read(Buffer, BufferSize);
                        }
                    } else {
                        IsCached = false;
                    }
                }
            }
        } else {
            Error(FILE_ERROR_ACCESS, false, 0);
        }
        size = total;
    } else {
        size = RawFileClass::Read(buffer, size);
    }
    if (opened) {
        Close();
    }
    return size;
}
