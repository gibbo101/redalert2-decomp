#include "shared/score.hpp"
#include "shared/sound_available.hpp"
#include "shared/crt_memory.hpp"
// 0x006682B0: 14-byte body and two original padding bytes.
// @ref _free=007825e8
ScoreSoundClass::~ScoreSoundClass()
{
    if (Name) {
        free(Name);
    }
}
