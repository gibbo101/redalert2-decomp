// MSEngine::~MSEngine() (0x005B2C70)
// Deletes the sound effects and the animations it owns.
#include "shared/ms_engine.hpp"
// @ref ??1MSSfx@@QAE@XZ=005b69e0
// @ref ??_7?$VectorClass@PAVMSAnim@@@@6B@=007a7078
// @ref ??_7?$VectorClass@PAVMSSfx@@@@6B@=007a7098
// @ref ??_7?$VectorClass@VRect@@@@6B@=007a5eb0

MSEngine::~MSEngine()
{
    int index;
    for (index = 0; index < Sfx.Count(); index++) {
        if (Sfx[index] != 0) {
            delete Sfx[index];
        }
    }
    Sfx.Clear();
    for (index = 0; index < Anims.Count(); index++) {
        if (Anims[index] != 0) {
            delete Anims[index];
        }
    }
    Anims.Clear();
    Rects.Clear();
}
