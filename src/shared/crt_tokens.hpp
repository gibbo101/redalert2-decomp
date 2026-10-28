// C runtime string scanning used by recovered source.
//
// strlen is an intrinsic at /O2 (repne scasb); strtok and _strnicmp are
// calls (bound by @ref until they are in manifests/symbols.json:
// _strtok 0x00782EC2, __strnicmp 0x00783810).
#ifndef RA2_SHARED_CRT_TOKENS_HPP
#define RA2_SHARED_CRT_TOKENS_HPP

#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif

extern "C" unsigned int __cdecl strlen(char const *string);
extern "C" char *__cdecl strtok(char *string, char const *delimiters);
extern "C" int __cdecl _strnicmp(char const *left, char const *right, unsigned int count);
// Wide forms (OptionsClass::Load_Settings reads [Network] NetID with them).
extern "C" unsigned short *__cdecl wcstok(unsigned short *string, unsigned short const *delimiters);   // 0x00784B11
extern "C" long __cdecl wcstol(unsigned short const *string, unsigned short **end, int base);           // 0x00784BB8
extern "C" unsigned int __cdecl _mbsnbcnt(unsigned char const *string, unsigned int count);   // 0x00784D8D
#pragma intrinsic(strlen)

#endif
