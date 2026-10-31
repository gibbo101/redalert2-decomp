// bool BuildingClass::unknown_slot52() (0x00442060)
// Takes the building off the map (hypothesis: Limbo). Unless already hidden
// (unknown_76) or typeless: its eight attachments get slot 60 and are
// cleared; an active ore purifier (unknown_5b4) lowers its house's purifier
// count and an active helipad its dock count (neither below 0); a laser
// fence post runs 0x0044DC40(0); outside the special mode a sensor array
// and a disguise detector run slots 289 and 291 with 0x0084ED10, and slot 31
// failing runs 0x004513B0. An upgrade that is a threat-rating node marks the
// house for 0x004F3160. With map updates on (0x00A40958): the rules' wall
// types refresh the surrounding cells (re-raising their wall overlays) or
// their X/Y neighbours, a building without +0xBF0 releases its foundation
// and border cells (+0x122), the screen rectangle is redrawn, +0x4D4 gets
// slot 60 and the house forgets the building; then the techno's slot 52.
// A factory tells its house it left. A laser fence post outside the special
// mode clears +0x4EC.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_44dc40@BuildingClass@@QAEXH@Z=0044dc40
// @ref ?unknown_4513b0@BuildingClass@@QAEXXZ=004513b0
// @ref _unknown_a40774=00a40774
// @ref ?unknown_84ed10@@3HA=0084ed10
// @ref _unknown_flag_a40958=00a40958
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?Unknown_00475960@UnknownBuildingCell52@@QAEXH@Z=00475960
// @ref ?Unknown_00475FE0@UnknownBuildingCell52@@QAEXH@Z=00475fe0
// @ref ?unknown_overlay_types_a35de8@@3V?$DynamicVectorClass@PAVUnknownOverlayType@@@@A=00a35de8
// @ref ?Width@BuildingTypeClass@@QBEHXZ=00458930
// @ref ?Foundation_Height@BuildingTypeClass@@QBEH_N@Z=00458940
// @ref ?Register_Dirty_Area@Tactical@@QAEXVRect@@_N@Z=006a3020
// @ref _unknown_tactical_83996c=0083996c
// @ref ?unknown_func_4eaba0@HouseClass@@QAEXPAVTechnoClass@@@Z=004eaba0
// @ref ?unknown_func_4e8640@HouseClass@@QAEXXZ=004e8640
// @ref _unknown_player_a35db4=00a35db4
// @ref ?unknown_flag_8339e8@@3_NA=008339e8
// @ref ?unknown_func_4f3f40@HouseClass@@QAEXPAVBuildingClass@@@Z=004f3f40
// @ref ?unknown_slot52@TechnoClass@@UAE_NXZ=006c4480
// @ref ?unknown_func_4f3160@HouseClass@@QAEXXZ=004f3160
// @ref ?unknown_func_4f3170@HouseClass@@QAEXH_NH@Z=004f3170

// Set when the player loses a building (0x008339E8; hypothesis).
extern bool unknown_flag_8339e8;

// The cell offsets of the eight facings (0x00851A70; Westwood's AdjacentCell).
#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
extern Cell const AdjacentCell[8];
// The cell next to `cell` toward an 8-way facing.
inline Cell Adjacent_Cell(Cell const &cell, int facing)
{
    Cell const &offset = AdjacentCell[facing & 7];
    return Cell(cell.X + offset.X, cell.Y + offset.Y);
}
#endif

// The cell members used here (a view of CellClass).
class UnknownBuildingCell52 {
public:
    void Unknown_00475960(int arg1);            // 0x00475960 (refreshes the cell; hypothesis)
    void Unknown_00475FE0(int arg1);            // 0x00475FE0 (raises the wall overlay; hypothesis)

    char unknown_000[0x44];
    int Overlay;                                // +0x044 (-1: none)
    char unknown_048[0x11E - 0x48];
    unsigned char unknown_11e;                  // +0x11E (overlay data)
    char unknown_11f[0x122 - 0x11F];
    char unknown_122;                           // +0x122 (buildings counting on the cell)
};

// Member-wise cell sum (as shared/cell.hpp's proposed Cell::operator+).
#ifndef RA2_CELLSTRUCT_PLUS
#define RA2_CELLSTRUCT_PLUS
inline Cell operator+(Cell const &left, Cell const &right)
{
    return Cell(left.X + right.X, left.Y + right.Y);
}
#endif

