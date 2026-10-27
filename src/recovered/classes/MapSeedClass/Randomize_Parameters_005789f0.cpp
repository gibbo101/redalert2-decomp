// Map-type index range0..4 follows Clamp_Parameters_00578D80.
// Range helper spells a real RNG operation; original helper name is unknown.
#include "shared/map_seed.hpp"
#include "shared/random.hpp"
extern int unknown_water_min_7e0b58[5],unknown_water_max_7e0b6c[5];
extern int unknown_rugged_min_7e0bbc[5],unknown_rugged_max_7e0bd0[5];
extern int unknown_urban_min_a70a54[5],unknown_urban_max_7e0ba8[5];
extern int unknown_access_min_a70a2c[5],unknown_access_max_7e0b80[5];
extern int unknown_region_min_7e0b30[5],unknown_region_max_7e0b44[5];
extern int *unknown_vegetation_min_a6fff0,*unknown_vegetation_max_a7000c;
// @ref ?unknown_water_min_7e0b58@@3PAHA=007e0b58
// @ref ?unknown_water_max_7e0b6c@@3PAHA=007e0b6c
// @ref ?unknown_rugged_min_7e0bbc@@3PAHA=007e0bbc
// @ref ?unknown_rugged_max_7e0bd0@@3PAHA=007e0bd0
// @ref ?unknown_urban_min_a70a54@@3PAHA=00a70a54
// @ref ?unknown_urban_max_7e0ba8@@3PAHA=007e0ba8
// @ref ?unknown_access_min_a70a2c@@3PAHA=00a70a2c
// @ref ?unknown_access_max_7e0b80@@3PAHA=007e0b80
// @ref ?unknown_region_min_7e0b30@@3PAHA=007e0b30
// @ref ?unknown_region_max_7e0b44@@3PAHA=007e0b44
// @ref ?unknown_vegetation_min_a6fff0@@3PAHA=00a6fff0
// @ref ?unknown_vegetation_max_a7000c@@3PAHA=00a7000c
inline int MapSeed_Random_Range(int minimum,int maximum)
{ return unknown_random_839218(minimum,maximum); }
void MapSeedClass::Randomize_Parameters_005789f0(int map_type)
{
    WaterAmount=MapSeed_Random_Range(unknown_water_min_7e0b58[map_type],unknown_water_max_7e0b6c[map_type]);
    Ruggedness=MapSeed_Random_Range(unknown_rugged_min_7e0bbc[map_type],unknown_rugged_max_7e0bd0[map_type]);
    UrbanPresence=MapSeed_Random_Range(unknown_urban_min_a70a54[map_type],unknown_urban_max_7e0ba8[map_type]);
    Accessibility=MapSeed_Random_Range(unknown_access_min_a70a2c[map_type],unknown_access_max_7e0b80[map_type]);
    RegionSize=MapSeed_Random_Range(unknown_region_min_7e0b30[map_type],unknown_region_max_7e0b44[map_type]);
    Tiberium=Resources*20;
    TiberiumLayout=MapSeed_Random_Range(0,100);
    int minimum=unknown_vegetation_min_a6fff0[map_type];
    int maximum=unknown_vegetation_max_a7000c[map_type];
    if(minimum<0) minimum=0;
    else if(minimum>100) minimum=100;
    if(maximum<0) maximum=0;
    else if(maximum>100) maximum=100;
    if(minimum>maximum) minimum=maximum;
    Vegetation=MapSeed_Random_Range(minimum,maximum);
    Seed=MapSeed_Random_Range(0,65535);
}
