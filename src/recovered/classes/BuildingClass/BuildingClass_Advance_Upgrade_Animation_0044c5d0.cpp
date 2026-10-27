// Advance the upgrade animation sequence and refresh animation names when strength changes.
// PRIVATE member/name and bool source spelling hypotheses; actual AL false/true and RET0.
#include "shared/building.hpp"
#include "shared/rules.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"
extern "C" char const unknown_turret_separator_007cf730[];
// @ref _unknown_turret_separator_007cf730=007cf730
// @ref ?Health_Ratio@ObjectClass@@=005d4540
// @ref ?unknown_44cfd0@BuildingClass@@=0044cfd0
// @ref ?unknown_44ca60@BuildingClass@@=0044ca60
inline void Start_Upgrade_Animation_0044c5d0(BuildingClass *building,int index,bool damaged)
{
    char const *name=damaged?building->Type->Anims[index].Damaged.Buffer:building->Type->Anims[index].Anim.Buffer;
    if(name && *name)building->unknown_44ca60(name,index,damaged,false,0);
}
bool BuildingClass::Advance_Upgrade_Animation_0044c5d0()
{
    int strength=Type->MaxStrength;
    if(Strength!=strength) {
        Strength=strength;
        if(unknown_5b6) {
            unknown_5b6=false;
            for(int index=0;index<18;++index) {
                if(unknown_454[index]) {
                    char const *name=Type->Anims[index].Anim.Buffer;
                    if(name && *name) unknown_44ca60(name,index,false,false,0);
                }
            }
        }
        if(Health_Ratio()>Rules->unknown_1368 && unknown_25c[3]) unknown_25c[3]->unknown_slot60();
        for(int index=3;index<=6;++index) {
            if(!unknown_454[index]) {
                char const *name=Type->Anims[index].Anim.Buffer;
                if(name && *name) unknown_44ca60(name,index,false,false,0);
            }
        }
        unknown_75=true;
    }
    if(Type==Rules->unknown_78c) {
    int frame=(int)((unsigned int)unknown_4d0+1u);
    if(frame>2)frame=0;
    if(frame!=unknown_4d0 && !Type->TurretAnimIsVoxel) {
        unknown_44cfd0(9);
        if(frame!=-1) {
            char name[64];
            strcpy(name,(char const *)Type->unknown_1c8);
            strcat(name,unknown_turret_separator_007cf730);
            unsigned int length=strlen(name);
            name[length]=(char)((unsigned int)frame+(unsigned int)'B');
            name[length+1]=0;
            unknown_44ca60(name,9,false,false,0);
            unknown_4d0=frame;
        }
    }
    unknown_5c6=(char)((unsigned char)unknown_5c6+1u);
    return true;
    }
    if((int)unknown_5c6==Type->Upgrades)return false;
    unknown_5c6=(char)((unsigned char)unknown_5c6+1u);
    Start_Upgrade_Animation_0044c5d0(this,(int)unknown_5c6-1,Health_Ratio()<=Rules->unknown_1368);
    return true;
}
