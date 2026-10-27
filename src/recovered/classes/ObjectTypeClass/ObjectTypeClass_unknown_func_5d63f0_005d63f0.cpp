// bool ObjectTypeClass::unknown_func_5d63f0(char const *image, int index) (0x005D63F0)
// Loads turret voxel `index` (<image>TUR.VXL for 0, else <image>TUR<n>.VXL,
// with the matching .HVA) into unknown_140[index]; the motion is scaled by
// the voxel's first section multiplier. When either fails both are freed.
#include "shared/object_type.hpp"
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
// @ref ??_C@_06OHAA@?$CFsBARL?$AA@=007e80f8
// @ref ??_C@_08LICN@?$CFsBARL?$CFd?$AA@=007e80ec
// @ref ??_C@_04DJPF@?4VXL?$AA@=007cfe60
// @ref ??_C@_04PCIF@?4HVA?$AA@=007cfe54

extern "C" void __cdecl _makepath(char *path, char const *drive, char const *dir, char const *fname, char const *ext);

bool ObjectTypeClass::unknown_func_5d63f0(char const *image, int index)
{
    char name[256];
    char fullname[260];

    if (index == 0) {
        sprintf(name, "%sBARL", image);
    } else {
        sprintf(name, "%sBARL%d", image, index);
    }
    _makepath(fullname, 0, 0, name, ".VXL");
    CCFileClass voxel(fullname);
    if (!voxel.Is_Available()) {
        return true;
    }

    bool voxel_loaded = false;
    unknown_140[index].unknown_00 = new UnknownPairFirst(&voxel);
    if (unknown_140[index].unknown_00 != 0 && !unknown_140[index].unknown_00->unknown_00) {
        voxel_loaded = true;
    }

    if (index == 0) {
        sprintf(name, "%sBARL", image);
    } else {
        sprintf(name, "%sBARL%d", image, index);
    }
    _makepath(fullname, 0, 0, name, ".HVA");
    CCFileClass motion(fullname);
    bool motion_loaded = false;
    unknown_140[index].unknown_04 = new UnknownPairSecond(&motion);
    if (unknown_140[index].unknown_04 != 0 && !unknown_140[index].unknown_04->unknown_00) {
        motion_loaded = true;
    }

    if (voxel_loaded && motion_loaded) {
        unknown_140[index].unknown_04->unknown_59ed30(unknown_140[index].unknown_00->unknown_719860(0, 0)->unknown_0c);
        return true;
    }
    delete unknown_140[index].unknown_00;
    delete unknown_140[index].unknown_04;
    return false;
}
