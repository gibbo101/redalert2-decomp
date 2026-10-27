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
#pragma intrinsic(strlen)

#endif
