// C runtime memory functions. VC6 expands memset, memcpy and memcmp inline
// at /O2 (`rep stosd`, `rep movsd`, `repe cmpsb`) when they are listed as
// intrinsics; memmove stays a call (bound through manifests/symbols.json).
#ifndef RA2_SHARED_CRT_MEMORY_HPP
#define RA2_SHARED_CRT_MEMORY_HPP

extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);
extern "C" void *__cdecl memcpy(void *destination, void const *source, unsigned int count);
extern "C" void *__cdecl memmove(void *destination, void const *source, unsigned int count);
extern "C" int __cdecl memcmp(void const *left, void const *right, unsigned int count);
extern "C" int __cdecl abs(int value);
extern "C" void *__cdecl malloc(unsigned int size);                                // 0x00782630
#pragma intrinsic(memset, memcpy, memcmp, abs)

#endif
