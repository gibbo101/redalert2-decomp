// BufferIOFileClass::Cache (0x0042F390)
// Attaches a cache buffer and fills it with the start of the file (or the
// window at the current position of an already open file).
//   size == 0  size the buffer to the whole file
//   size > 0   use that size, at least BUFFER_IO_MINIMUM_SIZE
//   buffer     use caller memory instead of allocating (requires a size)
// Returns false when a buffer is already attached with different arguments,
// when no size can be determined, or when allocation fails (ENOMEM).
// Note: IsAllocated is set even for caller-supplied memory, as in the
// original, so Free() would delete it.
#include "shared/buffer_io_file_class.hpp"

bool BufferIOFileClass::Cache(long size, void *buffer)
{
    if (Buffer) {
        if (size || buffer) {
            return false;
        }
        return true;
    }
    if (Is_Available()) {
        FileSize = Size();
    } else {
        FileSize = 0;
    }
    if (size) {
        if (size < BUFFER_IO_MINIMUM_SIZE) {
            size = BUFFER_IO_MINIMUM_SIZE;
            if (buffer) {
                Error(FILE_ERROR_INVALID, false, 0);
            }
        }
        BufferSize = size;
    } else {
        BufferSize = FileSize;
    }
    if (!size && buffer) {
        return false;
    }
    if (BufferSize) {
        if (buffer) {
            Buffer = (char *)buffer;
        } else {
            Buffer = new char[BufferSize];
        }
        if (Buffer) {
            IsAllocated = true;
            IsDiskOpen = false;
            BufferPos = 0;
            BufferFilePos = 0;
            BufferChangeBeg = -1;
            BufferChangeEnd = -1;
            FilePos = 0;
            TrueFileStart = 0;
            if (FileSize) {
                long position = 0;
                int opened = false;
                long fill = FileSize;
                if (FileSize > BufferSize) {
                    fill = BufferSize;
                }
                if (Is_Open()) {
                    position = Seek(0, FILE_SEEK_CURRENT);
                    if (Handle != INVALID_HANDLE_VALUE) {
                        TrueFileStart = RawFileClass::Seek(0, FILE_SEEK_CURRENT);
                    } else {
                        TrueFileStart = position;
                    }
                    if (FileSize <= BufferSize) {
                        if (position) {
                            Seek(0, FILE_SEEK_START);
                        }
                        BufferPos = position;
                        FilePos = position;
                    } else {
                        BufferFilePos = position;
                        FilePos = position;
                    }
                } else if (Open(FILE_RIGHTS_READ)) {
                    TrueFileStart = RawFileClass::Seek(0, FILE_SEEK_CURRENT);
                    opened = true;
                }
                if (Read(Buffer, fill) != fill) {
                    Error(FILE_ERROR_IO, false, 0);
                }
                if (opened) {
                    Close();
                    IsCached = true;
                    UseBuffer = true;
                    return true;
                }
                Seek(position, FILE_SEEK_START);
                IsCached = true;
            }
            UseBuffer = true;
            return true;
        }
        Error(FILE_ERROR_NO_MEMORY, false, 0);
    }
    return false;
}
