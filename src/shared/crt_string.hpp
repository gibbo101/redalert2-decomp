// C runtime string functions used by recovered source.
//
// VC6 expands strcmp, strcpy, strcat and memset inline at /O2 (intrinsics),
// so no call is emitted for them; the declarations only have to exist.
#ifndef RA2_SHARED_CRT_STRING_HPP
#define RA2_SHARED_CRT_STRING_HPP

extern "C" int __cdecl strcmp(char const *left, char const *right);
extern "C" char *__cdecl strcpy(char *destination, char const *source);
extern "C" char *__cdecl strcat(char *destination, char const *source);
extern "C" void __cdecl _splitpath(char const *path, char *drive, char *dir, char *fname, char *ext);   // 0x00784873
extern "C" void *__cdecl memmove(void *destination, void const *source, unsigned int count);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);
#pragma intrinsic(strcmp, strcpy, strcat, memset)

#endif
