// UnknownPathEstimator::Unknown_00429570() (0x00429570): walks a facing list
// backwards from index to stop until the walk turns back toward its start.
#include "shared/path_estimator.hpp"
#include "shared/crt_memory.hpp"

#include "shared/adjacent_cell.hpp"

void UnknownPathEstimator::Unknown_00429570(int const *facings, int index, int stop, int *out_index, Cell *cell)
{
    Cell offset(0, 0);
    int farthest = 0;
    int step = index;
    Cell position = *cell;
    bool returning = false;
    while (step >= stop) {
        int facing = facings[step];
        if (facing == -2) {
            step--;
            continue;
        }
        int back = (facing - 4) & 7;
        offset = AdjacentCell[back & 7] + offset;
        position = AdjacentCell[back & 7] + position;
        int distance = abs(offset.X) > abs(offset.Y) ? abs(offset.X) : abs(offset.Y);
        if (distance > farthest) {
            if (returning) {
                *out_index = step + 1;
                *cell = AdjacentCell[(back - 4) & 7] + position;
                return;
            }
            farthest = distance;
        } else {
            returning = true;
        }
        step--;
    }
    *out_index = stop;
    *cell = position;
}
