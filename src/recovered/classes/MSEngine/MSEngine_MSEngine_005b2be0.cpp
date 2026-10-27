// MSEngine::MSEngine() (0x005B2BE0)
// Empty lists and room for 20 dirty rectangles.
#include "shared/ms_engine.hpp"
// @ref ??_7MSEngine@@6B@=007a7028
// @ref ??_7?$DynamicVectorClass@PAVMSAnim@@@@6B@=007a7058
// @ref ??_7?$DynamicVectorClass@PAVMSSfx@@@@6B@=007a7038
// @ref ??_7?$VectorClass@VRect@@@@6B@=007a5eb0

MSEngine::MSEngine()
{
    RectCount = 0;
    Rects.Resize(20);
    Anims.Clear();
    Sfx.Clear();
}
