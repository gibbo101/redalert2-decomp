// void CellClass::unknown_47be60() (0x0047BE60): discards the cell's fogged
// objects: each is removed from the fogged lists of the other cells it covers
// and deleted, then the list itself is deleted.
#include "shared/cell.hpp"
#include "shared/object.hpp"
#include "shared/map_view.hpp"
#include "shared/fogged_object.hpp"
// @ref ?unknown_4c1f00@FoggedObjectClass@@QBEPBVCell@@XZ=004c1f00

void CellClass::unknown_47be60()
{
    if (FoggedObjects != 0) {
        int index = FoggedObjects->Count();
        while (--index >= 0) {
            FoggedObjectClass *object = (*FoggedObjects)[index];
            if (object->unknown_4c1f00() != 0) {
                for (Cell const *offset = object->unknown_4c1f00(); offset->X != 0x7FFF || offset->Y != 0x7FFF; offset++) {
                    CoordStruct coord = object->Coord;
                    CellClass &cell = Map[Coord_Cell(coord) + *offset];
                    if (&cell != this && cell.FoggedObjects != 0) {
                        cell.FoggedObjects->Delete(object);
                    }
                }
            }
            delete object;
        }
        FoggedObjects->Clear();
        delete FoggedObjects;
        FoggedObjects = 0;
    }
}