#define MAP_CELL(cell) ((UnknownBuildingCell52 &)Cell_At(cell))

bool BuildingClass::unknown_slot52()
{
    bool threat_node = false;
    CoordStruct center = Coord;
    Cell cell = Coord_Cell(center);
    bool result;
    if (!unknown_76 && Type != 0) {
        int index;
        for (index = 0; index < 8; index++) {
            if (unknown_49c[index] != 0) {
                unknown_49c[index]->unknown_slot60();
                unknown_49c[index] = 0;
            }
        }
        if (Type->OrePurifier && unknown_5b4) {
            House->unknown_52cc--;
            if (House->unknown_52cc < 0) {
                House->unknown_52cc = 0;
            }
        }
        if (Type->Helipad && unknown_5b4) {
            House->unknown_218 -= Type->NumberOfDocks;
            if (House->unknown_218 < 0) {
                House->unknown_218 = 0;
            }
        }
        if (Type->LaserFencePost) {
            unknown_44dc40(0);
        }
        if (unknown_a40774 == 0) {
            if (Type->SensorArray) {
                unknown_slot289(unknown_geometry_k);
            }
            if (Type->DetectDisguise) {
                unknown_slot291(unknown_geometry_k);
            }
            if (!unknown_slot31()) {
                unknown_4513b0();
            }
        }
        for (index = 0; index < 3; index++) {
            if (unknown_4c0[index] != 0 && ((BuildingTypeClass *)unknown_4c0[index])->IsThreatRatingNode) {
                threat_node = true;
                break;
            }
        }
        if (!unknown_flag_a40958) {
            result = true;
            goto fence;
        }
        if (Type == Rules->unknown_78c) {
            for (int facing = 0; facing < 8; facing += 2) {
                UnknownBuildingCell52 &near_cell = MAP_CELL(Adjacent_Cell(cell, facing));
                near_cell.Unknown_00475960(0);
                if (near_cell.Overlay != -1 && unknown_overlay_types_a35de8[near_cell.Overlay]->unknown_278
                    && near_cell.unknown_11e < 0x10) {
                    near_cell.Unknown_00475FE0(200);
                }
            }
        }
        if (Type == Rules->unknown_77c || Type == Rules->unknown_784) {
            MAP_CELL(Cell(cell.X - 1, cell.Y)).Unknown_00475960(0);
            MAP_CELL(Cell(cell.X + 3, cell.Y)).Unknown_00475960(0);
        }
        if (Type == Rules->unknown_780 || Type == Rules->unknown_788) {
            MAP_CELL(Cell(cell.X, cell.Y - 1)).Unknown_00475960(0);
            MAP_CELL(Cell(cell.X, cell.Y + 3)).Unknown_00475960(0);
        }
        if (Type->unknown_bf0 == 0) {
            int width = Type->Width();
            int height = Type->Foundation_Height(false);
            Cell base = unknown_slot104();
            for (int y = 0; y < height + 2; y++) {
                for (int x = 0; x < width + 2; x++) {
                    Cell corner(base.X - 1, base.Y - 1);
                    UnknownBuildingCell52 &spot = MAP_CELL(corner + Cell(x, y));
                    spot.unknown_122--;
                }
            }
        }
        if (unknown_tactical_83996c != 0) {
            unknown_tactical_83996c->Register_Dirty_Area(unknown_slot73(), 0);
        }
        if (unknown_4d4 != 0) {
            ((ObjectClass *)unknown_4d4)->unknown_slot60();
        }
        House->unknown_func_4eaba0(this);
        House->unknown_144 = true;
        House->unknown_func_4e8640();
        if (House == unknown_player_a35db4) {
            unknown_flag_8339e8 = true;
            Map.Flag_To_Redraw(0);
        }
        House->unknown_func_4f3f40(this);
    }
    result = TechnoClass::unknown_slot52();
    if (threat_node) {
        House->unknown_func_4f3160();
    }
    if (Type->Factory != 0) {
        House->unknown_func_4f3170(Type->Factory, Type->Naval, 0);
    }
fence:
    if (Type->LaserFencePost && unknown_a40774 == 0) {
        unknown_4ec = 0;
    }
    return result;
}
