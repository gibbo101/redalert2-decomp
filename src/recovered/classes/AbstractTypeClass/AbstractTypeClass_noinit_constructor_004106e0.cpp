// AbstractTypeClass::AbstractTypeClass(NoInitClass const &noinit) (0x004106E0)
// Load path: keeps the loaded fields and refetches the UIName text.
#include "shared/abstract_type.hpp"
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
// @ref ??_7AbstractTypeClass@@6BIPersistStream@@@=0079ae88
// @ref ??_7AbstractTypeClass@@6BIRTTITypeInfo@@@=0079ae6c
// @ref ??_7AbstractTypeClass@@6BINoticeSink@@@=0079ae64
// @ref ??_7AbstractTypeClass@@6BINoticeSource@@@=0079ae5c
// @ref ??_C@_0BD@BIBO@D?3?2Ra2?2AbsType?4cpp?$AA@=007ce288

AbstractTypeClass::AbstractTypeClass(NoInitClass const &noinit) :
    AbstractClass(noinit),
    ID(noinit),
    UINameLabel(noinit),
    Name(noinit)
{
    if (UINameLabel[0] != 0) {
        UIName = StringTable::Load_String(UINameLabel, 0, "D:\\Ra2\\AbsType.cpp", 127);
    } else {
        UIName = unknown_empty_wide_839d4c;
    }
}
