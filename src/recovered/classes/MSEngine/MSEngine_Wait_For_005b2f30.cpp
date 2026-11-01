// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// Wait for an animation to disappear or finish (005B2F30).
#include "shared/ms_engine.hpp"
#include "shared/ms_anim.hpp"
// @ref ?Run@MSEngine@@QAEXH@Z=005b3550
void MSEngine::Wait_For(MSAnim *anim,unsigned time)
{
    CDTimerClass<SystemTimerClass> timer(time);
    while (true) {
        int index=Anims.ID(anim);
        if (index==-1) break;
        if (Anims[index]->Unknown_Slot7()) break;
        if (time<=0) break;
        Run(1);
    }
}
