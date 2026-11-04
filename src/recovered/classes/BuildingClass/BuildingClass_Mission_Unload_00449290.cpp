// @ref ??_C@_0CO@IIJI@Weapons?5factory?5bib?5clear?5?9?5kick@=007cfa28
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Query@?$UnknownComPtr@UIPiggyback@@$1?unknown_uuid_IPiggyback_7cfc30@@3UGUID@@B@@QAEJABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00454c70
// @ref ?_AddRef@?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@QBEXXZ=00453ea0
// @ref ?CreateInstance@?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@QAEJABUGUID@@PAUIUnknown@@K@Z=0041b650
// @ref ??4?$UnknownComPtr@UIPiggyback@@$1?unknown_uuid_IPiggyback_7cfc30@@3UGUID@@B@@QAEAAV0@PAUIPiggyback@@@Z=00453e70
// Original-only bounds: 00449290, 1692 body bytes, 4 NOP padding bytes.
// Mission state and interface names are evidence-based source hypotheses.
#include "shared/building.hpp"
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/locomotion.hpp"
#include "shared/building_map.hpp"
#include "shared/id_source.hpp"
#include "shared/debug_printf.hpp"
extern "C" GUID const CLSID_TunnelLocomotionClass;
extern "C" GUID const CLSID_TeleportLocomotionClass;
extern "C" GUID const CLSID_DriveLocomotionClass;
extern "C" GUID const unknown_uuid_IPiggyback_7cfc30;
// @ref _CLSID_TunnelLocomotionClass=007a1f90
// @ref _CLSID_TeleportLocomotionClass=007a1fd0
// @ref _CLSID_DriveLocomotionClass=007a1f70
// @ref ?Debug_Printf@@=004068f0
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?Query@?$UnknownComPtr@UIPersist@@$1?unknown_uuid_IPersist_7cf208@@3UGUID@@B@@QAEJABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00454bf0
template <> void UnknownComPtr<ILocomotion,&unknown_uuid_ILocomotion_7ce600>::_AddRef() const;
template <> UnknownComPtr<ILocomotion,&unknown_uuid_ILocomotion_7ce600> &
UnknownComPtr<ILocomotion,&unknown_uuid_ILocomotion_7ce600>::operator=(UnknownComPtr const &other)
{
    if(Pointer!=other.Pointer) {
        ILocomotion *old=Pointer;
        Pointer=other.Pointer;
        _AddRef();
        if(old) old->Release();
    }
    return *this;
}

int BuildingClass::unknown_slot137()
{
    if(unknown_554.Count()>0) unknown_452f50(0);
    if(Type->WeaponsFactory) {
        CoordStruct destination(0,0,0);
        if(!Type->Naval) {
            Cell exit=Type->FoundationOutside[10];
            Cell position=unknown_slot104()+exit;
            destination=CoordStruct(Cell(position.X-1,position.Y));
        }
        switch(unknown_a8) {
        case 0: {
            TechnoClass *unit=Contact(0);
            if(unit) { unit->unknown_slot116(5,false); unit->unknown_slot117(); }
            unknown_2a8.unknown_496b70(Type->DeployTime);
            unknown_a8=Type->Naval ? 4 : 1;
            unknown_75=true;
            unknown_44cfd0(17);
            unknown_44c920(8,Health_Ratio()<=Rules->unknown_1368,false,0);
            break;
        }
        case 1:
            if(!unknown_4454b0()) {
                Debug_Printf("Weapons factory bib clear - kicking out unit\n");
                unknown_a8=2;
            }
            break;
        case 2:
            if(unknown_2a8.unknown_496b30()) {
                FootClass *unit=static_cast<FootClass *>(Contact(0));
                if(unit) {
                    unit->unknown_slot116(2,false);
                    UnknownComPtr<IPersist,&unknown_uuid_IPersist_7cf208> persist(unit->Locomotor);
                    GUID classid;
                    persist.Checked()->GetClassID(&classid);
                    if(classid==CLSID_TunnelLocomotionClass || classid==CLSID_TeleportLocomotionClass) {
                        UnknownComPtr<IPiggyback,&unknown_uuid_IPiggyback_7cfc30> piggy(unit->Locomotor);
                        if(piggy && piggy.Checked()->Is_Piggybacking()) {
                            unit->Locomotor.Attach(0);
                            piggy.Checked()->End_Piggyback(&unit->Locomotor.Pointer);
                        }
                        UnknownComPtr<ILocomotion,&unknown_uuid_ILocomotion_7ce600> drive(CLSID_DriveLocomotionClass);
                        drive.Checked()->Link_To_Object(unit);
                        piggy=UnknownComPtr<IPiggyback,&unknown_uuid_IPiggyback_7cfc30>(drive);
                        if(piggy) {
                            piggy.Checked()->Begin_Piggyback(unit->Locomotor);
                            unit->Locomotor=drive;
                            unit->Locomotor.Checked()->Force_Track(66,destination);
                        } else {
                            int damage=unit->Strength;
                            unit->unknown_slot86(&damage,0,Rules->unknown_c74,0,true,0);
                        }
                    } else if(!(classid==CLSID_DriveLocomotionClass)) {
                        unit->unknown_slot260(&Map[unknown_slot104()+Cell(5,1)],true);
                    } else {
                        unit->Locomotor.Checked()->Force_Track(66,destination);
                    }
                    unit->unknown_slot306(0.5);
                    unknown_a8=3;
                } else {
                    unknown_2a8.unknown_496bc0(Type->DeployTime);
                    unknown_a8=4;
                }
            }
            break;
        case 3:
            if(!unknown_370) { unknown_2a8.unknown_496bc0(Type->DeployTime); unknown_a8=4; }
            break;
        case 4:
            if(unknown_2a8.unknown_496b50() || Type->Naval) { unknown_slot261(false,true); unknown_75=true; }
            break;
        }
        int delay=Control()->Normal_Delay();
        return delay+unknown_id_source_a3d290->Random()(0,2);
    }
    if(Type->GapGenerator && Type->SuperGapRadiusInCells) {
        if(!unknown_1fc) {
            unknown_slot236();
            unknown_200=Type->SuperGapRadiusInCells;
            if(unknown_slot195()) {
                unknown_slot235();
                unknown_1fc=true;
                unknown_539=true;
                House->unknown_5668=true;
            } else {
                unknown_200=Type->GapRadiusInCells;
                unknown_slot235();
            }
        } else {
            unknown_slot236();
            unknown_1fc=false;
            unknown_539=false;
            unknown_200=Type->GapRadiusInCells;
            unknown_slot235();
            House->unknown_5668=true;
        }
    }
    unknown_slot116(5,false);
    return 1;
}
