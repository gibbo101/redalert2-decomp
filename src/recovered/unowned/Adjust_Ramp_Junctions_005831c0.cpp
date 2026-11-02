// Fresh complete5831C0 diagnostic. No required incoming receiver is established.
// Free/no-argvoid/name/operation spelling remain hypotheses; no invented per-function owner.
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/random2.hpp"
#include "shared/map_random.hpp"
// @ref ?unknown_map_random_a705c0@@3VRandom2Class@@A=00a705c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref __real@8@3fe08000000080000000=007a5de8
// @ref __ftol=0077f110
// @ref ?Unknown_0055BD70@MapClass@@=0055bd70
// Genuine repeated grid read/write operations; ordinary inline only, no external binding or forcing.
static inline int Read_Generation_Region(Cell const &position)
{
    UnknownMapGenerationCell *cells=unknown_map_cells_a70a24;
    unsigned side=(unsigned)unknown_map_cell_side_84e804;
    if(cells==0) {
        return -1;
    }
    unsigned at=(unsigned)(int)position.Y*side+(unsigned)(int)position.X;
    return cells[(int)at].RegionIndex;
}
static inline void Write_Generation_Region(Cell const &position,int region)
{
    UnknownMapGenerationCell *cells=unknown_map_cells_a70a24;
    unsigned side=(unsigned)unknown_map_cell_side_84e804;
    if(cells!=0) {
        unsigned at=(unsigned)(int)position.Y*side+(unsigned)(int)position.X;
        cells[(int)at].RegionIndex=region;
    }
}
void Adjust_Ramp_Junctions_005831c0()
{
    Map.Unknown_0055A550();
    CellClass *current=Map.Unknown_0055A490();
    while(current!=0) {
        CellClass &neighbor5=current->Adjacent_Cell(5);
        CellClass &neighbor1=current->Adjacent_Cell(1);
        CellClass &neighbor3=current->Adjacent_Cell(3);
        CellClass &neighbor2=current->Adjacent_Cell(2);
        CellClass &neighbor6=current->Adjacent_Cell(6);
        unsigned int mask=Map.Unknown_0055BD70(current);
        if(mask==0x83) {
            if(Map.Unknown_0055BD70(&neighbor3)==0x83 && neighbor2.unknown_47b590()) {
                unsigned int choice;
                do {
                    choice=(unsigned int)((unsigned int)unknown_map_random_a705c0()*(2.0/4294967295.0));
                } while(choice>1);
                if(choice==0) {
                    neighbor2.unknown_11b=(char)(neighbor2.unknown_11b-4);
                    Write_Generation_Region(neighbor2.MapCoords,Read_Generation_Region(current->MapCoords));
                }
            }
        } else if(mask==0x38) {
            if(Map.Unknown_0055BD70(&neighbor3)==0x38 && neighbor6.unknown_47b590()) {
                unsigned int choice;
                do {
                    choice=(unsigned int)((unsigned int)unknown_map_random_a705c0()*(2.0/4294967295.0));
                } while(choice>1);
                if(choice==0) {
                    neighbor6.unknown_11b=(char)(neighbor6.unknown_11b-4);
                    Write_Generation_Region(neighbor6.MapCoords,Read_Generation_Region(current->MapCoords));
                }
            }
        } else if(mask==0xE0) {
            if(Map.Unknown_0055BD70(&neighbor5)==0xE0 && Map.Unknown_0055BD70(&neighbor1)==0xE0 && current->unknown_47b590()) {
                current->unknown_11b=(char)(current->unknown_11b+4);
                Write_Generation_Region(current->MapCoords,Read_Generation_Region(neighbor6.MapCoords));
            }
        }
        current=Map.Unknown_0055A490();
    }
}
