// AudioSourceInfo *AudioSource::Info() -- 0x00408440
// Purpose: the source's first piece, or 0 when it has none.
#include "shared/audio.hpp"

AudioSourceInfo *AudioSource::Info()
{
    return (AudioSourceInfo *)Audio_List_Next_Unchecked(&Pieces);
}
