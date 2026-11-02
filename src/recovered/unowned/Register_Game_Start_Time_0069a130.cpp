#include "shared/bench.hpp"
#include "shared/system_timer.hpp"
// @ref ??RSystemTimerClass@@QBEJXZ=0069a430
// @ref ?GameTimer@@=00abd4c0
// @ref ?GameTimerInUse@@=00abd52c
extern BasicTimerClass<SystemTimerClass> GameTimer;
extern bool GameTimerInUse;
void Register_Game_Start_Time_0069a130()
{
    GameTimer=0;
    GameTimerInUse=true;
}

// External relocations checked against original operands.
// @ref ??RSystemTimerClass@@QBEJXZ=0069a430
// @ref ?GameTimer@@3V?$BasicTimerClass@VSystemTimerClass@@@@A=00abd4c0
// @ref ?GameTimerInUse@@3_NA=00abd52c
