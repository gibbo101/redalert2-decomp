// void UnknownOwner_00714460::unknown_bump_and_notify() -- 0x00714460
// Purpose: counts up +0x30, asks the member at +0x0C for an object
// (0x00406140) and, when there is one, runs 0x004053F0 on it.
// Assumptions: owner, member and object classes are unidentified (sound
// area). The counter is volatile (read, incremented and written back
// without folding).
// @ref ?unknown_find_406140@UnknownPart_00714460@@QAEPAUUnknownTarget_00714460@@XZ=00406140
// @ref ?unknown_call_4053f0@UnknownTarget_00714460@@QAEXXZ=004053f0

struct UnknownTarget_00714460 {
    void unknown_call_4053f0();             // 0x004053F0
};
struct UnknownPart_00714460 {
    UnknownTarget_00714460 *unknown_find_406140();  // 0x00406140
};
struct UnknownOwner_00714460 {
    char unknown_00[0x0C];
    UnknownPart_00714460 unknown_0c;        // +0x0C
    char unknown_0d[0x30 - 0x0D];
    volatile int unknown_30;                // +0x30
    void unknown_bump_and_notify();
};

void UnknownOwner_00714460::unknown_bump_and_notify()
{
    unknown_30++;
    UnknownTarget_00714460 *target = unknown_0c.unknown_find_406140();
    if (target != 0) {
        target->unknown_call_4053f0();
    }
}
