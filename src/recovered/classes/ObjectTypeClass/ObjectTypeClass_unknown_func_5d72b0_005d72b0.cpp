// void ObjectTypeClass::unknown_func_5d72b0() (0x005D72B0)
// For a turreted unit type with an image: loads <image>TUR.VXL and
// <image>BARL.VXL into unknown_b8 / unknown_c0, each with its .HVA motion
// scaled by the voxel's first section multiplier.
#include "shared/techno_type.hpp"
#include "shared/cc_file_class.hpp"
// @ref _sprintf=007820f4
// @ref __makepath=007831f0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Is_Available@CCFileClass@@UAE_NH@Z=004691a0
// @ref ??0UnknownPairFirst@@QAE@PAVFileClass@@H@Z=00719080
// @ref ??1UnknownPairFirst@@QAE@XZ=007190c0
// @ref ?unknown_719860@UnknownPairFirst@@QAEPAUUnknownVoxelTailer@@HH@Z=00719860
// @ref ??0UnknownPairSecond@@QAE@PAVFileClass@@@Z=0059eb70
// @ref ??1UnknownPairSecond@@QAE@XZ=0059eba0
// @ref ?unknown_59ed30@UnknownPairSecond@@QAEXM@Z=0059ed30
// @ref ??_C@_05NJAC@?$CFsTUR?$AA@=007e80e4
// @ref ??_C@_06OHAA@?$CFsBARL?$AA@=007e80f8
// @ref ??_C@_04DJPF@?4VXL?$AA@=007cfe60
// @ref ??_C@_04PCIF@?4HVA?$AA@=007cfe54

extern "C" void __cdecl _makepath(char *path, char const *drive, char const *dir, char const *fname, char const *ext);

void ObjectTypeClass::unknown_func_5d72b0()
{
    if (Kind_Of() == 0x28 && unknown_slot39() != 0 && ((TechnoTypeClass *)this)->Turret) {
        char name[256];
        char fullname[260];

        sprintf(name, "%sTUR", (char const *)unknown_1c8);
        _makepath(fullname, 0, 0, name, ".VXL");
        CCFileClass turret(fullname);
        if (turret.Is_Available()) {
            delete unknown_b8.unknown_00;
            unknown_b8.unknown_00 = new UnknownPairFirst(&turret);
            if (unknown_b8.unknown_00 != 0 && !unknown_b8.unknown_00->unknown_00) {
                sprintf(name, "%sTUR", (char const *)unknown_1c8);
                _makepath(fullname, 0, 0, name, ".HVA");
                CCFileClass motion(fullname);
                delete unknown_b8.unknown_04;
                unknown_b8.unknown_04 = new UnknownPairSecond(&motion);
                unknown_b8.unknown_04->unknown_59ed30(unknown_b8.unknown_00->unknown_719860(0, 0)->unknown_0c);
            }
        }

        sprintf(name, "%sBARL", (char const *)unknown_1c8);
        _makepath(fullname, 0, 0, name, ".VXL");
        CCFileClass barrel(fullname);
        if (barrel.Is_Available()) {
            delete unknown_c0.unknown_00;
            unknown_c0.unknown_00 = new UnknownPairFirst(&barrel);
            if (unknown_c0.unknown_00 != 0 && !unknown_c0.unknown_00->unknown_00) {
                sprintf(name, "%sBARL", (char const *)unknown_1c8);
                _makepath(fullname, 0, 0, name, ".HVA");
                CCFileClass motion(fullname);
                delete unknown_c0.unknown_04;
                unknown_c0.unknown_04 = new UnknownPairSecond(&motion);
                unknown_c0.unknown_04->unknown_59ed30(unknown_c0.unknown_00->unknown_719860(0, 0)->unknown_0c);
            }
        }
    }
}
