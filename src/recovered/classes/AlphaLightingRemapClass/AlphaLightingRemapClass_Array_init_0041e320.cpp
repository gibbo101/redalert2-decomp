// Dynamic initializer (0x0041E320) and atexit destructor (0x0041E360) of the
// shared remap list AlphaLightingRemapClass::Array (0x0083C5D8); the exit
// thunk tests and sets a guard bit (VC6 guards the destruction of a static
// data member). The functions of the unit follow in their own drafts.
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/alpha_lighting_remap.hpp"

DynamicVectorClass<AlphaLightingRemapClass *> AlphaLightingRemapClass::Array;
// @ref ?Array@AlphaLightingRemapClass@@2V?$DynamicVectorClass@PAVAlphaLightingRemapClass@@@@A=0083c5d8
// @ref ??_7?$DynamicVectorClass@PAVAlphaLightingRemapClass@@@@6B@=0079b800
// @ref ??_7?$VectorClass@PAVAlphaLightingRemapClass@@@@6B@=0079b820
// @ref ??3@YAXPAX@Z=00781d3b
// @ref _$E3=0041e360
// @ref _$S4=0083c5f0
