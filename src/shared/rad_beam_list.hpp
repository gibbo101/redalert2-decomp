// The list of live beams (0x00AB64E0; RadBeam.cpp's dynamic initializer
// 0x006353A0 constructs it, the atexit destructor 0x006353E0 tests a guard
// bit, so it is a static data member). Held apart from RadBeam: in VC6 a
// static data member of class type takes a static-initializer counter value
// in every unit that sees its class, and TechnoClass 0x006CA1D0 includes
// shared/rad_beam.hpp. Holder name hypothesis.
#ifndef RA2_SHARED_RAD_BEAM_LIST_HPP
#define RA2_SHARED_RAD_BEAM_LIST_HPP

#include "shared/rad_beam.hpp"
#include "shared/vector_class_decl.hpp"

struct RadBeamList {
    static DynamicVectorClass<RadBeam *> Array;     // 0x00AB64E0
};

#endif
