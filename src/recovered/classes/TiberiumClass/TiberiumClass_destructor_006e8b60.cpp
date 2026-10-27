// TiberiumClass::~TiberiumClass() (0x006E8B60)
#include "shared/tiberium.hpp"
// @ref ??1AbstractTypeClass@@UAE@XZ=00410740
// @ref ?Detach_This_From_All@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0

TiberiumClass::~TiberiumClass()
{
    Detach_This_From_All(this, true);
    unknown_objects_ac0cb0.Delete(this);
    unknown_TiberiumClass_list_00ac0b30.Delete(this);
    delete unknown_fc;
    unknown_fc = 0;
    delete unknown_f8;
    unknown_f8 = 0;
    delete unknown_f4;
    unknown_f4 = 0;
    if (unknown_110) {
        unknown_110->Clear();
        delete unknown_110;
        unknown_110 = 0;
    }
    if (unknown_118) {
        delete unknown_118;
        unknown_118 = 0;
    }
    if (unknown_114) {
        delete unknown_114;
        unknown_114 = 0;
    }
    unknown_10c = 0;
}
