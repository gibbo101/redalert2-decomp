#include "shared/map_select.hpp"
// @ref ??4Wstring@@QAEAAV0@ABV0@@Z=0076dc30
// @ref ??BSystemTimerClass@@=0069a430
void MapSelect::Queue_Voice_0058fd30(Wstring const &name,int delay)
{
    VoiceName=name;
    VoiceTimer=CDTimerClass<SystemTimerClass>(delay);
}
