// Tactical::Tactical(NoInitClass const &) (0x006A26C0): Load's placement
// constructor. Only the AbstractClass base, the flag pair at +0xAC (its NoInitClass
// constructor does nothing) and the timer at +0xDA4 (it has no
// NoInitClass constructor of its own) are constructed; then the vptrs. The
// unit emits the vtables; their slots are bound below.
#include "shared/tactical.hpp"
// @ref ??_7Tactical@@6BIPersistStream@@@=007ac570
// @ref ??_7Tactical@@6BIRTTITypeInfo@@@=007ac554
// @ref ??_7Tactical@@6BINoticeSink@@@=007ac54c
// @ref ??_7Tactical@@6BINoticeSource@@@=007ac544
// @ref ??_GTactical@@UAEPAXI@Z=006ac800
// @ref ??_ETactical@@UAEPAXI@Z=006ac800
// @ref ??1Tactical@@UAE@XZ=006a2710
// @ref ?Detach@Tactical@@UAEXPAVAbstractClass@@_N@Z=006aab60
// @ref ?GetClassID@Tactical@@UAGJPAUGUID@@@Z=006ac2e0
// @ref ?Load@Tactical@@UAGJPAUIStream@@@Z=006ac320
// @ref ?Save@Tactical@@UAGJPAUIStream@@H@Z=006ac400
// @ref ?Kind_Of@Tactical@@UBEHXZ=006ac7e0
// @ref ?Size_Of@Tactical@@UBEHXZ=006ac7f0
// @ref ?AI@Tactical@@UAEXXZ=006a2dd0
// @ref ?unknown_slot24@Tactical@@UAE_NABUCoordStruct@@0HH@Z=006ac160

Tactical::Tactical(NoInitClass const &noinit)
    : AbstractClass(noinit),
      unknown_ac(noinit)
{
}
