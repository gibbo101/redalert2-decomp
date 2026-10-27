// Dynamic initializer of ScrollClass::Counter (0x00669590, _$E) and its
// guarded atexit destructor (0x006695C0; guard byte 0x00AB7038), emitted by
// this definition (the timer's destructor is empty).
#include "shared/scroll.hpp"
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref _atexit=0078298a
// @ref ?Counter@ScrollClass@@2V?$CDTimerClass@VSystemTimerClass@@@@A=00ab7048

CDTimerClass<SystemTimerClass> ScrollClass::Counter;
// @ref _$E79=006695c0
// @ref _$S80=00ab7038
