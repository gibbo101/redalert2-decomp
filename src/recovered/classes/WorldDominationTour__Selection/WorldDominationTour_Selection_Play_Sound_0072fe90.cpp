// void Selection::Play_Sound(Wstring const &name) (0x0072FE90)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Play_Sound(Wstring const &name)
{
    if (name != 0) {
        SfxCursor cursor(Sounds);
        while (cursor && name == (*cursor)->Name) {
            ++cursor;
        }
        if (cursor) {
            (*cursor)->Play();
        }
    }
}
}
// @ref ??_7?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@6B@=007af37c
// @ref ??_G?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@UAEPAXI@Z=007303b0
// @ref ??B?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@UBE_NXZ=00730360
// @ref ??E?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@UAEAAV0@XZ=00730410
// @ref ??F?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@UAEAAV0@XZ=00730420
