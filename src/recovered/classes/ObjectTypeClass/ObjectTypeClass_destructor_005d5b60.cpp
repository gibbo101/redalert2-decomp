// ObjectTypeClass::~ObjectTypeClass() (0x005D5B60)
// Removes the type from ObjectTypes, frees an owned unknown_a4; the member
// destructors release the buffers and object pairs.
#include "shared/object_type.hpp"
// @ref ??1AbstractTypeClass@@UAE@XZ=00410740
// @ref ??1UnknownObjectPair@@QAE@XZ=005d4a60
// @ref ?ObjectTypes@ObjectTypeClass@@2V?$DynamicVectorClass@PAVObjectTypeClass@@@@A=00a72f90
// @ref ??_7ObjectTypeClass@@6BIPersistStream@@@=007a76f8
// @ref ??_7ObjectTypeClass@@6BIRTTITypeInfo@@@=007a76dc
// @ref ??_7ObjectTypeClass@@6BINoticeSink@@@=007a76d4
// @ref ??_7ObjectTypeClass@@6BINoticeSource@@@=007a76cc
// @ref ??3@YAXPAX@Z=00781d3b

ObjectTypeClass::~ObjectTypeClass()
{
    ObjectTypes.Delete(this);
    if (unknown_a8 && unknown_a4 != 0) {
        operator delete(unknown_a4);
        unknown_a4 = 0;
        unknown_a8 = false;
    }
}
