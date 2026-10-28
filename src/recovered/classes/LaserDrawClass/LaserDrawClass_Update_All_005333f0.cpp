// void LaserDrawClass::Update_All() (0x005333F0)
#include "shared/laser_draw_list.hpp"

void LaserDrawClass::Update_All()
{
    for (int index = LaserDrawList::Array.Count() - 1; index >= 0; index--) {
        LaserDrawList::Array[index]->Update();
    }
}
