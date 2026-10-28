// Refines movement/interaction results for infantry at a cell (0x00506650).
#include "shared/infantry.hpp"
#include "shared/cell.hpp"
#include "shared/fogged_object.hpp"
#include "shared/building_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?unknown_slot27@FootClass@@UAEHPBVCell@@_N1@Z=004cc650
// @ref ?unknown_6c16f0@TechnoClass@@QAEHH@Z=006c16f0
// @ref ?unknown_479cf0@CellClass@@QBE_NXZ=00479cf0
// @ref ?unknown_479f70@CellClass@@QBE_NXZ=00479f70
// @ref ?unknown_479cc0@CellClass@@QBE_NXZ=00479cc0
// @ref ?unknown_47a120@CellClass@@QBE_NPAVTechnoClass@@@Z=0047a120
// @ref ?Unknown_00569320@MapClass@@QAE_NABVCell@@@Z=00569320
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
inline BuildingTypeClass *Fogged_Building_Type(FoggedObjectClass const *object)
{
    return object->unknown_30 == 6 ? (BuildingTypeClass *)object->DrawRecords[0].Type : 0;
}
int InfantryClass::unknown_slot27(Cell const *cell, bool arg2, bool arg3)
{
    if (!House->Unknown_004F52B0()) {
        return 0;
    }
    int result = FootClass::unknown_slot27(cell, arg2, arg3);
    if (unknown_6c16f0(-1) < 0 && House->Unknown_004F52B0() && result == 5) {
        result = 26;
    }
    if (Type->JumpJet && (result == 1 || result == 2)) {
        if (Map[*cell].unknown_479cf0() || Map[*cell].unknown_479f70()) {
            result = 0;
        }
    }
    if (House->Unknown_004F52B0() && Type->Deployer && unknown_5090d0()) {
        if (result == 1) {
            result = 2;
        } else if (result == 5) {
            if (Type->DeployFire) {
                int weapon_index = unknown_slot174(0);
                CoordStruct fire_coord(cell->X * 256 + 128, cell->Y * 256 + 128, 0);
                if (!unknown_slot84(fire_coord, weapon_index)) result = 2;
            } else result = 2;
        } else {
            goto ordinary_cell;
        }
    } else {
    ordinary_cell:
        if (result == 1 && Map[*cell].unknown_479cc0()) {
            return Map[*cell].unknown_47a120(this) ? 35 : 36;
        }
    }

    CellClass &target_cell = Map[*cell];
    BuildingTypeClass *remembered_type = 0;
    FoggedObjectClass *remembered = 0;
    if ((unknown_id_source_a3d290->unknown_000 & 0x1000) && arg2 && target_cell.FoggedObjects != 0) {
        for (int index = 0; index < target_cell.FoggedObjects->Count(); ++index) {
            remembered = (*target_cell.FoggedObjects)[index];
            if (remembered->unknown_74 && remembered->unknown_30 == 6) {
                remembered_type = Fogged_Building_Type(remembered);
                break;
            }
        }
    }
    if (Type->Engineer && remembered_type != 0 && House->Unknown_004F52B0()) {
        if (remembered_type->BridgeRepairHut) {
            Cell hut_cell = Coord_Cell(remembered->Center_Coord());
            result = Map.Unknown_00569320(hut_cell) ? 29 : 32;
            goto result_ready;
        }
        if (remembered_type->Repairable) {
            result = 9;
            goto result_ready;
        }
    }
    if (result == 5 && !unknown_slot163()) {
        result = 59;
    }
result_ready:
    if (House->Unknown_004F52B0() && result == 0 && !Type->JumpJet && !unknown_slot111() && !unknown_slot112()) {
        result = 2;
    }
    return result;
}
