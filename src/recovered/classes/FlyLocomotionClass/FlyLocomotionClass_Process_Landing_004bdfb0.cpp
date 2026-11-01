// @ref ??0AnimClass@@QAE@PBVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref ??2@YAPAXI@Z=00782017
// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ??_C@_08EHBM@DROPLAND?$AA@=007d80c4
// @ref ??_C@_08LABN@CARYLAND?$AA@=007d80b8
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?AnimTypes@@3V?$TypeList@PAVAnimTypeClass@@@@A=008661e0
// @ref ?Contact@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e10
// @ref ?From_Name@AnimTypeClass@@SIHPBD@Z=00425640
// @ref ?Is_Radio_Contact@RadioClass@@QBE_NPAVTechnoClass@@@Z=00636e30
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Release_Held@?$UnknownComPtr@UUnknownFlyInterface@@$1?unknown_uuid_7d80a8@@3UGUID@@B@@QAEXXZ=004bfbc0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Take_Off_004bf0d0@FlyLocomotionClass@@QAEXXZ=004bf0d0
// @ref ?Unknown_00413310@UnknownTracker839EA0@@QAEXPAVTechnoClass@@@Z=00413310
// @ref ?Unknown_005502E0@MapClass@@QAE?AVCell@@ABV2@HHH_NUPoint2D@@11110H@Z=005502e0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?Voc_Play_At@@YIPAUAudioEvent@@HABUCoordStruct@@PAUAudioEventHandle@@@Z=00713e60
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
// @ref ?unknown_fly_pitch_floor_79b610@@3NB=0079b610
// @ref ?unknown_fly_pitch_rate_7a0ff8@@3NB=007a0ff8
// @ref ?unknown_fly_pitch_zero_79a738@@3MB=0079a738
// @ref ?unknown_tracker_839ea0@@3UUnknownTracker839EA0@@A=00839ea0
// @ref _unknown_geometry_j=00865e20
// @ref _unknown_geometry_k=00865dd8
// @ref _unknown_geometry_l=00865df8
// @ref _unknown_uuid_7d80a8=007d80a8
#include "shared/fly_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
extern float const unknown_fly_pitch_zero_79a738;
extern double const unknown_fly_pitch_floor_79b610;
extern double const unknown_fly_pitch_rate_7a0ff8;
inline CoordStruct Fly_Cell_Coord_004bdfb0(Cell const &cell)
{
    CoordStruct coord(cell.X*256+128,cell.Y*256+128,0);
    return coord;
}
// Cell step through the real TPoint2D<short> sum (TibSun inline.h Adjacent_Cell).
inline Cell Fly_Adjacent_Cell_004bdfb0(Cell const &cell,int facing)
{
    return cell+AdjacentCell[facing&7];
}
bool FlyLocomotionClass::Process_Landing_004bdfb0()
{
    if (!unknown_51) return true;
    bool has_landed=false;
    int height=LinkedTo->unknown_slot108();
    if ((Loco_Cell(Object_Coord(LinkedTo))->Flags & 0x100) && height>=unknown_geometry_j)
        height-=unknown_geometry_j;
    if (LinkedTo->unknown_slot32()->IsDropship) {
      if (height==0 && LinkedTo->unknown_240>unknown_fly_pitch_zero_79a738) {
        double pitch=LinkedTo->unknown_240-unknown_fly_pitch_rate_7a0ff8;
        if (unknown_fly_pitch_floor_79b610>pitch) pitch=unknown_fly_pitch_floor_79b610;
        LinkedTo->unknown_240=(float)pitch;
      }
      unknown_40=0;
    } else {
      unknown_40=0;
    }
    int landing_altitude=0;
    UnknownFlyPtr flyctrl(LinkedTo);
    if (flyctrl) landing_altitude=flyctrl->unknown_slot3();
    CellClass *destination=&Map[unknown_1c];
    if ((unknown_18 && !LinkedTo->Is_Radio_Contact((TechnoClass *)destination->unknown_4717b0())) ||
        (!unknown_18 && LinkedTo->unknown_slot101(destination,-1,-1,0,true)!=0)) {
        Take_Off_004bf0d0();
        Cell const &pos=Cell(Object_Coord(LinkedTo));
        Cell nearby=Map.Unknown_005502E0(pos,1,-1,9,false,Point2D(1,1),false,false,false,true,Cell(0,0),0);
        if (nearby!=unknown_geometry_k) {
            CoordStruct next=Fly_Cell_Coord_004bdfb0(nearby);
            next.Z=Map.Unknown_0055A280(next);
            if ((reinterpret_cast<UnknownLocoCell *>(&Map[nearby])->Flags&0x100)) next.Z+=unknown_geometry_j;
            Move_To(CoordStruct(next.X,next.Y,next.Z));
        } else {
            LinkedTo->unknown_slot86(&LinkedTo->Strength,0,Rules->unknown_c74,0,true,1);
            unknown_1c=unknown_geometry_l;
            return false;
        }
    }
    if (!unknown_52 && height<300) {
        CoordStruct coord=Object_Coord(LinkedTo);
        coord.Z=Map.Unknown_0055A280(coord);
        unknown_52=true;
        if (LinkedTo->unknown_slot32()->IsDropship) {
            new AnimClass(AnimTypes[AnimTypeClass::From_Name("DROPLAND")],coord,0,1,0x600,0);
        } else if (LinkedTo->Kind_Of()==2 && static_cast<AircraftClass *>(LinkedTo)->Type->Carryall) {
            new AnimClass(AnimTypes[AnimTypeClass::From_Name("CARYLAND")],coord,0,1,0x600,0);
        }
        if (LinkedTo->Strength>0) Voc_Play_At(LinkedTo->unknown_slot32()->AuxSound2,coord,0);
    }
    if (height<=landing_altitude && LinkedTo->unknown_240<=unknown_fly_pitch_zero_79a738) {
        CoordStruct coord=Object_Coord(LinkedTo);
        if ((Loco_Cell(coord)->Flags&0x100) && coord.Z>=Map.Unknown_0055A280(coord)+unknown_geometry_j)
            LinkedTo->unknown_79=true;
        LinkedTo->unknown_slot109(landing_altitude);
        unknown_51=false;
        unknown_50=false;
        has_landed=true;
        unknown_tracker_839ea0.Unknown_00413310(LinkedTo);
        LinkedTo->unknown_slot306(0);
        unknown_48=0;
        unknown_40=0;
        if (LinkedTo->unknown_454!=Cell(0,0)) {
            for (int facing=0;facing<8;facing++) {
                Cell adjacent=Fly_Adjacent_Cell_004bdfb0(LinkedTo->unknown_454,facing);
                CellClass *cell=&Map[adjacent];
                cell->unknown_122--;
            }
            LinkedTo->unknown_454=LinkedTo->unknown_slot104();
            for (facing=0;facing<8;facing++) {
                Cell adjacent=Fly_Adjacent_Cell_004bdfb0(LinkedTo->unknown_454,facing);
                CellClass *cell=&Map[adjacent];
                cell->unknown_122++;
            }
        } else {
            LinkedTo->unknown_454=LinkedTo->unknown_slot104();
            for (int facing=0;facing<8;facing++) {
                Cell adjacent=Fly_Adjacent_Cell_004bdfb0(LinkedTo->unknown_454,facing);
                CellClass *cell=&Map[adjacent];
                cell->unknown_122++;
            }
        }
        if (Cell(LinkedTo->Center_Coord())==Cell(unknown_1c) || Map[Cell(unknown_1c)].unknown_4717b0()==LinkedTo->Contact(0)) {
            unknown_34=false;
            Move_To(CoordStruct(unknown_geometry_l.X,unknown_geometry_l.Y,unknown_geometry_l.Z));
            LinkedTo->unknown_slot260(0,1);
        }
    }
    return has_landed;
}
