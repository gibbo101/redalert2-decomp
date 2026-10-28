// BombClass::BombClass() (0x00435BE0): an unplanted bomb with the ticking
// sound from Rules; added to the bomb list.
#include "shared/object.hpp"
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ?Init@UnknownAudioController@@QAEXXZ=00405bf0
// @ref ??_7BombClass@@6BIPersistStream@@@=0079ca08
// @ref ??_7BombClass@@6BIRTTITypeInfo@@@=0079c9ec
// @ref ??_7BombClass@@6BINoticeSink@@@=0079c9e4
// @ref ??_7BombClass@@6BINoticeSource@@@=0079c9dc
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Kind_Of@BombClass@@UBEHXZ=004369e0
// @ref ?Size_Of@BombClass@@UBEHXZ=004369d0
// @ref ?GetClassID@BombClass@@UAGJPAUGUID@@@Z=00436100
// @ref ?Save@BombClass@@UAGJPAUIStream@@H@Z=004361d0

BombClass::BombClass() :
    unknown_54(0)
{
    unknown_28 = 0;
    Target = 0;
    unknown_58 = false;
    unknown_3c.Init();
    unknown_50 = Rules->BombTickingSound;
    unknown_BombClass_list_0084eb78.Add(this);
}
