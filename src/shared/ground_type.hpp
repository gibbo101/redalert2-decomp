// A land type's movement costs (Westwood's GroundType; the RA2 values are floats): the
// speed factor of each SpeedType (Foot, Track, Wheel, Hover, Winged, Float, Amphibious,
// FloatBeach) and whether buildings may be placed. RulesClass::Land_Types reads one per
// land type; CellClass indexes it with its land type (+0xEC).
#ifndef RA2_SHARED_GROUND_TYPE_HPP
#define RA2_SHARED_GROUND_TYPE_HPP

struct GroundType {
    float Cost[8];   // +0x00
    bool  Build;     // +0x20
};

extern GroundType Ground[12];                   // 0x00850EA0

#endif
