// A radiation or chrono beam (0xB8 bytes; 0x00635440 allocates one into the
// list at 0x00AB64E8 and constructs it with 0x006356B0). The class name and
// member names are hypotheses (public YR references call it RadBeam); the
// setters are the out-of-line members TechnoClass 0x006CA1D0 calls.
#ifndef RA2_SHARED_RAD_BEAM_HPP
#define RA2_SHARED_RAD_BEAM_HPP

#include "shared/coord.hpp"
#include "shared/rgb_class.hpp"

class RadBeam {
public:
    static RadBeam *__fastcall Allocate(int type);  // 0x00635440 (type 1 for TechnoClass beams)
    void Set_Color(RGBClass const &color);          // 0x00635710 (+0x18)
    void Set_Depth(int depth);                      // 0x00635730 (+0x04; the screen height difference of the ends)
    void Set_Source(CoordStruct const &coord);      // 0x00635740 (+0x1C)
    void Set_Target(CoordStruct const &coord);      // 0x00635760 (+0x28)
    void Set_Period(int period);                    // 0x00635780 (+0x34)
    void Set_Amplitude(double amplitude);           // 0x00635790 (+0x38)
    void unknown_6357b0(double value);              // 0x006357B0 (+0x40)
    void unknown_6357d0(int value);                 // 0x006357D0 (+0x48)
};

#endif
