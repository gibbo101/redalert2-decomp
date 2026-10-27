// AbstractTypeClass::~AbstractTypeClass() (0x00410740)
// Removes the type from AbstractTypes.
#include "shared/abstract_type.hpp"
// @ref ??1AbstractClass@@UAE@XZ=0040ff90
// @ref ?AbstractTypes@@3V?$DynamicVectorClass@PAVAbstractTypeClass@@@@A=00a40928
// @ref ??_7AbstractTypeClass@@6BIPersistStream@@@=0079ae88
// @ref ??_7AbstractTypeClass@@6BIRTTITypeInfo@@@=0079ae6c
// @ref ??_7AbstractTypeClass@@6BINoticeSink@@@=0079ae64
// @ref ??_7AbstractTypeClass@@6BINoticeSource@@@=0079ae5c

AbstractTypeClass::~AbstractTypeClass()
{
    AbstractTypes.Delete(this);
}
