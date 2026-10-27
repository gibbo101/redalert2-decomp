#include "shared/unknown_pair_second.hpp"
#include "shared/matrix3d.hpp"

// Scales the translation column of every section/frame transform (the .HVA
// motion library scale applied by the voxel loader).
void UnknownPairSecond::unknown_59ed30(float scale)
{
    for (unsigned frame = 0; frame < unknown_frame_count; frame++) {
        for (unsigned section = 0; section < unknown_section_count; section++) {
            unknown_transforms[frame * unknown_section_count + section].Row[0][3] *= scale;
            unknown_transforms[frame * unknown_section_count + section].Row[1][3] *= scale;
            unknown_transforms[frame * unknown_section_count + section].Row[2][3] *= scale;
        }
    }
}
