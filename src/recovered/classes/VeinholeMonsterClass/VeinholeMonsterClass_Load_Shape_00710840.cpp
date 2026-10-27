// void VeinholeMonsterClass::Load_Shape(int theater) (0x00710840)
// Loads VEINHOLE.<theater suffix> into the shape pointer.
#include "shared/veinhole.hpp"
#include "shared/anim_type.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
// @ref ?Retrieve@?$MixFileClass@VCCFileClass@@@@SIPBXPBD@Z=005956c0
// @ref _sprintf=007820f4
// @ref ?unknown_veinhole_shape_ad079c@@3PBXB=00ad079c
// @ref ??_C@_0M@BKDE@VEINHOLE?4?$CFs?$AA@=007f96d8

void __fastcall VeinholeMonsterClass::Load_Shape(int theater)
{
    char name[32];
    sprintf(name, "VEINHOLE.%s", Theaters[theater].Suffix);
    unknown_veinhole_shape_ad079c = MixFileClass<CCFileClass>::Retrieve(name);
}
