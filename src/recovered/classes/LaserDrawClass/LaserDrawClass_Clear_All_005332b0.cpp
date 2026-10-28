// void LaserDrawClass::Clear_All() (0x005332B0)
#include "shared/laser_draw_list.hpp"

void LaserDrawClass::Clear_All()
{
    while (LaserDrawList::Array.Count() != 0) {
        delete LaserDrawList::Array[0];
    }
}
