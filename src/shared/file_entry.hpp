// FileEntryClass identity from RTTI DynamicVectorClass<FileEntryClass *> at007A5844.
// Allocation0053C252 and construction0053C263..0053C2A7 prove extent0x1BC.
// The immediately following virtual call0053C2BA passes it and WIN32_FIND_DATA
// to LoadOptionsClass slot4; MapSeed005794E0 writes the fields named below.
#ifndef RA2_SHARED_FILE_ENTRY_HPP
#define RA2_SHARED_FILE_ENTRY_HPP
#include "shared/win32_api.hpp"
#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif
class FileEntryClass {
public:
    wchar_t Description[128]; // +000
    char Filename[32]; // +100
    int unknown_120;
    int unknown_124;
    unsigned char unknown_128[0x80];
    int unknown_1a8;
    FILETIME LastWriteTime; // +1AC
    bool HasDescription; // +1B4
    bool NeedsDescription; // +1B5
    unsigned char unknown_1b6[2];
    int unknown_1b8;
};
typedef char FileEntryClass_size[(sizeof(FileEntryClass)==0x1BC)?1:-1];
#endif
