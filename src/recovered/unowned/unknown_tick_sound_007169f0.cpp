// void unknown_tick_sound() -- 0x007169F0
// Purpose: runs 0x00407F20 on the object at 0x00AD095C when there is one,
// then counts 0x00AD08C8 down to 0.
// Assumptions: sound area; names are hypotheses.
// @ref ?unknown_object_ad095c@@3PAUUnknownSound_007169f0@@A=00ad095c
// @ref ?unknown_call_407f20@UnknownSound_007169f0@@QAEXXZ=00407f20
// @ref ?unknown_countdown_ad08c8@@3HC=00ad08c8

struct UnknownSound_007169f0 {
    void unknown_call_407f20();             // 0x00407F20
};
extern UnknownSound_007169f0 *unknown_object_ad095c;
extern volatile int unknown_countdown_ad08c8;

void unknown_tick_sound()
{
    if (unknown_object_ad095c != 0) {
        unknown_object_ad095c->unknown_call_407f20();
    }
    if (unknown_countdown_ad08c8 != 0) {
        if (--unknown_countdown_ad08c8 < 0) {
            unknown_countdown_ad08c8 = 0;
        }
    }
}
