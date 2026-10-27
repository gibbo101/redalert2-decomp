// CCFileClass: the game's file class; resolves names inside mixfiles.
//
// Name from RTTI (vtable 0x0079A6A0, bases CDFileClass < BufferIOFileClass
// < RawFileClass < FileClass); members from the constructor at 0x00468F50.
//
// Opening a name first asks the mixfiles where it is. A file held in memory
// (a cached mixfile) is served from Data, with Position as the read offset;
// a file inside a mixfile on disk is opened as the mixfile with a bias
// window over the member; anything else is an ordinary searched disk file.
#ifndef RA2_SHARED_CC_FILE_CLASS_HPP
#define RA2_SHARED_CC_FILE_CLASS_HPP

#include "shared/cd_file_class.hpp"
#include "shared/buffer.hpp"

class Wstring;

class CCFileClass : public CDFileClass {
public:
    CCFileClass(char const *filename);
    // Names the file from the string's text (0x00468F90; MSPCXAnim).
    CCFileClass(Wstring const &filename);
    CCFileClass();
    virtual ~CCFileClass() { Position = 0; }
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

    ::Buffer Data;              // +0x54 in-memory file contents (cached mixfile member)
    long Position;              // +0x60 read position within Data
};

#endif
