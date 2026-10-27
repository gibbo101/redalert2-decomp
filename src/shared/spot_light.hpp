// SpotLightClass (SpotLight.cpp around 0x005DD590; not polymorphic; RTTI
// name from the unit's list): a light at a coordinate that registers itself
// in the list at 0x00A731C0. Only what ParticleSystemClass uses is
// declared; the layout is from the constructor 0x005DD590 (hypotheses).
#ifndef RA2_SHARED_SPOT_LIGHT_HPP
#define RA2_SHARED_SPOT_LIGHT_HPP

#include "shared/coord.hpp"

class SpotLightClass {
public:
    SpotLightClass(CoordStruct coord, int size);    // 0x005DD590
    ~SpotLightClass();                              // 0x005DD610
    void unknown_func_5ddb90();                     // 0x005DDB90

    CoordStruct Coord;                              // +0x00
    int unknown_0c;                                 // +0x0C (0)
    int unknown_10;                                 // +0x10 the size argument
    int unknown_14;                                 // +0x14 (0)
};

#endif
