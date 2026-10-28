#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/building_view.hpp"
#include "shared/house.hpp"
// @ref ?Place_Neutral_Building_00571db0@MapRegionClass@@=00571db0
// @ref ??0BuildingClass@@=00438ce0
// @ref ?unknown_47b590@CellClass@@=0047b590
// @ref ?Find_Index@HouseTypeClass@@=004f94d0
// @ref ?As_Pointer@HouseClass@@=004ed760
// @ref ?From_Name@BuildingTypeClass@@=004583d0
// @ref ??_C@_07BKIB@Neutral?$AA@=007e14b8
// @ref ??_C@_06FOEG@CABHUT?$AA@=007e14b0
bool MapRegionClass::Place_Neutral_Building_00571db0(Rect const &area)
{
    for(int y=area.Y;y<area.Y+area.Height+1;y++) {
        for(int x=area.X;x<area.X+area.Width+1;x++) {
            CellClass &cell=Map[Cell(x,y)];
            if(cell.OverlayIndex==-1 && cell.unknown_47b590() && !cell.OccupierPtr) {
                HouseClass *house=HouseClass::As_Pointer(HouseTypeClass::Find_Index("Neutral"));
                int type=BuildingTypeClass::From_Name("CABHUT");
                BuildingClass *building=new BuildingClass(BuildingTypes[type],house);
                int x=cell.MapCoords.X*256+128;
                int y=cell.MapCoords.Y*256+128;
                building->unknown_slot53(&CoordStruct(x,y,0),0);
                return true;
            }
        }
    }
    return false;
}
