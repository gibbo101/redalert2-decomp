// int TechnoClass::unknown_slot218(AbstractClass *target, int which, bool check_range) (0x006C9260, slot 218)
// TibSun Can_Fire: 0 when the object may fire, else the FireErrorType. The land
// targeting test sits in each arm (the arms cross-jump), and everything after the
// weapon test is nested in it so the CANT block stays last.
#include "shared/techno.hpp"
#include "shared/infantry.hpp"
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/warhead_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/bullet_type.hpp"
#include "shared/parasite.hpp"
#include "shared/team.hpp"
#include "shared/capture_manager.hpp"
#include "shared/spawn_manager.hpp"
#include "shared/unknown_geometry.hpp"
extern "C" int __cdecl abs(int);
int TechnoClass::unknown_slot218(AbstractClass *target,int which,bool check_range)
{
    TechnoClass *techno;
    CellClass *cellptr;
    WeaponTypeClass *weapon;
    WeaponTypeClass *other;
    bool water;
    bool check_rearm;
    FootClass *foot;
    bool parasite;
    if(target==0) goto ILLEGAL;
    if(unknown_slot112()) return 3;
    if(unknown_slot111()) goto ILLEGAL;
    if(unknown_325) goto ILLEGAL;
    if(unknown_slot113() && unknown_208 && (int)target==unknown_208->unknown_28) return 3;
    techno=target->AbstractFlags.IsTechno?static_cast<TechnoClass *>(target):0;
    cellptr=reinterpret_cast<CellClass *>(&Map[target->Center_Coord()]);
    if(techno) {
        if(techno->unknown_76) goto ILLEGAL;
        if(techno->unknown_210) goto ILLEGAL;
        if(techno->unknown_slot25(true,(int)House)==5 && !cellptr->unknown_47c2e0(House->ArrayIndex)) {
            if(unknown_6c16f0(-1)>0) goto CANT;
            if(!techno->House->Is_Ally(House)) goto CANT;
        }
    }
    if(unknown_7a) goto ILLEGAL;
    if(unknown_slot201()) {
        if(Kind_Of()!=1) goto CANT;
        UnitClass *unit=static_cast<UnitClass *>(this);
        if(!unit->Type->LargeVisceroid && !unit->Type->SmallVisceroid) goto CANT;
    }
    weapon=unknown_slot231(which)->WeaponType;
    if(weapon!=0) {
        if(weapon->unknown_125 && House->Unknown_0051FC80()) goto CANT;
        if(techno && weapon->Warhead && techno->unknown_slot111() && !weapon->Warhead->Temporal) goto ILLEGAL;
        if(weapon->unknown_10d) {
            if(unknown_6cf670()) goto CANT;
            if(unknown_slot202()) goto CANT;
            if(SpawnManager->Alive_Count()==0) return 3;
        }
        other=unknown_slot231(which==0)->WeaponType;
        if(other && ((other->unknown_105 && unknown_25c[0]) || (other->unknown_109 && unknown_25c[4]) || (other->unknown_106 && unknown_25c[1]) || (other->unknown_10c && unknown_27c))) goto CANT;
        if(target->unknown_slot21() && !weapon->Projectile->AA) goto ILLEGAL;
        if(techno) {
            water=(reinterpret_cast<CellClass *>(techno->unknown_slot105())->unknown_ec==2)
                || (reinterpret_cast<CellClass *>(techno->unknown_slot105())->unknown_ec==6);
            if(techno->unknown_slot21()) water=false;
            if(techno->unknown_79) water=false;
            else if(water && unknown_slot175(static_cast<ObjectClass *>(target))==-1) goto ILLEGAL;
            if(target->unknown_slot20() && !water && unknown_slot32()->LandTargeting==1) return 5;
        } else {
            if(!target->unknown_slot21() && !weapon->Projectile->AG) return 5;
            if(target->Kind_Of()==0xb && As_Cell(target)->unknown_ec!=2 && As_Cell(target)->unknown_ec!=6 && unknown_slot32()->LandTargeting==1) goto ILLEGAL;
        }
        check_rearm=true;
        if(which==0 && this && Kind_Of()==1) {
            UnitClass *unit=static_cast<UnitClass *>(this);
            int burst=unknown_310%weapon->Burst;
            if(burst<2 && unit->Type->FiringSyncFrame[burst]!=-1 && unit->unknown_5a8!=-1) {
                if(unit->unknown_5a8!=unit->Type->FiringSyncFrame[burst]) return 3;
                check_rearm=false;
            }
        }
        if(check_rearm && unknown_244.Value()!=0) return 3;
        if(weapon->unknown_105 && unknown_25c[0]) return 3;
        if(weapon->unknown_109 && unknown_25c[4]) return 3;
        if(weapon->unknown_106 && unknown_25c[1]) return 3;
        if(weapon->unknown_10c && unknown_27c) return 3;
        if(unknown_254==0) return 1;
        if(weapon->unknown_10f && unknown_1b8!=0 && (Kind_Of()!=2 || unknown_1b8==2)) return 9;
        if(unknown_slot32()->HunterSeeker) return 8;
        if(weapon->Warhead->Parasite && this && AbstractFlags.IsFoot) {
            foot=target->AbstractFlags.IsFoot?static_cast<FootClass *>(target):0;
            if(!static_cast<FootClass *>(this)->unknown_588->Can_Infect_006078F0(foot)) return 5;
        }
        parasite=weapon->Warhead->Parasite;
        if(parasite && target->AbstractFlags.IsFoot && Frame<static_cast<FootClass *>(target)->unknown_584) return 5;
        if(techno) {
            if(parasite && techno->unknown_slot203()) return 5;
            if(weapon->Warhead->MindControl && !reinterpret_cast<CaptureManagerClass *>(unknown_230)->Can_Capture(techno)) return 5;
            WarheadTypeClass *warhead=weapon->Warhead;
            if(warhead->Verses[techno->unknown_slot32()->unknown_9c]==0.0) return 5;
            if(warhead->BombDisarm && techno->unknown_38==0) return 5;
            if(warhead->IvanBomb && techno->unknown_38!=0) return 5;
            if(techno->unknown_325) return 5;
            if(unknown_79!=techno->unknown_79) {
                if(unknown_slot105() && (reinterpret_cast<CellClass *>(unknown_slot105())->unknown_140&0x100) && !unknown_slot21()
                    && techno->unknown_slot105() && (reinterpret_cast<CellClass *>(techno->unknown_slot105())->unknown_140&0x100)) return 5;
                int mine=Position_Coord_004f3f40().Z;
                int theirs=techno->Position_Coord_004f3f40().Z;
                if(weapon->Warhead->Parasite && abs(mine-theirs)>unknown_geometry_g*2) return 5;
            }
        }
        if(unknown_slot32()->Organic && unknown_slot202()) return 5;
        if(check_range && !unknown_slot212(target,which)) return 8;
        return 0;
    }
CANT:
    return 6;
ILLEGAL:
    return 5;
}
