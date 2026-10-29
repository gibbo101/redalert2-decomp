// MSFadeAnim::MSFadeAnim(Wstring const &filename, int x, int y, ConvertClass *drawer, int unknown_24, int flags,
//     DynamicVectorClass<MSAnim *> *anims) (0x005ACDB0)
#include "shared/ms_anim.hpp"
// @ref ??_7MSFadeAnim@@6B@=007a6d8c

MSFadeAnim::MSFadeAnim(Wstring const &filename, int x, int y, ConvertClass *drawer, int unknown_24, int flags,
                       DynamicVectorClass<MSAnim *> *anims) :
    MSShapeAnim(filename, x, y, drawer, unknown_24, false, flags),
    unknown_40(0),
    Anims(anims)
{
}
