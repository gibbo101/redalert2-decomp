// void MapClass::Unknown_00557090(Cell const &cell) (0x00557090)
// Destroys the high bridge span near a cell (RA2 only; 0x00556520 is its twin for the second low bridge set).
// The span advance stands before the destroy block in the source: inline sites number in source order, so the
// goto layout is what puts the end-walk sums on the original operand order (docs/VC6_MATCHING_NOTES, Cell sum tie).
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/map_isotile.hpp"
#include "shared/tileset_index.hpp"
#include "shared/tactical.hpp"
// @ref ?Destroy_High_Bridge_Connections_00558BD0@MapClass@@QAEXABVCell@@@Z=00558bd0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
void MapClass::Unknown_00557090(Cell const &cell)
{
    for (int x = -2; x < 3; ++x) {
        for (int y = -2; y < 3; ++y) {
            if (Unknown_00562930(cell + Cell(x, y))) {
                Destroy_Low_Bridge_Span(cell + Cell(x, y));
                return;
            }
        }
    }
    CellClass *cellptr = &Map[cell];
    int step;
    int facing = 0;
    if (!cellptr->IsUnderBridge && !cellptr->WasUnderBridge) {
        for (int index = 0; index < 8; ++index) {
            Cell adjacent = Adjacent_Cell(cell, facing);
            cellptr = &Map[adjacent];
            if (cellptr->IsUnderBridge || cellptr->WasUnderBridge) break;
            Cell adjacent2 = Adjacent_Cell(adjacent, facing);
            cellptr = &Map[adjacent2];
            if (cellptr->IsUnderBridge || cellptr->WasUnderBridge) break;
            adjacent = Adjacent_Cell(adjacent2, facing);
            cellptr = &Map[adjacent];
            if (cellptr->IsUnderBridge || cellptr->WasUnderBridge) break;
            facing = (facing + 1) & 7;
        }
    }
    if (!cellptr->IsUnderBridge && !cellptr->WasUnderBridge) return;
    Cell origin;
    if (cellptr->IsUnderBridge) {
        if (cellptr->IsBridgeDeck) origin = cellptr->MapCoords;
        else origin = cellptr->unknown_2c->MapCoords;
    } else {
        Cell walk = cellptr->Fetch_CellID();
        int count = 0;
        
        if (cellptr->IsBridgeEastWest) step = 4;
        else step = 2;
        CellClass *walkptr;
        while (true) {
            Cell const &from = walk; walk = Adjacent_Cell_L(from, step);
            walkptr = &Map[walk];
            if (walkptr->WasUnderBridge) {
                if (++count >= 4) return;
            } else {
                break;
            }
        }
        int back = (step - 4) & 7;
        origin = (AdjacentCell[back & 7] + walk) + AdjacentCell[back & 7];
    }
    
    int shared_direction = cellptr->IsBridgeEastWest ? 6 : 0;
    Cell spancell = origin;
    DynamicVectorClass<Cell> cells;
    int tile;
    CellClass *spanptr;
    if (spancell.X >= unknown_120) {
        while (spancell.X >= unknown_120) {
            if (spancell.X > unknown_120 + unknown_128) break;
            if (spancell.Y < unknown_124 || spancell.Y > unknown_124 + unknown_12c) break;
            if (Cells[spancell.X + spancell.Y * 512] != 0) {
                spanptr = &Map[spancell];
                tile = spanptr->IsoTileIndex - unknown_tileset_a6cb68 + 1;
                if (((tile == unknown_tileset_a6e0e4 || tile == unknown_tileset_a52f80) && spanptr->unknown_11a == 8) ||
                    ((tile == unknown_tileset_a53394 || tile == unknown_tileset_a52588) && spanptr->unknown_11a == 12)) {
                    goto destroy_span;
                }
            }
            spancell = Adjacent_Cell(spancell, shared_direction);
        }
    }
    goto finished;

destroy_span:
    {
        step = (shared_direction - 4) & 7;
        Cell end = spancell;
        int hits;
        for (hits = 0; hits < 3; ++hits) {
            if (Unknown_00569090(&spancell)) break;
        }
        while (true) {
            end = Adjacent_Cell(end, step);
            spanptr = &Map[end];
            if (end.X < unknown_120 || end.X > unknown_120 + unknown_128 ||
                end.Y < unknown_124 || end.Y > unknown_124 + unknown_12c)
                goto destroy_connections;
            tile = spanptr->IsoTileIndex - unknown_tileset_a6cb68 + 1;
            if (Unknown_00556B30(tile, step, spanptr)) break;
        }
        if (tile != -1) {
            end = end + AdjacentCell[(step - 4) & 7];
            for (hits = 0; hits < 3; ++hits) {
                if (Unknown_00569090(&end)) break;
            }
        }
destroy_connections:
        Destroy_High_Bridge_Connections_00558BD0(spancell);
        unknown_tactical_83996c->unknown_d7c = true;
    }

finished:
    Unknown_0054EBD0();
}
