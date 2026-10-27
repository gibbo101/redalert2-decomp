// void ObjectTypeClass::unknown_func_5d6730() (0x005D6730)
// Loads the type's voxel: <image>.VXL/.HVA into unknown_b0; for unit
// types without a turret the water (<image>W, the APC only) and
// no-spawn-alternate (<image>WO, NoSpawnAlt=) images into unknown_b8; else
// the turret voxels (<image>TUR, or one per turret weapon) and barrel
// voxels (<image>BARL, or one per turret weapon). On any failure the main
// and secondary voxels are freed; otherwise unknown_1bc becomes the largest
// section dimension (at least 8) and the cached buffers are released.
#include "shared/techno_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/crt_string.hpp"
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
// @ref ?Has_Turret_Weapons@TechnoTypeClass@@QBE_NXZ=006df680
// @ref ?unknown_func_5d6150@ObjectTypeClass@@QAE_NPBDH@Z=005d6150
// @ref ?unknown_func_5d63f0@ObjectTypeClass@@QAE_NPBDH@Z=005d63f0
// @ref ?unknown_func_5d66a0@ObjectTypeClass@@QAEXXZ=005d66a0
// @ref ??_C@_05NJAC@?$CFsTUR?$AA@=007e80e4
// @ref ??_C@_06OHAA@?$CFsBARL?$AA@=007e80f8
// @ref ??_C@_04DJPF@?4VXL?$AA@=007cfe60
// @ref ??_C@_04PCIF@?4HVA?$AA@=007cfe54
// @ref ??_C@_03CPGN@?$CFsW?$AA@=007e8108
// @ref ??_C@_03ENMJ@APC?$AA@=007e810c
// @ref ??_C@_04PLC@?$CFsWO?$AA@=007e8100

extern "C" void __cdecl _makepath(char *path, char const *drive, char const *dir, char const *fname, char const *ext);

