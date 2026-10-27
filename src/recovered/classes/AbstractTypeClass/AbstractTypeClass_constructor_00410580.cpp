// AbstractTypeClass::AbstractTypeClass(char const *ini_name) (0x00410580)
// A type named ini_name (or its own address in hex); Name starts as the ID; registers it in AbstractTypes.
#include "shared/abstract_type.hpp"
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ?AbstractTypes@@3V?$DynamicVectorClass@PAVAbstractTypeClass@@@@A=00a40928
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
// @ref ??_7AbstractTypeClass@@6BIPersistStream@@@=0079ae88
// @ref ??_7AbstractTypeClass@@6BIRTTITypeInfo@@@=0079ae6c
// @ref ??_7AbstractTypeClass@@6BINoticeSink@@@=0079ae64
// @ref ??_7AbstractTypeClass@@6BINoticeSource@@@=0079ae5c
// @ref ??_C@_04CLEA@?$CF08X?$AA@=007ce280

AbstractTypeClass::AbstractTypeClass(char const *ini_name)
{
    if (ini_name == 0) {
        char buffer[16];
        sprintf(buffer, "%08X", this);
        ID = buffer;
    } else {
        ID = ini_name;
    }
    Name = ID;
    UIName = unknown_empty_wide_839d4c;
    AbstractTypes.Add(this);
}
