// Rally eligible owned technos near the base, original004F6310;419body+13padding.
// Inventory129-byte extent ends at a returning Map call; original CFG proves the complete419-byte body.
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"

void HouseClass::Unknown_004F6310()
{
    int count=Technos.Count();
    Cell destination=Coord_Cell(BaseCenter);
    destination=Map.Unknown_005502E0(destination,0,-1,0,false,Point2D(4,4),
                                         0,0,0,1,Cell(0,0),0);
    if (destination!=unknown_cell_a40f10) {
        ++destination.X;
        ++destination.Y;
        for (int index=0;index<count;++index) {
            TechnoClass *techno=Technos[index];
            if (techno && techno->House==this && techno->Kind_Of()!=6 && techno->Kind_Of()!=2 &&
                (!techno->unknown_slot32()->DeploysInto ||
                 !techno->unknown_slot32()->DeploysInto->ConstructionYard) &&
                Coord_Cell(BaseCenter)!=unknown_cell_a40f10) {
                techno->unknown_slot260(&Map[destination],1);
                techno->unknown_6d6e50(0);
                techno->unknown_slot116(2,false);
            }
        }
    }
}
