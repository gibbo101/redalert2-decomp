// @ref ??0UnknownVector3@@QAE@HHH@Z=0041b630
// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ?Frame@@3HA=00a40d2c
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Reduce_Path_Length_004fdfd0@HoverLocomotionClass@@QAE_NXZ=004fdfd0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?Unknown_0055A660@MapClass@@QAE_NABVCell@@_N@Z=0055a660
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref ?unknown_471660@CellClass@@QBEPAVObjectClass@@ABUPoint2D@@_NPAV2@@Z=00471660
// @ref ?unknown_476920@CellClass@@QAEXPBX_N11@Z=00476920
// @ref ?unknown_4c3000@FootClass@@QAE_NVCell@@HH@Z=004c3000
// @ref ?unknown_4c8d60@FootClass@@QAE_NXZ=004c8d60
// @ref ?unknown_5d47d0@ObjectClass@@QAEHXZ=005d47d0
// @ref ?unknown_coord_a41080@@3UCoordStruct@@A=00a41080
// @ref ?unknown_func_6baa30@TeamClass@@QAEXXZ=006baa30
// @ref __ftol=0077f110
// @ref __real@8@4008e100000000000000=0079b608
// @ref _unknown_geometry_g=00a410b8
#include "shared/hover_locomotion.hpp"
#include "shared/adjacent_cell.hpp"
#include "shared/cell_class.hpp"
#include "shared/house.hpp"
#include "shared/team.hpp"
#include "shared/rules.hpp"
#include "shared/crt_memory.hpp"
#include "shared/sound_play.hpp"
#include "shared/unknown_vector3.hpp"
inline int Hover_Close_Distance_004fe0f0(CoordStruct const &from,CoordStruct const &to)
{
    CoordStruct difference=from-to;
    return (int)Fast_Sqrt((double)difference.X*difference.X+(double)difference.Z*difference.Z+(double)difference.Y*difference.Y);
}
inline int Hover_Foot_Distance_004fe0f0(CoordStruct const &from,CoordStruct const &to)
{
    UnknownVector3 difference=UnknownVector3(from.X-to.X,from.Y-to.Y,from.Z-to.Z);
    return (int)Fast_Sqrt((double)difference.Z*difference.Z+(double)difference.Y*difference.Y+(double)difference.X*difference.X);
}
void HoverLocomotionClass::Start_Of_Move_004fe0f0(int num)
{
    Reduce_Path_Length_004fdfd0();
    int facing=LinkedTo->Path[0];
    if (unknown_18!=unknown_coord_a41080) {
        if (LinkedTo->unknown_slot104()==Coord_Cell(unknown_18) && abs(LinkedTo->unknown_slot19(0).Z-unknown_18.Z)<2*unknown_geometry_g) {
            Stop_Moving();
            LinkedTo->unknown_slot260(0,1);
            return;
        }
    }
    if (facing!=-1) return;
    if (unknown_18==unknown_coord_a41080) return;
    if (LinkedTo->unknown_slot104()==Coord_Cell(unknown_18) && abs(LinkedTo->unknown_slot19(0).Z-unknown_18.Z)<=2*unknown_geometry_g) return;
    if (LinkedTo->unknown_530!=0) return;
    if (!LinkedTo->unknown_4c3000(Coord_Cell(unknown_18),0,num)) {
        LinkedTo->unknown_530=CDTimerClass<FrameTimerClass>((int)(Rules->unknown_13c8*900));
        if (!LinkedTo->unknown_slot171(unknown_18)) {
            LinkedTo->unknown_slot260(0,1);
            return;
        }
        if (!LinkedTo->unknown_4c8d60() && Hover_Foot_Distance_004fe0f0(LinkedTo->Center_Coord(),unknown_18)<Rules->unknown_1380 && (LinkedTo->unknown_slot91()==2 || LinkedTo->unknown_slot91()==11)) {
            LinkedTo->unknown_slot260(0,1);
            if (!LinkedTo->unknown_7d) return;
        } else {
            if (LinkedTo->unknown_53c>0) --LinkedTo->unknown_53c;
            else {
                LinkedTo->unknown_slot260(0,1);
                if (!LinkedTo->unknown_7d) return;
                if (LinkedTo->unknown_57a) Voc_Play(Rules->unknown_620,1.0f,0x2000,0);
                LinkedTo->unknown_57a=false;
            }
        }
        if (!Is_Moving() && LinkedTo->unknown_228 && !LinkedTo->unknown_slot213(LinkedTo->unknown_228)) {
            LinkedTo->unknown_578=true;
            if (LinkedTo->Team) LinkedTo->Team->unknown_func_6baa30();
            LinkedTo->unknown_slot220(0);
        }
        if (unknown_24!=unknown_coord_a41080) {
            LinkedTo->unknown_slot59(unknown_24);
            unknown_24=unknown_coord_a41080;
        }
        Stop_Moving();
        return;
    } else {
    LinkedTo->unknown_530=CDTimerClass<FrameTimerClass>((int)(Rules->unknown_13c8*900));
    Cell cell=Coord_Cell(LinkedTo->Center_Coord())+AdjacentCell[LinkedTo->Path[0]&7];
    if (Map.Unknown_0055A660(cell,true)) {
        int ok=LinkedTo->unknown_slot101(&Map[cell],LinkedTo->Path[0],LinkedTo->unknown_5d47d0(),0,true);
        if (ok==6) {
            CellClass *cellptr=&Map[cell];
            TechnoClass *blockage=static_cast<TechnoClass *>(cellptr->unknown_471660(Point2D(0,0),Object_Coord(LinkedTo).Z>Map.Unknown_0055A280(CoordStruct(cell.X*256+128,cell.Y*256+128,0))+3*unknown_geometry_g,0));
            if (blockage && LinkedTo->House->Is_Ally(blockage)) {
                if (Hover_Close_Distance_004fe0f0(LinkedTo->Center_Coord(),unknown_18)<Rules->unknown_1380 && !LinkedTo->In_Radio_Contact() && abs(unknown_18.Z-Object_Coord(LinkedTo).Z)<2*unknown_geometry_g && Map[Object_Coord(LinkedTo)].unknown_ec!=10) {
                    Stop_Moving();
                    LinkedTo->unknown_slot260(0,1);
                    return;
                } else {
                    bool bridge=(cellptr->unknown_140&0x100) && abs(Object_Coord(LinkedTo).Z/unknown_geometry_g-cellptr->unknown_11b)>2;
                    cellptr->unknown_476920(&unknown_coord_a41080,true,true,bridge);
                }
            }
        }
    }
    LinkedTo->unknown_53c=10;
    }
}
