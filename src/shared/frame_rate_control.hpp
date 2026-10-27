#ifndef RA2_SHARED_FRAME_RATE_CONTROL_HPP
#define RA2_SHARED_FRAME_RATE_CONTROL_HPP

// Frame-rate adjustment receiver observed at 0x00A40B18; full layout unknown.
class UnknownFrameRateControl {
public:
    int Adjust_005d9760(int rate) const;
    int unknown_00;
};
extern UnknownFrameRateControl unknown_frame_rate_a40b18;

#endif
