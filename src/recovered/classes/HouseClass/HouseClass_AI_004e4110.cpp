// House per-frame logic, original004E4110:3544 body bytes plus8 frozenNOP.
// Complete original1034-instruction CFG; inventory55-byte prefix/interior414C are not separate bodies.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/building_class.hpp"
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/aircraft.hpp"
#include "shared/infantry_type.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/tag.hpp"
#include "shared/team_type.hpp"
#include "shared/type_list_decl.hpp"
#include "shared/super.hpp"
#include "shared/rules.hpp"
#include "shared/options.hpp"
#include "shared/session_state.hpp"
#include "shared/special.hpp"
#include "shared/vox_class.hpp"
#include "shared/system_timer.hpp"

// Incoming interface at House+56CC: its saved IID007A2030 equals the IAIHouse IID.
// Slot4's stdcall/long* call is verified on this target; names are supported by the same-IID TLB reference.
struct __declspec(novtable) IAIHouse : public IUnknown {
    virtual long __stdcall Link_House(IHouse *house) = 0;
    virtual long __stdcall AI(long *frame_delay) = 0;
};
extern bool player_wins_a35db1;
extern bool player_loses_a40c78;
extern int low_power_notice_a40fc8;
extern bool unknown_sell_mode_83368d;
extern CoordStruct const unknown_coord_a40f48;
extern char const eva_insufficient_funds_007cf9e8[];
extern char const eva_low_power_007da284[];
extern char const txt_low_power_007da260[];
extern char const house_cpp_path_007da270[];
// @ref ?player_wins_a35db1@@3_NA=00a35db1
// @ref ?player_loses_a40c78@@3_NA=00a40c78
// @ref ?low_power_notice_a40fc8@@3HA=00a40fc8
// @ref ?unknown_sell_mode_83368d@@3_NA=0083368d
// @ref ?unknown_coord_a40f48@@3UCoordStruct@@B=00a40f48
// @ref ?eva_insufficient_funds_007cf9e8@@3QBDB=007cf9e8
// @ref ?eva_low_power_007da284@@3QBDB=007da284
// @ref ?txt_low_power_007da260@@3QBDB=007da260
// @ref ?house_cpp_path_007da270@@3QBDB=007da270
// @ref ?Expert_AI@HouseClass@@QAEHXZ=004e8990
// @ref ?unknown_69d390@SuperClass@@QAE_N_N@Z=0069d390
// @ref ??0?$DynamicVectorClass@PBVTeamTypeClass@@@@QAE@ABV0@@Z=004f6f30
// @ref ?Clear@?$VectorClass@PBVTeamTypeClass@@@@UAEXXZ=004f7cd0

// Checked Foot view: target Foot constructor sets Abstract+14 bit2.
// Primary Abstract/Object base adjustment is zero; this performs the actual type test.
static inline FootClass *House_Foot_View(AbstractClass *object)
{
    if (object && object->unknown_14_bit2) return reinterpret_cast<FootClass *>(object);
    return 0;
}

