Point2D UnknownPreview_0061D430::Cell_To_Preview_Pixel(Cell cell) const
{
    int x;
    int y;
    // The X lepton comes from the coordinate constructor, the Y from Cell::As_Coord (the inlined
    // copies in 0x0061D660 call the two out of line differently).
    unknown_tactical_83996c->Lepton_To_Map_Pixel(UnknownCoord434820(cell).X, cell.As_Coord().Y, x, y);
    return Point2D(x / 60, y / 30);
}
// @ref ?Lepton_To_Map_Pixel@Tactical@@QAEXHHAAH0@Z=006a6920
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
