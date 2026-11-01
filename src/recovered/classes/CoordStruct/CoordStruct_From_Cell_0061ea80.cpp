// The centre of a cell at height z (0x0061EA80; defined last in the unit, expanded inline where the budget allows).
CoordStruct::CoordStruct(Cell const &cell, int z)
{
    int x = cell.X * 256 + 128;
    int y = cell.Y * 256 + 128;
    X = x;
    Y = y;
    Z = z;
}
