// void LaserDrawClass::Draw_All() (0x005334D0)
#include "shared/laser_draw_list.hpp"
// @ref ?Draw_It@LaserDrawClass@@QAEXXZ=005334f0

void LaserDrawClass::Draw_All()
{
    for (int index = LaserDrawList::Array.Count() - 1; index >= 0; index--) {
        LaserDrawList::Array[index]->Draw_It();
    }
}
