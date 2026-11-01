// FileClass and RawFileClass: the engine's file interface and its Win32 version.
//
// Names come from the executable's RTTI (FileClass vtable 0x007A8C7C,
// RawFileClass vtable 0x007A8CC4). Virtual slot order, member offsets and
// behavior are taken from the original code; method names follow Westwood's
// file-class vocabulary, which every slot's behavior matches.
//
// A RawFileClass reads and writes a disk file through a Win32 handle. An
// optional bias window (BiasStart, BiasLength) restricts all positioning and
// sizes to a sub-range, so one file embedded in a larger one (a mixfile
// member) can be used like a whole file. BiasLength == -1 means no window.
#ifndef RA2_SHARED_RAW_FILE_CLASS_HPP
#define RA2_SHARED_RAW_FILE_CLASS_HPP

#include "shared/win32_api.hpp"

// Access rights passed to Open().
enum FileRights {
    FILE_RIGHTS_READ = 1,
    FILE_RIGHTS_WRITE = 2,
    FILE_RIGHTS_READ_WRITE = 3
};

// Pure virtual slots of FileClass point at the game's own _purecall
// (0x004B8960), which simply returns 0.

// Seek origins (SEEK_SET/SEEK_CUR/SEEK_END).
enum FileSeekOrigin {
    FILE_SEEK_START = 0,
    FILE_SEEK_CURRENT = 1,
    FILE_SEEK_END = 2
};

// Error codes Error() receives besides Win32 GetLastError values.
enum FileErrorCode {
    FILE_ERROR_NO_FILE_NAME = 2,  // ENOENT: operation needs a file name
    FILE_ERROR_NOT_OPEN = 9,      // EBADF: operation needs an open file
    FILE_ERROR_NO_MEMORY = 12     // ENOMEM: copying the file name failed
};

class FileClass {
public:
    virtual ~FileClass() {}                                        // slot 0
    virtual char const *File_Name() const = 0;                     // slot 1
    virtual char const *Set_Name(char const *filename) = 0;        // slot 2
    virtual int Create() = 0;                                      // slot 3
    virtual int Delete() = 0;                                      // slot 4
    virtual bool Is_Available(int forced = 0) = 0;                 // slot 5
    virtual bool Is_Open() const = 0;                              // slot 6
    virtual int Open(char const *filename, int rights) = 0;        // slot 8 (VC6 lists overloads in reverse)
    virtual int Open(int rights = FILE_RIGHTS_READ) = 0;           // slot 7
    virtual long Read(void *buffer, long size) = 0;                // slot 9
    virtual long Seek(long position, int origin) = 0;              // slot 10
    virtual long Size() = 0;                                       // slot 11
    virtual long Write(void const *buffer, long size) = 0;         // slot 12
    virtual void Close() = 0;                                      // slot 13
    virtual unsigned long Get_Date_Time();                         // slot 14
    virtual bool Set_Date_Time(unsigned long datetime);            // slot 15
    virtual void Error(int error, int can_retry = 0, char const *filename = 0) = 0;  // slot 16
};

class RawFileClass : public FileClass {
public:
    RawFileClass() :
        Rights(FILE_RIGHTS_READ), BiasStart(0), BiasLength(-1), Handle(INVALID_HANDLE_VALUE),
        Filename(0), Date(0), Time(0), Allocated(false)
    {
    }
    RawFileClass(char const *filename);
    virtual ~RawFileClass();
    virtual char const *File_Name() const { return Filename; }
    virtual char const *Set_Name(char const *filename);
    virtual int Create();
    virtual int Delete();
    virtual bool Is_Available(int forced = 0);
    virtual bool Is_Open() const;
    virtual int Open(char const *filename, int rights);
    virtual int Open(int rights = FILE_RIGHTS_READ);
    virtual long Read(void *buffer, long size);
    virtual long Seek(long position, int origin);
    virtual long Size();
    virtual long Write(void const *buffer, long size);
    virtual void Close();
    virtual unsigned long Get_Date_Time();
    virtual bool Set_Date_Time(unsigned long datetime);
    virtual void Error(int error, int can_retry = 0, char const *filename = 0);

    int Rights;                 // +0x04 rights the file was last opened with

    // Restricts the file to the window [start, start + length) of the disk
    // file (relative to any current window); start 0 removes the window.
    void Bias(int start, int length = -1);

protected:
    // Positions the Win32 file pointer without applying the bias window.
    // Defined with the class (0x006393D0); VC6 also inlines it into Seek
    // and Write.
    long Raw_Seek(long position, int origin = FILE_SEEK_CURRENT);

public:
    // Public as in TibSun rawfile.h (MixFileClass's constructor adds BiasStart to DataStart).
    long BiasStart;             // +0x08 window start within the disk file
    long BiasLength;            // +0x0C window length, -1 when unbiased
protected:
    HANDLE Handle;              // +0x10 Win32 handle, INVALID_HANDLE_VALUE when closed
    char const *Filename;       // +0x14 file name (owned when Allocated)
    unsigned short Date;        // +0x18 DOS date (unused by these methods)
    unsigned short Time;        // +0x1A DOS time
    bool Allocated;             // +0x1C Filename was duplicated and must be freed
};

// Set by callers that prefer a short read to an error report: when ReadFile
// fails while it is set, Read stops instead of calling Error(). Read clears it
// on every return. Original global at 0x00AB663C; its setters are unrecovered.
extern "C" bool RawFileReadStopOnError;

// C runtime functions RawFileClass uses (the game's statically linked CRT).
extern "C" char *__cdecl _strdup(char const *text);
extern "C" void __cdecl free(void *block);

#endif
