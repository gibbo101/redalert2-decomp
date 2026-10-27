// AnimClass::~AnimClass() (0x00420A90)
// Detaches itself everywhere; while unknown_flag_a40958 is set it also lets
// go of the object it follows (clearing that object's flag when no other
// animation follows it) and leaves the map (slot 52, expanded here). Then
// it leaves the object list, releases its type's image and audio, and
// leaves Anims (or the 0x00A35E60 list for an ID of -2).
// Needs ObjectClass::unknown_slot52 declared bool (see slot 52).
#include "shared/anim.hpp"
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?unknown_anims_a35e60@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a35e60
// @ref ?Unknown_00406070@UnknownAudioController@@QAEXXZ=00406070
// @ref ?Unknown_00405C10@UnknownAudioController@@QAEXXZ=00405c10
// @ref ?unknown_func_426700@AnimTypeClass@@QAEXXZ=00426700
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ??1ObjectClass@@UAE@XZ=005d2530

AnimClass::~AnimClass()
{
    Unknown_006ECB90(this, true);
    if (unknown_flag_a40958) {
        if (unknown_b4 != 0) {
            ObjectClass *object = unknown_b4;
            int index;
            for (index = 0; index < Anims.Count(); index++) {
                AnimClass *anim = Anims[index];
                if (anim != this && anim->unknown_b4 == object) {
                    break;
                }
            }
            if (index == Anims.Count()) {
                object->unknown_slot89();
                object->unknown_78 = false;
            }
            unknown_b4 = 0;
        }
        unknown_slot52();
    }
    unknown_objects_ac0cb0.Delete(this);
    Class->unknown_func_426700();
    unknown_180.Unknown_00406070();
    unknown_194.Unknown_00406070();
    unknown_180.Unknown_00405C10();
    unknown_194.Unknown_00405C10();
    unknown_b4 = 0;
    Class = 0;
    if (Fetch_ID() == -2) {
        unknown_anims_a35e60.Delete(this);
    } else {
        Anims.Delete(this);
    }
}
