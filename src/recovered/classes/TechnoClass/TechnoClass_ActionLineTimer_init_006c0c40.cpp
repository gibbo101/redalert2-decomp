// Techno.CPP's two static timers (TibSun TechnoClass::ActionLineTimer and
// TalkBubbleTimer), defined after the unit's header statics: dynamic
// initializers 0x006C0C40 / 0x006C0C80 (_$E) and their guarded atexit
// destructors 0x006C0C60 / 0x006C0CB0 (guard byte 0x00AC0128; the timer's
// destructor is empty), emitted by these definitions.
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref _atexit=0078298a
// @ref ?ActionLineTimer@TechnoClass@@2V?$CDTimerClass@VFrameTimerClass@@@@A=00ac0178
// @ref ?TalkBubbleTimer@TechnoClass@@2V?$CDTimerClass@VSystemTimerClass@@@@A=00ac0168

CDTimerClass<FrameTimerClass> TechnoClass::ActionLineTimer;
CDTimerClass<SystemTimerClass> TechnoClass::TalkBubbleTimer;
// @ref _$E51=006c0c60
// @ref _$E57=006c0cb0
// @ref _$S52=00ac0128
