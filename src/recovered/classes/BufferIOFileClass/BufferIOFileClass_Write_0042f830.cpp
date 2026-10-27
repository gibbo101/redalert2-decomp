// BufferIOFileClass::Write (0x0042F830, virtual slot 12)
// Writes through the buffer. A partially overwritten window is first filled
// from disk so unchanged bytes survive. Each write extends the changed range
// and, past the end, the logical file size; a full window is committed and
// the next one loaded if more data follows. A closed file is opened for
// writing (and later closed) around the call.
#include "shared/buffer_io_file_class.hpp"
#include "shared/crt_string.hpp"

long BufferIOFileClass::Write(void const *buffer, long size)
{
    int opened = false;

    if (!Is_Open()) {
        if (!Open(FILE_RIGHTS_WRITE)) {
            return 0;
        }
        TrueFileStart = RawFileClass::Seek(0, FILE_SEEK_CURRENT);
        opened = true;
    }
    if (UseBuffer) {
        long total = 0;
        if (BufferRights != FILE_RIGHTS_READ) {
            while (size) {
                long chunk = (size >= BufferSize - BufferPos) ? BufferSize - BufferPos : size;
                if (chunk != BufferSize && !IsCached) {
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
                memmove(Buffer + BufferPos, (char const *)buffer + total, chunk);
                total += chunk;
                size -= chunk;
                IsChanged = true;
                if (BufferChangeBeg == -1) {
                    BufferChangeBeg = BufferPos;
                    BufferChangeEnd = BufferPos;
                } else if (BufferChangeBeg > BufferPos) {
                    BufferChangeBeg = BufferPos;
                }
                BufferPos += chunk;
                if (BufferChangeEnd < BufferPos) {
                    BufferChangeEnd = BufferPos;
                }
                FilePos = BufferFilePos + BufferPos;
                if (FileSize < FilePos) {
                    FileSize = FilePos;
                }
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
        size = RawFileClass::Write(buffer, size);
    }
    if (opened) {
        Close();
    }
    return size;
}
