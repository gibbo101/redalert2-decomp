// Complete laser-fence placement preview, original 0x006A5D70.
void Tactical::Draw_Fence_Placement(bool drawtrans, Cell cell)
{
    for (int index = 0; index < 8; index += 2) {
        Cell scan = cell;
        int count = 0;
        int range = ((BuildingClass *)Map.unknown_11a0)->Type->GuardRange.Value >> 8;
        if (range <= 0) continue;
        int facing = index;
        BuildingClass *building;
        bool found = false;
        while (true) {
            scan = Adjacent_Cell(scan, facing);
            building = (BuildingClass *)Map[scan].unknown_4717b0();
            if (building) {
                found = true;
                break;
            }
            CellClass *nearby = &Map[scan];
            if (nearby->Cell_Terrain(false) || nearby->unknown_11c > 0 || nearby->unknown_4c != 0 || ++count >= range) break;
        }
        if (found && building->Type->LaserFencePost && building->House->Unknown_004F52B0() && count > 0) {
            int flags = drawtrans ? 0x10606 : 0x20606;
            Cell drawcell = Adjacent_Cell(cell, facing);
            for (int i = 0; i < count; ++i) {
                int height = 15 * Map[drawcell].unknown_11b;
                int zheight = 15 * Map[drawcell].unknown_11b;
                Point2D offset(0, -1 - height);
                int zoff = -2 - zheight;
                CoordStruct coord = Coord_Snap(Cell_Center(drawcell));
                Point2D pixel;
                Coord_To_Pixel(coord, pixel);
                pixel.X -= 30;
                int px = pixel.X + 30;
                int py = offset.Y + pixel.Y;
                Point2D point(px, py);
                CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c4, (ShapeFileStruct const *)DisplayClass::TransIconset, 0, point,
                    unknown_rect_839630, flags, 0, zoff, 0, 1000, 0, 0, Point2D(0, 0));
                drawcell = Adjacent_Cell(drawcell, facing);
            }
        }
    }
}
