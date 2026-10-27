// void __fastcall Unknown_00420D30(ObjectClass *object) (0x00420D30)
// Ends the loops of the animations attached to an object.
#include "shared/anim.hpp"
// @ref ?Anims@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a40960

void __fastcall Unknown_00420D30(ObjectClass *object)
{
    if (object != 0) {
        for (int index = 0; index < Anims.Count(); index++) {
            AnimClass *anim = Anims[index];
            if (anim->unknown_b4 == object) {
                anim->Loops = 0;
            }
        }
    }
}
