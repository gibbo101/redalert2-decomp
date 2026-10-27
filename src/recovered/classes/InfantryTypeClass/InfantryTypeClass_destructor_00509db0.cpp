// InfantryTypeClass::~InfantryTypeClass() (0x00509DB0)
// Leaves InfantryTypes and frees the sequences.
#include "shared/infantry_type.hpp"
// @ref ??_7InfantryTypeClass@@6BIPersistStream@@@=007a3a78
// @ref ??_7InfantryTypeClass@@6BIRTTITypeInfo@@@=007a3a5c
// @ref ??_7InfantryTypeClass@@6BINoticeSink@@@=007a3a54
// @ref ??_7InfantryTypeClass@@6BINoticeSource@@@=007a3a4c
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?InfantryTypes@@3V?$DynamicVectorClass@PAVInfantryTypeClass@@@@A=00a40350
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_7?$VectorClass@H@@6B@=0079d9d4
// @ref ??_7?$VectorClass@PAVAnimTypeClass@@@@6B@=007a3b5c
// @ref ??1TechnoTypeClass@@UAE@XZ=006da950

InfantryTypeClass::~InfantryTypeClass()
{
    Unknown_006ECB90(this, true);
    InfantryTypes.Delete(this);
    operator delete(DoControls);
    DoControls = 0;
}
