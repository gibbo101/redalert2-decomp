#define SOUND_PLAY_DECLARE_HANDLE_INIT
#include "shared/sound_play.hpp"
extern AudioBag *Audio_Event_Bag;
// @ref ?Audio_Event_Bag@@3PAUAudioBag@@A=00830fac
void AudioEventHandle::Init()
{
    Token = &Audio_Event_Bag;
    Event = 0;
    Serial = 0;
    Type = 0;
}
