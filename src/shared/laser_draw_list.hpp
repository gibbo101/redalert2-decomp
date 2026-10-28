// The list of live lasers (0x00A6E698; LaserDraw.cpp's dynamic initializer
// 0x00533070 constructs it, the atexit destructor 0x005330B0 tests a guard
// bit, so it is a static data member). It is held apart from LaserDrawClass:
// in VC6 a static data member of class type takes a static-initializer
// counter value in every unit that sees its class, and BuildingClass's laser
// caller (0x00446820) includes shared/laser_draw.hpp. Holder name hypothesis.
#ifndef RA2_SHARED_LASER_DRAW_LIST_HPP
#define RA2_SHARED_LASER_DRAW_LIST_HPP

#include "shared/laser_draw.hpp"
#include "shared/vector_class_decl.hpp"

struct LaserDrawList {
    static DynamicVectorClass<LaserDrawClass *> Array;   // 0x00A6E698
};

#endif
