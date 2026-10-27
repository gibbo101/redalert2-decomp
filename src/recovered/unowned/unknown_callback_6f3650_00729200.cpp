// bool __stdcall unknown_callback_6f3650(int arg1, int arg2) -- 0x00729200
// Purpose: while the flag at 0x007FBD04 is set, passes both arguments
// and 1 to 0x006F3650; returns false.
// Assumptions: the flag and the callee are unidentified.
// @ref ?unknown_flag_7fbd04@@3_NA=007fbd04
// @ref ?unknown_call_6f3650@@YIXHHH@Z=006f3650

extern bool unknown_flag_7fbd04;
void __fastcall unknown_call_6f3650(int arg1, int arg2, int arg3);  // 0x006F3650

bool __stdcall unknown_callback_6f3650(int arg1, int arg2)
{
    if (unknown_flag_7fbd04) {
        unknown_call_6f3650(arg1, arg2, 1);
    }
    return false;
}
