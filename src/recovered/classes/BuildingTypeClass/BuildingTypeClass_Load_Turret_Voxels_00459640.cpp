// Load the building turret and barrel voxel/motion pairs.
#include "shared/building_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/crt_string.hpp"
extern "C" char *__cdecl _strupr(char *);
extern "C" char *__cdecl strstr(char const *,char const *);
extern "C" void __cdecl _makepath(char *,char const *,char const *,char const *,char const *);
// @ref ??_C@_03DJAI@TUR?$AA@=007cfe5c
// @ref __strupr=007961e4
// @ref _strstr=007836b0
// @ref __makepath=007831f0
// @ref ??_C@_04DJPF@?4VXL?$AA@=007cfe60
// @ref ??_C@_04PCIF@?4HVA?$AA@=007cfe54
void BuildingTypeClass::unknown_func_459640()
{
    if(TurretAnimIsVoxel || BarrelAnimIsVoxel) {
        char name[128];
        char fullname[256];
        strcpy(name,Anims[9].Anim.Buffer);
        _makepath(fullname,0,0,name,".VXL");
        if(strstr(_strupr(fullname+4),_strupr("TUR"))) {
            CCFileClass turret(fullname);
            if(turret.Is_Available()) {
                delete unknown_b8.unknown_00;
                unknown_b8.unknown_00=new UnknownPairFirst(&turret);
                _makepath(fullname,0,0,name,".HVA");
                CCFileClass motion(fullname);
                delete unknown_b8.unknown_04;
                unknown_b8.unknown_04=new UnknownPairSecond(&motion);
                if(unknown_b8.unknown_04 && !unknown_b8.unknown_04->unknown_00) {
                    unknown_b8.unknown_04->unknown_59ed30(unknown_b8.unknown_00->unknown_719860(0,0)->unknown_0c);
                }
            }
            char *suffix=strstr(_strupr(name+4),_strupr("TUR"));
            if(suffix) {
                *suffix++='B';
                *suffix++='A';
                *suffix++='R';
                *suffix++='L';
                *suffix=0;
            }
        } else if(BarrelAnimIsVoxel) {
            strncpy(name,VoxelBarrelFile,128);
        }
        _makepath(fullname,0,0,name,".VXL");
        CCFileClass barrel(fullname);
        if(barrel.Is_Available()) {
            delete unknown_c0.unknown_00;
            unknown_c0.unknown_00=new UnknownPairFirst(&barrel);
            _makepath(fullname,0,0,name,".HVA");
            CCFileClass motion(fullname);
            delete unknown_c0.unknown_04;
            unknown_c0.unknown_04=new UnknownPairSecond(&motion);
            if(unknown_c0.unknown_04 && !unknown_c0.unknown_04->unknown_00) {
                unknown_c0.unknown_04->unknown_59ed30(unknown_c0.unknown_00->unknown_719860(0,0)->unknown_0c);
            }
        }
    }
}
