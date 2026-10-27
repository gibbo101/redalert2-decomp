// AbstractClass *ObjectClass::unknown_slot105() (0x005D51E0)
#include "shared/object_type.hpp"
#include "shared/map_view.hpp"

AbstractClass *ObjectClass::unknown_slot105()
{
    CoordStruct coord = Coord;
    &Map[coord];
    coord = Coord;
    return (AbstractClass *)&Map[coord];   // the cell object (hypothesis)
}
