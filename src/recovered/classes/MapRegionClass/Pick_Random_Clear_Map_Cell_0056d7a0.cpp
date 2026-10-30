#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/random2.hpp"
extern Random2Class unknown_map_random_a705c0;
// @ref ?unknown_map_random_a705c0@@=00a705c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref __real@8@3fdf8000000080000000=007a5dd0
// @ref __ftol=0077f110
// ECX hidden result, EAX same result pointer, RET0; retry limit precedes the map-clear test.
Cell __fastcall MapRegionClass::Pick_Random_Clear_Map_Cell_0056d7a0()
{
    int tries=0;
    for(;;) {
        Cell position=Pick_Random_Map_Cell_0056d720();
        if(++tries>200)return Cell(0,0);
        if(Map[position].unknown_47b590())return position;
    }
}

// @ref __real@8@3fe2a0000000a0000000=007a5f28
// @ref __real@8@3fe6f2000000f2000000=007a5f20
// @ref __real@8@3fe6c9000000c9000000=007a5f18
#include "shared/random.hpp"
extern Random2Class unknown_map_random_a705c0;
// @ref ?unknown_map_random_a705c0@@3VRandom2Class@@A=00a705c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref __real@8@3fdf8000000080000000=007a5dd0
#include "shared/random.hpp"
extern Random2Class unknown_map_random_a705c0;
// @ref ?unknown_map_random_a705c0@@3VRandom2Class@@A=00a705c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref __real@8@3fdf8000000080000000=007a5dd0
// Random map callback: map the generator's complete unsigned word to [0,1].
double __cdecl Map_Random_Fraction_00579770()
{
    return (unsigned int)unknown_map_random_a705c0() * (1.0 / 4294967295.0);
}

unsigned int __fastcall Map_Random_Range_005797a0(unsigned int minimum,unsigned int maximum)
{
    unsigned int result;
    do {
        result=(unsigned int)(Map_Random_Fraction_00579770()*(unsigned int)(maximum-minimum+1)+(double)minimum);
    } while(result>maximum);
    return result;
}
