// Complete Building animation update; source names remain hypotheses.
#include "shared/building.hpp"
#include "shared/cell.hpp"
#include "shared/rules.hpp"
#include "shared/frame_rate_control.hpp"
extern "C" int const unknown_turret_frame_table_007acab0[32];
extern "C" float const unknown_charge_scale_0079d148;
extern "C" float const unknown_charge_limit_0079d14c;
// @ref _unknown_turret_frame_table_007acab0=007acab0
// @ref _unknown_charge_scale_0079d148=0079d148
// @ref _unknown_charge_limit_0079d14c=0079d14c
// @ref ?unknown_69ae10@UnknownQuad@@=0069ae10
// @ref ?Adjust_005d9760@UnknownFrameRateControl@@=005d9760
// @ref ?unknown_frame_rate_a40b18@@=00a40b18
// @ref ?Health_Ratio@ObjectClass@@=005d4540
// @ref ?unknown_6d86f0@TechnoClass@@=006d86f0
// @ref ?unknown_44d0f0@BuildingClass@@=0044d0f0
// @ref ?unknown_44d2d0@BuildingClass@@=0044d2d0
// @ref ?unknown_44ca60@BuildingClass@@=0044ca60
// @ref ?unknown_44cfd0@BuildingClass@@=0044cfd0
// @ref ?Current@FacingClass@@=004b8be0
// @ref ?Rules@@=00839848
// @ref ?Frame@@=00a40d2c
inline void Start_Condition_Animation_0044BD40(BuildingClass *building,int index,bool damaged)
{
 char const *name=damaged?building->Type->Anims[index].Damaged.Buffer:building->Type->Anims[index].Anim.Buffer;
 if(name && *name)building->unknown_44ca60(name,index,damaged,false,0);
}
inline int Refinery_Storage_Stage_0044BD40(BuildingClass *building)
{
    int stored=(int)building->unknown_294.unknown_69ae10();
    if(stored!=0) {
        stored=(int)building->unknown_294.unknown_69ae10();
        stored=(int)((unsigned int)stored<<2)/building->Type->Storage;
    }
    return stored;
}
inline void Apply_Frame_And_Layer_0044BD40(BuildingClass *building,int value,int level)
{
    building->unknown_44d0f0(value,(unsigned short)level);
    building->unknown_44d2d0(building->unknown_5bd);
}
inline void Refresh_Building_Frame_0044BD40(BuildingClass *building)
{
    int value=building->unknown_slot115();
    CellClass *cell=static_cast<CellClass *>(building->unknown_slot105());
    int level=building->unknown_4521e0(cell->unknown_10a);
    building->unknown_5c4=(short)level;
    Apply_Frame_And_Layer_0044BD40(building,value,level);
}
// @ref ?Value@?$CDTimerClass@VFrameTimerClass@@@@QBEJXZ=00453eb0
inline bool Stage_Frame_Due_0044BD40(UnknownStage const &stage)
{
    return stage.Timer.Value()==0 && stage.unknown_10!=0;
}
inline bool Advance_Stage_Frame_0044BD40(UnknownStage &stage)
{
    if(Stage_Frame_Due_0044BD40(stage)) {
        stage.Value+=stage.unknown_14;
        stage.Timer=CDTimerClass<FrameTimerClass>(stage.unknown_10);
        return true;
    }
    return false;
}
inline int Silo_Storage_Frame_0044BD40(BuildingClass *building)
{
 int frame=0;
 if(building->Type->Storage>0) {
  int stored=(int)building->unknown_294.unknown_69ae10();
  stored=(int)((unsigned int)stored<<2);
  frame=(int)((double)stored/building->Type->Storage+0.5);
  if(frame<0)return 0;
  if(frame>3)return 3;
 }
 return frame;
}
void BuildingClass::Update_Animations_0044BD40()
{
    bool advanced=Advance_Stage_Frame_0044BD40(AnimationStage);
    bool finished=false;
    Refresh_Building_Frame_0044BD40(this);
    if(Type->UnitRepair && unknown_slot91()!=20 && (unknown_454[8] || unknown_454[11]) && !Type->Naval) {
        Start_Condition_Animation_0044BD40(this,12,!(Health_Ratio()>Rules->unknown_1368));
        unknown_44cfd0(8);
        unknown_44cfd0(11);
    }
    if(Type->SiloDamage) {
        int stage=Silo_Storage_Frame_0044BD40(this);
        AnimClass *animation=static_cast<AnimClass *>(unknown_454[10]);
        if(stage!=0) {
            if(!animation) {
                Start_Condition_Animation_0044BD40(this,10,!(Health_Ratio()>Rules->unknown_1368));
            }
            static_cast<AnimClass *>(unknown_454[10])->Stage=stage;
        }else if(animation)unknown_44cfd0(10);
    }
    if(Type->Refinery) {
        int stage=Refinery_Storage_Stage_0044BD40(this);
        if(unknown_5c0!=stage) {
            int previous=unknown_5c0;
            if(previous>=3)unknown_44cfd0(6);
            else if(previous>=2)unknown_44cfd0(5);
            else if(previous>=1)unknown_44cfd0(4);
            else if(previous>=0)unknown_44cfd0(3);
            unknown_5c0=Refinery_Storage_Stage_0044BD40(this);
            if(unknown_5c0>=3)Start_Condition_Animation_0044BD40(this,6,!(Health_Ratio()>Rules->unknown_1368));
            else if(unknown_5c0>=2)Start_Condition_Animation_0044BD40(this,5,!(Health_Ratio()>Rules->unknown_1368));
            else if(unknown_5c0>=1)Start_Condition_Animation_0044BD40(this,4,!(Health_Ratio()>Rules->unknown_1368));
            else if(unknown_5c0>=0)Start_Condition_Animation_0044BD40(this,3,!(Health_Ratio()>Rules->unknown_1368));
        }
    }
    if(Type->SuperWeapon!=-1 && unknown_slot91()!=18 && unknown_slot91()!=19 && !(Type->ChargedAnimTime>unknown_charge_limit_0079d14c)) {
        for(int index=0;index<House->Supers.Count();++index) {
            SuperClass *super=House->Supers[index];
            int super_type=super->Type->Type;
            if(super_type==Type->SuperWeapon) {
                if(!(Type->ChargedAnimTime<super->RechargeTimer.Value()*unknown_charge_scale_0079d148)) {
                    if(unknown_454[13]) {
                        unknown_44cfd0(13);
                        Start_Condition_Animation_0044BD40(this,14,!(Health_Ratio()>Rules->unknown_1368));
                    }
                }else if(unknown_454[15]) {
                    unknown_44cfd0(15);
                    Start_Condition_Animation_0044BD40(this,16,!(Health_Ratio()>Rules->unknown_1368));
                }
            }
        }
    }
    if(!unknown_slot232() || unknown_slot91()==18 || unknown_slot91()==19) {
        if(advanced) {
            BuildingTriple *state=&Type->AnimFrames[unknown_42c];
            if(AnimationStage.Value==state->unknown_04-1+state->unknown_00 ||
               (!unknown_1b0 && Type->UndeploysInto && unknown_slot91()==19 && AnimationStage.Value==23))unknown_5ad=true;
            if(AnimationStage.Value>=state->unknown_04+state->unknown_00)finished=true;
            unknown_75=true;
        }else if(unknown_42c==-1 || AnimationStage.unknown_10==0)unknown_5ad=true;
    }
    if(unknown_slot203())unknown_75=true;
    if(unknown_slot232() && unknown_slot232() && unknown_454[9]) {
        int index=Dir_To_32(unknown_2e0.Current());
        AnimClass *animation=static_cast<AnimClass *>(unknown_454[9]);
        if(animation) {
            int &frame=animation->Stage;
            int &step=animation->Step;
            frame=unknown_turret_frame_table_007acab0[index];
            step=0;
        }
    }
    if(finished) {
        BuildingTriple *state=&Type->AnimFrames[unknown_42c];
        if(unknown_42c==0 || unknown_42c==1) {
            AnimationStage.Set_Rate(unknown_frame_rate_a40b18.Adjust_005d9760(state->unknown_08));
        }else {
            AnimationStage.Set_Rate(state->unknown_08);
        }
        AnimationStage.Value=state->unknown_00;
        unknown_slot71(2);
    }
}