void HouseClass::AI()
{
    if (unknown_1ec.Value()==1) {
        unknown_1ec = CDTimerClass<FrameTimerClass>(0);
        unknown_5668 = true;
    }
    if (unknown_1f8.Value()==1) {
        unknown_1f8 = CDTimerClass<FrameTimerClass>(0);
        unknown_5669 = true;
    }
    if (unknown_5668 != false) {
        Recalc_Power_004f2cc0();
        unknown_5669 = true;
    }
    if ((unknown_5669 != false) && (unknown_int_a3d548 == 0)) {
        unknown_func_4f2e50();
        unknown_func_4f2fc0();
    }
    if (Frame%100==0) {
        for (int index=0;index<AngerNodes.Count();++index) {
            if (AngerNodes[index].Value>1) --AngerNodes[index].Value;
        }
    }
    if (unknown_56cc) {
        long frame_delay=0;
        static_cast<IAIHouse *>(unknown_56cc)->AI(&frame_delay);
    }
    if (!Is_Human_Control() && (unknown_13b || unknown_194>=Rules->IQProduction)) {
        unknown_13b=true;
        unknown_136=true;
        unknown_137=true;
    }
    if (unknown_13f && unknown_1e0.Value()==0 && (unknown_game_mode_a3d298!=0 || unknown_1c4<=0)) {
        CDTimerClass<SystemTimerClass> speech_wait(120);
        while (Speech_Is_Playing() && speech_wait.Value()!=0) Service_Game_IO_00481fb0();
        unknown_13f=false;
        if (Is_Player_Control()) player_wins_a35db1=true;
        else if ((unknown_game_mode_a3d298==3 || unknown_game_mode_a3d298==4) && unknown_session_a3d29c &&
                 unknown_session_a3d29c->unknown_slot1() && unknown_session_a3d29c->unknown_slot2()) {
            if (Is_Human_Control()) player_wins_a35db1=true;
            else player_loses_a40c78=true;
        } else player_loses_a40c78=true;
    }
    if (unknown_140 && unknown_1e0.Value()==0) {
        CDTimerClass<SystemTimerClass> speech_wait(120);
        while (Speech_Is_Playing() && speech_wait.Value()!=0) Service_Game_IO_00481fb0();
        if (unknown_game_mode_a3d298==0) {
            if (Is_Player_Control()) player_loses_a40c78=true;
            else player_wins_a35db1=true;
        } else if (Is_Player_Control()) player_loses_a40c78=true;
        else player_wins_a35db1=true;
    }
    if (unknown_13e && unknown_1e0.Value()==0) {
        unknown_13e=false;
        unknown_func_4e7df0();
    }
    Power=Power>0 ? Power : 0;
    Drain=Drain>0 ? Drain : 0;
    if (unknown_530c!=unknown_cell_a40f10 && Frame%15==0) {
        FootClass *foot=0;
        ObjectClass *occupant=Map[unknown_530c].unknown_471660(Point2D(0,0),false,0);
        if (occupant) {
            bool moving=false;
            foot=House_Foot_View(occupant);
            if (foot && foot->unknown_494) moving=true;
            if (!moving) occupant->unknown_slot87(unknown_coord_a40f48,true,true);
            if (foot && foot->unknown_494) moving=true;
            if (!moving) {
                int count=0;
                while (!occupant->unknown_76 && count++<5) {
                    int damage=occupant->Strength;
                    occupant->unknown_slot86(&damage,0,Rules->unknown_c74,0,true,0);
                }
            }
        }
    }
    if (unknown_5684.Value()==0 && !Is_Human_Control() && !Type->MultiplayPassive) {
        TypeList<TeamTypeClass const *> teams=Suggested_New_Team(false);
        if (teams.Count()>0) {
            for (int index=0;index<teams.Count();++index) {
                // The underlying recipes belong to mutable TeamTypes; the list's pointer qualification does not make those objects const.
                const_cast<TeamTypeClass *>(teams[index])->Create_One_Of(this);
            }
        }
        unknown_5684=CDTimerClass<FrameTimerClass>(Rules->TeamDelays[unknown_c8]);
    }
    if (unknown_player_a35db4==this) {
        if (!CurBuildings && unknown_sell_mode_83368d) Map.Unknown_0049C7C0(0);
        if (unknown_player_a35db4==this) {
            if (unknown_56c0.Value()==0 && Available_Money()<100 &&
                unknown_52c8+unknown_52c4+unknown_52c0+unknown_52bc>0) {
                Speech_Play_Name(eva_insufficient_funds_007cf9e8,-1,-1);
                Map.Unknown_006A1770();
                unknown_56c0=CDTimerClass<FrameTimerClass>(Options.Normalize_Delay((int)(Rules->SpeakDelay*900.0)));
            }
            if (unknown_56c0.Value()==0) {
                int capacity=Capacity;
                if (capacity-(int)Tiberium.Get_Total_Amount()<30 && capacity>50) {
                    unknown_56c0=CDTimerClass<FrameTimerClass>(Options.Normalize_Delay((int)(Rules->SpeakDelay*900.0)));
                }
            }
            if (Power_Fraction()<1.0) {
                if (unknown_5460.unknown_func_491d10(Rules->unknown_7c8[0]->ArrayIndex)>0 ||
                    unknown_5460.unknown_func_491d10(Rules->unknown_7c8[1]->ArrayIndex)>0) {
                    if (!low_power_notice_a40fc8) {
                        Speech_Play_Name(eva_low_power_007da284,-1,-1);
                        unknown_session_a3d298.Messages.Add_Message(0,0,StringTable::Load_String(txt_low_power_007da260,0,house_cpp_path_007da270,0x892),
                            ColorSchemeIndex,0x4046,(int)(Rules->MessageDelay*900.0),false);
                        low_power_notice_a40fc8=1;
                    }
                    unknown_56a8=CDTimerClass<FrameTimerClass>(Options.Normalize_Delay((int)(Rules->SpeakDelay*900.0)));
                }
            } else low_power_notice_a40fc8=0;
        }
    }
    ObjectClass *flag=static_cast<ObjectClass *>(unknown_5308);
    if (flag && flag->Kind_Of()==1) flag->unknown_slot71(2);
    if (unknown_5690.Value()==0 || unknown_18d) {
        unknown_5690=CDTimerClass<FrameTimerClass>(90);
        unknown_18d=false;
    }
    for (int super_index=0;super_index<Supers.Count();++super_index) {
        SuperClass *super=Supers[super_index];
        if (super->Is_Present() && super->unknown_69d390(this==unknown_player_a35db4) && this==unknown_player_a35db4) {
            int type_index=super->Type->unknown_slot16();
            Map.Unknown_0067C2D0(Unknown_006818D0(0x39,type_index,0));
        }
    }
    if (unknown_game_mode_a3d298!=0 && !unknown_13d && Frame>0 && !Type->MultiplayPassive) {
        bool defeated=false;
        if (unknown_session_a3d298.unknown_2a) {
            int units=unknown_5430.unknown_func_491d10(Rules->BaseUnit[0]->ArrayIndex)
                + unknown_5430.unknown_func_491d10(Rules->BaseUnit[1]->ArrayIndex);
            if (!CurBuildings && units<=0) defeated=true;
        } else if (!CurBuildings && !unknown_238 && !unknown_234) {
            int units=unknown_228;
            if (units && unknown_id_source_a3d290->Special().HarvesterImmune) {
                int immune=unknown_5430.unknown_func_491d10(Rules->unknown_9ec[0]->ArrayIndex)
                    + unknown_5430.unknown_func_491d10(Rules->unknown_9ec[1]->ArrayIndex);
                units-=immune;
            }
            if (units<=0) defeated=true;
        }
        if (defeated) {
            unknown_func_4e7df0();
            MPlayer_Defeated_004e77f0();
        }
    }
LAB_004e4b72:;
    if (Frame%8==0) {
        for (int tag_index=unknown_38.Count()-1;tag_index>=0;--tag_index) {
            unknown_38[tag_index]->Spring(8,0,unknown_cell_a40f10,false,0);
        }
    }
    if (unknown_5524.Value()==0 && !Is_Human_Control() && !Type->MultiplayPassive) {
        unknown_5524=CDTimerClass<FrameTimerClass>(Expert_AI());
    }
    if (!Is_Human_Control() && !Type->MultiplayPassive) {
        int mode=unknown_12c;
        if (mode==0 || unknown_game_mode_a3d298==0) {
            AI_Building();
            AI_Unit();
            AI_Infantry();
            AI_Aircraft();
        } else if (mode==1) {
            AI_Building();
            if (unknown_553c==-1 || !BuildingTypes[unknown_553c]->Who_Can_Build_Me(true,true,true,this)) {
                AI_Unit();
                AI_Infantry();
                AI_Aircraft();
            }
        } else if (mode==2) {
            AI_Unit();
            UnitTypeClass *harvester=Unknown_004EF6F0(Rules->unknown_9ec);
            if (unknown_5540!=harvester->ArrayIndex) {
                AI_Infantry();
                AI_Aircraft();
            }
            bool none=unknown_5540==-1 && unknown_5544==-1 && unknown_5548==-1;
            if (unknown_5540!=-1 && !UnitTypes[unknown_5540]->Who_Can_Build_Me(true,true,true,this)) none=true;
            if (unknown_5544!=-1 && !InfantryTypes[unknown_5544]->Who_Can_Build_Me(true,true,true,this)) none=true;
            if ((unknown_5548!=-1 && !AircraftTypes[unknown_5548]->Who_Can_Build_Me(true,true,true,this)) || none) {
                AI_Building();
            }
        }
    }
    if (unknown_player_a35db4 == this) {
        if (unknown_144 != false) {
            unknown_144 = false;
            {
            int building_count=Buildings.Count();
            for (int index=0;index<building_count;++index) {
                BuildingClass *building=Buildings[index];
                if (building && building->unknown_7d && building->Strength>0 && building->unknown_slot91()!=0x13 &&
                    building->MissionQueue!=0x13 && unknown_player_a35db4==building->House) {
                    building->unknown_slot283();
                }
            }
            Map.Unknown_0067E1C0();
            }
LAB_004e4e75:;
            unknown_func_4f4b20();
            Enable_Available_Super_Weapons_004f4db0();
        }
    }
    else if (unknown_144 != false) {
        unknown_144 = false;
        goto LAB_004e4e75;
    }
    if (unknown_18c && unknown_1c8.Value()==0) unknown_18c=false;
    if (this==unknown_player_a35db4 && unknown_192) {
        unknown_192=false;
        Map.Unknown_0049DE00(false,false);
    }
}
