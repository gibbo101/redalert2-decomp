// Existing shared Checked() emits the complete original004CDE90 accessor32 bytes.
// This real-body binding reuses that original copy and earns no new byte credit.
// @ref ?Checked@?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@QBEPAUILocomotion@@XZ=004cde90
// Approach the current combat target from a reachable cell inside weapon range.
// Existing virtual slot304; source and member names remain explicit hypotheses.
#include "shared/foot.hpp"
#include "shared/dir_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/infantry.hpp"
#include "shared/building_type.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_vector3.hpp"
#include "shared/fast_math.hpp"
extern "C" GUID const CLSID_JumpjetLocomotionClass;
extern int const unknown_approach_angles_7d8178[25];
extern int unknown_approach_bridge_height_865f60;
extern Cell const unknown_approach_none_865f00;
// @ref ?Unknown_00568ED0@MapClass@@QAE?AVCell@@ABV2@0@Z=00568ed0
// @ref __real@8@40078cccccccccccd000=007a17c8
// @ref __real@8@4006b333333333333000=007a17c0
// @ref __real@8@4006ccccccccccccd000=007a17b8
// @ref _CLSID_JumpjetLocomotionClass=007a2000
// @ref ?unknown_approach_angles_7d8178@@3QBHB=007d8178
// @ref ?unknown_approach_bridge_height_865f60@@3HA=00865f60
// @ref ?unknown_approach_none_865f00@@3VCell@@B=00865f00
// @ref ?Release_Held@?$UnknownComPtr@UIPersist@@$1?unknown_uuid_IPersist_7cf208@@3UGUID@@B@@QAEXXZ=004a4d00
// @ref ?Query@?$UnknownComPtr@UIPersist@@$1?unknown_uuid_IPersist_7cf208@@3UGUID@@B@@QAEJABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00454bf0

template<class Interface, GUID const *iid>
HRESULT UnknownComPtr<Interface,iid>::Query(UnknownComPtr<ILocomotion, &unknown_uuid_ILocomotion_7ce600> const &other)
    {
        if (other) {
            Interface *pointer;
            HRESULT result=other.Checked()->QueryInterface(*iid,(void **)&pointer);
            if (FAILED(result)) {
                Release_Held();
                Pointer=0;
            } else {
                Interface *attached=pointer;
                Release_Held();
                Pointer=attached;
            }
            return result;
        }
        Interface *old=Pointer;
        if (old) {
            Pointer=0;
            old->Release();
        }
        return E_NOINTERFACE;
    }

