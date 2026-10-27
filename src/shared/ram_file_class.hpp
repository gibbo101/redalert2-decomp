// RAMFileClass: a FileClass over a block of memory (RTTI vtable 0x007A8C34,
// unit 0x00638310-0x00638660; Westwood's ramfile.cpp shape).
//
// Layout (constructors 0x00638310, 0x00638360):
//   +0x04  char *Buffer
//   +0x08  int MaxLength      capacity
//   +0x0C  int Length         bytes of valid data
//   +0x10  int Offset         read/write position
//   +0x14  int Access         FILE_RIGHTS_* of the open
//   +0x18  bool IsOpen
//   +0x19  bool IsAllocated   the buffer is owned
// Names follow Westwood's RAMFileClass; slot addresses from the vtable.
#ifndef RA2_SHARED_RAM_FILE_CLASS_HPP
#define RA2_SHARED_RAM_FILE_CLASS_HPP

#include "shared/raw_file_class.hpp"

class RAMFileClass : public FileClass {
public:
    RAMFileClass(void *buffer, int length);                     // 0x00638310
    virtual ~RAMFileClass();                                    // 0x00638360 (scalar deleting 0x00638660)

    virtual char const *File_Name() const;                      // slot 1  0x00638610
    virtual char const *Set_Name(char const *filename);         // slot 2  0x00638620
    virtual int Create();                                       // slot 3  0x006383A0
    virtual int Delete();                                       // slot 4  0x006383C0
    virtual bool Is_Available(int forced = 0);                  // slot 5  0x006383E0
    virtual bool Is_Open() const;                               // slot 6  0x006383F0
    virtual int Open(char const *filename, int rights);         // slot 8  0x00638400
    virtual int Open(int rights = FILE_RIGHTS_READ);            // slot 7  0x00638410
    virtual long Read(void *buffer, long size);                 // slot 9  0x00638460
    virtual long Seek(long position, int origin);               // slot 10 0x006384E0
    virtual long Size();                                        // slot 11 0x00638560
    virtual long Write(void const *buffer, long size);          // slot 12 0x00638570
    virtual void Close();                                       // slot 13 0x00638600
    virtual unsigned long Get_Date_Time();                      // slot 14 0x00638630
    virtual bool Set_Date_Time(unsigned long datetime);         // slot 15 0x00638640
    virtual void Error(int error, int can_retry = 0, char const *filename = 0);   // slot 16 0x00638650

    char *Buffer;           // +0x04
    int MaxLength;          // +0x08
    int Length;             // +0x0C
    int Offset;             // +0x10
    int Access;             // +0x14
    bool IsOpen;            // +0x18
    bool IsAllocated;       // +0x19
};

#endif
