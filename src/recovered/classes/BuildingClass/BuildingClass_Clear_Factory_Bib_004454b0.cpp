// Clear occupants from the weapons factory exit and surrounding bib cells.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Factory_Exit_Message@@=007cf99c
// @ref ?Factory_Bib_Message@@=007cf970
// @ref ?Debug_Printf@@=004068f0
// @ref ?unknown_471660@CellClass@@=00471660
// @ref ?unknown_476920@CellClass@@=00476920
// @ref ?Adjacent_Cell@CellClass@@QAEAAV1@I@Z=00476ac0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
extern char const Factory_Exit_Message[];
extern char const Factory_Bib_Message[];
// @ref ?unknown_4454b0@BuildingClass@@QAE_NXZ=004454b0
bool BuildingClass::unknown_4454b0()
{
    if(Type->WeaponsFactory) {
        Cell offset=Type->FoundationOutside[10];
        Cell cell=unknown_slot104()+offset;
        cell=cell+Cell(-1,0);
        Cell lookup=cell;
        CoordStruct coordinate=Cell_Center(lookup);
        CellClass &exit=Map[lookup];
        ObjectClass *occupant=exit.unknown_471660(Point2D(0,0),false,this);
        if(occupant) {
            Debug_Printf(Factory_Exit_Message,(char const *)occupant->unknown_slot32()->ID);
            exit.unknown_476920(&unknown_geometry_l,true,true,false);
            for(int facing=0;facing<8;++facing) {
                CellClass &neighbor=exit.Adjacent_Cell(facing);
                occupant=neighbor.unknown_471660(Point2D(0,0),false,this);
                if(occupant) {
                    Debug_Printf(Factory_Bib_Message,(char const *)occupant->unknown_slot32()->ID);
                    neighbor.unknown_476920(&coordinate,true,true,false);
                }
            }
            return true;
        }
    }
    return false;
}
