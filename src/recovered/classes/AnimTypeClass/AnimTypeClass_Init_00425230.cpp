// static void __fastcall AnimTypeClass::Init(int theater) (0x00425230)
// Loads every non-demand-loaded animation image for a theater. When the
// theater is unchanged (and no reload is forced) only the missing
// "NewTheater" images are loaded.
// Assumptions: unknown_1fc is "Theater=" and unknown_207 "NewTheater=";
// fullname size 512 (_MAX_FNAME + _MAX_EXT) from the frame size.
#include "shared/anim_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// @ref ?unknown_a40d13@@3_NA=00a40d13
// @ref ?unknown_loaded_theater_7d88dc@@3HA=007d88dc
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68
// @ref ?Retrieve@?$MixFileClass@VCCFileClass@@@@SIPBXPBD@Z=005956c0
// @ref __makepath=007831f0
// @ref ??3@YAXPAX@Z=00781d3b

void __fastcall AnimTypeClass::Init(int theater)
{
    if (!unknown_a40d13 && theater == unknown_loaded_theater_7d88dc) {
        for (int index = 0; index < AnimTypes.Count(); index++) {
            AnimTypeClass *anim = AnimTypes[index];
            if (anim->unknown_207 && anim->unknown_a4 == 0) {
                anim->unknown_slot40(theater);
            }
        }
        return;
    }

    for (int index = 0; index < AnimTypes.Count(); index++) {
        AnimTypeClass *anim = AnimTypes[index];
        if (!anim->DemandLoad) {
            if (anim->unknown_1fc) {
                if (anim->unknown_a4 != 0 && anim->unknown_a8) {
                    operator delete(anim->unknown_a4);
                    anim->unknown_a8 = false;
                }
                anim->unknown_a4 = 0;
                char fullname[512];
                _makepath(fullname, 0, 0, anim->ID, Theaters[theater].Suffix);
                anim->unknown_a4 = (void *)MixFileClass<CCFileClass>::Retrieve(fullname);
                if (anim->unknown_a4 == 0) {
                    _makepath(fullname, 0, 0, anim->ID, ".SHP");
                    anim->unknown_a4 = (void *)MixFileClass<CCFileClass>::Retrieve(fullname);
                }
            } else if (anim->unknown_207) {
                anim->unknown_slot40(theater);
            }
        } else if (anim->unknown_1fc || anim->unknown_207) {
            if (anim->unknown_a4 != 0 && anim->unknown_a8) {
                operator delete(anim->unknown_a4);
                anim->unknown_a8 = false;
            }
            anim->unknown_a4 = 0;
        }
    }
}
