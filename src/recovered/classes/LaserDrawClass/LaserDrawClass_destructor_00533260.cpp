// LaserDrawClass::~LaserDrawClass() (0x00533260)
#include "shared/laser_draw_list.hpp"

LaserDrawClass::~LaserDrawClass()
{
    LaserDrawList::Array.Delete(this);
}
