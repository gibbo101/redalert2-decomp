// IsometricTileClass::IsometricTileClass(int type, Cell const &cell) (0x00527ED0)
// A tile of the given type; unless the cell is the "no cell" value it is
// placed at the middle of the cell by slot 53 (qualified, expanded inline).
#include "shared/isometric_tile.hpp"
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref ?IsoTileTypes@@3V?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@A=00a40cd0
// @ref ?IsoTiles@@3V?$DynamicVectorClass@PAVIsometricTileClass@@@@A=00832448
// @ref ?unknown_cell_a52520@@3VCell@@B=00a52520
// @ref ??_7IsometricTileClass@@6BIPersistStream@@@=007a47d0
// @ref ??_7IsometricTileClass@@6BIRTTITypeInfo@@@=007a47b4
// @ref ??_7IsometricTileClass@@6BINoticeSink@@@=007a47ac
// @ref ??_7IsometricTileClass@@6BINoticeSource@@@=007a47a4

IsometricTileClass::IsometricTileClass(int type, Cell const &cell) :
    Type(IsoTileTypes[type])
{
    if (cell != unknown_cell_a52520) {
        CoordStruct coord(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
        IsometricTileClass::unknown_slot53(&coord, 0);
    }
    IsoTiles.Add(this);
}
