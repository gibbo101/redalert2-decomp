// Seven 24-byte records at 0x00AABDD0 with a timeGetTime stamp at +0x14.
// The dynamic initializer 0x006232D0 sets +0x00 to -1 and the rest to 0;
// 0x00623300 stamps one record. What the records describe is unknown.
#ifndef RA2_SHARED_UNKNOWN_TIMED_SLOTS_HPP
#define RA2_SHARED_UNKNOWN_TIMED_SLOTS_HPP

struct UnknownTimedSlot_aabdd0 {
    int unknown_00;                 // +0x00 (initially -1)
    int unknown_04;                 // +0x04
    int unknown_08;                 // +0x08
    int unknown_0C;                 // +0x0C
    int unknown_10;                 // +0x10
    unsigned long Time;             // +0x14 timeGetTime() when stamped
};

extern UnknownTimedSlot_aabdd0 unknown_timed_slots_aabdd0[7];   // 0x00AABDD0

// Stamps record index with the current timeGetTime() (0x00623300).
void __fastcall unknown_stamp_timed_slot_00623300(int index);

#endif
