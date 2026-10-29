// MSOverlayAnim::MSOverlayAnim(Wstring const &filename, int x, int y, ConvertClass *drawer, int unknown_24,
//     DynamicVectorClass<MSAnim *> *anims, bool unknown_48, int frame, bool unknown9) (0x005AD370)
#include "shared/ms_anim.hpp"
// @ref ??_7MSOverlayAnim@@6B@=007a6db4

MSOverlayAnim::MSOverlayAnim(Wstring const &filename, int x, int y, ConvertClass *drawer, int unknown_24,
                             DynamicVectorClass<MSAnim *> *anims, bool unknown_48, int frame, bool unknown9) :
    MSFadeAnim(filename, x, y, drawer, unknown_24, 0, anims),
    unknown_48(unknown_48)
{
    Frame = frame;
    if (!unknown9) {
        unknown_40 = 4;
    }
}