// Original free coordinate-distance operation; the three-int difference constructor
// stays out of line, while this caller expands the length in Y,Z,X load order.
inline int Approach_Coord_Distance_004c4c30(CoordStruct const &left,CoordStruct const &right)
{
    UnknownVector3 const &difference=reinterpret_cast<UnknownVector3 const &>(left)-reinterpret_cast<UnknownVector3 const &>(right);
    double y=difference.Y;
    double z=difference.Z;
    double x=difference.X;
    return (int)Fast_Sqrt(x*x+z*z+y*y);
}
inline UnknownFacingDir Approach_Direction_004c4c30(CoordStruct const &from,CoordStruct const &to)
{
    int to_x=to.X;
    return UnknownFacingDir((unsigned short)(int)((Fast_Atan2((double)from.Y-(double)to.Y,(double)to_x-(double)from.X)-1.5707963267948966)*-10430.060040584269));
}
inline CoordStruct Approach_Move_Coord_004c4c30(CoordStruct const &start,DirType const &dir,double distance)
{
    double angle=(dir.As_Int()-16383)*-9.587672516830327e-05;
    double start_x=start.X;
    double start_y=start.Y;
    return CoordStruct((int)(start_x+Fast_Cos(angle)*distance),(int)(start_y-Fast_Sin(angle)*distance),start.Z);
}
void FootClass::unknown_slot304()
{
    if (unknown_228) {
    int weapon=unknown_slot174(unknown_228);
    int maximum_range=unknown_slot85(weapon);
    if (maximum_range>=512) maximum_range-=128;
    bool in_range=unknown_slot212(unknown_228,weapon);
    if (!in_range) {
        if (Mission==6) {
            unknown_slot220(0);
            unknown_slot260(0,1);
            return;
        }
        if (!unknown_slot32()->CanApproachTarget) {
            bool pursue=false;
            if (Mission==1) pursue=true;
            if (Mission==11 && House->unknown_func_4f52f0()) pursue=true;
            if ((Mission!=15 || House->unknown_func_4f52f0()) && !pursue) {
                unknown_slot220(0);
                unknown_slot260(0,1);
                return;
            }
        }
    }
    bool require_deploy_cell=false;
    if (Kind_Of()==1 && ((UnitClass *)this)->Type->DeployToFire) {
        CoordStruct position=Coord;
        if (!Map[position].unknown_47cdd0()) {
            require_deploy_cell=true;
            int near_range=unknown_5d4c00(unknown_228)+512;
            if (maximum_range>=near_range) maximum_range=near_range;
        }
    }
    bool flyer=Kind_Of()==2;
    UnknownComPtr<IPersist,&unknown_uuid_IPersist_7cf208> persist(Locomotor);
    GUID class_id;
    persist.Checked()->GetClassID(&class_id);
    if (class_id==CLSID_JumpjetLocomotionClass) flyer=true;
    if (unknown_494) {
        if (unknown_228 && unknown_slot32()->CanRecalcApproachTarget && !in_range) {
            int separation=Approach_Coord_Distance_004c4c30(unknown_494->Center_Coord(),unknown_228->Center_Coord());
            if (separation>Rules->unknown_bec*maximum_range) {
                unknown_490=0;
                unknown_494=0;
            }
        }
    }
    if ((!unknown_494 || unknown_slot21()) && (!in_range || !unknown_32d || require_deploy_cell)) {
    if (unknown_478.Count()>0) {
        unknown_slot260(unknown_478[0],0);
        unknown_478.Delete(0);
        return;
    }
    if (unknown_228->Kind_Of()==11) {
        CellClass *target_cell=(CellClass *)unknown_228;
        if (target_cell->unknown_47bb10()) {
            Cell destination=unknown_slot19(0).As_Cell();
            Cell nearer=Map.Unknown_00568ED0(target_cell->MapCoords,destination);
            unknown_slot220(&Map[nearer]);
        }
    }
    if (unknown_228->Kind_Of()==6) {
        BuildingClass *building=(BuildingClass *)unknown_228;
        if (building) maximum_range+=(building->Type->Width()+building->Type->Foundation_Height(false))*64;
    }
    double adjusted;
    if (Kind_Of()==15) adjusted=(double)maximum_range-281.6;
    else adjusted=(double)maximum_range-179.2;
    maximum_range=(int)adjusted;
    maximum_range=maximum_range<=0?0:maximum_range;
    if (maximum_range>0 && maximum_range<=255) maximum_range=255;
    CoordStruct target_position=unknown_228->Center_Coord();
    CoordStruct trial_position;
    Cell target_cell=target_position.As_Cell();
    Cell trial_cell=target_cell;
    int direction=Dir_To_256(Approach_Direction_004c4c30(target_position,Center_Coord()));
    bool target_bridge=false;
    if (unknown_228->Kind_Of()==11) target_bridge=(((CellClass *)unknown_228)->unknown_140&0x100)!=0;
    else {
        AbstractClass *target=unknown_228;
        if (target && target->unknown_14_bit1) target_bridge=((ObjectClass *)target)->unknown_79;
    }
    int movement_zone=unknown_slot32()->MovementZone;
    bool found=false;
    double floating_radius;
    int radius=maximum_range;
    if ((double)radius>204.8) {
    floating_radius=(double)radius;
    do {
        for (int index=0;index<25;++index) {
            DirType angle((Dir256)(direction+unknown_approach_angles_7d8178[index]));
            trial_position=CoordStruct(Approach_Move_Coord_004c4c30(target_position,angle.Snap_To_256(),floating_radius).As_Cell(),0);
            if (require_deploy_cell && !Map[trial_position].unknown_47cdd0()) continue;
            trial_position.Z=Map.Unknown_0055A280(trial_position);
            if (Map[trial_position].unknown_140&0x100) trial_position.Z+=unknown_approach_bridge_height_865f60;
            if (!unknown_6c4bb0(&trial_position,unknown_228,unknown_slot231(weapon)->WeaponType)) continue;
            trial_cell=trial_position.As_Cell();
            if (!Map.Unknown_0055A660(trial_cell,true)) continue;
            bool clear=Map[trial_cell].unknown_478760(unknown_slot32()->SpeedType,false,false,
                Map.Zone(unknown_slot19(0).As_Cell(),movement_zone,unknown_79),movement_zone,-1,true);
            if (!clear) {
                if (Kind_Of()==15) continue;
                CoordStruct saved_position=trial_position;
                Cell saved_cell=trial_cell;
                for (int adjacent=0;adjacent<8;++adjacent) {
                    trial_cell=AdjacentCell[adjacent&7].TPoint2D<short>::operator+(trial_cell);
                    trial_position=CoordStruct(trial_cell);
                    if (unknown_6c4bb0(&trial_position,unknown_228,unknown_slot231(weapon)->WeaponType)
                        && Map[trial_cell].unknown_478760(unknown_slot32()->SpeedType,false,false,
                            Map.Zone(unknown_slot19(0).As_Cell(),movement_zone,unknown_79),movement_zone,-1,true)) {
                        clear=true;
                        break;
                    }
                }
                if (!clear) {
                    trial_position=saved_position;
                    trial_cell=saved_cell;
                    continue;
                }
            }
            int dy=abs((int)trial_cell.Y-target_cell.Y);
            int dx=abs((int)trial_cell.X-target_cell.X);
            int maximum_distance=dx>dy?dx:dy;
            CellClass *cell=&Map[trial_cell];
            if (!flyer && unknown_path_estimator_8315c8.Unknown_0042AA30(trial_cell,target_cell,this,
                    (cell->unknown_140&0x100)!=0,target_bridge,-1)>maximum_distance+8) {
                Cell destination=unknown_slot19(0).As_Cell();
                int dest_dy=abs((int)destination.Y-trial_cell.Y);
                int dest_dx=abs((int)destination.X-trial_cell.X);
                int dest_distance=dest_dx>dest_dy?dest_dx:dest_dy;
                if (unknown_path_estimator_8315c8.Unknown_0042AA30(destination,trial_cell,this,
                        unknown_slot46(0),(cell->unknown_140&0x100)!=0,-1)>dest_distance+8) continue;
            }
            found=true;
            break;
        }
        if (found) break;
    } while ((floating_radius=(double)(radius-=256))>204.8);
    }
    if (found) {
        unknown_slot260(&Map[trial_cell],1);
    } else if (unknown_slot32()->HunterSeeker || (Kind_Of()==15 && ((InfantryClass *)this)->Type->VehicleThief)) {
        unknown_slot260(unknown_228,1);
    } else {
        trial_cell=Map.Unknown_005502E0(trial_cell,unknown_slot32()->SpeedType,
            Map.Zone(unknown_slot19(0).As_Cell(),movement_zone,unknown_slot46(0)),movement_zone,
            (Map[trial_cell].unknown_140&0x100)!=0,Point2D(1,1),false,true,false,false,Cell(0,0),0);
        unknown_slot220(0);
        if (trial_cell!=unknown_approach_none_865f00) unknown_slot260(&Map[trial_cell],1);
        else unknown_slot260(0,1);
    }
    }
    }
}
