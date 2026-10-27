// void Audio_DS_Stop_Primary() -- 0x0040A860
// Purpose: stops the primary buffer, if any.
// @ref ?Audio_Primary_Buffer@@3PAUIDirectSoundBuffer@@A=008315b0
#include "shared/audio.hpp"

void Audio_DS_Stop_Primary()
{
    if (Audio_Primary_Buffer != 0) {
        Audio_Primary_Buffer->Stop();
    }
}
