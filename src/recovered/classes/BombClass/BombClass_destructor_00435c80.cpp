// BombClass::~BombClass() (0x00435C80): stops the ticking sound and leaves the
// bomb list.
#include "shared/object.hpp"
// @ref ?Unknown_00405C10@UnknownAudioController@@QAEXXZ=00405c10
// @ref ??1AbstractClass@@UAE@XZ=0040ff90

BombClass::~BombClass()
{
    unknown_3c.Unknown_00405C10();
    unknown_BombClass_list_0084eb78.Delete(this);
}
