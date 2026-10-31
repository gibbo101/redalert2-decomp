#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/crt_memory.hpp"
void Mark_Adjacent_Grid_Weights_00584bd0();
// Original free deformation operations. Return/source names are qualified hypotheses.
void Init_Deform_Grid_RMG_00685600();
void Commit_Deform_Grid_RMG_006863e0();
int __fastcall Get_Deformed_Cell_Height_00686c90(CellClass *cell);
int __fastcall Get_Deformable_Cell_Corners_00686dd0(CellClass *cell,int direction);
bool __fastcall Deform_Cell_RMG_006869f0(Cell position,int direction,char flag,unsigned corners);
// @ref ?Mark_Adjacent_Grid_Weights_00584bd0@@=00584bd0
// @ref ?Seed_Hill_Heights_00584730@UnknownMapGenerator@@=00584730
// @ref ?Init_Deform_Grid_RMG_00685600@@=00685600
// @ref ?Commit_Deform_Grid_RMG_006863e0@@=006863e0
// @ref ?Get_Deformed_Cell_Height_00686c90@@=00686c90
// @ref ?Get_Deformable_Cell_Corners_00686dd0@@=00686dd0
// @ref ?Deform_Cell_RMG_006869f0@@=006869f0
void UnknownMapGenerator::Generate_Hills_00584dd0()
{
    Mark_Adjacent_Grid_Weights_00584bd0();
    Seed_Hill_Heights_00584730();
    Init_Deform_Grid_RMG_00685600();
    int size=unknown_map_cell_side_84e804*unknown_map_cell_side_84e804;
    for(int index=0;index<size;++index) {
        UnknownMapGenerationCell &data=unknown_map_cells_a70a24[index];
        if(data.Position.X!=0 || data.Position.Y!=0) {
            CellClass *cell=&Map[data.Position];
            int change=(int)(cell->unknown_11b+data.unknown_08-Get_Deformed_Cell_Height_00686c90(cell));
            int steps=abs(change);
            int direction=change<0?-1:1;
            while(steps>0) {
                Deform_Cell_RMG_006869f0(data.Position,direction,0,Get_Deformable_Cell_Corners_00686dd0(cell,direction));
                --steps;
            }
        }
    }
    Commit_Deform_Grid_RMG_006863e0();
    Map.Unknown_0055A550();
    CellClass *current=Map.Unknown_0055A490();
    Cell const offsets[]={Cell(0,0),Cell(1,0),Cell(1,1),Cell(0,1)};
    int ramps[]={11,12,9,10};
    while(current!=0) {
        int heightStep=0;
        bool raise=true;
        if(current->unknown_11c==5) {
            for(int direction=0;direction<4;++direction) {
                if(Map[current->Fetch_CellID() + offsets[direction]].unknown_11c!=5+direction)raise=false;
            }
        } else if(current->unknown_11c==11) {
            ++heightStep;
            for(int direction=0;direction<4;++direction) {
                if(Map[current->Fetch_CellID() + offsets[direction]].unknown_11c!=ramps[direction])raise=false;
            }
        } else raise=false;
        if(raise) {
            for(int direction=0;direction<4;++direction) {
                CellClass *cell=&Map[current->Fetch_CellID() + offsets[direction]];
                cell->IsoTileIndex=0xffff;
                cell->unknown_11a=0;
                cell->unknown_11c=0;
                cell->unknown_11b+=heightStep;
            }
        }
        current=Map.Unknown_0055A490();
    }
}
