// Name the SHP turret animation from its image, separator and frame letter.
#include "shared/building.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"
extern "C" char const unknown_turret_separator_007cf730[];
// @ref _unknown_turret_separator_007cf730=007cf730
// @ref ?unknown_44cfd0@BuildingClass@@=0044cfd0
// @ref ?unknown_44ca60@BuildingClass@@=0044ca60
void BuildingClass::Set_Turret_Animation_Frame_0043bd40(int frame)
{
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
}
