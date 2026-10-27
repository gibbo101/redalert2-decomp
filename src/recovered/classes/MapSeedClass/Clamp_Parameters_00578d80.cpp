#include "shared/map_seed.hpp"
void MapSeedClass::Clamp_Parameters_00578d80()
{
    if(Resources>=4) Resources=3;
    else if(Resources<0) Resources=0;
    if(MapType>=5) MapType=4;
    else if(MapType<0) MapType=0;
    if(Time>=4) Time=3;
    else if(Time<0) Time=0;
    if(Ruggedness>100) Ruggedness=100;
    else if(Ruggedness<0) Ruggedness=0;
    if(WaterAmount>100) WaterAmount=100;
    else if(WaterAmount<0) WaterAmount=0;
    if(NumPlayers>8) NumPlayers=8;
    else if(NumPlayers<2) NumPlayers=2;
    if(Tiberium>100) Tiberium=100;
    else if(Tiberium<1) Tiberium=1;
    if(TiberiumLayout>100) TiberiumLayout=100;
    else if(TiberiumLayout<0) TiberiumLayout=0;
    if(Vegetation>100) Vegetation=100;
    else if(Vegetation<0) Vegetation=0;
    if(UrbanPresence>100) UrbanPresence=100;
    else if(UrbanPresence<0) UrbanPresence=0;
    if(Width>=4) Width=3;
    else if(Width<0) Width=0;
    if(Height>=4) Height=3;
    else if(Height<0) Height=0;
    if(Accessibility>100) Accessibility=100;
    else if(Accessibility<0) Accessibility=0;
    if(RegionSize>100) RegionSize=100;
    else if(RegionSize<0) RegionSize=0;
    if(Seed>65535) Seed=65535;
    else if(Seed<0) Seed=0;
}
