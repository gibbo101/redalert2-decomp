// void MapClass::Destroy_Low_Bridge_EW(Cell const &cell) (0x005576A0)
// Blows up the east-west low bridge run through a cell (first low bridge overlays
// 0x4A..0x65, Is_Low_Bridge 0x00562930): the run is measured both ways along X, the walk
// starts at its middle and steps toward the longer end (dir) for up to 4 cells while the
// bridge continues. At each cell not already wrecked (overlay 0x64) three random
// Rules->BridgeExplosions go off at random spots of the cells Y-1..Y+1 (at the bridge
// height), then the cell's low bridge is damaged (0x0055DCA0) up to three times until it
// gives way. Then 0x0054EBD0 and the tactical view's +0xD7C redraw flag.
// The coordinate is built member-wise with a Z = 0 store before the height (the
// original keeps that dead store as an immediate; Cell_Coord's inline would hoist the 0
// into a register).
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

void MapClass::Destroy_Low_Bridge_EW(Cell const &cell)
{
    Cell cellnum = cell;
    Cell center = cellnum;
    int dir = 1;
    int left = 0;
    int right = 0;

    do {
        cellnum.X--;
        left++;
    } while (Unknown_00562930(cellnum));

    cellnum = center;
    do {
        cellnum.X++;
        right++;
    } while (Unknown_00562930(cellnum));

    if (right < left) {
        dir = -1;
    }

    cellnum = center;
    cellnum.X -= (left - right) / 2;

    int count = 4;
    while (true) {
        if (count <= 0) {
            break;
        }
        if (Map[cellnum].OverlayIndex != 0x64) {
            Cell piece = Cell(cellnum.X, cellnum.Y - 1);
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
                piece = Cell(piece.X, piece.Y + 1);
            }
        }

        for (int tries = 0; tries < 3; tries++) {
            if (Unknown_0055DCA0(cellnum)) {
                break;
            }
        }

        cellnum.X += dir;
        count--;
        if (!Unknown_00562930(cellnum)) {
            break;
        }
    }

    Unknown_0054EBD0();
    unknown_tactical_83996c->unknown_d7c = true;
}
