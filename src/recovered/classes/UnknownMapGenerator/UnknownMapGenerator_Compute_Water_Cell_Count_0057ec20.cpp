#include "shared/unknown_map_generator.hpp"
extern double const unknown_water_scale_7a5f38,unknown_water_offset_79b7f0;
// @ref ?unknown_water_scale_7a5f38@@=007a5f38
// @ref ?unknown_water_offset_79b7f0@@=0079b7f0
// @ref __ftol=0077f110
int UnknownMapGenerator::Compute_Water_Cell_Count_0057ec20() const
{
    int water=SeedOptions.WaterAmount;
    if(water==0)return 0;
    return (int)((double)unknown_184*unknown_180*water*unknown_water_scale_7a5f38+unknown_water_offset_79b7f0);
}
