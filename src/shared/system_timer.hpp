// The system clock time source of CDTimerClass: timeGetTime() / 16
// (0x0069A430; an identical copy follows at 0x0069A440). Shared by the
// MSAnim/movie code and the screen layers (RadarClass +0x14FC).
#ifndef RA2_SHARED_SYSTEM_TIMER_HPP
#define RA2_SHARED_SYSTEM_TIMER_HPP

class SystemTimerClass {
public:
    operator long() const;
};

#endif
