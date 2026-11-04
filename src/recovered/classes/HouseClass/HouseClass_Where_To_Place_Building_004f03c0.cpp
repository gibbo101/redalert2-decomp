// HouseClass::Where_To_Place_Building, original 0x004F03C0, 2,629 B body (TibSun twin). Facing_Offset, Coord_Span and
// Coord_Span2 stay file-local until the real table element and distance helpers are identified.
// @ref ?Increase_Table_Size@?$IndexClass@HVCell@@@@QAE_NH@Z=004f8c60
// @ref ?search_compfunc@?$IndexClass@HVCell@@@@CAHPBX0@Z=004f8cf0
// @ref _?$S65@?DK@??Where_To_Place_Building@HouseClass@@QAE?AVCell@@PAVBuildingTypeClass@@P6IHPAV2@ABV3@HH@ZH@Z@4EA=00a40fc0
// @ref _?scan_offsets@?DK@??Where_To_Place_Building@HouseClass@@QAE?AVCell@@PAVBuildingTypeClass@@P6IHPAV2@ABV3@HH@ZH@Z@4PAUFacing_Offset@@A=00a40f60
// @ref _?step_offsets@?DK@??Where_To_Place_Building@HouseClass@@QAE?AVCell@@PAVBuildingTypeClass@@P6IHPAV2@ABV3@HH@ZH@Z@4PAUFacing_Offset@@A=00a40f80
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/rules.hpp"
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/cell_class.hpp"
#include "shared/house_adjacent.hpp"
#include "shared/crt_memory.hpp"
#include "shared/fast_math.hpp"
#include "shared/unknown_vector3.hpp"
#include "shared/ini_class.hpp"
#include "shared/facing.hpp"
#include "shared/coord_distance.hpp"
struct Facing_Offset : Cell {
    Facing_Offset(Cell const &cell) : Cell(cell) {}
    ~Facing_Offset() {}
};
inline int Coord_Span(CoordStruct const &a, CoordStruct const &b) { return ((UnknownVector3 const &)(a - b)).Length(); }
inline int Coord_Span2(CoordStruct const &a, CoordStruct const &b)
{
    CoordStruct d(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
    double x = d.X;
    double y = d.Y;
    double z = d.Z;
    return (int)unknown_sqrt_4ba410(z * z + y * y + x * x);
}
Cell HouseClass::Where_To_Place_Building(BuildingTypeClass *type, int (__fastcall *score)(HouseClass *, Cell const &, int, int), int context)
{
    if (type->Naval) {
        Cell no_cell(0,0);
        int width = unknown_func_4ef600(Rules->Shipyard)->Width() + 2;
        int height = unknown_func_4ef600(Rules->Shipyard)->Foundation_Height(false) + 2;
        Cell center = Coord_Cell(BaseCenter);
        Cell spot = Map.Unknown_005502E0(center, 5, -1, 0, false, Point2D(width, height), false, false, false, true, no_cell, 0);
        if (spot != unknown_cell_a40f10) {
            if (unknown_50[0] != 0) {
                if (Coord_Span(Map[spot].Center_Coord(), unknown_50[0]->Center_Coord()) > Rules->AINavalYardAdjacency * 256) {
                    return unknown_cell_a40f10;
                }
            }
        }
        return spot;
    } else {
    DynamicVectorClass<Cell> sorted;
    if (unknown_55f0.unknown_50 == Cell(0,0)) {
        return Coord_Cell(BaseCenter);
    }
    IndexClass<int, Cell> ranking;
    sorted.Clear();
    int i;
    for (i = 0; i < unknown_55f0.unknown_20.Count(); ++i) {
        Cell cell = unknown_55f0.unknown_20[i];
        int value;
        if (!type->CloakGenerator) {
            value = score(this, cell, i, context);
        } else {
            CoordStruct cell_coord = CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
            value = i + 1000 * Coord_Span2(BaseCenter, cell_coord);
        }
        ranking.Add_Index(value, cell);
    }
    for (i = 0; i < ranking.Count(); ++i) {
        sorted.Add(ranking.Fetch_By_Position(i));
    }
    int base_height = Map[unknown_55f0.unknown_50].unknown_11b;
    int house_mask = 1 << ArrayIndex;
    Cell base_cell;
    for (int pass = 0; pass < 2; ++pass) {
        for (i = 0; i < sorted.Count(); ++i) {
            base_cell = sorted[i];
            Cell occupied(0,0);
            for (int face = 0; face < 8; ++face) {
                CellClass *cptr = &Map[Adjacent_Cell(base_cell, (FacingType)face)];
                if (cptr->unknown_dc & house_mask) {
                    occupied = Adjacent_Cell(occupied, (FacingType)face);
                }
            }
            if (occupied == Cell(0,0)) {
                continue;
            }
            Point2D delta;
            delta.X = -(int)occupied.X;
            delta.Y = -(int)occupied.Y;
            double angle = Fast_Atan2((double)-delta.Y, (double)delta.X);
            UnknownFacingDir dir = UnknownFacingDir((unsigned short)((angle - 1.5707963267948966) * -10430.060040584269));
            int facing = Dir_To_8(dir);
            Cell offset(0,0);
            int width = type->Width();
            int height = type->Foundation_Height(false);
            bool extra = type->ProtectWithWall || type->WantsExtraSpace;
            int spacing = Rules->AIBaseSpacing;
            if (extra) ++spacing;
            if (facing >= 1 && facing <= 3) {
                offset.X = (short)spacing;
            } else if (facing >= 5 && facing <= 7) {
                offset.X = (short)(1 - width - spacing);
            }
            if (facing >= 3 && facing <= 5) {
                offset.Y = (short)(spacing + 1);
            } else if (facing >= 7 || facing <= 1) {
                offset.Y = (short)(1 - height - spacing);
            }
            for (int trial = 0; trial < 2; ++trial) {
                static Facing_Offset scan_offsets[8] = {
                    Cell(-1,0), Cell(-1,-1), Cell(0,-1), Cell(1,-1),
                    Cell(1,0), Cell(1,1), Cell(0,1), Cell(-1,1)
                };
                static Facing_Offset step_offsets[8] = {
                    Cell(1,0), Cell(1,1), Cell(0,1), Cell(-1,1),
                    Cell(-1,0), Cell(-1,-1), Cell(0,-1), Cell(1,-1)
                };
                Cell pos = base_cell + offset + scan_offsets[facing];
                if (trial == 1) {
                    pos = Adjacent_Cell(pos, facing - 4);
                    spacing -= Rules->AIBaseSpacing;
                }
                for (int attempt = 0; attempt < 3; ++attempt) {
                    Rect rect(pos.X - spacing, pos.Y - spacing, width + spacing * 2, height + spacing * 2);
                    if (Map.Unknown_005686B0(rect, ArrayIndex)) {
                        if (type->unknown_slot42(pos, this)) {
                            if (abs(base_height - Map[pos].unknown_11b) < 3 && unknown_func_4f5320(type, pos)) {
                                return pos;
                            }
                        }
                    }
                    pos.X += step_offsets[facing].X;
                    pos.Y += step_offsets[facing].Y;
                }
            }
        }
    }
    return Cell(0,0);
    }
}
