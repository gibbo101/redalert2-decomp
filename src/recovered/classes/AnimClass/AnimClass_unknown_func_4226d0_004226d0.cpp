// void AnimClass::unknown_func_4226d0() (0x004226D0)
// Starts the animation: slot 71 (2), the type's StartSound through the
// first audio controller (or just restarts it), restarts the second one,
// marks the ground when the type asks for it (+0x268 == 0), and for a
// TiberiumChainReaction type on a tiberium cell: grows the cell's overlay,
// one time in three spawns one of the tiberium's animations 10 leptons
// up, damages the area and clears the cell.
#include "shared/random.hpp"
#include "shared/anim.hpp"
#include "shared/crt_memory.hpp"
#include "shared/map_view.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_00713E60@@YIXHABUCoordStruct@@PAVUnknownAudioController@@@Z=00713e60
// @ref ?Unknown_00405D50@UnknownAudioController@@QAEXXZ=00405d50
// @ref ?Unknown_0047A220@UnknownAnimCell@@QAEHXZ=0047a220
// @ref ?Unknown_00472540@UnknownAnimCell@@QAEXH@Z=00472540
// @ref ?Unknown_00475DB0@UnknownAnimCell@@QAEXH@Z=00475db0
// @ref ?unknown_tiberiums_ac0b30@@3V?$DynamicVectorClass@PAUUnknownAnimTiberium@@@@A=00ac0b30
// @ref ?Unknown_0047E2C0@@YIXABUCoordStruct@@HHPAVWarheadTypeClass@@H@Z=0047e2c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0AnimClass@@QAE@PAVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110

void AnimClass::unknown_func_4226d0()
{
    unknown_slot71(2);
    if (!unknown_178 && Class->StartSound != -1) {
        Unknown_00713E60(Class->StartSound, Center_Coord(), &unknown_180);
    } else {
        unknown_180.Unknown_00405D50();
    }
    unknown_194.Unknown_00405D50();
    if (Class->unknown_268 == 0) {
        unknown_func_4228f0();
    }
    if (!unknown_178 && Class->TiberiumChainReaction) {
        UnknownAnimCell *cell = (UnknownAnimCell *)&Map[Center_Coord()];
        int index = cell->Unknown_0047A220();
        if (index != -1) {
            UnknownAnimTiberium *tiberium = unknown_tiberiums_ac0b30[index];
            cell->Unknown_00475DB0(cell->unknown_11e + 1);
            if (tiberium->unknown_c4.Count() > 0 && abs(unknown_id_source_a3d290->Random()()) % 3 == 0) {
                AnimClass *anim = new AnimClass(
                    tiberium->unknown_c4[unknown_id_source_a3d290->Random()(0, tiberium->unknown_c4.Count() - 1)],
                    Center_Coord() + CoordStruct(0, 0, 10), 0, 1, 0x600, 0);
                anim->unknown_bc = unknown_list_ab6ef8[tiberium->unknown_c0]->unknown_30c;
                anim->unknown_e4 = cell->unknown_10a;
            }
            {
                CoordStruct coord = Coord;
                Unknown_0047E2C0(coord, Rules->unknown_488, 0, Rules->unknown_c74, 0);
            }
            cell->Unknown_00472540(-1);
            Map.Unknown_0054FB20(cell->unknown_24);
            Map.Unknown_00566340(cell->unknown_24);
        }
    }
}
