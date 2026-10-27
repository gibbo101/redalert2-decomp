// BufferIOFileClass: a RawFileClass with an optional memory cache.
//
// Name from RTTI (vtable 0x0079C73C, bases RawFileClass < FileClass); member
// offsets from the constructor at 0x0042F2F0, behavior from the methods.
//
// Cache() attaches a buffer (supplied or allocated). While UseBuffer is set,
// reads and writes go through the buffer: a file no larger than the buffer is
// read once and served from memory; a larger file is paged through the buffer
// window [BufferFilePos, BufferFilePos + BufferSize). Writes mark the changed
// range [BufferChangeBeg, BufferChangeEnd), which Commit() writes back.
// TrueFileStart is the disk position where the logical file begins when the
// underlying file was already open (a file within a file).
#ifndef RA2_SHARED_BUFFER_IO_FILE_CLASS_HPP
#define RA2_SHARED_BUFFER_IO_FILE_CLASS_HPP

#include "shared/raw_file_class.hpp"

// Smallest buffer Cache() will create; smaller requests are raised to this.
const long BUFFER_IO_MINIMUM_SIZE = 0x400;
// Extra error codes BufferIOFileClass reports.
const int FILE_ERROR_IO = 5;            // EIO: a cache fill read fewer bytes than expected
const int FILE_ERROR_ACCESS = 13;       // EACCES: reading a file opened write-only
const int FILE_ERROR_INVALID = 22;      // EINVAL: supplied buffer smaller than the minimum

class BufferIOFileClass : public RawFileClass {
public:
    BufferIOFileClass(char const *filename);
    BufferIOFileClass();
    virtual ~BufferIOFileClass();
    virtual char const *Set_Name(char const *filename);
    virtual bool Is_Available(int forced = 0);
    virtual bool Is_Open() const;
    virtual int Open(char const *filename, int rights);
    virtual int Open(int rights = FILE_RIGHTS_READ);
    virtual long Read(void *buffer, long size);
    virtual long Seek(long position, int origin);
    virtual long Size();
    virtual long Write(void const *buffer, long size);
    virtual void Close();

    bool Cache(long size = 0, void *buffer = 0);
    void Free();
    bool Commit();

    bool IsAllocated;           // +0x20 Buffer was allocated by Cache() and is owned
    bool IsOpen;                // +0x21 logically open (possibly served from the cache)
    bool IsDiskOpen;            // +0x22 the underlying disk file is open
    bool IsCached;              // +0x23 the buffer holds valid file data
    bool IsChanged;             // +0x24 the buffer holds unwritten changes
    bool UseBuffer;             // +0x25 a buffer is attached
    int BufferRights;           // +0x28 rights of the logical open
    char *Buffer;               // +0x2C cache memory
    long BufferSize;            // +0x30 cache size in bytes
    long BufferPos;             // +0x34 current position within the buffer
    long BufferFilePos;         // +0x38 file position of the buffer's first byte
    long BufferChangeBeg;       // +0x3C first changed buffer byte, -1 when clean
    long BufferChangeEnd;       // +0x40 end of the changed range, -1 when clean
    long FileSize;              // +0x44 logical file size
    long FilePos;               // +0x48 logical file position
    long TrueFileStart;         // +0x4C disk position of logical position 0
};

#endif
