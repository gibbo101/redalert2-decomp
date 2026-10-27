// A recorded timeGetTime() value (0x004D0040) and the global one built at
// startup (0x00866074, dynamic initializer 0x004D0030). Owner not identified.
#ifndef RA2_SHARED_UNKNOWN_TIME_STAMP_HPP
#define RA2_SHARED_UNKNOWN_TIME_STAMP_HPP

struct UnknownTimeStamp_004d0040 {
    UnknownTimeStamp_004d0040();                    // 0x004D0040 records timeGetTime()
    int unknown_elapsed_004d0050() const;           // 0x004D0050 milliseconds since then

    unsigned long Time;     // +0x00
};

extern UnknownTimeStamp_004d0040 unknown_time_stamp_866074;   // 0x00866074

#endif
