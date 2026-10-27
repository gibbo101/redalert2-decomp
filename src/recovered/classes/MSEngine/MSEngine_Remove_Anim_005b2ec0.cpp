// void MSEngine::Remove_Anim(MSAnim *anim) (0x005B2EC0)
// Removes and deletes an animation in the list.
#include "shared/ms_engine.hpp"

void MSEngine::Remove_Anim(MSAnim *anim)
{
    if (anim != 0 && Anims.ID(anim) != -1) {
        Anims.Delete(anim);
        delete anim;
    }
}
