// Cell MPCooperative::unknown_slot42(int house, DynamicVectorClass<Cell> &cells, bool *taken) -- 0x005A3F90
// Picks a start cell for a house and marks it taken: a random one while none is taken, the one
// nearest the single taken cell, else the one farthest from all taken cells.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/multiplayer_game_mode.hpp"
#include "shared/coord.hpp"
#include "shared/coord_distance.hpp"
#include "shared/id_source.hpp"

Cell MPCooperative::unknown_slot42(int house, DynamicVectorClass<Cell> &cells, bool *taken)
{
    int count = 0;
    int i;
    for (i = 0; i < cells.Count(); i++) {
        if (taken[i]) {
            count++;
        }
    }
    int index;
    if (count == 0) {
        index = unknown_id_source_a3d290->RandomNumber(0, cells.Count() - 1);
        taken[index] = true;
        return cells[index];
    } else {
        int nearest = -1;
        int nearest_index = -1;
        if (count == 1) {
            for (i = 0; i < cells.Count(); i++) {
                if (!taken[i]) {
                    int total = 0;
                    for (int j = 0; j < cells.Count(); j++) {
                        if (taken[j]) {
                            Cell delta(cells[i].X - cells[j].X, cells[i].Y - cells[j].Y);
                            total += (short)Cell_Distance(delta.X, delta.Y);
                        }
                    }
                    if (total < nearest || nearest < 0) {
                        nearest = total;
                        nearest_index = i;
                    }
                }
            }
            taken[nearest_index] = true;
            return cells[nearest_index];
        } else {
            int farthest = -1;
            int farthest_index = -1;
            for (i = 0; i < cells.Count(); i++) {
                if (!taken[i]) {
                    int total = 0;
                    for (int j = 0; j < cells.Count(); j++) {
                        if (taken[j]) {
                            Cell delta(cells[i].X - cells[j].X, cells[i].Y - cells[j].Y);
                            total += (short)Cell_Distance(delta.X, delta.Y);
                        }
                    }
                    if (total > farthest) {
                        farthest = total;
                        farthest_index = i;
                    }
                }
            }
            index = farthest_index;
        }
    }
    taken[index] = true;
    return cells[index];
}
