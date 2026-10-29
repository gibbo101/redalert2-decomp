// C runtime string functions used by recovered source.
//
// VC6 expands strcmp, strcpy, strcat and memset inline at /O2 (intrinsics),
// so no call is emitted for them; the declarations only have to exist.
#ifndef RA2_SHARED_CRT_STRING_HPP
#define RA2_SHARED_CRT_STRING_HPP

extern "C" int __cdecl strcmp(char const *left, char const *right);
extern "C" char *__cdecl strcpy(char *destination, char const *source);
extern "C" char *__cdecl strcat(char *destination, char const *source);
extern "C" int __cdecl strncmp(char const *left, char const *right, unsigned int count);   // 0x00783810
extern "C" char *__cdecl strncpy(char *destination, char const *source, unsigned int count);   // 0x007823D0
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);   // 0x007820F4
extern "C" int __cdecl _stricmp(char const *left, char const *right);      // 0x00781F20
extern "C" void __cdecl _splitpath(char const *path, char *drive, char *dir, char *fname, char *ext);   // 0x00784873
extern "C" void *__cdecl memmove(void *destination, void const *source, unsigned int count);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);
extern "C" void __cdecl qsort(void *base, unsigned int count, unsigned int width,
                              int(__cdecl *compare)(void const *, void const *));   // 0x00781D46
#pragma intrinsic(strcmp, strcpy, strcat, memset)

#endif
