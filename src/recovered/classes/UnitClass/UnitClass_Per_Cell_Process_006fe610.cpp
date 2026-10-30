// Per-cell arrival, docking, movement completion and terrain consequences.
#include "shared/unit.hpp"
#include "shared/building_type_class.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/team.hpp"
#include "shared/anim.hpp"
#include "shared/overlay_type.hpp"
#include "shared/locomotion.hpp"
#include "shared/sound_play.hpp"
extern "C" GUID const CLSID_HoverLocomotionClass;
extern CoordStruct const unknown_coord_ad04c0;
extern Cell const unknown_cell_ad0488;
TechnoClass *__fastcall Unknown_0040DC20(AbstractClass *object);
ILocomotion *__fastcall Unit_Checked_Locomotor_004cde90(UnknownComPtr<ILocomotion,&unknown_uuid_ILocomotion_7ce600> const &owner);
// @ref ?Unit_Checked_Locomotor_004cde90@@=004cde90
// @ref __real@4@3ff9a3d70a0000000000=007ae2dc
// @ref ?Unknown_0040DC20@@=0040dc20
// @ref ?Unknown_00473E80@UnknownCellClass@@=00473e80
// @ref _CLSID_HoverLocomotionClass=007a1f80
// @ref ?unknown_coord_ad04c0@@=00ad04c0
// @ref ?unknown_cell_ad0488@@=00ad0488

