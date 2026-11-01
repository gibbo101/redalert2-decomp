// int __fastcall Get_Deformable_Cell_Corners_00686dd0(CellClass *cell, int direction) (0x00686DD0)
// The mask (bit i = corner i: NW, NE, SE, SW) of the cell's unlocked corners
// that a step in direction would move: every unlocked corner on flat ground,
// else those below the highest (raising) or above the lowest (lowering).

int __fastcall Get_Deformable_Cell_Corners_00686dd0(CellClass *cell, int direction)
{
    int x = cell->Fetch_CellID().X - unknown_undo_x_8286e8;
    int y = cell->Fetch_CellID().Y - unknown_undo_y_8286ec;
    UnknownUndoCell corners[4] = {
        unknown_undo_cells_abceac[y * unknown_undo_width_8286e4 + x],
        unknown_undo_cells_abceac[y * unknown_undo_width_8286e4 + x + 1],
        unknown_undo_cells_abceac[(y + 1) * unknown_undo_width_8286e4 + x + 1],
        unknown_undo_cells_abceac[(y + 1) * unknown_undo_width_8286e4 + x]
    };
    int heights[4] = { corners[0].Value, corners[1].Value, corners[2].Value, corners[3].Value };
    int lowest = 1000;
    int highest = -1;
    int index;
    for (index = 0; index < 4; index++) {
        if (heights[index] < lowest) {
            lowest = heights[index];
        }
        if (heights[index] > highest) {
            highest = heights[index];
        }
    }
    int result = 0;
    if (highest == lowest) {
        for (index = 0; index < 4; index++) {
            if (!corners[index].unknown_04) {
                result += 1 << index;
            }
        }
        return result;
    }
    if (direction > 0) {
        for (index = 0; index < 4; index++) {
            if (heights[index] < highest && !corners[index].unknown_04) {
                result += 1 << index;
            }
        }
        return result;
    }
    for (index = 0; index < 4; index++) {
        if (heights[index] > lowest && !corners[index].unknown_04) {
            result += 1 << index;
        }
    }
    return result;
}
