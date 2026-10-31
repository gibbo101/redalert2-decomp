// Recruit up to six infantry and vehicles to respond to an attack on this base.
#include "shared/techno.hpp"
#include "shared/infantry.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
#include "shared/warhead_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_func_6ba8e0@TeamClass@@SIXHPAVHouseClass@@@Z=006ba8e0
// @ref ?unknown_4c82a0@FootClass@@QAEHPAVAbstractClass@@@Z=004c82a0
// @ref ?Unknown_0054F7C0@MapClass@@QAE_NABVCell@@0H_N11@Z=0054f7c0
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@4008e100000000000000=0079b608
void TechnoClass::unknown_6d3400(TechnoClass *attacker)
{
    FootClass *responders[6];
    int scores[6];
    memset(responders,0,sizeof(responders));
    memset(scores,0,sizeof(scores));
    int count=0;
    int minimum=0;
    int required=attacker->unknown_slot168()*Rules->ComputerBaseDefenseResponse;
    int recruited=0;
    if (!attacker || House->Is_Ally(attacker) || House->unknown_func_4f52f0() || attacker->unknown_76) return;
    if (!unknown_game_mode_a3d298 && unknown_slot163()) return;
    if (attacker->Kind_Of()!=15 && attacker->Kind_Of()!=1) return;
    if (unknown_slot32()->unknown_202) return;
    bool is_foot;
    if (attacker) is_foot=attacker->unknown_14_bit2;
    if (attacker && is_foot && static_cast<FootClass *>(attacker)->unknown_540!=0) return;
    TeamClass::unknown_func_6ba8e0(Rules->SuspendPriority,House);
    for (int index=0;index<Infantry.Count();++index) {
        if (required<=0) break;
        InfantryClass *member=Infantry[index];
        if (member && member->unknown_7d && member->Owner()==Owner()) {
            bool base_defense=member->Team && member->Team->Class->IsBaseDefense;
            if ((!member->Team || base_defense) && member->unknown_379 && member->unknown_slot163() && member->unknown_37a && (member->Control()->unknown_06 || unknown_game_mode_a3d298)) {
                int armor=attacker->unknown_slot32()->unknown_9c;
                if (member->unknown_slot230()->WeaponType->Warhead->Verses[armor]!=0.0) {
                    Cell from=Coord_Cell(unknown_slot19(0));
                    Cell to=Coord_Cell(member->unknown_slot19(0));
                    if (Map.Unknown_0054F7C0(to,from,member->Type->MovementZone,member->unknown_slot46(0),false,false)) {
                        int value=member->unknown_4c82a0(attacker);
                        if (value) {
                            if (unknown_1b0==this) value*=100;
                            if (value<0) required+=value;
                            else if (count<6) { responders[count]=member; scores[count]=value; ++count; }
                            else if (value>minimum) {
                                int lowest=value;
                                for (int check=0;check<count;++check) {
                                    if (scores[check]==minimum) { scores[check]=value;responders[check]=member; }
                                    else if (scores[check]<lowest) lowest=scores[check];
                                }
                                minimum=lowest;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int unit_index=0;unit_index<Units.Count();++unit_index) {
        if (required<=0) break;
        UnitClass *member=Units[unit_index];
        if (member && member->unknown_7d) {
            int member_owner=member->Owner();
            if (member_owner!=Owner()) continue;
            bool base_defense=member->Team && member->Team->Class->IsBaseDefense;
            if ((!member->Team || base_defense) && member->unknown_379 && member->unknown_slot163() && member->unknown_37a && (member->Control()->unknown_06 || unknown_game_mode_a3d298)) {
                int armor=attacker->unknown_slot32()->unknown_9c;
                if (member->unknown_slot230()->WeaponType->Warhead->Verses[armor]!=0.0) {
                    Cell from=Coord_Cell(unknown_slot19(0));
                    Cell to=Coord_Cell(member->unknown_slot19(0));
                    if (Map.Unknown_0054F7C0(to,from,member->Type->MovementZone,member->unknown_slot46(0),false,false)) {
                        int value=member->unknown_4c82a0(attacker);
                        if (value) {
                            if (value>0 && unknown_1b0==this) value*=10;
                            if (value<0) required+=value;
                            else if (count<6) { responders[count]=member;scores[count]=value;++count; }
                            else if (value>minimum) {
                                int lowest=value;
                                for (int check=0;check<count;++check) {
                                    if (scores[check]==minimum) {scores[check]=value;responders[check]=member;}
                                    else if (scores[check]<lowest) lowest=scores[check];
                                }
                                minimum=lowest;
                            }
                        }
                    }
                }
            }
        }
    }
    if (required>0) {
        for (int first=0;first<count-1;++first) {
            for (int second=first+1;second<count;++second) {
                if (scores[first]<scores[second]) {
                    scores[first]^=scores[second];scores[second]^=scores[first];scores[first]^=scores[second];
                    FootClass *saved=responders[first];responders[first]=responders[second];responders[second]=saved;
                }
            }
        }
        for (int chosen=0;chosen<count;++chosen) {
            FootClass *member=responders[chosen];
            bool base_defense=member->Team && member->Team->Class->IsBaseDefense;
            if (unknown_id_source_a3d290->Random()(0,99)>=66 || base_defense) {
                member->unknown_slot116(11,false);
                member->unknown_1b0=this;
            } else {
                member->unknown_slot116(21,false);
                member->unknown_1b0=this;
            }
            member->unknown_slot220(attacker);
            recruited+=member->unknown_slot168();
            if (recruited>required) break;
        }
    }
    if (recruited>required) {
        if (attacker) is_foot=attacker->unknown_14_bit2;
        if (attacker && is_foot) static_cast<FootClass *>(attacker)->unknown_540=(int)(Rules->BaseDefenseDelay*900.0);
    }
}
