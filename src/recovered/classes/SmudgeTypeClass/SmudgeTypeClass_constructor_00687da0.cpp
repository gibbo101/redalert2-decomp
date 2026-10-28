// SmudgeTypeClass::SmudgeTypeClass(char const *ini_name) (0x00687DA0)
// A 1 x 1 smudge that is neither crater nor scorch mark, registered in
// SmudgeTypes (ArrayIndex is its position there).
#include "shared/smudge_type.hpp"
// @ref ??0ObjectTypeClass@@QAE@PBD@Z=005d57f0
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?SmudgeTypes@@3V?$DynamicVectorClass@PAVSmudgeTypeClass@@@@A=00a40bc8
// @ref ??_7SmudgeTypeClass@@6BIPersistStream@@@=007ab7a0
// @ref ??_7SmudgeTypeClass@@6BIRTTITypeInfo@@@=007ab784
// @ref ?QueryInterface@AbstractClass@@W3AGJABUGUID@@PAPAX@Z=00410380
// @ref ?AddRef@AbstractClass@@W3AGKXZ=00410390
// @ref ?Release@AbstractClass@@W3AGKXZ=004103a0
// @ref ?unknown_slot27@ObjectTypeClass@@UBE?AUCoordStruct@@ABU2@@Z=0041c2e0
// @ref ?unknown_slot39@ObjectTypeClass@@UBEPAXXZ=0041c300
// @ref ??_7SmudgeTypeClass@@6BINoticeSink@@@=007ab77c
// @ref ??_7SmudgeTypeClass@@6BINoticeSource@@@=007ab774

SmudgeTypeClass::SmudgeTypeClass(char const *ini_name) :
    ObjectTypeClass(ini_name),
    ArrayIndex(-1),
    Width(1),
    Height(1),
    Crater(false),
    Burn(false)
{
    AbstractClass::Create_ID();
    unknown_1ff = true;
    unknown_200 = false;
    unknown_201 = false;
    unknown_202 = true;
    unknown_203 = true;
    unknown_205 = false;
    SmudgeTypes.Add(this);
    ArrayIndex = SmudgeTypes.ID(this);
}
