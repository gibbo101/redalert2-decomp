// Finds an exit coordinate for the attached unit; original00607C30.
#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
#include "shared/cell.hpp"
#include "shared/parasite.hpp"
#include "shared/unknown_geometry.hpp"
// @ref _unknown_geometry_l=00a76468
CoordStruct ParasiteClass::Unknown_00607C30()
{
    if (unknown_28 == 0) return unknown_geometry_l;
    {
        bool can_exit = false;
        if (!unknown_28->unknown_slot21()) {
            if (Owner->unknown_slot32()->Naval) {
                can_exit = true;
            } else if (!(Owner != 0 && Owner->Kind_Of() == 1 && ((CellClass *)unknown_28->unknown_slot105())->Cell_Terrain() != 0)) {
                int land = ((CellClass *)unknown_28->unknown_slot105())->unknown_ec;
                if (land != 2 && land != 6 && land != 3) can_exit = true;
            }
        }
        if (can_exit) {
            return unknown_28->Coord;
        }
        int facing = Dir_To_8(unknown_28->unknown_2e0.Current());
        CellClass *victim_cell = (CellClass *)unknown_28->unknown_slot105();
        CellClass &cell = victim_cell->Adjacent_Cell(facing);
        if (!Owner->unknown_slot32()->Naval) {
            int land = cell.unknown_ec;
            if (land == 2 || land == 6 || land == 3) {
                return unknown_geometry_l;
            }
        }
        CoordStruct spot = cell.Closest_Free_Spot(cell.Center_Coord(), false, false);
        if (spot != unknown_geometry_l) {
            return spot;
        }
    }
    return unknown_geometry_l;
}
