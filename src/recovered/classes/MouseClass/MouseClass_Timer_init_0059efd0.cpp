// Dynamic initializer of MouseClass::Timer (0x0059EFD0, _$E) and its guarded
// atexit destructor (0x0059F000; guard byte 0x00A70F18), emitted by this
// definition (the timer's destructor is empty).
#include "shared/mouse_class.hpp"
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref _atexit=0078298a
// @ref ?Timer@MouseClass@@2V?$CDTimerClass@VSystemTimerClass@@@@A=00a70f70

CDTimerClass<SystemTimerClass> MouseClass::Timer;
// @ref _$E82=0059f000
// @ref _$S83=00a70f18
