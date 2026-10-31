// bool MapClass::Unknown_00569090(Cell *cell) (0x00569090; TibSun Damage_Bridge, a rename candidate)
// Damages the bridge at a cell (TibSun Damage_Bridge): a low bridge overlay (0x4A-0x63,
// 0x0055DCA0; 0xCD-0xE6, 0x0055EDB0); a high bridge (deck overlay 0x18/0x19 or a bridge
// middle tile, 0x00559000) or a train bridge (deck overlay 0xED/0xEE or a train bridge
// middle tile, 0x005539B0). The cells left pending (+0xD0) collapse (0x0047C930).
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Unknown_0055DCA0@MapClass@@QAE_NABVCell@@@Z=0055dca0
// @ref ?Unknown_0055EDB0@MapClass@@QAE_NABVCell@@@Z=0055edb0
// @ref ?Unknown_00559000@MapClass@@QAE_NABVCell@@@Z=00559000
// @ref ?Unknown_005539B0@MapClass@@QAE_NABVCell@@@Z=005539b0
// @ref ?unknown_47c930@CellClass@@QAEXXZ=0047c930

bool MapClass::Unknown_00569090(Cell *cell)
{
    bool result = false;
    unknown_d0.Clear();
    CellClass *cptr = &Map[*cell];

    if (cptr->OverlayIndex >= 0x4A && cptr->OverlayIndex <= 0x63) {
        result = Unknown_0055DCA0(*cell);
    } else if (cptr->OverlayIndex >= 0xCD && cptr->OverlayIndex <= 0xE6) {
        result = Unknown_0055EDB0(*cell);
    } else {
        int ittype = cptr->IsoTileIndex - unknown_tileset_a52c74 + 1;
        CellClass *bcptr = 0;
        if (cptr->unknown_140 & 0x100) {
            if (cptr->unknown_140 & 0x80) {
                bcptr = &Map[cptr->Fetch_CellID()];
            } else {
                bcptr = &Map[cptr->unknown_2c->Fetch_CellID()];
            }
        }

        if ((bcptr != 0 && (bcptr->OverlayIndex == 0x18 || bcptr->OverlayIndex == 0x19)) ||
            ittype == unknown_tileset_a6cb7c + 0 ||
            ittype == unknown_tileset_a6cb7c + 1 ||
            ittype == unknown_tileset_a6cb7c + 2 ||
            ittype == unknown_tileset_a6cb7c + 3 ||
            ittype == unknown_tileset_a52e70 + 0 ||
            ittype == unknown_tileset_a52e70 + 1 ||
            ittype == unknown_tileset_a52e70 + 2 ||
            ittype == unknown_tileset_a52e70 + 3) {
            result = Unknown_00559000(*cell);
        } else {
            ittype = cptr->IsoTileIndex - unknown_tileset_a6cb68 + 1;
            if ((bcptr != 0 && (bcptr->OverlayIndex == 0xED || bcptr->OverlayIndex == 0xEE)) ||
                ittype == unknown_tileset_a6cb7c + 0 ||
                ittype == unknown_tileset_a6cb7c + 1 ||
                ittype == unknown_tileset_a6cb7c + 2 ||
                ittype == unknown_tileset_a6cb7c + 3 ||
                ittype == unknown_tileset_a52e70 + 0 ||
                ittype == unknown_tileset_a52e70 + 1 ||
                ittype == unknown_tileset_a52e70 + 2 ||
                ittype == unknown_tileset_a52e70 + 3) {
                result = Unknown_005539B0(*cell);
            }
        }
    }

    for (int i = 0; i < unknown_d0.Count(); i++) {
        Map[unknown_d0[i]].unknown_47c930();
    }

    unknown_d0.Clear();
    return result;
}
