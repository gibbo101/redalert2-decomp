// @ref ??0UnknownPersistPtr@@QAE@ABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00509870
// @ref ??1UnknownPersistPtr@@QAE@XZ=004a4d00
// Assign an infantry destination, including transport contact and locomotor transitions.
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/sidebar_building.hpp"
#include "shared/infantry_piggyback_ptr.hpp"
extern "C" GUID const unknown_Walk_clsid_007a1fa0;
extern "C" GUID const CLSID_JumpjetLocomotionClass;
// @ref _unknown_Walk_clsid_007a1fa0=007a1fa0
// @ref _CLSID_JumpjetLocomotionClass=007a2000
// @ref ?Release_Held@UnknownPersistPtr@@QAEXXZ=004a4d00
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Query@?$UnknownComPtr@UIPersist@@$1?unknown_uuid_IPersist_7cf208@@3UGUID@@B@@QAEJABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00454bf0
// @ref ?Query@?$UnknownComPtr@UIPiggyback@@$1?unknown_uuid_IPiggyback_7cfc30@@3UGUID@@B@@QAEJABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00454c70
// @ref ??4?$UnknownComPtr@UIPiggyback@@$1?unknown_uuid_IPiggyback_7cfc30@@3UGUID@@B@@QAEAAV0@PAUIPiggyback@@@Z=00453e70
// RTTI-checked unit view, like the shared As_Building/As_Infantry operations.
class UnitClass;
inline UnitClass *As_Unit(AbstractClass *object)
{
    if (object==0) return 0;
    return object->Kind_Of()==1 ? (UnitClass *)object : 0;
}
void InfantryClass::unknown_slot260(AbstractClass *target,int immediate)
{
    if (Owning_House()->unknown_func_4f52f0()) {
        if (Sequence==27 || Sequence==28 || Sequence==29 || Sequence==30) return;
    }
    if (Type->JumpJet && target) {
        if (Cell(target->Center_Coord())==Cell(Center_Coord())) return;
    }
    if (Locomotor.Checked()->Is_Moving() && target &&
        Map[Center_Coord()].unknown_478760(Type->SpeedType,true,false,-1,0,-1,true)) {
        if (Type->JumpJet || Mission!=1 || unknown_494!=target) unknown_slot291();
    }
    if (House->unknown_func_4f52f0() && target && unknown_494==target &&
        unknown_5c3 && !Type->Fraidycat && !Type->Cyborg) unknown_slot311(7,false,false);
    if (unknown_slot91()==7 || MissionQueue==7) {
        if (!In_Radio_Contact()) {
            TechnoClass *transport=target->As_Techno();
            if (transport) {
                if (transport->In_Radio_Contact()) {
                    if (transport->Kind_Of()==1) {
                        unknown_3f8=(AbstractClass *)As_Unit(target);
                        unknown_6d6e50(0);
                        target=0;
                    } else if (transport->Kind_Of()==6) {
                        unknown_3f8=As_Building((ObjectClass *)target);
                        unknown_6d6e50(0);
                        target=0;
                    } else unknown_6d6e50(target);
                } else {
                    if (unknown_slot150(2,transport)==1) {
                        int reply=unknown_slot149(14);
                        if (reply==14) return;
                        if (reply!=1) unknown_slot149(3);
                    }
                }
            }
        } else unknown_4d0=-1;
    } else unknown_4d0=-1;
    if (target && Type->JumpJet && Locomotor.Checked()->Is_Moving()) {
        UnknownComPtr<IPersist,&unknown_uuid_IPersist_7cf208> persist(Locomotor);
        GUID class_id;
        persist.Checked()->GetClassID(&class_id);
        if (memcmp(&class_id,&unknown_Walk_clsid_007a1fa0,sizeof(GUID))==0) {
            unknown_49c.Add_Head(target);
            target=unknown_slot107();
            if (target && (static_cast<CellClass *>(target)->unknown_140&0x100)) target=0;
        }
    }
    if (Type->JumpJet && target && !Locomotor.Checked()->Is_Moving()) {
        bool should_fly=unknown_508dd0(&unknown_slot19(0).As_Cell(),&target->Center_Coord().As_Cell());
        bool is_jumpjet=unknown_508d00();
        if (Type->HoverAttack) should_fly=true;
        if (is_jumpjet) {
            if (!should_fly) {
                UnknownComPtr<IPiggyback,&unknown_uuid_IPiggyback_7cfc30> piggy(Locomotor);
                if (piggy && piggy.Checked()->Is_Piggybacking() && piggy.Checked()->Is_Ok_To_End()) { piggy.Checked()->End_Piggyback(&Locomotor); }
                UnknownComPtr<ILocomotion,&unknown_uuid_ILocomotion_7ce600> walk(unknown_Walk_clsid_007a1fa0);
                walk.Checked()->Link_To_Object(this);
                piggy=UnknownComPtr<IPiggyback,&unknown_uuid_IPiggyback_7cfc30>(walk);
                if (piggy) {
                    piggy.Checked()->Begin_Piggyback(Locomotor);
                    Locomotor=walk;
                }
            }
        } else if (should_fly) {
            UnknownComPtr<IPiggyback,&unknown_uuid_IPiggyback_7cfc30> piggy(Locomotor);
            if (piggy && piggy.Checked()->Is_Piggybacking() && piggy.Checked()->Is_Ok_To_End()) { piggy.Checked()->End_Piggyback(&Locomotor); }
        }
    }
    FootClass::unknown_slot260(target,immediate);
}
