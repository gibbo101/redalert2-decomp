// void ObjectTypeClass::unknown_func_5d66a0() (0x005D66A0)
// Frees both voxel-pair tables (unknown_c8 and unknown_140, 15 each).
#include "shared/object_type.hpp"
// @ref ??1UnknownPairFirst@@QAE@XZ=007190c0
// @ref ??1UnknownPairSecond@@QAE@XZ=0059eba0
// @ref ??3@YAXPAX@Z=00781d3b

void ObjectTypeClass::unknown_func_5d66a0()
{
    for (int index = 0; index < 15; index++) {
        if (unknown_c8[index].unknown_00 != 0) {
            delete unknown_c8[index].unknown_00;
            unknown_c8[index].unknown_00 = 0;
        }
        if (unknown_c8[index].unknown_04 != 0) {
            delete unknown_c8[index].unknown_04;
            unknown_c8[index].unknown_04 = 0;
        }
        if (unknown_140[index].unknown_00 != 0) {
            delete unknown_140[index].unknown_00;
            unknown_140[index].unknown_00 = 0;
        }
        if (unknown_140[index].unknown_04 != 0) {
            delete unknown_140[index].unknown_04;
            unknown_140[index].unknown_04 = 0;
        }
    }
}
