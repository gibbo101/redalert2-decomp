// void TerrainClass::Start_Crumbling() (0x006E40D0)
// Starts the crumbling animation once (rate 2, from stage 0).
// Assumptions: the name follows Westwood's TerrainClass; unknown_b5 marks it.
#include "shared/terrain.hpp"
// @ref ?Frame@@3HA=00a40d2c

void TerrainClass::Start_Crumbling()
{
    if (!unknown_b5) {
        unknown_b5 = true;
        Animation.Set_Rate(2);
        Animation.Value = 0;
    }
}
