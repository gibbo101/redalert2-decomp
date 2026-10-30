// void CellClass::unknown_4798f0() (0x004798F0): Westwood's Recalc_Light. The cell's brightness
// (+0x10A), tile brightness (+0x10C) and bridge brightness (+0x10E) from its ambient (+0x108), the
// scenario light (ion storm, dominator or normal ground/level values) and its intensity (+0x104),
// limited to 0..2000.
#include "shared/cell.hpp"
#include "shared/id_source.hpp"
#include "shared/lightning_storm.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Unknown_0051FC50@@YA_NXZ=0051fc50
// @ref ?Unknown_0051FC60@@YA_NXZ=0051fc60
void CellClass::unknown_4798f0()
{
    unknown_10a = unknown_108 + 1000 * unknown_id_source_a3d290->unknown_22ac / 100;
    unknown_10e = unknown_10a;

    if (Unknown_0051FC50()) {
        unknown_10a += unknown_11b * unknown_id_source_a3d290->IonLevel - unknown_id_source_a3d290->IonGround;
        unknown_10e += (unknown_11b + 4) * unknown_id_source_a3d290->IonLevel - unknown_id_source_a3d290->IonGround;
    } else if (Unknown_0051FC60()) {
        unknown_10a += unknown_11b * unknown_id_source_a3d290->unknown_22f4 - unknown_id_source_a3d290->unknown_22f0;
        unknown_10e += (unknown_11b + 4) * unknown_id_source_a3d290->unknown_22f4 - unknown_id_source_a3d290->unknown_22f0;
    } else {
        unknown_10a += unknown_11b * unknown_id_source_a3d290->AmbientLevel - unknown_id_source_a3d290->AmbientGround;
        unknown_10e += (unknown_11b + 4) * unknown_id_source_a3d290->AmbientLevel - unknown_id_source_a3d290->AmbientGround;
    }

    unknown_10c = (unknown_10a * unknown_104) >> 16;
    unknown_10e = (unknown_10e * unknown_104) >> 16;
    unknown_10a = (unknown_10a < 2000) ? unknown_10a : 2000;
    unknown_10c = (unknown_10c < 2000) ? unknown_10c : 2000;
    unknown_10e = (unknown_10e < 2000) ? unknown_10e : 2000;

    unknown_10a = (unknown_10a > 0) ? unknown_10a : 0;
    unknown_10c = (unknown_10c > 0) ? unknown_10c : 0;
    unknown_10e = (unknown_10e > 0) ? unknown_10e : 0;
}
