// A progress countdown: Building gate state uses the four words at +0x4D8.
// Name is a TibSun hypothesis; field width and behavior are checked on RA2.
#ifndef RA2_SHARED_PROGRESS_TIMER_HPP
#define RA2_SHARED_PROGRESS_TIMER_HPP
#include "shared/cd_timer.hpp"
template<class T> class ProgressTimerClass : protected CDTimerClass<T> {
public:
    ProgressTimerClass(int duration = 0) : CDTimerClass<T>(duration), TotalTime(duration) {}
    ProgressTimerClass(NoInitClass const &noinit) : CDTimerClass<T>(noinit) {}
    ~ProgressTimerClass() {}
    double Progress() const {
        if (TotalTime == 0) return 1.0;
        long elapsed = TotalTime - CDTimerClass<T>::Value();
        return (double)elapsed / TotalTime;
    }
protected:
    int TotalTime;
};
#endif
