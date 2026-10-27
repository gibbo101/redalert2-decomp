// Complete original 0043F8E0: 1099 body bytes and 5 padding bytes.
// Name and unused void return are hypotheses. Explicit input is the attacker.
#include "shared/building.hpp"
// Reuse the Building unit's existing genuine adjacent-cell operation before
// the Infantry header sees its shared guarded copy. Operand order is retained.
#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
#include "shared/adjacent_cell.hpp"
inline Cell Adjacent_Cell(Cell const &cell, int facing)
{
    Cell const &offset = AdjacentCell[facing & 7];
    return Cell(cell.X + offset.X, cell.Y + offset.Y);
}
#endif
#include "shared/infantry.hpp"
#include "shared/house.hpp"
#include "shared/cell.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/id_source.hpp"
#include "shared/smudge_type.hpp"
#include "shared/debug_printf.hpp"
// Identical existing declaration from bullet.hpp; no Bullet layout needed.
CoordStruct __fastcall Coord_Scatter(CoordStruct const &coord, int distance, bool lock);
// @ref ??0InfantryClass@@=004ff640
// @ref ?Closest_Free_Spot@UnknownPlacementCellView@@=004764b0
// @ref ??RRandom2Class@@=006388a0
// @ref ?Is_Ally@HouseClass@@QBE_NPBVObjectClass@@@Z=004e55e0
// @ref ?unknown_func_4f52f0@HouseClass@@=004f52f0
// @ref ?unknown_478760@CellClass@@=00478760
// @ref ?Coord_Scatter@@=00491750
// @ref ?Create_Scorch@SmudgeTypeClass@@=00688460
// @ref ?Create_Crater@SmudgeTypeClass@@=00688750
// @ref ?Debug_Printf@@=004068f0
// @ref ??_C@_0DF@NBIL@Creating?5survivor?5type?5?8?$CFs?8?5from@=007cf7d8
// @ref ??_C@_0BF@HKBA@Survivor?5unlimbo?5OK?6?$AA@=007cf7c0
void BuildingClass::Spawn_Survivors_0043f8e0(ObjectClass *attacker)
{
    Cell origin=unknown_slot104();
    Cell const *offset=unknown_slot64(0);
    int odds=2;
    if(unknown_438)odds=1;
    if(unknown_5b3)odds+=6;
    CoordStruct coordinate;
    int remaining=unknown_slot172();
    if(remaining==0)return;
    while(offset->X!=32767 || offset->Y!=32767) {
        Cell location=*offset++ + origin;
        CellClass *cell=&Map[location];
        if(!House->unknown_13e && remaining>0 && unknown_id_source_a3d290->Random()(0,odds)==1) {
            InfantryClass *survivor=0;
            InfantryTypeClass *crew=unknown_slot184();
            if(crew)survivor=new InfantryClass(crew,House);
            Debug_Printf("Creating survivor type '%s' from building type '%s'\n",survivor->Type->Name.Buffer,Type->Name.Buffer);
            if(survivor) {
                if(unknown_5b9 && survivor->Type->Nominal)survivor->unknown_5c1=true;
                ++unknown_a40774;
                coordinate=CoordStruct(location.X*256+128,location.Y*256+164,0);
                coordinate=((UnknownPlacementCellView *)&Map[coordinate])->Closest_Free_Spot(coordinate,false,false);
                if(coordinate==unknown_geometry_l || !survivor->unknown_slot53(&coordinate,0)) {
                    delete survivor;
                } else {
                    Debug_Printf("Survivor unlimbo OK\n");
                    --remaining;
                    int maximumStrength=survivor->Type->MaxStrength;
                    survivor->Strength=unknown_id_source_a3d290->Random()(5,maximumStrength);
                    survivor->unknown_slot87(unknown_geometry_l,true,false);
                    if(attacker && !House->Is_Ally(attacker)) {
                        survivor->unknown_slot116(1,false);
                        survivor->unknown_slot220(attacker);
                    } else if(House->unknown_func_4f52f0()) {
                        survivor->unknown_slot116(2,false);
                    } else {
                        survivor->unknown_slot116(15,false);
                    }
                }
                --unknown_a40774;
            }
        }
        if(cell->unknown_478760(1,1,1,-1,0,-1,1)) {
            if(unknown_id_source_a3d290->Random()(0,99)<50) {
                Cell hit=Coord_Cell(Coord_Scatter(CoordStruct(location.X*256+128,location.Y*256+128,0),128,false));
                CoordStruct center(hit.X*256+128,hit.Y*256+128,0);
                SmudgeTypeClass::Create_Scorch(center,100,100,false);
            } else {
                Cell hit=Coord_Cell(Coord_Scatter(CoordStruct(location.X*256+128,location.Y*256+128,0),128,false));
                CoordStruct center(hit.X*256+128,hit.Y*256+128,0);
                SmudgeTypeClass::Create_Crater(center,100,100,false);
            }
        }
    }
}
