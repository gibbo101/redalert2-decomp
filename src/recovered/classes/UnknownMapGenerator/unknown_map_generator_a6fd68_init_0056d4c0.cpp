// The region-generation unit's globals (definition order = dynamic initializer order): the map generator
// 0x00A6FD68 (initializer 0x0056D4C0, atexit destructor 0x0056D4E0), the generation random generator 0x00A705C0
// (Random2Class(0), initializer 0x0056D4F0) and the generator's Gaussian source 0x00A6FD50 over
// Map_Random_Fraction_00579770 (initializer 0x0056D500). The region list 0x00A6FD28 that follows
// (initializer 0x0056D530, atexit destructor 0x0056D570) is not defined here yet.
#include "shared/unknown_map_generator.hpp"
#include "shared/map_gaussian.hpp"
#include "shared/map_random.hpp"
// @ref ?unknown_map_generator_a6fd68@@3VUnknownMapGenerator@@A=00a6fd68
// @ref ?unknown_map_random_a705c0@@3VRandom2Class@@A=00a705c0
// @ref ??0Random2Class@@QAE@I@Z=00638790
// @ref ?unknown_map_gaussian_a6fd50@@3VMapGaussianClass@@A=00a6fd50
// @ref ??0UnknownMapGenerator@@QAE@XZ=00577010
// @ref ??1UnknownMapGenerator@@QAE@XZ=005771b0
// @ref ?Map_Random_Fraction_00579770@@YANXZ=00579770
double __cdecl Map_Random_Fraction_00579770();

UnknownMapGenerator unknown_map_generator_a6fd68;
Random2Class unknown_map_random_a705c0;
MapGaussianClass unknown_map_gaussian_a6fd50(Map_Random_Fraction_00579770);
