// void unknown_dispatch() -- 0x006F6490
// Purpose: runs 0x00614AA0 on the object 0x00617A00 returns, or, when
// there is none, 0x0042E990(-1, -1) on the object at 0x0084E8D0.
// Assumptions: the objects are unidentified; /O1 like its neighbours.
// @ref ?unknown_find_617a00@@YAPAUUnknownTarget_006f6490@@XZ=00617a00
// @ref ?unknown_call_614aa0@UnknownTarget_006f6490@@QAEXXZ=00614aa0
// @ref ?unknown_call_42e990@UnknownFallback_006f6490@@QAEXHH@Z=0042e990
// @ref ?unknown_object_84e8d0@@3UUnknownFallback_006f6490@@A=0084e8d0

struct UnknownTarget_006f6490 {
    void unknown_call_614aa0();             // 0x00614AA0
};
struct UnknownFallback_006f6490 {
    void unknown_call_42e990(int arg1, int arg2);   // 0x0042E990
};
UnknownTarget_006f6490 *unknown_find_617a00();      // 0x00617A00
extern UnknownFallback_006f6490 unknown_object_84e8d0;

void unknown_dispatch()
{
    UnknownTarget_006f6490 *target = unknown_find_617a00();
    if (target != 0) {
        target->unknown_call_614aa0();
        return;
    }
    unknown_object_84e8d0.unknown_call_42e990(-1, -1);
}
