// LightSourceClass::Unknown_005375D0(bool defer) (0x005375D0): TibSun's Recalculate_Affected_Cells with
// RA2's detail-level test.

void LightSourceClass::Unknown_005375D0(bool defer)
{
    if (unknown_flag_7df630 && Options.DetailLevel >= DetailLevel) {
        if (defer && PendingCellClass::Array.Count() != 0) {
            Unknown_00537830(0, true);
        }

        Cell center = Cell(Location);
        int radius = Visibility / 256 + 1;

        for (int y = -radius; y <= radius; y++) {
            for (int x = -radius; x <= radius; x++) {
                Cell test_cell = center + Cell(x, y);
                if (test_cell.X >= 0 && test_cell.X < 512 && test_cell.Y >= 0 && test_cell.Y < 512 && Map.Has_Cell(test_cell)) {
                    CoordStruct cell_coord = Cell_Coord(test_cell);
                    int dx = cell_coord.X - Location.X;
                    int dy = cell_coord.Y - Location.Y;
                    int dist = dx * dx + dy * dy;

                    if ((int)unknown_sqrt_4ba410(dist) <= Visibility) {
                        if (defer) {
                            PendingCellClass::Array.Add(new PendingCellClass(test_cell));
                        } else {
                            Map[test_cell].Init_Drawer(0, 0x10000, 0, 1000, 1000, 1000);
                        }
                    }
                }
            }
        }

        Map.Flag_To_Redraw(true);
    }
}
// @ref ?Unknown_00537830@LightSourceClass@@SIXH_N@Z=00537830
