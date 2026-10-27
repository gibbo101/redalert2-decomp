// void VoxelAnimTypeClass::Detach(AbstractClass *target, bool all) (0x0070ED10)
// Clears every type pointer that refers to a removed object.
#include "shared/voxel_anim_type.hpp"

void VoxelAnimTypeClass::Detach(AbstractClass *target, bool all)
{
    if ((AbstractClass *)Warhead == target) {
        Warhead = 0;
    }
    if ((AbstractClass *)BounceAnim == target) {
        BounceAnim = 0;
    }
    if ((AbstractClass *)ExpireAnim == target) {
        ExpireAnim = 0;
    }
    if ((AbstractClass *)TrailerAnim == target) {
        TrailerAnim = 0;
    }
    if ((AbstractClass *)Spawns == target) {
        Spawns = 0;
    }
    if ((AbstractClass *)AttachedSystem == target) {
        AttachedSystem = 0;
    }
}
