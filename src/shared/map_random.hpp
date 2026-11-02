// The random map generator's random number generator (0x00A705C0), defined by the region-generation unit's
// first-globals source (dynamic initializer 0x0056D4F0). Kept out of shared/random2.hpp: VC6 re-emits a global's
// dynamic initializer after every extern redeclaration that follows its definition in the same TU, so the
// defining unit includes this header before the definition and its later sources include it again (guarded).
#ifndef RA2_SHARED_MAP_RANDOM_HPP
#define RA2_SHARED_MAP_RANDOM_HPP
#include "shared/random2.hpp"
extern Random2Class unknown_map_random_a705c0;  // 0x00A705C0
#endif
