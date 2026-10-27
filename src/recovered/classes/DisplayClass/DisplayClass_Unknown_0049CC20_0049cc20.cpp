// void DisplayClass::Unknown_0049CC20() (0x0049CC20)
// Over all 512 x 512 cells on the map: marks the visible ones that are not
// fully shrouded (+0x140 bit 5); then unmaps each marked cell through
// 0x0049CF00 (clearing the mark), runs 0x0049E110 (false, false) and redraws.
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Unknown_0054AAB0@MapClass@@QAE_NABVCell@@@Z=0054aab0
// @ref ?Unknown_0049CF00@DisplayClass@@QAEXABVCell@@@Z=0049cf00
// @ref ?Unknown_0049E110@DisplayClass@@QAEX_N0@Z=0049e110

void DisplayClass::Unknown_0049CC20()
{
    int x;
    int y;
    for (y = 0; y < 512; y++) {
        for (x = 0; x < 512; x++) {
            if (Unknown_0054AAB0(Cell(x, y))) {
                CellClass &cell = (*this)[Cell(x, y)];
                if (!(cell.unknown_12c & 0x10) && (cell.unknown_12c & 8)) {
                    cell.unknown_140 |= 0x20;
                }
            }
        }
    }
    for (y = 0; y < 512; y++) {
        for (x = 0; x < 512; x++) {
            Cell where(x, y);
            if (Unknown_0054AAB0(where) && ((*this)[where].unknown_140 & 0x20)) {
                (*this)[where].unknown_140 &= ~0x20;
                Unknown_0049CF00(where);
            }
        }
    }
    Unknown_0049E110(false, false);
    Flag_To_Redraw(true);
}
