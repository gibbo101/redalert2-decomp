// int __stdcall unknown_callback_741750(int arg1, int result, UnknownTarget_0075eeb0 *target) -- 0x0075EEB0
// Purpose: a callback: when result is not negative, runs 0x00741750 on
// target; returns 0. arg1 is unused.
// Assumptions: the target class is unidentified (WOL area).
// @ref ?unknown_call_741750@UnknownTarget_0075eeb0@@QAEXXZ=00741750

struct UnknownTarget_0075eeb0 {
    void unknown_call_741750();             // 0x00741750
};

int __stdcall unknown_callback_741750(int arg1, int result, UnknownTarget_0075eeb0 *target)
{
    if (result >= 0) {
        target->unknown_call_741750();
    }
    return 0;
}
