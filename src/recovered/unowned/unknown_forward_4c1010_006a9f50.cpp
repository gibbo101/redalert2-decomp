// void __stdcall unknown_forward_4c1010(UnknownTarget_006a9f50 *target) -- 0x006A9F50
// Purpose: runs 0x004C1010 on target.
// Assumptions: a callback-style wrapper; target's class is unidentified.
// @ref ?unknown_call_4c1010@UnknownTarget_006a9f50@@QAEXXZ=004c1010

struct UnknownTarget_006a9f50 {
    void unknown_call_4c1010();             // 0x004C1010
};

void __stdcall unknown_forward_4c1010(UnknownTarget_006a9f50 *target)
{
    target->unknown_call_4c1010();
}
