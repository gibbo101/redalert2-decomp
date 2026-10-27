// void __fastcall unknown_start(UnknownFixedTimer_00407030 *timer, int target) -- 0x00407030
// Purpose: (re)starts a 16.16 fixed-point interpolating timer: clears the
// flags, latches the current 64-bit time (0x004092D0) at +0x18, marks it
// running (bit 0), sets the per-second rate 1000 (+0x10) and its scaled
// reciprocal 0x10624D (+0x0C), the target value (+0x08, 16.16), zeroes
// +0x14 and updates (0x004070F0). No direct callers. Names are hypotheses.
// @ref ?unknown_time_4092d0@@YA_JXZ=004092d0
// @ref ?unknown_update_4070f0@@YIXPAUUnknownFixedTimer_00407030@@@Z=004070f0

__int64 unknown_time_4092d0();

struct UnknownFixedTimer_00407030 {
    unsigned int Flags;          // +0x00 bit 0 running
    int Current;                 // +0x04 (16.16)
    int Target;                  // +0x08 (16.16)
    int RateScale;               // +0x0C
    int Rate;                    // +0x10
    int unknown_14;              // +0x14
    struct {
        unsigned int LowPart;
        unsigned int HighPart;
    } StartTime;                 // +0x18 (64-bit time)
};

void __fastcall unknown_update_4070f0(UnknownFixedTimer_00407030 *timer);

void __fastcall unknown_start_00407030(UnknownFixedTimer_00407030 *timer, int target)
{
    timer->Flags = 0;
    unsigned __int64 now = unknown_time_4092d0();
    timer->StartTime.LowPart = (unsigned int)now;
    timer->Rate = 1000;
    timer->Flags |= 1;
    timer->Target = target << 16;
    timer->StartTime.HighPart = (unsigned int)(now >> 32);
    timer->RateScale = 0x10624d;
    timer->unknown_14 = 0;
    unknown_update_4070f0(timer);
}
