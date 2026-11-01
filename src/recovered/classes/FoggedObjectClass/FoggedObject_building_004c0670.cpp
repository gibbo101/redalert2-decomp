#include "shared/fogged_object.hpp"
#include "shared/building_class.hpp"
#include "shared/house.hpp"
#include "shared/anim.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
// @ref ?unknown_43be20@BuildingClass@@=0043be20
FoggedObjectClass::FoggedObjectClass(BuildingClass *building,bool fade)
    : unknown_24(-1),unknown_28(building->House),unknown_2c(0),unknown_30(6),Coord(building->Coord),
      unknown_50(Map[CoordStruct(building->Coord)].unknown_11b),unknown_54(-1),unknown_58(0),unknown_74(fade)
{
    unknown_40=building->unknown_slot73();
    Array.Add(this);
    Index.Add_Index(unknown_index_key(unknown_coord_cell(Coord),unknown_30),this);
    building->unknown_5b7=true;
    int shape=building->unknown_43be20();
    DrawRecord record;
    record.Type=building->Type;
    record.unknown_04=shape;
    if(building->Type->LaserFence && (building->unknown_4ec==12 || building->unknown_4ec==8))record.unknown_08=1;
    else {
        record.unknown_08=0;
        if(building->Type->FirestormWall)record.unknown_08=1;
    }
    DrawRecords.Add(record);
    for(int index=0;index<18;++index) {
        if(building->unknown_454[index]) {
            ((AnimClass*)building->unknown_454[index])->unknown_179=true;
            AnimTypeClass *type=((AnimClass*)building->unknown_454[index])->Class;
            unknown_40=Union(unknown_40,((AnimClass*)building->unknown_454[index])->unknown_slot72());
            record.Type=type;
            record.unknown_04=type->Start+((AnimClass*)building->unknown_454[index])->Stage;
            record.unknown_08=0;
            record.unknown_0c=((AnimClass*)building->unknown_454[index])->ZAdjust;
            DrawRecords.Add(record);
        }
    }
    unknown_tactical_83996c->Register_Dirty_Area(unknown_40,false);
    unknown_40.X+=unknown_tactical_83996c->unknown_b0.X;
    unknown_40.Y+=unknown_tactical_83996c->unknown_b0.Y;
}
