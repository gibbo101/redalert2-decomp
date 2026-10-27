// Private full184-byte helper plus8 NOP. Class/method spelling is a hypothesis.
// No actual incoming references found; canonical neighboring bodies independently bound it.
#include "shared/building.hpp"
#include "shared/building_map.hpp"
Cell BuildingClass::Offset_Toward_Map_Center_0044aa40(int mode)
{
    int dx=6;
    int dy=5;
    Cell cell=Coord_Cell(Center_Coord());
    switch(mode) {
    case 0:dx=0;break;
    case 2:dy=0;break;
    }
    if((int)((unsigned int)cell.X-(unsigned int)Map.unknown_120)>Map.unknown_128/2)dx=-dx;
    if((int)((unsigned int)cell.Y-(unsigned int)Map.unknown_124)>Map.unknown_12c/2)dy=-dy;
    int vertical=dy;
    return Cell((short)(cell.X+dx),(short)(vertical+cell.Y));
}
