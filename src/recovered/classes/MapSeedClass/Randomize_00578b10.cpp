#include "shared/map_seed.hpp"
#include "shared/random.hpp"
// @ref ?Randomize_Parameters_005789f0@MapSeedClass@@=005789f0
// @ref ?Clamp_Parameters_00578d80@MapSeedClass@@=00578d80
void MapSeedClass::Randomize_00578b10()
{
    Theater=unknown_random_839218(0,100)>=50U;
    MapType=unknown_random_839218(1,4);
    Time=unknown_random_839218(0,3);
    Resources=unknown_random_839218(0,3);
    Height=Width=unknown_random_839218(0,3);
    Randomize_Parameters_005789f0(MapType);
    Set_Default_Description_00576fe0();
    Seed=unknown_random_839218(0,65535);
    Clamp_Parameters_00578d80();
}
