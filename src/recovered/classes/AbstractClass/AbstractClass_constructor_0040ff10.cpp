// AbstractClass::AbstractClass() (0x0040FF10)
// No unique ID yet (-1), clean, reference count 0.
#include "shared/abstract.hpp"
// @ref ??_7AbstractClass@@6BIPersistStream@@@=0079add8
// @ref ??_7AbstractClass@@6BIRTTITypeInfo@@@=0079adbc
// @ref ??_7AbstractClass@@6BINoticeSink@@@=0079adb4
// @ref ??_7AbstractClass@@6BINoticeSource@@@=0079adac
// @ref ??_7INoticeSink@@6B@=0079ae44
// @ref ??_7INoticeSource@@6B@=0079ae3c

AbstractClass::AbstractClass() :
    UniqueID(-1),
    unknown_18(0),
    RefCount(0),
    Dirty(false)
{
    unknown_14_bit0 = 0;
    unknown_14_bit1 = 0;
    unknown_14_bit2 = 0;
}