void UnitClass::unknown_slot93(int reason)
{
    Cell cell=unknown_slot104();
    if ((reason==2 || reason==0) && unknown_57c) {
        unknown_6fdfc0();
        if (!unknown_7d) return;
    }
    if (reason==2) {
        TechnoClass *contact=Contact(0);
        if ((unknown_slot91()==7 || unknown_slot91()==25) && contact && contact->Kind_Of()==6) {
            CoordStruct center=Cell_Coord(Coord_Cell(Center_Coord()));
            CoordStruct contact_center=Cell_Coord(Coord_Cell(contact->unknown_slot41((int)this)));
            if (Coord_Cell(center)==Coord_Cell(contact_center)) {
                UnknownComPtr<IPersist,&unknown_uuid_IPersist_7cf208> persist;
                if (Locomotor) {
                    HRESULT status=persist.Query_Held(Unit_Checked_Locomotor_004cde90(Locomotor));
                    if (FAILED(status) && status!=E_NOINTERFACE) _com_issue_error(status);
                }
                GUID clsid;
                persist.Checked()->GetClassID(&clsid);
                if (clsid==CLSID_HoverLocomotionClass && ((BuildingClass *)contact)->Type->UnitRepair && !unknown_494) unknown_494=contact;
                if (contact==unknown_494) {
                    FootClass::unknown_slot93(2);
                    unknown_slot149(21);
                    Locomotor.Checked()->Power_Off();
                    return;
                }
            }
        }
        if (unknown_370 && contact && contact->Kind_Of()==6 && unknown_slot91()==7) {
            if (contact==Map[cell-Cell(0,1)].unknown_4717b0()) {
                switch (unknown_slot150(21,contact)) {
                case 1: case 5: break;
                default: unknown_slot87(unknown_coord_ad04c0,true,false);break;
                }
            }
        }
        UnknownCellClass *current=(UnknownCellClass *)unknown_slot105();
        TechnoClass *transport=current->Unknown_004717B0();
        if (!transport) {
            transport=((UnknownCellClass *)unknown_slot105())->Unknown_00473E80(unknown_79);
            if (!transport) {
                transport=((UnknownCellClass *)unknown_slot105())->Unknown_00473E30(unknown_79);
            }
        }
        if (transport==this) transport=Unknown_0040DC20(transport->unknown_30);
        if (unknown_slot91()==7 && transport && transport!=this) {
            if (unknown_slot104()==transport->unknown_slot104() && Is_Radio_Contact(transport) && transport->unknown_slot32()->Passengers>0) {
                if (unknown_slot150(15,transport)==1) {
                    unknown_6d6e50(0);
                    unknown_79=false;
                    unknown_slot52();
                    transport->Cargo.Unknown_00468960(this);
                    unknown_slot69();
                } else {
                    unknown_slot260(0,1);
                    unknown_slot116(5,false);
                    unknown_slot87(unknown_coord_ad04c0,true,true);
                }
                return;
            }
        }
        if (unknown_370 && (unknown_slot91()!=7 || (Unknown_0040DC20(unknown_494) && Contact(0)!=unknown_494)) && unknown_slot91()!=16) {
            bool arrived=unknown_494==0;
            if (unknown_494 && unknown_494->Kind_Of()==11 && ((CellClass *)unknown_494)->MapCoords==Coord_Cell(Position_Coord_004f3f40())) arrived=true;
            if (!Map[Position_Coord_004f3f40()].unknown_4717b0() || arrived) {
                contact=Contact(0);
                if (arrived || !contact || contact->Kind_Of()!=6 || !((BuildingClass *)contact)->Type->WeaponsFactory || Map[Position_Coord_004f3f40()].unknown_4717b0()!=contact) {
                    int response=unknown_slot149(8);
                    if (response==23) {
                        if (unknown_494 && unknown_494!=unknown_slot105()) {
                            AbstractClass *destination=unknown_494;
                            if (destination && destination->unknown_14_bit0) unknown_slot150(14,(TechnoClass *)destination);
                        } else {
                            BuildingClass *building;
                            if (!contact) building=0;
                            else building=contact->Kind_Of()==6 ? (BuildingClass *)contact : 0;
                            if (!Type->Harvester && !Type->Weeder) {
                                if (!House->Unknown_004F52F0() && building && building->Type->WeaponsFactory) {
                                    Cell where=House->Unknown_004EB270(this);
                                    if (where!=unknown_cell_ad0488) {
                                        unknown_slot116(2,false);
                                        unknown_slot260(&Map[where],1);
                                        unknown_slot117();
                                        unknown_6d6e50(&Map[where]);
                                        unknown_slot116(11,false);
                                    } else unknown_6d6e50(0);
                                } else {
                                    AbstractClass *destination=unknown_1b0;
                                    if (destination && destination!=unknown_494) unknown_slot260(destination,1);
                                    else { unknown_4cd9b0();unknown_slot87(unknown_coord_ad04c0,true,false); }
                                }
                            } else unknown_slot116(10,true);
                        }
                    } else if (response!=10 && (Type->Harvester || Type->Weeder)) {
                        if (unknown_1b0) {
                            unknown_slot116(10,false);
                            unknown_slot260(unknown_1b0,1);
                            unknown_6d6e50(0);
                        } else if (!unknown_494) unknown_slot87(unknown_coord_ad04c0,true,false);
                    }
                }
            }
            if (Map[Position_Coord_004f3f40()].unknown_4717b0() && !unknown_494 && unknown_49c.Count()==0 && unknown_478.Count()==0) unknown_slot87(unknown_coord_ad04c0,true,true);
        }
        if (unknown_slot91()==5 && !Map.Unknown_0054AB00(Position_Coord_004f3f40()) && unknown_32d) {
            if (Team) Team->TargetNotAssigned=true;
            unknown_slot210();
            unknown_slot60();
            return;
        }
        unknown_slot263(false,false,false,0);
        unknown_slot262(false,false,false,0);
        Map.Unknown_0054A550(Position_Coord_004f3f40(),0,unknown_1f4+3,0);
        if (!unknown_5b9 && unknown_slot122()) unknown_slot117();
        if (Type->Harvester && unknown_slot91()!=16 && Mission!=7 && MissionQueue!=7 && !unknown_5b9) {
            RadioClass *radio=Contact(0);
            if (radio && radio->What_Am_I()==6 && ((BuildingClass *)radio)->Type->Refinery) unknown_slot149(3);
        }
        if (Type->Weeder && unknown_slot91()!=16 && Mission!=7 && MissionQueue!=7 && !unknown_5b9) {
            RadioClass *radio=Contact(0);
            if (radio && radio->What_Am_I()==6 && ((BuildingClass *)radio)->Type->Weeder) unknown_slot149(3);
        }
        if (!unknown_494 && Path[0]==-1 && !Type->MobileFire) unknown_244=unknown_slot187(1)/4;
        CellClass *current_cell=&Map[Position_Coord_004f3f40()];
        int land=current_cell->unknown_ec;
        if (!Locomotor.Checked()->Is_Moving() && unknown_slot101(current_cell,-1,-1,0,1)==7 && (!unknown_79 || !(current_cell->unknown_140&0x100)) && !unknown_325) {
            if (Mission!=7) {
                new AnimClass(Select_Damage_Anim(Strength,Rules->unknown_c74,land,&Position_Coord_004f3f40()),Position_Coord_004f3f40(),0,1,0x2600,Unknown_0047FCC0(Position_Coord_004f3f40()));
                int damage=Strength;
                Unknown_0047F600(Center_Coord(),damage,Rules->unknown_c74,0,0);
                unknown_slot86(&damage,0,Rules->unknown_c74,0,true,0);
                return;
            }
            unknown_slot87(unknown_coord_ad04c0,true,true);
        }
    }
    CellClass *current_cell=&Map[cell];
    if ((Type->Crusher || unknown_6d7910(17)) && current_cell->OverlayIndex!=-1) {
        OverlayTypeClass *overlay=OverlayTypes[current_cell->OverlayIndex];
        if (overlay->unknown_1fd) {
            Voc_Play_At(overlay->unknown_1c0,Center_Coord(),0);
            current_cell->unknown_475fe0(-1);
            unknown_59f=false;
            unknown_28c+=0.019999999552965164f;
        }
    }
    unknown_slot302(&unknown_slot104(),false);
    if (unknown_7d) FootClass::unknown_slot93(reason);
}
