// void __fastcall AudioTimeSpan::Format(char *buffer) -- 0x004039C0
// Purpose: print "period (elapsed,maximum,peak,~late) spinner" for the device dump; the spinner advances once per tick.
// @ref ?Audio_Time_Span_Spinner@@3PADA=0x007CC96C
// @ref ??_C@_0CC@IMPB@?$CF05dms?5?$CI?$CF04d?0?$CF04d?0?$CF04d?0?$HO?$CF2d?$CJ?5?$CFc?5@=0x007CC978
#include "shared/crt_string.hpp"
#include "shared/audio.hpp"

extern char *Audio_Time_Span_Spinner;

void __fastcall AudioTimeSpan::Format(char *buffer)
{
    __int64 now = Audio_Now();
    if (TickCount != unknown_50) {
        if ((unsigned)++unknown_54 >= strlen(Audio_Time_Span_Spinner)) {
            unknown_54 = 0;
        }
        unknown_50 = TickCount;
    }
    if ((unsigned __int64)(unknown_40 + unknown_38) < (unsigned __int64)now) {
        Maximum = unknown_00;
        unknown_38 = now;
    }
    sprintf(buffer, "%05dms (%04d,%04d,%04d,~%2d) %c \n", (int)unknown_00, (int)Elapsed, (int)Maximum, (int)Peak,
            LateCount, Audio_Time_Span_Spinner[unknown_54]);
}
