// void ObjectClass::unknown_slot60() (0x005D4E90)
#include "shared/object_type.hpp"
// @ref ?unknown_objects_ac0cd8@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cd8
// @ref ?Unknown_00435FB0@BombClass@@QAEXXZ=00435fb0
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90

void ObjectClass::unknown_slot60()
{
    if (unknown_38 != 0) {
        unknown_38->Unknown_00435FB0();
    }
    Unknown_006ECB90(this, true);
    unknown_slot52();
    unknown_7d = false;
    unknown_objects_ac0cd8.Add(this);
}
