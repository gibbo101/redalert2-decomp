// bool UnitClass::unknown_6fd930() (0x006FD930; slot 132 calls it: may start
// deploying). Without a DeploysInto type it returns true. A unit whose
// DeploysInto is one of the Rules +0x7C8 (BuildConst) types and whose house
// has +0x139 set looks for a free area (a Shipyard-sized one near the unit,
// then a BuildConst-sized one near that) and moves there, clearing +0x139.
// Otherwise it tries to place the building with its origin one cell
// north-west (AdjacentCell[7]) of the unit's centre, then of each of 36
// cells around the unit; when one fits it moves to that cell. The 36 offsets
// are a local static array (its atexit callback is 0x006FDFB0). The first
// placement test calls the cell sum out of line (0x0042ADD0, thiscall: a
// nested site in Deploy_Origin_6fd930 after the direct sites have spent the
// inline budget). The two zero cells are separate block locals (their shared
// slot puts the found cell below them). Names are hypotheses.
#include "shared/unit.hpp"
#include "shared/building_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?unknown_func_4ef600@HouseClass@@QAEPAVBuildingTypeClass@@ABV?$DynamicVectorClass@PAVBuildingTypeClass@@@@@Z=004ef600
// @ref ?Unknown_005502E0@MapClass@@QAE?AVCell@@ABV2@HHH_NUPoint2D@@11110H@Z=005502e0
// @ref _unknown_geometry_k=00ad0488
// @ref _unknown_geometry_l=00ad04c0
// @ref _?$S46@?BN@??unknown_6fd930@UnitClass@@QAE_NXZ@4EA=00ad04b8
// @ref _?offsets@?BN@??unknown_6fd930@UnitClass@@QAE_NXZ@4PAVCell@@A=00ad04e8
// @ref ?unknown_42add0@Cell@@QBE?AV1@ABV1@@Z=0042add0

// The building origin for a unit cell: one cell north-west.
static inline Cell Deploy_Origin_6fd930(Cell const &cell)
{
    return cell.unknown_42add0(AdjacentCell[7]);
}

// A search offset added to the unit's cell.
static inline Cell Offset_Cell_6fd930(Cell const &offset, Cell const &position)
{
    Cell result;
    result.X = offset.X;
    result.Y = offset.Y;
    result.X += position.X;
    result.Y += position.Y;
    return result;
}

bool UnitClass::unknown_6fd930()
{
    if (Type->DeploysInto == 0) return true;
    unknown_slot71(0);
    for (int index = 0; index < Rules->unknown_7c8.Count(); index++) {
        if (Rules->unknown_7c8[index] == Type->DeploysInto) {
            if (Owning_House()->unknown_139) {
                if (!unknown_494) {
                    Cell first;
                    {
                        Cell zero(0, 0);
                        first = Map.Unknown_005502E0(unknown_slot104(), 5, -1, 0, false, Point2D(House->unknown_func_4ef600(Rules->Shipyard)->Width() + 1, House->unknown_func_4ef600(Rules->Shipyard)->Foundation_Height(false) + 1), 0, 0, 0, 1, zero, 0);
                    }
                    {
                        Cell zero(0, 0);
                        first = Map.Unknown_005502E0(first, 1, -1, 0, false, Point2D(House->unknown_func_4ef600(Rules->unknown_7c8)->Width() + 1, House->unknown_func_4ef600(Rules->unknown_7c8)->Foundation_Height(false) + 1), 0, 0, 0, 1, zero, 0);
                    }
                    if (first != unknown_geometry_k) unknown_slot260(&Map[first], 1);
                    Owning_House()->unknown_139 = false;
                }
                goto finish;
            }
            break;
        }
    }
    if (!unknown_494) {
        {
        if (Type->DeploysInto->unknown_slot42(Deploy_Origin_6fd930(Coord_Cell(Center_Coord())), 0)) {
            unknown_slot71(1);
            return true;
        }
        }
        if (!unknown_494) {
            static Cell offsets[36] = {
                Cell(0, -1),
                Cell(0, -2),
                Cell(1, -2),
                Cell(-1, -2),
                Cell(0, -3),
                Cell(1, -3),
                Cell(-1, -3),
                Cell(2, -3),
                Cell(-2, -3),
                Cell(0, -4),
                Cell(1, -4),
                Cell(-1, -4),
                Cell(2, -4),
                Cell(-2, -4),
                Cell(0, 1),
                Cell(0, 2),
                Cell(1, 2),
                Cell(-1, 2),
                Cell(0, 3),
                Cell(1, 3),
                Cell(-1, 3),
                Cell(2, 3),
                Cell(-2, 3),
                Cell(0, 4),
                Cell(1, 4),
                Cell(-1, 4),
                Cell(2, 4),
                Cell(-2, 4),
                Cell(-1, 0),
                Cell(-2, 0),
                Cell(-3, 0),
                Cell(-4, 0),
                Cell(1, 0),
                Cell(2, 0),
                Cell(3, 0),
                Cell(4, 0)
            };
            for (int offset_index = 0; offset_index < 36; offset_index++) {
                Cell adjacent = Offset_Cell_6fd930(offsets[offset_index], unknown_slot104());
                Cell placement = adjacent + AdjacentCell[7];
                if (Type->DeploysInto->unknown_slot42(placement, 0)) {
                    unknown_slot260(&Map[adjacent], 1);
                    break;
                }
            }
        }
    }
finish:
    unknown_slot71(1);
    if (!unknown_494 && !House->Unknown_004F52F0()) unknown_slot87(unknown_geometry_l, false, false);
    return false;
}
