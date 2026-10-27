#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
void __fastcall Wait_Timer_00496A20(long ticks)
{
    CDTimerClass<SystemTimerClass> wait(ticks);
    while (wait.Value() != 0) {}
}
