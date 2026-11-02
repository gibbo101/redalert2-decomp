// The frame and tick timers of the unit at 0x0040E3C0 (Westwood's FrameTimer, NetFrameTimer
// and TickCount; names hypotheses). Each dynamic initializer reads its time source before the
// source member is constructed (Started precedes Timer), then registers the atexit destructor
// that follows it: 0x0040E9A0 and 0x0040EA20 only return, 0x0040E9E0 runs ~MSTimerClass.
#include "shared/main_loop.hpp"
#include "shared/comm_buffer.hpp"
// @ref ??0MSTimerClass@@QAE@XZ=005b6a00
// @ref ??1MSTimerClass@@QAE@XZ=005b6a10
// @ref ??BMSTimerClass@@QBEJXZ=005b6a20
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref _atexit=0078298a
// @ref ?unknown_frame_timer_839990@@3V?$CDTimerClass@VSystemTimerClass@@@@A=00839990
// @ref ?unknown_net_frame_timer_839970@@3V?$CDTimerClass@VMSTimerClass@@@@A=00839970
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980
// @ref _$E43=0040e9a0
// @ref _$E48=0040e9e0
// @ref _$E53=0040ea20

CDTimerClass<SystemTimerClass> unknown_frame_timer_839990;
CDTimerClass<MSTimerClass> unknown_net_frame_timer_839970;
TTimerClass<SystemTimerClass> TickCount;
