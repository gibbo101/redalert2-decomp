// The CRT's stream functions the game calls directly (VC6 msvcrt-style statics).
#ifndef RA2_SHARED_CRT_STDIO_HPP
#define RA2_SHARED_CRT_STDIO_HPP

struct _iobuf;
extern "C" _iobuf *__cdecl fopen(char const *name, char const *mode);   // 0x00783A45
extern "C" int __cdecl fgetc(_iobuf *file);                            // 0x00784A0B
extern "C" int __cdecl fclose(_iobuf *file);                           // 0x0078395B

#endif
