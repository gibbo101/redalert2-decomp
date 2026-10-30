// bool MapClass::Unknown_0055ACD0(ObjectClass *object, Cell const &cell) (0x0055ACD0)
// Whether the object may enter the cell (TibSun Try_Open_Gate): a gate building
// among the cell's other occupiers opens for an allied object (BuildingClass
// 0x0044D7D0) and otherwise lets it pass only when already open (0x0044D880).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/house_screen.hpp"
#include "shared/map_techno.hpp"

bool MapClass::Unknown_0055ACD0(ObjectClass *object, Cell const &cell)
{
    TechnoClass *optr = (TechnoClass *)Map[cell].OccupierPtr;
    while (optr != 0) {
        if ((TechnoClass *)object != optr) {
            BuildingClass *bptr = (BuildingClass *)optr;
            if (bptr->Kind_Of() == 6 && bptr->Type->Gate) {
                if (bptr->House->Is_Ally((TechnoClass *)object)) {
                    return bptr->unknown_44d7d0();
                }
                if (bptr->unknown_44d880()) {
                    return true;
                }
            }
        }
        optr = (TechnoClass *)optr->unknown_30;
    }
    return true;
}
