// CoordStruct CellClass::Closest_Free_Spot(CoordStruct const &coord, bool any, bool alt) const
// (0x004764B0): Westwood's Closest_Free_Spot. The free sub-cell spot of the cell (alt: on the bridge)
// closest to coord's sub-cell position, or the null coordinate when the cell holds a vehicle, a
// closed gate or a building or no spot is free; any: the nearest spot even if taken.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/id_source.hpp"
#include "shared/infantry.hpp"
// @ref ?unknown_cell_offsets_00850e50@@3PAUCoordStruct@@A=00850e50
// @ref ?unknown_spot_sequence_7d2b6c@@3PAY03EA=007d2b6c
// @ref ?unknown_spot_alternate_7d2b80@@3PAY03EA=007d2b80
// The offset of each sub-cell spot from the cell corner (Westwood's StoppingCoordAbs, 0x00850E50).
extern CoordStruct unknown_cell_offsets_00850e50[5];
// The spots nearest each spot, closest first (Westwood's _sequence, a function-local static).
extern unsigned char unknown_spot_sequence_7d2b6c[5][4];
// The orders to try the outer spots in when the centre is taken (Westwood's _alternate).
extern unsigned char unknown_spot_alternate_7d2b80[4][4];


// The cell corner of a coordinate: its sub-cell part dropped (Westwood's Coord_Whole).
inline CoordStruct Coord_Whole(CoordStruct const &coord)
{
    int x = coord.X - (coord.X & 0xFF);
    int y = coord.Y - (coord.Y & 0xFF);
    return CoordStruct(x, y, coord.Z);
}

// The gate building in the cell, if any (Westwood's Get_Gate; inline here).
inline BuildingClass *CellClass::Get_Gate() const
{
    BuildingClass *building = (BuildingClass *)Find_Object(6);
    if (building != 0 && !building->Type->Gate) {
        building = 0;
    }
    return building;
}

CoordStruct CellClass::Closest_Free_Spot(CoordStruct const &xcoord, bool any, bool alt) const
{
    int spot_index = Unknown_004763D0(xcoord);

    CoordStruct coord = Coord_Whole(xcoord);

    bool is_vehicle_occupied;
    if (alt) {
        is_vehicle_occupied = Occupy_128.Vehicle;
    } else {
        is_vehicle_occupied = Occupy_124.Vehicle;
    }

    if (!any) {
        if (is_vehicle_occupied || (Occupy_124.Monolith && (!Get_Gate() || !Get_Gate()->unknown_44d880()))) {
            return unknown_geometry_l;
        }
    }

    if (any || unknown_476460(spot_index, alt)) {
        coord = coord + unknown_cell_offsets_00850e50[spot_index];
        coord.Z = Map.Unknown_0055A280(xcoord);
        if (alt) {
            coord.Z += unknown_geometry_j;
        }
        return coord;
    }

    unsigned char *sequence;
    if (spot_index == 0) {
        sequence = &unknown_spot_alternate_7d2b80[Random_Pick(0, 3)][0];
    } else {
        sequence = &unknown_spot_sequence_7d2b6c[spot_index][0];
    }
    for (int index = 0; index < 4; index++) {
        int pos = *sequence++;

        if (unknown_476460(pos, alt)) {
            coord = coord + unknown_cell_offsets_00850e50[pos];
            coord.Z = Map.Unknown_0055A280(xcoord);
            if (alt) {
                coord.Z += unknown_geometry_j;
            }
            return coord;
        }
    }
    return unknown_geometry_l;
}
