// The CRT's low-level file functions (io.h) the game calls directly.
#ifndef RA2_SHARED_CRT_IO_HPP
#define RA2_SHARED_CRT_IO_HPP

extern "C" int __cdecl _open(char const *name, int flags, ...);          // 0x0078D841
extern "C" int __cdecl _read(int handle, void *buffer, unsigned int count); // 0x00788A6F
extern "C" long __cdecl _lseek(int handle, long offset, int origin);       // 0x0078FD48
extern "C" long __cdecl _filelength(int handle);                          // 0x00797198
extern "C" int __cdecl _close(int handle);                                // 0x0078AD04

// _open flags.
#define _O_RDONLY 0x0000
#define _O_BINARY 0x8000

#endif
