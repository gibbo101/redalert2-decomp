// ObjectClass::ObjectClass() (0x005D22E0)
#include "shared/object_type.hpp"
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ?Init@UnknownAudioController@@QAEXXZ=00405bf0
// @ref ?unknown_objects_a40368@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40368
// @ref ?unknown_objects_ac0d60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00ac0d60
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0
// @ref ?unknown_objects_ac0c58@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00ac0c58
// @ref ??_7ObjectClass@@6BIPersistStream@@@=007a7498
// @ref ??_7ObjectClass@@6BIRTTITypeInfo@@@=007a747c
// @ref ??_7ObjectClass@@6BINoticeSink@@@=007a7474
// @ref ??_7ObjectClass@@6BINoticeSource@@@=007a746c

ObjectClass::ObjectClass() :
    unknown_30(0),
    unknown_34(0),
    unknown_38(0),
    unknown_64(-1),
    unknown_68(false),
    Strength(0xFF),
    unknown_70(0xFF),
    unknown_74(false),
    unknown_75(false),
    unknown_76(true),
    unknown_77(false),
    unknown_78(false),
    unknown_79(false),
    unknown_7a(false),
    unknown_7b(false),
    unknown_7c(false),
    unknown_7d(true),
    unknown_80(-1),
    unknown_84(false),
    unknown_85(true),
    Coord(unknown_geometry_l),
    unknown_94(0)
{
    unknown_3c.Init();
    unknown_50.Init();
    unknown_objects_a40368.Add(this);
    unknown_objects_ac0d60.Add(this);
    unknown_objects_ac0cb0.Add(this);
    unknown_objects_ac0c58.Add(this);
    unknown_14_bit1 = 1;
}
