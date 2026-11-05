// bool ScoreClass::Is_Anim_Done(ScoreAnimClass *anim) (0x00665EC0)
// True once Update_Anims has removed the (finished) animation.
#include "shared/score.hpp"
bool ScoreClass::Is_Anim_Done(ScoreAnimClass *anim)
{
    bool done = Anims.ID(anim) == -1 ? true : false;
    return done;
}
