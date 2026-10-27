// void Unknown_00423C70() (0x00423C70)
// Gives every IsAnimatedTiberium animation the 0x00AB6EF8 entry value of
// the tiberium in its cell (as unknown_bc).
#include "shared/anim.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_0047A220@UnknownAnimCell@@QAEHXZ=0047a220
// @ref ?unknown_tiberiums_ac0b30@@3V?$DynamicVectorClass@PAUUnknownAnimTiberium@@@@A=00ac0b30

void Unknown_00423C70()
{
    for (int index = 0; index < Anims.Count(); index++) {
        AnimClass *anim = Anims[index];
        if (anim->Class->IsAnimatedTiberium) {
            CoordStruct coord = anim->Coord;
            int tiberium = ((UnknownAnimCell *)&Map[coord])->Unknown_0047A220();
            if (tiberium != -1) {
                UnknownAnimTiberium *type = unknown_tiberiums_ac0b30[tiberium];
                if (type != 0) {
                    anim->unknown_bc = unknown_list_ab6ef8[type->unknown_c0]->unknown_30c;
                }
            }
        }
    }
}
