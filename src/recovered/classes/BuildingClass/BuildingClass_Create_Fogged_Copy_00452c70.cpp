// Complete483-byte owned helper; original boundary proof in ORIGINAL.json.
#include "shared/building.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/fogged_object.hpp"
// @ref ??0FoggedObjectClass@@QAE@PAVBuildingClass@@_N@Z=004c0670
void BuildingClass::Create_Fogged_Copy_00452c70(
    DynamicVectorClass<FoggedObjectClass *> *replacement_list,
    CellClass *replacement_cell, bool arg)
{
    Cell const *offset=Type->unknown_slot36(0);
    unknown_slot81();
    FoggedObjectClass *copy=new FoggedObjectClass(this,arg);
    Cell base=unknown_slot104();
    for(;offset->X!=0x7fff || offset->Y!=0x7fff;++offset) {
        CellClass &cell=Cell_At(*offset+base);
        if(replacement_cell && &cell==replacement_cell) {
            replacement_list->Add(copy);
        }else if(cell.FoggedObjects) {
            cell.FoggedObjects->Add(copy);
        }else {
            cell.FoggedObjects=new DynamicVectorClass<FoggedObjectClass *>;
            cell.FoggedObjects->Resize(1);
            cell.FoggedObjects->Set_Growth_Step(1);
            cell.FoggedObjects->Add(copy);
        }
    }
}
