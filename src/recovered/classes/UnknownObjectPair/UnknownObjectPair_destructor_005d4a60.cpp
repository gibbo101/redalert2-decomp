// UnknownObjectPair::~UnknownObjectPair() (0x005D4A60)
#include "shared/object_type.hpp"
// @ref ??1UnknownPairFirst@@QAE@XZ=007190c0
// @ref ??1UnknownPairSecond@@QAE@XZ=0059eba0
// @ref ??3@YAXPAX@Z=00781d3b

UnknownObjectPair::~UnknownObjectPair()
{
    delete unknown_00;
    unknown_00 = 0;
    delete unknown_04;
    unknown_04 = 0;
}
