// Building radio dispatch: load permission, docking maintenance and construction.
// Message values and sender downcasts follow the observed original ABI.
#include "shared/building.hpp"
#include "shared/unit.hpp"
#include "shared/house.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/fast_math.hpp"
#include "shared/rules.hpp"
extern CoordStruct const Building_Radio_No_Coord_0084ed30;
// @ref ?Building_Radio_No_Coord_0084ed30@@=0084ed30

#include "shared/coord_distance.hpp"

// Hypothesis: the reference three-axis object-distance inline operation.
// This is distinct from the accepted planar ObjectClass::Distance_To.
inline int Building_Radio_Object_Distance_004397f0(ObjectClass const &origin,AbstractClass const &target)
{
    CoordStruct delta=origin.Center_Coord()-target.Center_Coord();
    return (int)unknown_sqrt_4ba410((double)delta.X*delta.X+(double)delta.Z*delta.Z+(double)delta.Y*delta.Y);
}
inline FootClass *Building_Radio_Foot_004397f0(RadioClass *sender)
{
    if (!sender) return 0;
    return sender->AbstractFlags.IsFoot?static_cast<FootClass *>(sender):0;
}
inline TechnoClass *Building_Radio_Infantry_004397f0(RadioClass *sender)
{
    if (!sender) return 0;
    return sender->Kind_Of()==15?static_cast<TechnoClass *>(sender):0;
}

inline CoordStruct Position_Coord_00450950(ObjectClass const &object);

int BuildingClass::unknown_slot95(RadioClass *radio,int message,long &param)
{
    TechnoClass *sender=static_cast<TechnoClass *>(radio);
    switch (message) {
    case 15:
        TechnoClass::unknown_slot95(radio,message,param);
        if (!House->Is_Ally(sender)) return 0;
        if (unknown_slot91()==18 || unknown_slot91()==19 || unknown_42c==0 ||
            (!unknown_a40774 && !Unknown_00636ED0(sender))) return 10;
        if (sender->unknown_slot32()->MovementZone!=5 &&
            ((unknown_slot32()->Naval && !sender->unknown_slot32()->Naval) ||
             (!unknown_slot32()->Naval && sender->unknown_slot32()->Naval))) return 10;
        if (sender->unknown_slot32()->BalloonHover) return 10;
        if (!unknown_530) return 10;
        if (Type->UnitRepair) {
            if (radio->Kind_Of()==1 || radio->Kind_Of()==2) {
                if (unknown_slot150(35,sender)!=1) return 1;
            }
            return 10;
        }
        if ((Type->Armory || Type->Hospital) && radio->Kind_Of()==15) {
            TechnoClass *infantry=Building_Radio_Infantry_004397f0(radio);
            if (infantry->unknown_230 && static_cast<UnknownTechno230 *>(infantry->unknown_230)->unknown_24) return 10;
            if (infantry->unknown_234) return 10;
            return unknown_254!=0?1:10;
        }
        if (Type->Helipad) return radio->What_Am_I()==2?1:10;
        if (Type->DockUnload && radio->Kind_Of()==1 && static_cast<UnitClass *>(radio)->Type->Harvester) {
            if (unknown_a40774 || !Cargo.Object) return 1;
        }
        if (Type->Weeder && radio->Kind_Of()==1 && static_cast<UnitClass *>(radio)->Type->Weeder) {
            if (unknown_a40774 || !Cargo.Object) return 1;
        }
        return 0;
    case 21:
        if (unknown_slot91()==19) return 10;
        if (Type->UnitRepair || Type->UnitReload || Type->Hospital || Type->Armory) {
            unknown_5ad=true;
            unknown_slot116(20,false);
            radio->unknown_slot116(0,false);
            return 1;
        }
        if (Type->DockUnload) { radio->unknown_slot116(16,false); return 1; }
        break;
    case 14: {
        TechnoClass::unknown_slot95(radio,message,param);
        if (!unknown_530) return 10;
        if (Type->UnitRepair && Is_Radio_Contact(sender) && unknown_slot150(34,sender)==10) return 10;
        if (!Type->Hospital && !Type->Armory) {
            if (!Is_Radio_Contact(sender) && Unknown_00636ED0(sender)) {
                unknown_slot150(2,sender);
                Is_Radio_Contact(sender);
            }
            bool needs_to_move=false;
            if (Is_Radio_Contact(sender) && (Type->DockUnload || Type->Weeder)) {
                FootClass *foot=Building_Radio_Foot_004397f0(radio);
                CellClass *cell=&Map[unknown_slot41((int)foot)];
                AbstractClass *destination=foot->unknown_494;
                if (destination && reinterpret_cast<AbstractClass *>(cell)!=destination) needs_to_move=true;
            }
            if (Contact(0) && Type->UnitRepair &&
                Building_Radio_Object_Distance_004397f0(*this,*Contact(0))>128) needs_to_move=true;
            if (unknown_slot150(19,sender)==1 || needs_to_move) {
                param=(long)this;
                if (Type->DockUnload || Type->Weeder) {
                    param=(long)&Map[unknown_slot104()+Cell(3,1)];
                    if (unknown_slot151(18,reinterpret_cast<int *>(&param),sender)==20) {
                        unknown_slot150(24,sender);
                        if (unknown_slot150(22,sender)!=1) radio->unknown_slot87(Building_Radio_No_Coord_0084ed30,true,true);
                    }
                } else if (Type->Helipad) {
                    param=(long)this;
                    if (unknown_slot151(18,reinterpret_cast<int *>(&param),sender)==20) unknown_slot149(24);
                }
            }
            return 1;
        }
        if (!Unknown_00636ED0(sender)) {
            for (int index=0;index<RadioLinks.Length();++index) {
                TechnoClass *contact=Contact(index);
                if (unknown_slot150(34,contact)==10) unknown_slot150(23,contact);
            }
            if (!Unknown_00636ED0(sender)) return 10;
        } else {
            param=(long)&Map[Position_Coord_00450950(*this)];
            unknown_slot151(18,reinterpret_cast<int *>(&param),sender);
        }
        return 1;
    }
    case 16:
        if (!Cargo.Object && Unknown_00636ED0(sender) && !unknown_76 && House==radio->Owning_House()) {
            if (Type->Refinery || Type->UnitRepair || Type->Weeder) return 1;
        }
        return 10;
    case 11:
        unknown_slot116(20,false);
        TechnoClass::unknown_slot95(radio,message,param);
        return 1;
    case 12:
        if (unknown_slot91()!=19) {
            unknown_slot116(5,false);
            if (Type->ConstructionYard) {
                unknown_44cfd0(7);
                unknown_44cfd0(17);
                unknown_44c920(8,Health_Ratio()<=Rules->unknown_1368,false,0);
            }
        }
        TechnoClass::unknown_slot95(radio,message,param);
        return 1;
    case 3:
        unknown_443d60(1);
        TechnoClass::unknown_slot95(radio,message,param);
        return 1;
    case 8:
        if (Type->UnitRepair && Building_Radio_Object_Distance_004397f0(*this,*radio)<384) return 1;
        TechnoClass::unknown_slot95(radio,message,param);
        if (!Type->WeaponsFactory && !Type->UnitRepair) return 1;
        return 23;
    case 13:
        if (Type->WeaponsFactory) return 1;
        break;
    }
    return TechnoClass::unknown_slot95(radio,message,param);
}
