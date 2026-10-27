// void TerrainClass::unknown_slot89() (0x006E3E90)
// Ends burning (unknown_b4); a destroyed object then starts crumbling.
#include "shared/terrain.hpp"
// @ref ?Frame@@3HA=00a40d2c

void TerrainClass::unknown_slot89()
{
    if (unknown_b4) {
        unknown_b4 = false;
        if (!unknown_b5 && Strength == 0) {
            unknown_slot54(1);
            unknown_slot71(2);
            Start_Crumbling();
        }
    }
}
