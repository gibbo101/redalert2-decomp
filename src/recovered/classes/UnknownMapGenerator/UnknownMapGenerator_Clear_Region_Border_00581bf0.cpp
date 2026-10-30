#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &position);
// @ref ?Build_Region_Border_Cell_List_00581ee0@UnknownMapGenerator@@=00581ee0
// @ref ??0?$VectorClass@VCell@@@@=0042d4a0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
Cell __fastcall CellClass::Adjacent_Cell(Cell const &cell,int facing)
{
    return cell.unknown_42add0(unknown_adjacent_851a70[facing&7]);
}
bool UnknownMapGenerator::Clear_Region_Border_00581bf0(int region,int rings,int newRegion)
{
    int ring,index;
    DynamicVectorClass<Cell> *border=Build_Region_Border_Cell_List_00581ee0(region);
    if(rings>1) {
        Map.Unknown_0055A550();
        for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
            Cell position=cell->MapCoords;
            unknown_map_cells_a70a24[position.Y*unknown_map_cell_side_84e804+position.X].unknown_3c=0;
        }
    }
    for(ring=0;ring<rings;++ring) {
        for(index=border->Count()-1;index>=0;--index) {
            Cell position=(*border)[index];
            if(unknown_map_cells_a70a24)unknown_map_cells_a70a24[position.Y*unknown_map_cell_side_84e804+position.X].RegionIndex=newRegion;
            CellClass &cell=Map[position];
            cell.IsoTileIndex=0;
            cell.unknown_11a=0;
            cell.unknown_11b=(char)unknown_30c;
        }
        if(ring<rings-1) {
            DynamicVectorClass<Cell> *next=new DynamicVectorClass<Cell>;
            next->Set_Growth_Step(border->Count());
            for(index=border->Count()-1;index>=0;--index) {
                Cell position=(*border)[index];
                for(int facing=0;facing<8;++facing) {
                    Cell adjacent=CellClass::Adjacent_Cell(position,facing);
                    if(Generation_Cell_In_Bounds_0058da10(adjacent)) {
                        UnknownMapGenerationCell &data=unknown_map_cells_a70a24[adjacent.Y*unknown_map_cell_side_84e804+adjacent.X];
                        if(data.RegionIndex==region && data.unknown_3c!=ring+1) {
                            next->Add(adjacent);
                            data.unknown_3c=ring+1;
                        }
                    }
                }
            }
            delete border;
            border=next;
        }
    }
    delete border;
    if(rings>1) {
        Map.Unknown_0055A550();
        for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
            Cell position=cell->MapCoords;
            unknown_map_cells_a70a24[position.Y*unknown_map_cell_side_84e804+position.X].unknown_3c=0;
        }
    }
    return true;
}
