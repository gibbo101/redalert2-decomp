// int BuildingLightClass::unknown_func_434530() const (0x00434530)
// The distance step (unknown_func_434610) scaled by the constant 5.9733 at
// 0x0079C7A8 and offset by the rules value at +0x6D0. The scale is read
// from memory (not folded), so it is an object, not a literal.
#include "shared/building_light.hpp"
#include "shared/rules.hpp"
// @ref ?unknown_func_434610@BuildingLightClass@@QBEHXZ=00434610
// @ref ?unknown_light_scale_79c7a8@@3NB=0079c7a8

extern double const unknown_light_scale_79c7a8;    // 0x0079C7A8 (5.973333333333333)

int BuildingLightClass::unknown_func_434530() const
{
    return (int)(unknown_func_434610() * unknown_light_scale_79c7a8) + Rules->unknown_6d0;
}
