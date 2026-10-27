// StringTable: the localized string table (CSF labels such as TXT_CD_DIALOG_1).
//
// 0x006F9EC0 is __fastcall (label in ecx, optional speech-name output in
// edx) with the caller's source file and line on the stack (ret 8), and
// returns a wide string. Its callers pass "D:\Ra2\<file>" and a line number,
// i.e. __FILE__/__LINE__ in the original; recovered callers pass them as
// literals because the reproduction compiles other file names. Class and
// method names are hypotheses.
#ifndef RA2_SHARED_STRING_TABLE_HPP
#define RA2_SHARED_STRING_TABLE_HPP

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

class StringTable {
public:
    static int Is_Loaded_006fa030(); // original DWORD query at006FA030
    static wchar_t const *__fastcall Load_String(char const *label, char *speech, char const *file,
                                                 int line);   // 0x006F9EC0
};

extern "C" int __cdecl swprintf(wchar_t *buffer, wchar_t const *format, ...);   // 0x00783764
extern "C" wchar_t *__cdecl wcsncpy(wchar_t *destination, wchar_t const *source, unsigned int count);   // 0x00783622

#endif
