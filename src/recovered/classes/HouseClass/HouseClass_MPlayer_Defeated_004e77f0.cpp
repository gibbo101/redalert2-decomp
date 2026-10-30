// @ref ??_C@_0BB@GHMK@D?3?2Ra2?2House?4CPP?$AA@=007da270
// @ref ??_C@_0CC@DKFO@MPlayer_Defeated?$CI?$CJ?5?9?5Flag_To_Win@=007da530
// @ref ??_C@_0CD@CFDF@MPlayer_Defeated?$CI?$CJ?5?9?5Flag_To_Los@=007da554
// @ref ??_C@_0DA@BHLN@MPlayer_Defeated?$CI?$CJ?5?9?5Allies?5lost@=007da578
// @ref ??_C@_0CO@JBDB@MPlayer_Defeated?$CI?$CJ?5?9?5Allies?5win?0@=007da5a8
// @ref ??_C@_0DH@DDGH@MPlayer_Defeated?$CI?$CJ?5?9?5All?5remaini@=007da5d8
// @ref ??_C@_0CK@CIMI@Saw?5game?5completion?5due?5to?5playe@=007da610
// @ref ??_C@_0CO@JEKI@MPlayer_Defeated?$CI?$CJ?5?9?5Alive?5?$DN?5?$CFd?0@=007da63c
// @ref ??_C@_0DE@OPJP@MPlayer_Defeated?$CI?$CJ?5?9?5Opponent?5?$CFs@=007da66c
// @ref ??_C@_0BD@LNAN@EVA_PlayerDefeated?$AA@=007da6a0
// @ref ??_C@_0EA@HPJD@MPlayer_Defeated?$CI?$CJ?5?9?5Player?5?$CFs?5h@=007da6b4
// @ref ??_C@_0BA@DFJP@EVA_YouHaveLost?$AA@=007da6f4
// @ref ??_C@_0BE@PMCG@TXT_PLAYER_DEFEATED?$AA@=007da704
// House defeat handling, original004E77F0; complete1535body+1NOP.
#include "shared/unit.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/id_source.hpp"
#include "shared/rules.hpp"
#include "shared/session_state.hpp"
#include "shared/vox_class.hpp"
#include "shared/lobby.hpp"
#include "shared/planning.hpp"
#include "shared/string_table.hpp"
#include "shared/dsurface.hpp"
#include "shared/crt_memory.hpp"
#include "shared/debug_printf.hpp"
extern bool unknown_flag_8373f4;
extern bool unknown_flag_7d9fe8;
extern bool unknown_flag_a3d8d1;
// @ref ?unknown_flag_8373f4@@3_NA=008373f4
// @ref ?unknown_flag_7d9fe8@@3_NA=007d9fe8
// @ref ?unknown_flag_a3d8d1@@3_NA=00a3d8d1
// @ref ?Unknown_0042EBE0@Unknown84E8D0@@QAEXH@Z=0042ebe0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
void HouseClass::MPlayer_Defeated_004e77f0()
{
    wchar_t text[80];
    int i,j;
    HouseClass *house,*other;
    int alive,humans;
    bool all_allies;
    unknown_13d=true;
    if (unknown_194==Rules->MaxIQ && !Is_Human_Control() && Rules->Paranoid && unknown_game_mode_a3d298!=0) unknown_func_4ec5e0();
    if (unknown_id_source_a3d290->unknown_000 & 0x10) {
        if (unknown_5308) unknown_func_4e7580(unknown_5308,true);
        else if (unknown_530c!=unknown_cell_a40f10) unknown_func_4e7580((AbstractClass *)&Map[unknown_530c],true);
    }
    if (unknown_game_mode_a3d298!=0 && (unknown_id_source_a3d290->unknown_000 & 0x800)) {
        for (i=0;i<Units.Count();++i) {
            UnitClass *unit=Units[i];
            if (unit->House==this && unit->unknown_7d) unit->unknown_slot60();
        }
    }
    if (unknown_player_a35db4==this) {
        unknown_object_84e8d0.Unknown_0042EBE0(unknown_player_a35db4->ArrayIndex);
        if (unknown_flag_8373f4) {
            Map.Unknown_006A1F10();
            unknown_flag_7d9fe8=true;
        } else unknown_flag_7d9fe8=false;
        Planning_End();
        Map.Unknown_0049CAC0(0);
        unknown_int_a3d548=1;
        Map.Unknown_0055A1F0();
        Map.Unknown_00633140(true);
        unknown_surface_839954->Fill(0);
        Map.Flag_To_Redraw(2);
        memset(unknown_flags_a3f118,1,sizeof(unknown_flags_a3f118));
        if (Current_Dialog_Id_00735b20()==0x73) Map.Unknown_00634970((int)Unknown_00735B10());
        if (unknown_house_a72d28!=unknown_player_a35db4) {
            swprintf(text,StringTable::Load_String("TXT_PLAYER_DEFEATED",0,"D:\\Ra2\\House.CPP",0x125f),UIName);
            unknown_session_a3d298.Messages.Add_Message(0,0,text,unknown_session_a3d298.Unknown_006715D0(unknown_a3d3b4),0x4046,(int)(Rules->MessageDelay*900),false);
            Speech_Play_Name("EVA_YouHaveLost",-1,-1);
        }
        Map.Flag_To_Redraw(0);
        Debug_Printf("MPlayer_Defeated() - Player %s has been defeated (OBIWAN MODE)\n",(char const *)IniName);
    } else {
        if (!Type->MultiplayPassive) {
            if (this!=unknown_house_a72d28) {
                swprintf(text,StringTable::Load_String("TXT_PLAYER_DEFEATED",0,"D:\\Ra2\\House.CPP",0x126f),UIName);
                unknown_session_a3d298.Messages.Add_Message(0,0,text,ColorSchemeIndex,0x4046,(int)(Rules->MessageDelay*900),false);
                Speech_Play_Name("EVA_PlayerDefeated",-1,-1);
            }
            Map.Flag_To_Redraw(0);
        }
        Debug_Printf("MPlayer_Defeated() - Opponent %s has been defeated\n",(char const *)IniName);
    }
    alive=0;
    humans=0;
    for (i=0;i<Houses.Count();++i) {
        house=Houses[i];
        if (house && !house->unknown_13d && !house->Type->MultiplayPassive) {
            if (house->Is_Human_Control()) ++humans;
            ++alive;
        }
    }
    Debug_Printf("MPlayer_Defeated() - Alive = %d, Humans = %d\n",alive,humans);
    all_allies=true;
    for (i=0;i<Houses.Count();++i) {
        house=Houses[i];
        if (!house || house->unknown_13d || (unknown_game_mode_a3d298!=5 && house->Type->MultiplayPassive)) continue;
        for (j=0;j<Houses.Count();++j) {
            other=Houses[j];
            if (other && !other->unknown_13d && (unknown_game_mode_a3d298==5 || !other->Type->MultiplayPassive) && (!house->Is_Ally(other) || !other->Is_Ally(house))) {
                all_allies=false;
                break;
            }
        }
        if (!all_allies) break;
    }
    if (all_allies) {
        unknown_flag_a3d8d1=true;
        Debug_Printf("Saw game completion due to player defeat\n");
        alive=1;
        Debug_Printf("MPlayer_Defeated() - All remaining players are allied\n");
    }
    if (alive==1 || humans==0) {
        if (unknown_flag_7d9fe8) Map.Unknown_006A1EC0();
        if (unknown_player_a35db4->unknown_13d) {
            UnknownSessionA3D29C *mode=unknown_session_a3d29c;
            bool present=mode!=0;
            bool cooperative=(unknown_game_mode_a3d298==3 || unknown_game_mode_a3d298==4) && present && mode->unknown_slot1() && mode->unknown_slot2();
            if (alive==1 && cooperative) {
                bool human_alive=false;
                for (i=0;i<Houses.Count();++i) {
                    house=Houses[i];
                    if (house && !house->unknown_13d && house->Is_Human_Control()) human_alive=true;
                }
                if (human_alive) {
                    Debug_Printf("MPlayer_Defeated() - Allies win, Flag_To_Win\n");
                    unknown_player_a35db4->Flag_To_Win(false);
                } else {
                    Debug_Printf("MPlayer_Defeated() - Allies lost, Flag_To_Lose\n");
                    unknown_player_a35db4->Flag_To_Lose(false);
                }
            } else {
                Debug_Printf("MPlayer_Defeated() - Flag_To_Lose\n");
                unknown_player_a35db4->Flag_To_Lose(false);
            }
        } else {
            Debug_Printf("MPlayer_Defeated() - Flag_To_Win\n");
            unknown_player_a35db4->Flag_To_Win(false);
        }
    }
}
