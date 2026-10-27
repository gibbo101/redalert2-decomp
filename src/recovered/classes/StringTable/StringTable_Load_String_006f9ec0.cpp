// wchar_t const *__fastcall StringTable::Load_String(char const *label, char *speech, char const *file, int line) (0x006F9EC0)
// Looks a label up (case-insensitively, by binary search over the 0x28-byte
// entries at 0x00AD0440) and answers its text (and, through speech, its
// speech name); a label that is missing answers a fresh "MISSING:'label'"
// text kept on the chunk list at 0x00AD0454 and logs it through the empty
// 0x004068F0. A table that never loaded answers the FATAL text.
#include "shared/string_table.hpp"
// @ref ?unknown_labels_ad0440@@3PAXA=00ad0440
// @ref ?unknown_label_count_ad0438@@3HA=00ad0438
// @ref ?unknown_texts_ad0444@@3PAPAGA=00ad0444
// @ref ?unknown_speech_ad0448@@3PAPADA=00ad0448
// @ref ?unknown_chunks_ad0454@@3PAUUnknownTextChunk@@A=00ad0454
// @ref _bsearch=00782025
// @ref ?unknown_compare_781f20@@YAHPBX0@Z=00781f20
// @ref ?Unknown_004068F0@@YAXPBDZZ=004068f0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_C@_0CJ@HLOI@?$CK?$CK?$CKNO_STRING?$CK?$CK?$CK?5?8?$CFs?8?5?9?$DO?5file?3?$CFs?5@=007f8e70
// @ref ??_C@_1BM@EMMK@?$AAM?$AAI?$AAS?$AAS?$AAI?$AAN?$AAG?$AA?3?$AA?8?$AA?$CF?$AAh?$AAs?$AA?8?$AA?$AA@=007f8e9c
// @ref ??_C@_1HE@KFCA@?$AA?$CK?$AA?$CK?$AA?$CK?$AAF?$AAA?$AAT?$AAA?$AAL?$AA?$CK?$AA?$CK?$AA?$CK?$AA?5?$AAS?$AAt?$AAr?$AAi?$AAn?$AAg?$AA?5?$AAM@=007f8eb8

struct UnknownTextChunk {
    UnknownTextChunk *Next;
    wchar_t Text[1];
};
extern void *unknown_labels_ad0440;
extern int unknown_label_count_ad0438;
extern wchar_t **unknown_texts_ad0444;
extern char **unknown_speech_ad0448;
extern UnknownTextChunk *unknown_chunks_ad0454;
extern "C" void *__cdecl bsearch(void const *key, void const *base, unsigned int count, unsigned int width,
                                 int (__cdecl *compare)(void const *, void const *));
int __cdecl unknown_compare_781f20(void const *left, void const *right);
void __cdecl Unknown_004068F0(char const *format, ...);

struct UnknownLabelEntry {
    char Label[0x24];
    int Index;                          // +0x24
};

wchar_t const *__fastcall StringTable::Load_String(char const *label, char *speech, char const *file, int line)
{
    if (speech) {
        *(char **)speech = 0;
    }
    if (!unknown_labels_ad0440) {
        return L"***FATAL*** String Manager failed to initilaized properly";
    }
    UnknownLabelEntry *entry = (UnknownLabelEntry *)bsearch(label, unknown_labels_ad0440, unknown_label_count_ad0438, 0x28, unknown_compare_781f20);
    if (entry) {
        if (speech) {
            *(char **)speech = unknown_speech_ad0448[entry->Index];
        }
        return unknown_texts_ad0444[entry->Index];
    }
    UnknownTextChunk *chunk = (UnknownTextChunk *)::operator new(0x208);
    swprintf(chunk->Text, L"MISSING:'%hs'", label, file, line);
    Unknown_004068F0("***NO_STRING*** '%s' -> file:%s line:%d\n", label, file, line);
    chunk->Next = unknown_chunks_ad0454;
    unknown_chunks_ad0454 = chunk;
    return chunk->Text;
}
