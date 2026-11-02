// CDTimerClass<FrameTimerClass>::Stop, original006B32C0 complete54+10.
#include "shared/cd_timer.hpp"
template<> void CDTimerClass<FrameTimerClass>::Stop()
{
    if (Started != -1) {
        DelayTime = Value();
        Started = -1;
    }
}

