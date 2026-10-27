// MSFadeAnim::MSFadeAnim(Wstring const &filename, int x, int y, ConvertClass *drawer, int unknown_24, int flags, int unknown_44) (0x005ACDB0)
#include "shared/ms_anim.hpp"
// @ref ??_7MSFadeAnim@@6B@=007a6d8c

MSFadeAnim::MSFadeAnim(Wstring const &filename, int x, int y, ConvertClass *drawer, int unknown_24, int flags, int unknown_44) :
    MSShapeAnim(filename, x, y, drawer, unknown_24, false, flags),
    unknown_40(0),
    unknown_44(unknown_44)
{
}
