// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// UnknownPathEstimator::Unknown_004290C0() (0x004290C0): replaces wandering
// runs of a found path by straight lines where foot can walk them, then packs
// out the emptied moves (Tiberian Sun's Optimize_Moves; hypothesis).
// From ra2-decomp AStarClass::Optimize_Moves (YR 0x0042B7F0), adapted to our names.
#include "shared/path_estimator.hpp"
#include "shared/crt_memory.hpp"

#include "shared/adjacent_cell.hpp"

// The cell next to one toward a facing, the cell taken by value.
static inline Cell Adjacent_Cell_By_Value(Cell cell, int facing)
{
    Cell const &offset = AdjacentCell[facing & 7];
    return Cell(cell.X + offset.X, cell.Y + offset.Y);
}


// Westwood's max template (defined with the Unknown_0042AA30 row of this unit).
template <class T> T max(T a, T b);

void UnknownPathEstimator::Unknown_004290C0(UnknownPathType *path, FootClass *foot)
{
    int splice_index;
    Cell splice_cell;
    int *moves = path->Command;
    int max_len = path->Length;
    max_len--;
    int scan_index = 0;
    int prev_turn_index = 0;
    Cell cursor_cell = path->Start;
    int *heights = path->Height;
    int index;
    int last_turn_index = 0;
    int max_axis;
    int max_axis_extent = 0;
    Cell path_offset(0, 0);
    Cell last_turn_cell(0, 0);
    int max_dev_x = 0;
    int max_dev_y = 0;
    Cell candidate_offset(0, 0);
    while (scan_index < max_len && scan_index < 20) {
        int move = moves[scan_index];
        int step = moves[scan_index];

        if (step == 8) {
            cursor_cell = Adjacent_Cell_By_Value(cursor_cell, 0);
            path_offset = Cell(0, 0);
            scan_index++;
            prev_turn_index = scan_index;
            max_axis_extent = 0;
            max_dev_x = 0;
            max_dev_y = 0;
            candidate_offset = Cell(0, 0);
            last_turn_index = scan_index;
            last_turn_cell = Cell(0, 0);
            continue;
        }

        if (move == -2) {
            scan_index++;
            continue;
        }

        Cell new_offset = path_offset + AdjacentCell[move & 7];
        Cell new_candidate_offset = AdjacentCell[move & 7] + candidate_offset;
        if (abs(new_candidate_offset.X) >= max_dev_x && abs(new_candidate_offset.Y) >= max_dev_y) {

            candidate_offset = new_candidate_offset;

            max_dev_x = abs(new_candidate_offset.X);
            max_dev_y = abs(new_candidate_offset.Y);

            max_axis = max(abs(new_offset.X), abs(new_offset.Y));

            cursor_cell = Adjacent_Cell_By_Value(cursor_cell, step);
            if (max_axis_extent < max_axis) {
                max_axis_extent = max_axis;
            } else {
                splice_cell = cursor_cell;
                Unknown_00429570(moves, scan_index, prev_turn_index, &splice_index, &splice_cell);

                Unknown_004296F0(&moves[splice_index], scan_index - splice_index + 1, splice_cell,
                    Cell(cursor_cell - splice_cell), foot, heights[splice_index], false);
            }

            path_offset = new_offset;
            ++scan_index;
        } else {
            if (last_turn_cell == Cell(0, 0)) {
                max_dev_x = 0;
                max_dev_y = 0;
                last_turn_cell = cursor_cell;
                last_turn_index = scan_index;
                candidate_offset = Cell(0, 0);
            } else {
                prev_turn_index = last_turn_index;
                path_offset = last_turn_cell - cursor_cell;
                max_dev_x = 0;
                max_dev_y = 0;
                candidate_offset = Cell(0, 0);
                max_axis_extent = max(abs(path_offset.X), abs(path_offset.Y));
                last_turn_cell = cursor_cell;
                last_turn_index = scan_index;
            }
        }
    }
    if (last_turn_cell != Cell(0, 0)) {
        Cell diff = cursor_cell - last_turn_cell;
        max_axis = max(abs(diff.X), abs(diff.Y));
        if ((scan_index - last_turn_index - 1) > max_axis) {
            scan_index--;
            splice_cell = cursor_cell;
            Unknown_00429570(moves, scan_index, last_turn_index, &splice_index, &splice_cell);

            Unknown_004296F0(&moves[splice_index], scan_index - splice_index + 1, splice_cell,
                Cell(cursor_cell - splice_cell), foot, heights[splice_index], true);
        }
    }
    index = 0;
    int new_len = 0;
    int dir = moves[index];
    while (dir != -1 && index < max_len) {
        if (dir != -2) {
            moves[new_len++] = moves[index];
        }
        dir = moves[++index];
    }
    int fill = new_len;
    while (fill < path->Length + 1) {
        moves[fill++] = -1;
    }

    path->Length = new_len + 1;
}
