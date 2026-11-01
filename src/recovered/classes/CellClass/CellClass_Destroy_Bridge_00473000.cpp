// void CellClass::Destroy_Bridge() (0x00473000): unless the map is being
// edited, destroys the cell's occupants, drops the bridge occupants, queues the
// cell for the bridge pass (Map +0xD0) and sets off bridge explosions and
// debris (TibSun Destroy_Bridge).
#include "shared/cell.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
#include "shared/rules.hpp"
#include "shared/anim.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref __real@8@4004c800000000000000=0079db68
// @ref __real@8@3ffef333333333333000=0079db70

void CellClass::Destroy_Bridge()
{
    if (!unknown_flag_a40d13) {
        ObjectClass *occupier = OccupierPtr;
        while (occupier != 0) {
            ObjectClass *next = occupier->unknown_30;
            occupier->unknown_slot86(&occupier->Strength, 0, Rules->unknown_c74, 0, true, true);
            occupier = next;
        }

        occupier = AltOccupierPtr;
        while (occupier != 0) {
            ObjectClass *next = occupier->unknown_30;
            occupier->unknown_slot57();
            occupier = next;
        }

        Map.unknown_d0.Add(MapCoords);

        if (Rules->BridgeExplosions.Count() > 0 && Random_Pick(0, 0x7ffffffe) * 4.656612877414201e-10 < 0.95) {
            CoordStruct coord;
            coord.X = MapCoords.X * 256 + 128;
            coord.Y = MapCoords.Y * 256 + 128;
            coord.Z = unknown_11b * unknown_geometry_g + unknown_geometry_j;
            coord.X += (Random_Pick(0, 0x7ffffffe) * 4.656612877414201e-10 - 0.5) * 50.0;
            coord.Y += (Random_Pick(0, 0x7ffffffe) * 4.656612877414201e-10 - 0.5) * 50.0;

            if (Random_Pick(0, 0x7ffffffe) * 4.656612877414201e-10 < 0.5) {
                new AnimClass(Rules->MetallicDebris[Random_Pick(0, Rules->MetallicDebris.Count() - 1)], coord, 0, 1, 0x600, 0);
            }

            new AnimClass(Rules->BridgeExplosions[Random_Pick(0, Rules->BridgeExplosions.Count() - 1)], coord, Random_Pick(1, 5), 1, 0x600, 0);
        }
    }
}
