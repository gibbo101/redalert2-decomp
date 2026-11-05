// void Selection::Leave_Territory() (0x0072F340)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Leave_Territory()
{
    Play_Sound("MapLeave");
    unknown_460 = -1;
    rc_ptr<Territory> none;
    Select_Territory(none);
}
}
// @ref ??_7?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@6B@=007af37c
// @ref ??_7?$rc_ptr@VTerritory@WorldDominationTour@@@@6B@=007af27c
// @ref ??_C@_08DLBG@MapLeave?$AA@=007fc43c
// @ref ??_C@_08DLBG@MapLeave?$AA@=007fc43c
// @ref ?Select_Territory@Selection@WorldDominationTour@@QAE_NABV?$rc_ptr@VTerritory@WorldDominationTour@@@@@Z=0072ed80
// @ref ??_G?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@UAEPAXI@Z=007303b0
// @ref ??B?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@UBE_NXZ=00730360
// @ref ??E?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@UAEAAV0@XZ=00730410
// @ref ??F?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@UAEAAV0@XZ=00730420
