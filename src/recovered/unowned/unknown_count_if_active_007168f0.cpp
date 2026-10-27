// void unknown_count_if_active() -- 0x007168F0
// Purpose: counts (0x00AD0910) while the value at 0x00AD0968 is set.
// Assumptions: both globals are unidentified (sound area); the counter is
// volatile (it is read and written back without folding, like the
// countdown at 0x00AD08C8).
// @ref ?unknown_active_ad0968@@3HA=00ad0968
// @ref ?unknown_count_ad0910@@3HC=00ad0910

extern int unknown_active_ad0968;
extern volatile int unknown_count_ad0910;

void unknown_count_if_active()
{
    if (unknown_active_ad0968 != 0) {
        unknown_count_ad0910++;
    }
}
