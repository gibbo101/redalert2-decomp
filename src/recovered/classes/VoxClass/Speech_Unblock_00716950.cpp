// void Unknown_00716950() (0x00716950): counts the speech block down, not
// below 0.
#include "shared/vox_speech.hpp"
// @ref ?unknown_vox_ad0878@@3HC=00ad0878

void Unknown_00716950()
{
    if (unknown_vox_ad0878 != 0) {
        if (--unknown_vox_ad0878 < 0) {
            unknown_vox_ad0878 = 0;
        }
    }
}
