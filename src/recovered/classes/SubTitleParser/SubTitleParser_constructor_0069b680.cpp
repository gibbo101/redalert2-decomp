// The movie subtitle parser unit (0x0069B680-0x0069C3AF; RA2 only, no static initializers): SubTitleParser reads
// a movie's section of the UTF-16 subtitle script into SubTitle objects (shared/subtitle.hpp), with the
// keyword handlers and the DynamicVectorClass<SubTitle *> instances.
#define VECTOR_IMPLEMENT_ALL
#include "shared/subtitle.hpp"
#include "shared/vector_class.hpp"
#include "shared/debug_printf.hpp"
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);                                    // 0x00783605
extern "C" unsigned short *__cdecl wcschr(unsigned short const *string, unsigned short character);       // 0x00783AC6
extern "C" unsigned short *__cdecl wcspbrk(unsigned short const *string, unsigned short const *set);     // 0x00785509
extern "C" int __cdecl _wcsicmp(unsigned short const *left, unsigned short const *right);                // 0x00796318
extern "C" int __cdecl _wcsnicmp(unsigned short const *left, unsigned short const *right, unsigned int count);   // 0x007970A0
extern "C" unsigned int __cdecl mbstowcs(unsigned short *wide, char const *string, unsigned int count);  // 0x007853AC
unsigned short *__fastcall wcstrim(unsigned short *buffer);                                              // 0x006EEF80

bool __fastcall Read_Line(Straw &input, unsigned short *buffer, int count);   // 0x0069C100

// Script keywords and their handlers (0x007F62F0; null-terminated).
struct SubTitleHook {
    unsigned short const *Token;
    void (__fastcall *Handler)(unsigned short *param, SubTitle *subtitle);
};
extern SubTitleHook unknown_subtitle_hooks_7f62f0[];
// @ref ?unknown_subtitle_hooks_7f62f0@@3PAUSubTitleHook@@A=007f62f0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?wcstrim@@YIPAGPAG@Z=006eef80
// @ref ??0SubTitle@@QAE@XZ=0069b0c0
// @ref ??1SubTitle@@QAE@XZ=0069b0f0
// @ref _wcspbrk=00785509
// @ref _wcschr=00783ac6
// @ref _wcslen=00783605
// @ref __wcsicmp=00796318
// @ref __wcsnicmp=007970a0
// @ref _mbstowcs=007853ac
// @ref _wcstol=00784bb8

// SubTitleParser::SubTitleParser(Straw &input) (0x0069B680): checks the UTF-16 byte order mark.
// @ref ??_C@_0CO@CFJA@Error?3?5Subtitle?5control?5file?5is?5@=007f63b4
SubTitleParser::SubTitleParser(Straw &input) : Input(input), LineNumber(0)
{
    unsigned short mark = 0;
    input.Get(&mark, sizeof(mark));
    if (mark != 0xFEFF) {
        Debug_Printf("Error: Subtitle control file is not unicode!\n");
    }
}
