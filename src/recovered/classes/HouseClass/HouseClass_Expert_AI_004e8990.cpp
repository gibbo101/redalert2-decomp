// Expert-system house decisions, original 0x004E8990.
#include "shared/house.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/coord_distance.hpp"

int HouseClass::Expert_AI()
{
    if(unknown_5530==0) {
        if(unknown_54f0==-1 && unknown_game_mode_a3d298!=0 && !Type->MultiplayPassive) {
            CoordStruct center=BaseCenter;
            if(center!=unknown_geometry_l) {
                int closest=0x7fffffff;
                HouseClass *enemy=0;
                for(int index=0;index<Houses.Count();++index) {
                    HouseClass *house=Houses[index];
                    if(house!=this && !house->Type->MultiplayPassive && !house->unknown_13d) {
                        CoordStruct offset=house->BaseCenter;
                        offset-=center;
                        int distance=(int)unknown_sqrt_4ba410((double)offset.X*offset.X+(double)offset.Z*offset.Z+(double)offset.Y*offset.Y);
                        if(distance<closest) {enemy=house;closest=distance;}
                    }
                }
                if(enemy) unknown_func_4eeba0(1,enemy);
            }
        }
    }
    if(unknown_54f0!=-1) {
        HouseClass *enemy=Houses[unknown_54f0];
        if(enemy->unknown_13d) {
            for(int index=0;index<AngerNodes.Count();++index) {
                if(AngerNodes[index].House==enemy) {
                    unknown_func_4eeba0(-AngerNodes[index].Value,enemy);
                    break;
                }
            }
            unknown_54f0=-1;
        }
    }
    if(unknown_game_mode_a3d298!=0 || unknown_194>=Rules->IQSuperWeapons) AI_Supers_004f3910();
    if(unknown_198==4) {
        Fire_Sale();
        All_To_Hunt();
    } else {
        if(unknown_198==0 && Available_Money()<25) unknown_198=1;
        if(unknown_198==1 && Available_Money()>=25) unknown_198=0;
        if(unknown_198==3 && unknown_5408+900<Frame) unknown_198=0;
        if(unknown_198!=3 && unknown_5408+900>Frame) unknown_198=3;
    }
    if(unknown_game_mode_a3d298!=0) {
        int urgency[2];
        int strategy;
        for(strategy=0;strategy<2;++strategy) {
            urgency[strategy]=0;
            switch(strategy) {
            case 0:
                urgency[0]=unknown_func_4e8d20();
                break;
            case 1: urgency[1]=Check_Raise_Money_004e8d80();break;
            default: urgency[strategy]=0;break;
            }
        }
        for(int level=4;level>=1;--level) {
            for(strategy=0;strategy<2;++strategy) {
                if(urgency[strategy]==level) {
                    switch(strategy) {
                    case 0: if(CurBuildings>0 && level==4) {Fire_Sale();All_To_Hunt();}break;
                    case 1: AI_Raise_Money_004e90f0(level);break;
                    }
                }
            }
        }
    }
    return 105+Random_Pick(1,7);
}
