// static void __fastcall SmudgeTypeClass::Init(int theater) (0x00687FB0)
// Loads the theater images of the theater-specific smudge types when the
// theater changes (or a reload is forced).
// Assumptions: unknown_1fc is "Theater="; fullname size 512.
#include "shared/smudge_type.hpp"
#include "shared/anim_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// @ref ?unknown_a40d13@@3_NA=00a40d13
// @ref ?unknown_loaded_theater_7d88dc@@3HA=007d88dc
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68
// @ref ?Retrieve@?$MixFileClass@VCCFileClass@@@@SIPBXPBD@Z=005956c0
// @ref __makepath=007831f0

void __fastcall SmudgeTypeClass::Init(int theater)
{
    if (unknown_a40d13 || theater != unknown_loaded_theater_7d88dc) {
        for (int index = 0; index < SmudgeTypes.Count(); index++) {
            SmudgeTypeClass *smudge = SmudgeTypes[index];
            if (smudge->unknown_1fc) {
                char fullname[512];
                _makepath(fullname, 0, 0, smudge->ID, Theaters[theater].Suffix);
                smudge->unknown_a4 = (void *)MixFileClass<CCFileClass>::Retrieve(fullname);
            }
        }
    }
}
