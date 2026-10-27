// ObjectClass::~ObjectClass() (0x005D2530)
#include "shared/object_type.hpp"
// @ref ??1AbstractClass@@UAE@XZ=0040ff90
// @ref ?Unknown_00405C10@UnknownAudioController@@QAEXXZ=00405c10
// @ref ?Unknown_00405D50@UnknownAudioController@@QAEXXZ=00405d50
// @ref ?unknown_objects_a40368@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40368
// @ref ?unknown_objects_ac0d60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00ac0d60
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0
// @ref ?unknown_objects_ac0c58@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00ac0c58
// @ref ?unknown_objects_ac0cd8@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00ac0cd8
// @ref ??_7ObjectClass@@6BIPersistStream@@@=007a7498
// @ref ??_7ObjectClass@@6BIRTTITypeInfo@@@=007a747c
// @ref ??_7ObjectClass@@6BINoticeSink@@@=007a7474
// @ref ??_7ObjectClass@@6BINoticeSource@@@=007a746c

ObjectClass::~ObjectClass()
{
    unknown_objects_ac0cd8.Delete(this);
    unknown_objects_a40368.Delete(this);
    unknown_objects_ac0d60.Delete(this);
    unknown_objects_ac0cb0.Delete(this);
    unknown_objects_ac0c58.Delete(this);
    unknown_30 = 0;
    unknown_7d = false;
    unknown_3c.Unknown_00405D50();
    unknown_50.Unknown_00405D50();
    unknown_3c.Unknown_00405C10();
    unknown_50.Unknown_00405C10();
    unknown_func_5d2710();
}
