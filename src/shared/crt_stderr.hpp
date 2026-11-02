// The CRT's stderr stream and vfprintf (JSHELL.CPP Fatal 0x0052EE00). A separate header so units
// that only use shared/crt_stdio.hpp's FILE pointers keep their declaration counts (a new type in a
// shared header renumbers $L labels in fragile units such as Pick_Lobby 0x00744090).
#ifndef RA2_SHARED_CRT_STDERR_HPP
#define RA2_SHARED_CRT_STDERR_HPP

#include "shared/crt_stdio.hpp"

// VC6 stdio.h's FILE (0x20 bytes).
struct _iobuf {
    char *_ptr;
    int _cnt;
    char *_base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char *_tmpfname;
};
extern "C" int __cdecl vfprintf(_iobuf *file, char const *format, char *arguments);  // 0x00784502
// The CRT's stream table (0x0082EC90; _iob[2] at 0x0082ECD0 is stderr).
extern "C" _iobuf _iob[];
#define stderr (&_iob[2])

#endif
