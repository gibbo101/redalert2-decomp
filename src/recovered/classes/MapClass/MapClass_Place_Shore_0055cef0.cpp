// Select and place a shore tile from adjacent water and straight-coast length, original0055CEF0.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_isotile.hpp"
#include "shared/tileset_index.hpp"
#include "shared/crt_memory.hpp"
// @ref ?Unknown_0055D410@MapClass@@QAEHPAVCellClass@@H@Z=0055d410
// @ref ?Pick_Random_Tile_Variant@MapClass@@QAE_NHHHHAA_N_N@Z=0055d640
// @ref ?Unknown_004994D0@DisplayClass@@QAE?AVCell@@ABV2@@Z=004994d0
// @ref ?unknown_shore_offsets_a6f91c@@3PAVCell@@A=00a6f91c
extern Cell unknown_shore_offsets_a6f91c[42];
unsigned int __fastcall Map_Random_Range_005797a0(unsigned int minimum, unsigned int maximum);

bool MapClass::Place_Shore(CellClass *cellptr, int pass, int region_id, bool set_region)
{
    int random = Map_Random_Range_005797a0(0, 5);
    int mask;
    if (pass == 2) mask = Unknown_0055D410(cellptr, 1);
    else mask = Unknown_0055D410(cellptr, 0);
    if (mask == 0) return true;
    int index = -1;
    int count;
    CellClass *adj1;
    CellClass *adj2;
    bool side_1_is_land;
    bool side_2_is_water;
    if (pass == 2) {
        if ((mask & 0xA0) == 0xA0) {
            if ((mask & 0x11) == 0x11) index = (random & 1) + 23;
            else { if ((mask & 1) != 0) index = 21; else index = 30; }
        } else if ((mask & 0x82) == 0x82) {
            if ((mask & 0x44) == 0x44) index = (random & 1) + 15;
            else { if ((mask & 4) != 0) index = 14; else index = 22; }
        } else if ((mask & 0x0A) == 0x0A) {
            if ((mask & 0x11) == 0x11) index = (random & 1) + 7;
            else { if ((mask & 1) != 0) index = 13; else index = 6; }
        } else {
            if ((mask & 0x28) != 0x28) return true;
            if ((mask & 0x44) == 0x44) index = (random & 1) + 31;
            else { if ((mask & 4) != 0) index = 5; else index = 29; }
        }
    } else {
    if (mask & 2) {
        count = 1;
        adj1 = &cellptr->Adjacent_Cell(4);
        adj2 = &adj1->Adjacent_Cell(2);
        side_1_is_land = !adj1->unknown_47a270();
        side_2_is_water = adj2->unknown_47a270();
        while (side_1_is_land && side_2_is_water) {
            ++count;
            adj1 = &adj1->Adjacent_Cell(4);
            adj2 = &adj2->Adjacent_Cell(4);
            side_1_is_land = !adj1->unknown_47a270();
            side_2_is_water = adj2->unknown_47a270();
        }
        if ((count & 1) && !(mask & 0x80)) index = 12;
        if (index == -1) {
            if (!(mask & 4) || (mask & 0x18)) index = 12;
            else index = abs(random % 3) + 9;
        }
    } else if (mask & 0x20) {
        count = 1;
        adj1 = &cellptr->Adjacent_Cell(4);
        adj2 = &adj1->Adjacent_Cell(6);
        side_1_is_land = !adj1->unknown_47a270();
        side_2_is_water = adj2->unknown_47a270();
        while (side_1_is_land && side_2_is_water) {
            ++count;
            adj1 = &adj1->Adjacent_Cell(4);
            adj2 = &adj2->Adjacent_Cell(4);
            side_1_is_land = !adj1->unknown_47a270();
            side_2_is_water = adj2->unknown_47a270();
        }
        if ((count & 1) && !(mask & 0x80)) index = 28;
        if (index == -1) {
            if (!(mask & 0x10) || (mask & 0x0C)) index = 28;
            else index = random % 3 + 25;
        }
    } else if (mask & 8) {
        count = 1;
        adj1 = &cellptr->Adjacent_Cell(2);
        adj2 = &adj1->Adjacent_Cell(4);
        side_1_is_land = !adj1->unknown_47a270();
        side_2_is_water = adj2->unknown_47a270();
        while (side_1_is_land && side_2_is_water) {
            ++count;
            adj1 = &adj1->Adjacent_Cell(2);
            adj2 = &adj2->Adjacent_Cell(2);
            side_1_is_land = !adj1->unknown_47a270();
            side_2_is_water = adj2->unknown_47a270();
        }
        if (count & 1) index = 4;
        if (index == -1) {
            if (!(mask & 4) || (mask & 3)) index = 4;
            else index = random % 3 + 1;
        }
    } else if (mask & 0x80) {
        count = 1;
        adj1 = &cellptr->Adjacent_Cell(2);
        adj2 = &adj1->Adjacent_Cell(0);
        side_1_is_land = !adj1->unknown_47a270();
        side_2_is_water = adj2->unknown_47a270();
        while (side_1_is_land && side_2_is_water) {
            ++count;
            adj1 = &adj1->Adjacent_Cell(2);
            adj2 = &adj2->Adjacent_Cell(2);
            side_1_is_land = !adj1->unknown_47a270();
            side_2_is_water = adj2->unknown_47a270();
        }
        if (count & 1) index = 20;
        if (index == -1) {
            if (!(mask & 1) || (mask & 6)) index = 20;
            else index = random % 3 + 17;
        }
    }
    if (index == -1) {
        if (mask & 1) index = (random & 1) + 35;
        else if (mask & 4) index = (random & 1) + 33;
        else if (mask & 0x10) index = (random & 1) + 39;
        else {
            if (!(mask & 0x40)) return true;
            index = (random & 1) + 37;
        }
    }
    }
    if (index > 0) {
        Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a6cb74 + index - 1];
        Cell cellid = cellptr->Fetch_CellID();
        Cell cursor = Map.Unknown_004994D0(cellid + unknown_shore_offsets_a6f91c[index]);
        bool result = true;
        if (pass == 1) Pick_Random_Tile_Variant(0, 0, cellptr->unknown_11b, region_id, result, set_region);
        else {
            if (pass != 2) return true;
            Pick_Random_Tile_Variant(unknown_tileset_a6cb74, unknown_tileset_a6cb74 + 41, cellptr->unknown_11b, region_id, result, set_region);
        }
        if (!result) return false;
    }
    return true;
}
