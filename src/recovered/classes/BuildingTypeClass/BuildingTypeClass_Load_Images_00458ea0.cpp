// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14
// @ref ??_C@_05LADG@Image?$AA@=007cfddc
// @ref ??_C@_08ICDL@DoorAnim?$AA@=007cfe24
// @ref ??_C@_08JLE@BibShape?$AA@=007cfde4
// @ref ??_C@_0BA@GHPH@SpecialZOverlay?$AA@=007cfdf0
// @ref ??_C@_0BC@JAED@RoofDeployingAnim?$AA@=007cfe30
// @ref ??_C@_0BC@KGJH@UnderRoofDoorAnim?$AA@=007cfe00
// @ref ??_C@_0O@IEKH@UnderDoorAnim?$AA@=007cfe14
// @ref ??_C@_0O@OKCE@DeployingAnim?$AA@=007cfe44
// Resolve building buildup, deployment, door, overlay and base images.
#include "shared/building_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/anim_type.hpp"
#include "shared/rules.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
extern "C" void __cdecl _makepath(char *,char const *,char const *,char const *,char const *);
void const *__fastcall Unknown_Load_Shape_00495270(char const *name,bool &allocated);
// @ref __makepath=007831f0
// @ref __ftol=0077f110
// @ref ?ArtINI@@3VCCINIClass@@A=008397f0
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref ?Unknown_Load_Shape_00495270@@YIPBXPBDAA_N@Z=00495270
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14
void BuildingTypeClass::unknown_func_458ea0(int theater)
{
    char name[64];
    char extension[16];
    char fullname[260];
    if(!DemandLoadBuildup && strlen(BuildupFile)!=0) {
        _makepath(fullname,0,0,BuildupFile,".SHP");
        Theater_Naming_Convention(fullname,theater);
        void *shape=(void *)MixFileClass::Retrieve(fullname);
        if(shape==0) {
            Generic_Naming_Convention(fullname);
            CCFileClass file(fullname);
            shape=Load_Alloc_Data(file);
        }
        BuildupData=shape;
        if(shape) {
            int rate=1;
            int frames=((ShapeFileStruct *)shape)->FrameCount/2;
            if(Gate) frames=(int)((unsigned int)GateStages+1u);
            if(frames>0) rate=(int)(Rules->unknown_1178*900.0/frames);
            AnimFrames[0].unknown_00=0;
            AnimFrames[0].unknown_04=frames;
            AnimFrames[0].unknown_08=rate;
        }
    }
    ArtINI.Get_String(unknown_1c8,"DeployingAnim",unknown_string_83c55c,name,64);
    if(strlen(name)!=0) {
        _makepath(fullname,0,0,name,".SHP");
        Theater_Naming_Convention(fullname,theater);
        Free_unknown_11a0();
        unknown_11a0=(void *)Unknown_Load_Shape_00495270(fullname,unknown_11a4);
        if(unknown_11a0==0) {
            Generic_Naming_Convention(fullname);
            Free_unknown_11a0();
            unknown_11a0=(void *)Unknown_Load_Shape_00495270(fullname,unknown_11a4);
        }
    }
    ArtINI.Get_String(unknown_1c8,"RoofDeployingAnim",unknown_string_83c55c,name,64);
    if(strlen(name)!=0) {
        _makepath(fullname,0,0,name,".SHP");
        Theater_Naming_Convention(fullname,theater);
        Free_unknown_11b0();
        unknown_11b0=(void *)Unknown_Load_Shape_00495270(fullname,unknown_11b4);
        if(unknown_11b0==0) {
            Generic_Naming_Convention(fullname);
            Free_unknown_11b0();
            // The original roof fallback writes the deploying-image allocation flag.
            unknown_11b0=(void *)Unknown_Load_Shape_00495270(fullname,unknown_11a4);
        }
    }
    ArtINI.Get_String(unknown_1c8,"DoorAnim",unknown_string_83c55c,name,64);
    if(strlen(name)!=0) {
        _makepath(fullname,0,0,name,".SHP");
        Theater_Naming_Convention(fullname,theater);
        DoorAnimData_11c0=(void *)MixFileClass::Retrieve(fullname);
        if(DoorAnimData_11c0==0) {
            Generic_Naming_Convention(fullname);
            DoorAnimData_11c0=(void *)MixFileClass::Retrieve(fullname);
        }
    }
    ArtINI.Get_String(unknown_1c8,"UnderDoorAnim",unknown_string_83c55c,name,64);
    if(strlen(name)!=0) {
        _makepath(fullname,0,0,name,".SHP");
        Theater_Naming_Convention(fullname,theater);
        Free_unknown_11a8();
        unknown_11a8=(void *)Unknown_Load_Shape_00495270(fullname,unknown_11ac);
        if(unknown_11a8==0) {
            Generic_Naming_Convention(fullname);
            Free_unknown_11a8();
            unknown_11a8=(void *)MixFileClass::Retrieve(fullname);
        }
    }
    ArtINI.Get_String(unknown_1c8,"UnderRoofDoorAnim",unknown_string_83c55c,name,64);
    if(strlen(name)!=0) {
        _makepath(fullname,0,0,name,".SHP");
        Theater_Naming_Convention(fullname,theater);
        Free_unknown_11b8();
        unknown_11b8=(void *)Unknown_Load_Shape_00495270(fullname,unknown_11bc);
        if(unknown_11b8==0) {
            Generic_Naming_Convention(fullname);
            Free_unknown_11b8();
            unknown_11b8=(void *)MixFileClass::Retrieve(fullname);
        }
    }
    ArtINI.Get_String(unknown_1c8,"SpecialZOverlay",unknown_string_83c55c,name,64);
    if(strlen(name)!=0) {
        _makepath(fullname,0,0,name,".SHP");
        Theater_Naming_Convention(fullname,theater);
        SpecialZOverlayData_11c4=(void *)MixFileClass::Retrieve(fullname);
        if(SpecialZOverlayData_11c4==0) {
            Generic_Naming_Convention(fullname);
            SpecialZOverlayData_11c4=(void *)MixFileClass::Retrieve(fullname);
        }
    }
    ArtINI.Get_String(unknown_1c8,"BibShape",unknown_string_83c55c,name,64);
    if(strlen(name)!=0) {
        _makepath(fullname,0,0,name,".SHP");
        Theater_Naming_Convention(fullname,theater);
        Free_unknown_11cc();
        unknown_11cc=(void *)Unknown_Load_Shape_00495270(fullname,unknown_11d0);
        if(unknown_11cc==0) {
            Generic_Naming_Convention(fullname);
            Free_unknown_11cc();
            unknown_11cc=(void *)MixFileClass::Retrieve(fullname);
        }
    }
    ArtINI.Get_String(unknown_1c8,"Image",unknown_string_83c55c,name,64);
    if(unknown_1fc && theater!=-1) strcpy(extension,Theaters[theater].Suffix);
    else strcpy(extension,".SHP");
    if(strlen(name)!=0) _makepath(fullname,0,0,name,extension);
    else _makepath(fullname,0,0,unknown_1c8,extension);
    Theater_Naming_Convention(fullname,theater);
    strncpy(unknown_13eb,fullname,19);
    if(!DemandLoad) {
        unknown_a4=(void *)MixFileClass::Retrieve(fullname);
        if(unknown_a4==0) {
            Generic_Naming_Convention(fullname);
            strncpy(unknown_13eb,fullname,19);
            unknown_a4=(void *)MixFileClass::Retrieve(fullname);
        }
    }
    unknown_func_459640();
}
