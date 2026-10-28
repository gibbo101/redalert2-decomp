// TargetClass::TargetClass(CoordStruct const &coord) (0x006B5560): the cell
// holding the coordinate.

TargetClass::TargetClass(CoordStruct const &coord)
{
    Kind = 11;
    ID = coord.X / 256 + coord.Y / 256 * 1000;
}
