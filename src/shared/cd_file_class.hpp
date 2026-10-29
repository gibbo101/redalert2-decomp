// CDFileClass: a BufferIOFileClass that searches a list of directories.
//
// Name from RTTI (vtable 0x0079A658, bases BufferIOFileClass < RawFileClass
// < FileClass); IsDisabled at +0x50 from the constructors; the search list
// head at 0x00850898 from Set_Name; the other statics from the search-list
// functions 0x0046FDB0-0x004702B0.
//
// Opening a file for reading tries the name as given, then each search
// directory in turn (the path prefix is prepended), and keeps the first name
// that exists. IsDisabled turns the search off for this object.
#ifndef RA2_SHARED_CD_FILE_CLASS_HPP
#define RA2_SHARED_CD_FILE_CLASS_HPP

#include "shared/buffer_io_file_class.hpp"

// One search directory; the list is singly linked through Next.
struct CDSearchDrive {
    CDSearchDrive *Next;        // +0x00
    char const *Path;           // +0x04 directory prefix, including the separator
};

class CDFileClass : public BufferIOFileClass {
public:
    CDFileClass(char const *filename);
    CDFileClass();
    virtual ~CDFileClass() {}
    virtual char const *Set_Name(char const *filename);
    virtual int Open(char const *filename, int rights);
    virtual int Open(int rights = FILE_RIGHTS_READ);

    // Search-list management (cdfile.cpp statics, all __fastcall).
    static int __fastcall Set_Search_Drives(char *pathlist);     // 0x0046FE70
    static void __fastcall Add_Search_Drive(char *path);         // 0x00470090
    static void __fastcall Set_CD_Drive(int drive);              // 0x004700E0
    static void __fastcall Clear_Search_Drives();                // 0x00470100
    static void __fastcall Refresh_Search_Drives();              // 0x0046FE20
    static int __fastcall Is_Disk_Inserted(int drive);           // 0x0046FDB0
    static bool __fastcall Find_File(char *filename);            // 0x004702B0
    // The next file matching Find_File's pattern into filename, and the end of the search
    // (names hypotheses).
    static bool __fastcall Find_Next_File(char *filename);       // 0x00470400
    static void Find_Close();                                    // 0x00470470

    bool IsDisabled;            // +0x50 do not search the directory list

    static CDSearchDrive *First;   // 0x00850898 head of the search list
    static int CurrentCDDrive;     // 0x0085089C drive index (0 = A:) of the CD, 0 when none
    static int LastCDDrive;        // 0x008508A0 previous CurrentCDDrive
    static char RawPath[];         // 0x008508A4 every path list given to Set_Search_Drives
    static void *FindHandle;       // 0x007D27D4 Find_File's FindFirstFile handle (INVALID when idle)
};

// Waits up to timeout for a disk in the CD drive and returns its index
// (-1 when none). Hypothesis from the call in Set_Search_Drives (0x004983E0).
int __fastcall Get_CD_Index(int drive, int timeout);

#endif
