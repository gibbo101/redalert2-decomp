// UnknownPathEstimator::Unknown_004296F0() (0x004296F0): tries the two-leg
// straight path (a diagonal then a straight run, or the reverse) to a cell
// offset and writes its facings (Tiberian Sun's Plot_Straight_Line;
// hypothesis).
// @ref ?unknown_4cafb0@FootClass@@QBENXZ=004cafb0
#include "shared/path_estimator.hpp"
#include "shared/foot.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/crt_memory.hpp"

// The cell next to one toward a facing (the guarded block of shared/display.hpp, shared/terrain.hpp,
// shared/infantry.hpp and shared/aircraft.hpp; those headers are too heavy for this unit).
#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
#include "shared/adjacent_cell.hpp"
inline Cell Adjacent_Cell(Cell cell, int facing)
{
    Cell const &offset = AdjacentCell[facing & 7];
    return Cell(cell.X + offset.X, cell.Y + offset.Y);
}
#endif

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

template <class T> void swap(T &left, T &right)
{
    T temp = left;
    left = right;
    right = temp;
}

bool UnknownPathEstimator::Unknown_004296F0(int *moves, int move_count, Cell const &from, Cell const &to, FootClass *foot, int level, bool fearless)
{
    int tries = 0;
    int x = to.X;
    int y = to.Y;
    int first_dir;
    if (to.X < 0) {
        first_dir = to.Y < 0 ? 7 : 5;
    } else {
        first_dir = to.Y < 0 ? 1 : 3;
    }
    int sub_xy = x - y;
    int sum_xy = x + y;
    int second_dir;
    if (sub_xy > 0) {
        second_dir = sum_xy > 0 ? 2 : 0;
    } else {
        second_dir = sum_xy > 0 ? 4 : 6;
    }
    int y_dist = abs(y);
    int x_dist = abs(x);
    int first_dist = MIN(x_dist, y_dist);
    int second_dist = MAX(x_dist, y_dist) - first_dist;
    double avoidance = foot->unknown_4cafb0();
    int threats = 0;
    HouseClass *house = foot->House;
    bool avoid_threats = avoidance > 0.00001;
    bool blocked = false;
    while (tries < 2) {
        threats = 0;
        if (first_dist != 0) {
            int height = level;
            blocked = false;
            Cell current = from;
            int count1 = first_dist;
            int count2 = second_dist;
            while (count1 > 0 && !blocked) {
                current = Adjacent_Cell(current, first_dir);
                CellClass *cellptr = &Map[current];
                if (avoid_threats && Map.Unknown_0054E3A0(current, house) * avoidance >= 0.01) {
                    threats++;
                }
                blocked = foot->unknown_slot101(cellptr, first_dir, height, 0, 1) != 0 || (cellptr->unknown_140 & 0x40000) || threats > 3 || (!fearless && threats > 0);
                count1--;
                int step_height = cellptr->unknown_11b;
                if (height - step_height == 4) {
                    height = step_height + 4;
                    if (cellptr->unknown_140 & 0x100) {
                        continue;
                    }
                }
                height = step_height;
            }
            while (count2 > 0 && !blocked) {
                current = Adjacent_Cell(current, second_dir);
                CellClass *cellptr = &Map[current];
                if (avoid_threats && Map.Unknown_0054E3A0(current, house) * avoidance >= 0.01) {
                    threats++;
                }
                blocked = foot->unknown_slot101(cellptr, second_dir, height, 0, 1) != 0 || (cellptr->unknown_140 & 0x40000) || threats > 3 || (!fearless && threats > 0);
                count2--;
                int step_height = cellptr->unknown_11b;
                if (height - step_height == 4) {
                    height = step_height + 4;
                    if (cellptr->unknown_140 & 0x100) {
                        continue;
                    }
                }
                height = step_height;
            }
        }
        if (first_dist == 0 || blocked) {
            swap(second_dir, first_dir);
            swap(second_dist, first_dist);
        } else {
            int i;
            for (i = 0; i < first_dist; i++) {
                moves[i] = first_dir;
            }
            for (i = 0; i < second_dist; i++) {
                moves[first_dist + i] = second_dir;
            }
            for (i = 0; i < move_count - first_dist - second_dist; i++) {
                moves[first_dist + second_dist + i] = -2;
            }
            return true;
        }
        tries++;
    }
    return false;
}
