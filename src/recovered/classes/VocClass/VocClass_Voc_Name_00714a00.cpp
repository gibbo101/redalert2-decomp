// char const *__fastcall Voc_Name(int voc) -- 0x00714A00
// Purpose: the name of a sound effect: "<none>" for an index outside the
// VocClass list (0x00AD0818), "Invalid Voc" when the entry has no sound
// object, otherwise that object's name (0x00405150, a tail call).
// Assumptions: VocClass's first member is the sound object whose name
// 0x00405150 returns; that class and its name are unidentified.
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
// @ref ?unknown_VocClass_list_00ad0818@@3V?$DynamicVectorClass@PAVVocClass@@@@A=00ad0818
// @ref ?Name@UnknownSound_405150@@QAEPBDXZ=00405150
// @ref ??_C@_0M@OOFK@Invalid?5Voc?$AA@=007f9b3c
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc

class UnknownSound_405150 {
public:
    char const *Name();
};

class VocClass {
public:
    UnknownSound_405150 *Sound;     // +0x00
};
extern DynamicVectorClass<VocClass *> unknown_VocClass_list_00ad0818;

char const *__fastcall Voc_Name(int voc)
{
    if (voc >= 0 && voc < unknown_VocClass_list_00ad0818.Count()) {
        UnknownSound_405150 *sound = unknown_VocClass_list_00ad0818[voc]->Sound;
        if (sound != 0) {
            return sound->Name();
        }
        return "Invalid Voc";
    }
    return "<none>";
}
