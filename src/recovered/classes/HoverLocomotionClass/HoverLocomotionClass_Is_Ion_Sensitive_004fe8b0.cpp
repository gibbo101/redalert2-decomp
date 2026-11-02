// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
// @ref ?Contact@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e10
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
#include "shared/hover_locomotion.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/cell.hpp"
bool __stdcall HoverLocomotionClass::Is_Ion_Sensitive()
{
    if (LinkedTo->In_Radio_Contact()) {
        BuildingClass *contact=static_cast<BuildingClass *>(LinkedTo->Contact(0));
        if (contact->Kind_Of()==6) {
            contact=static_cast<BuildingClass *>(LinkedTo->Contact(0));
            if (contact->Type->WeaponsFactory) return false;
        }
    }
    BuildingClass *building=static_cast<BuildingClass *>(Map[Object_Coord(LinkedTo)].unknown_4717b0());
    if (building && building->Type->WeaponsFactory) {
        Cell difference=Cell(Object_Coord(LinkedTo))-Cell(Object_Coord(building));
        if (difference.X==0 && difference.Y==1) return false;
        else if (difference.X==2 && difference.Y==1) return false;
        else if (difference.X==3 && difference.Y==1) return false;
    }
    return true;
}
