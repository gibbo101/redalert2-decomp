// void MSEngine::Replace_Anim(MSAnim *anim, MSAnim *old) (0x005B2DD0)
// Inserts anim after old (at index 0 when old is absent), then removes and
// deletes old.
#include "shared/ms_engine.hpp"
// @ref _memmove=00783290

void MSEngine::Replace_Anim(MSAnim *anim, MSAnim *old)
{
    Anims.Add_After(anim, old);
    Remove_Anim(old);
}