void ObjectTypeClass::unknown_func_5d6730()
{
    char name[256];
    char fullname[260];
    bool failed = false;

    _makepath(fullname, 0, 0, unknown_1c8, ".VXL");
    CCFileClass voxel(fullname);
    if (voxel.Is_Available()) {
        delete unknown_b0.unknown_00;
        unknown_b0.unknown_00 = new UnknownPairFirst(&voxel);
        if (unknown_b0.unknown_00 == 0 || unknown_b0.unknown_00->unknown_00) {
            failed = true;
        }
        _makepath(fullname, 0, 0, unknown_1c8, ".HVA");
        CCFileClass motion(fullname);
        delete unknown_b0.unknown_04;
        unknown_b0.unknown_04 = new UnknownPairSecond(&motion);
        if (unknown_b0.unknown_04 != 0 && !unknown_b0.unknown_04->unknown_00) {
            unknown_b0.unknown_04->unknown_59ed30(unknown_b0.unknown_00->unknown_719860(0, 0)->unknown_0c);
        } else {
            failed = true;
        }
    } else {
        failed = true;
    }

    if (Kind_Of() == 0x28 && !((TechnoTypeClass *)this)->Turret) {
        if (strcmp(ID, "APC") == 0) {
            sprintf(name, "%sW", (char const *)unknown_1c8);
            _makepath(fullname, 0, 0, name, ".VXL");
            CCFileClass voxel(fullname);
            if (voxel.Is_Available()) {
                delete unknown_b8.unknown_00;
                unknown_b8.unknown_00 = new UnknownPairFirst(&voxel);
                if (unknown_b8.unknown_00 == 0 || unknown_b8.unknown_00->unknown_00) {
                    failed = true;
                }
                sprintf(name, "%sW", (char const *)unknown_1c8);
                _makepath(fullname, 0, 0, name, ".HVA");
                CCFileClass motion(fullname);
                delete unknown_b8.unknown_04;
                unknown_b8.unknown_04 = new UnknownPairSecond(&motion);
                if (unknown_b8.unknown_04 != 0 && !unknown_b8.unknown_04->unknown_00) {
                    unknown_b8.unknown_04->unknown_59ed30(unknown_b8.unknown_00->unknown_719860(0, 0)->unknown_0c);
                } else {
                    failed = true;
                }
            }
        }
        if (unknown_1b8) {
            sprintf(name, "%sWO", (char const *)unknown_1c8);
            _makepath(fullname, 0, 0, name, ".VXL");
            CCFileClass voxel(fullname);
            if (voxel.Is_Available()) {
                delete unknown_b8.unknown_00;
                unknown_b8.unknown_00 = new UnknownPairFirst(&voxel);
                if (unknown_b8.unknown_00 == 0 || unknown_b8.unknown_00->unknown_00) {
                    failed = true;
                }
                sprintf(name, "%sWO", (char const *)unknown_1c8);
                _makepath(fullname, 0, 0, name, ".HVA");
                CCFileClass motion(fullname);
                delete unknown_b8.unknown_04;
                unknown_b8.unknown_04 = new UnknownPairSecond(&motion);
                if (unknown_b8.unknown_04 != 0 && !unknown_b8.unknown_04->unknown_00) {
                    unknown_b8.unknown_04->unknown_59ed30(unknown_b8.unknown_00->unknown_719860(0, 0)->unknown_0c);
                } else {
                    failed = true;
                }
            }
        }
    } else if (Kind_Of() == 0x28 && ((TechnoTypeClass *)this)->Has_Turret_Weapons()) {
        int count = ((TechnoTypeClass *)this)->TurretCount;
        for (int index = 0; index < count; index++) {
            if (!unknown_func_5d6150(unknown_1c8, index)) {
                failed = true;
                break;
            }
        }
    } else {
        sprintf(name, "%sTUR", (char const *)unknown_1c8);
        _makepath(fullname, 0, 0, name, ".VXL");
        CCFileClass voxel(fullname);
        if (voxel.Is_Available()) {
            delete unknown_b8.unknown_00;
            unknown_b8.unknown_00 = new UnknownPairFirst(&voxel);
            if (unknown_b8.unknown_00 == 0 || unknown_b8.unknown_00->unknown_00) {
                failed = true;
            }
            sprintf(name, "%sTUR", (char const *)unknown_1c8);
            _makepath(fullname, 0, 0, name, ".HVA");
            CCFileClass motion(fullname);
            delete unknown_b8.unknown_04;
            unknown_b8.unknown_04 = new UnknownPairSecond(&motion);
            if (unknown_b8.unknown_04 != 0 && !unknown_b8.unknown_04->unknown_00) {
                unknown_b8.unknown_04->unknown_59ed30(unknown_b8.unknown_00->unknown_719860(0, 0)->unknown_0c);
            } else {
                failed = true;
            }
        }
    }

    if (Kind_Of() != 0x28 || ((TechnoTypeClass *)this)->Turret) {
        if (Kind_Of() == 0x28 && ((TechnoTypeClass *)this)->Has_Turret_Weapons()) {
            int count = ((TechnoTypeClass *)this)->TurretCount;
            for (int index = 0; index < count; index++) {
                if (!unknown_func_5d63f0(unknown_1c8, index)) {
                    failed = true;
                    break;
                }
            }
        } else {
            sprintf(name, "%sBARL", (char const *)unknown_1c8);
            _makepath(fullname, 0, 0, name, ".VXL");
            CCFileClass voxel(fullname);
            if (voxel.Is_Available()) {
                delete unknown_c0.unknown_00;
                unknown_c0.unknown_00 = new UnknownPairFirst(&voxel);
                if (unknown_c0.unknown_00 == 0 || unknown_c0.unknown_00->unknown_00) {
                    failed = true;
                }
                sprintf(name, "%sBARL", (char const *)unknown_1c8);
                _makepath(fullname, 0, 0, name, ".HVA");
                CCFileClass motion(fullname);
                delete unknown_c0.unknown_04;
                unknown_c0.unknown_04 = new UnknownPairSecond(&motion);
                if (unknown_c0.unknown_04 != 0 && !unknown_c0.unknown_04->unknown_00) {
                    unknown_c0.unknown_04->unknown_59ed30(unknown_c0.unknown_00->unknown_719860(0, 0)->unknown_0c);
                } else {
                    failed = true;
                }
            }
        }
    }

    if (failed) {
        if (unknown_b0.unknown_00 != 0) {
            delete unknown_b0.unknown_00;
            unknown_b0.unknown_00 = 0;
        }
        if (unknown_b0.unknown_04 != 0) {
            delete unknown_b0.unknown_04;
            unknown_b0.unknown_04 = 0;
        }
        if (Kind_Of() == 0x28 && ((TechnoTypeClass *)this)->Has_Turret_Weapons()) {
            unknown_func_5d66a0();
        } else {
            if (unknown_b8.unknown_00 != 0) {
                delete unknown_b8.unknown_00;
                unknown_b8.unknown_00 = 0;
            }
            if (unknown_b8.unknown_04 != 0) {
                delete unknown_b8.unknown_04;
                unknown_b8.unknown_04 = 0;
            }
        }
    } else {
        int size = unknown_b0.unknown_00->unknown_719860(0, 0)->unknown_a0;
        for (int index = 0; index < unknown_b0.unknown_00->unknown_04; index++) {
            if (size <= unknown_b0.unknown_00->unknown_719860(index, 0)->unknown_a0) {
                size = unknown_b0.unknown_00->unknown_719860(index, 0)->unknown_a0;
            }
            if (size <= unknown_b0.unknown_00->unknown_719860(index, 0)->unknown_a1) {
                size = unknown_b0.unknown_00->unknown_719860(index, 0)->unknown_a1;
            }
            if (size <= unknown_b0.unknown_00->unknown_719860(index, 0)->unknown_a2) {
                size = unknown_b0.unknown_00->unknown_719860(index, 0)->unknown_a2;
            }
        }
        unknown_1bc = size > 8 ? size : 8;
        unknown_214.~UnknownBuffer();
        unknown_228.~UnknownBuffer();
        unknown_23c.~UnknownBuffer();
        unknown_250.~UnknownBuffer();
    }
}
