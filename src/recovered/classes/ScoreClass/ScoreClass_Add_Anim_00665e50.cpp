// int ScoreClass::Add_Anim(ScoreAnimClass *anim) (0x00665E50)
// Lists a new animation for Update_Anims; nonzero when it was added.
#include "shared/score.hpp"

int ScoreClass::Add_Anim(ScoreAnimClass *anim)
{
    return Anims.Add(anim);
}
