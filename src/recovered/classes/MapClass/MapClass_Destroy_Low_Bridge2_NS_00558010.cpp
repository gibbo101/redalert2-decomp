// void MapClass::Destroy_Low_Bridge2_NS(Cell const &cell) (0x00558010)
// Destroy_Low_Bridge_NS (0x005579C0) for the second low bridge overlays 0xCD..0xE8
// (0x00562980; wrecked 0xE8; damaged by 0x0055EDB0).
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/id_source.hpp"
#include "shared/rules.hpp"
#include "shared/map_techno.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref _unknown_geometry_g=00a6fc30
// @ref __real@8@4004c800000000000000=0079db68

void MapClass::Destroy_Low_Bridge2_NS(Cell const &cell)
{
    Cell cellnum = cell;
    Cell center = cellnum;
    int dir = 1;
    int left = 0;
    int right = 0;

    do {
        cellnum.Y--;
        left++;
    } while (Unknown_00562980(cellnum));

    cellnum = center;
    do {
        cellnum.Y++;
        right++;
    } while (Unknown_00562980(cellnum));

    if (right < left) {
        dir = -1;
    }

    cellnum = center;
    cellnum.Y -= (left - right) / 2;

    int count = 4;
    while (true) {
        if (count <= 0) {
            break;
        }
        if (Map[cellnum].OverlayIndex != 0xE8) {
            Cell piece = Cell(cellnum.X - 1, cellnum.Y);
            for (int index = 3; index > 0; index--) {
                CellClass *cellptr = &Map[piece];
                Cell id = cellptr->Fetch_CellID();
                CoordStruct coord;
                coord.X = id.X * 256 + 128;
                coord.Y = id.Y * 256 + 128;
                coord.Z = 0;
                coord.Z = cellptr->unknown_11b * unknown_geometry_g;
                coord.X += (Random_Pick(0, 0x7ffffffe) * 4.656612877414201e-10 - 0.5) * 50.0;
                coord.Y += (Random_Pick(0, 0x7ffffffe) * 4.656612877414201e-10 - 0.5) * 50.0;
                new AnimClass(Rules->BridgeExplosions[Random_Pick(0, Rules->BridgeExplosions.Count() - 1)], coord, Random_Pick(1, 5), 1, 0x600, 0);
                piece = Cell(piece.X + 1, piece.Y);
            }
        }

        for (int tries = 0; tries < 3; tries++) {
            if (Unknown_0055EDB0(cellnum)) {
                break;
            }
        }

        cellnum.Y += dir;
        count--;
        if (!Unknown_00562980(cellnum)) {
            break;
        }
    }

    Unknown_0054EBD0();
    unknown_tactical_83996c->unknown_d7c = true;
}
