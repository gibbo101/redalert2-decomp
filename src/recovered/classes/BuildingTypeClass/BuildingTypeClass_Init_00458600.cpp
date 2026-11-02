// static void __fastcall BuildingTypeClass::Init(int theater) (0x00458600)
// Loads the building images for a theater: the shared shapes
// (0x00458510, POWEROFF.SHP, WRENCH.SHP), then per type with a theater
// image (unknown_1fc) the image and its buildup unless demand loaded
// (otherwise any loaded copy is freed); a buildup sets its animation
// triple (frame 0, the buildup's frame count, 75 / frames per frame or 1).
// "NewTheater" types (unknown_207) free demand-loaded images and load
// through 0x00458EA0. Finally the cloak surface is rebuilt for the largest
// CloakRadiusInCells.
#include "shared/building_type.hpp"
#include "shared/surface.hpp"
#include "shared/anim_type.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
// @ref ?unknown_func_458510@BuildingTypeClass@@SAXXZ=00458510
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref ?unknown_poweroff_shape_8502a4@@3PBXB=008502a4
// @ref ?unknown_wrench_shape_8502a8@@3PBXB=008502a8
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68
// @ref __makepath=007831f0
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_func_458ea0@BuildingTypeClass@@QAEXH@Z=00458ea0
// @ref ?unknown_cloak_surface_8502a0@@3PAVBSurface@@A=008502a0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_C@_0N@PPEK@POWEROFF?4SHP?$AA@=007cfdcc
// @ref ??_C@_0L@EHK@WRENCH?4SHP?$AA@=007cfdc0

extern "C" void __cdecl _makepath(char *path, char const *drive, char const *dir, char const *fname, char const *ext);

// A shape file header as read here (its frame count at +0x06).
struct UnknownBuildupShape {
    short unknown_0;
    short unknown_2;
    short unknown_4;
    short Frames;                       // +0x06
};

void __fastcall BuildingTypeClass::Init(int theater)
{
    unknown_func_458510();
    unknown_poweroff_shape_8502a4 = MixFileClass::Retrieve("POWEROFF.SHP");
    unknown_wrench_shape_8502a8 = MixFileClass::Retrieve("WRENCH.SHP");
    int radius = 0;
    for (int index = 0; index < BuildingTypes.Count(); index++) {
        BuildingTypeClass *type = BuildingTypes[index];
        if (radius <= type->CloakRadiusInCells) {
            radius = type->CloakRadiusInCells;
        }
        if (type->unknown_1fc) {
            char fullname[512];
            if (!type->DemandLoad) {
                _makepath(fullname, 0, 0, type->unknown_1c8, Theaters[theater].Suffix);
                type->unknown_a4 = (void *)MixFileClass::Retrieve(fullname);
            } else if (type->unknown_a4 != 0) {
                operator delete(type->unknown_a4);
                type->unknown_a4 = 0;
                type->unknown_a8 = false;
            }
            if (!type->DemandLoadBuildup) {
                _makepath(fullname, 0, 0, type->BuildupFile, Theaters[theater].Suffix);
                type->BuildupData = (void *)MixFileClass::Retrieve(fullname);
            } else if (type->BuildupData != 0) {
                operator delete(type->BuildupData);
                type->BuildupData = 0;
                type->BuildupDataAllocated = false;
            }
            if (type->BuildupData != 0) {
                int rate = 1;
                int frames = ((UnknownBuildupShape *)type->BuildupData)->Frames;
                if (frames != 0) {
                    rate = 75 / frames;
                }
                type->AnimFrames[0].unknown_00 = 0;
                type->AnimFrames[0].unknown_04 = frames;
                type->AnimFrames[0].unknown_08 = rate;
            }
        } else if (type->unknown_207) {
            if (type->DemandLoad && type->unknown_a4 != 0) {
                operator delete(type->unknown_a4);
                type->unknown_a4 = 0;
                type->unknown_a8 = false;
            }
            if (type->DemandLoadBuildup && type->BuildupData != 0) {
                operator delete(type->BuildupData);
                type->BuildupData = 0;
                type->BuildupDataAllocated = false;
            }
            type->unknown_func_458ea0(theater);
        }
    }
    if (radius != 0) {
        delete unknown_cloak_surface_8502a0;
        unknown_cloak_surface_8502a0 = new BSurface(radius + 16, radius + 16, 1);
    }
}
