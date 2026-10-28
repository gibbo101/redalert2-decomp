// Cell MultiplayerGameMode::unknown_slot42(int house, DynamicVectorClass<Cell> &cells, bool *taken) -- 0x005B7920
// Picks a house's start cell and marks it taken: a random one while none is taken (an observer's
// is not marked and noted in unknown_flag_a71a3c), the observer's cell again for the next house
// once, an observer gets the first taken cell, else the free cell farthest from the taken ones.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref ??_C@_0BO@KPNI@First?5cell?5taken?3?5?$CFd?5?$CI?$CFd?0?$CFd?$CJ?6?$AA@=007e609c
// @ref ??_C@_0CB@EDCI@Starting?5cell?5taken?3?5?$CFd?5?$CI?$CFd?0?$CFd?$CJ?6@=007e604c
// @ref ??_C@_0CF@NCNJ@Observer?5Observing?5cell?3?5?$CFd?5?$CI?$CFd?0@=007e6024
// @ref ??_C@_0CM@MPLO@Observer?5observing?5random?5cell?3?5@=007e6070
// @ref ?unknown_flag_a71a3c@@3_NA=00a71a3c
// @ref ?unknown_flag_a71a3d@@3_NA=00a71a3d
#include "shared/multiplayer_game_mode.hpp"
#include "shared/id_source.hpp"
#include "shared/house.hpp"
#include "shared/coord.hpp"
#include "shared/coord_distance.hpp"
#include "shared/lobby.hpp"
#include "shared/debug_printf.hpp"

Cell MultiplayerGameMode::unknown_slot42(int house, DynamicVectorClass<Cell> &cells, bool *taken)
{
    int index;
    for (index = 0; index < cells.Count(); index++) {
        if (taken[index]) {
            break;
        }
    }
    if (index == cells.Count()) {
        unknown_flag_a71a3c = false;
        unknown_flag_a71a3d = false;
        bool observer = false;
        HouseClass *owner = Houses[house];
        if (owner != 0) {
            for (int p = 0; p < unknown_players_a3fa7c.Count(); p++) {
                if (owner->unknown_func_4f52f0() && Compare_Wide_007837d3(owner->UIName, unknown_players_a3fa7c[p]->Name) == 0) {
                    observer = unknown_players_a3fa7c[p]->Team == -1;
                    break;
                }
            }
        }
        if (observer) {
            index = unknown_id_source_a3d290->RandomNumber(0, cells.Count() - 1);
            taken[index] = true;
            unknown_flag_a71a3c = true;
            Debug_Printf("Observer observing random cell: %d (%d,%d)\n", index, cells[index].X, cells[index].Y);
            return cells[index];
        }
        index = unknown_id_source_a3d290->RandomNumber(0, cells.Count() - 1);
        Debug_Printf("First cell taken: %d (%d,%d)\n", index, cells[index].X, cells[index].Y);
        taken[index] = true;
        return cells[index];
    }
    if (unknown_flag_a71a3c && !unknown_flag_a71a3d) {
        unknown_flag_a71a3d = true;
        return cells[index];
    }
    bool observer = false;
    HouseClass *owner = Houses[house];
    if (owner != 0) {
        for (int p = 0; p < unknown_players_a3fa7c.Count(); p++) {
            if (owner->unknown_func_4f52f0() && Compare_Wide_007837d3(owner->UIName, unknown_players_a3fa7c[p]->Name) == 0) {
                observer = unknown_players_a3fa7c[p]->Team == -1;
                break;
            }
        }
    }
    if (observer) {
        unknown_flag_a71a3d = true;
        unknown_flag_a71a3c = true;
        Debug_Printf("Observer Observing cell: %d (%d,%d)\n", index, cells[index].X, cells[index].Y);
        return cells[index];
    }
    int farthest = -1;
    int farthest_index = -1;
    for (int i = 0; i < cells.Count(); i++) {
        if (!taken[i]) {
            int total = 0;
            for (int j = 0; j < cells.Count(); j++) {
                if (taken[j]) {
                    Cell delta(cells[i].X - cells[j].X, cells[i].Y - cells[j].Y);
                    total += (short)Cell_Distance(delta.Y, delta.X);
                }
            }
            if (total > farthest) {
                farthest = total;
                farthest_index = i;
            }
        }
    }
    index = farthest_index;
    taken[index] = true;
    Debug_Printf("Starting cell taken: %d (%d,%d)\n", index, cells[index].X, cells[index].Y);
    return cells[index];
}
