// int MSEngine::Add_Anim(MSAnim *anim) (0x005B2D60)
// Appends an animation; its index, or -1 when null or the list is full.
#include "shared/ms_engine.hpp"

int MSEngine::Add_Anim(MSAnim *anim)
{
    if (anim != 0 && Anims.Add(anim)) {
        return Anims.ID(anim);
    }
    return -1;
}
