// @ref ?Unknown_00568140@MapClass@@QAE_NABUCoordStruct@@@Z=00568140
// @ref ?Unknown_005683C0@MapClass@@QAE_NABUCoordStruct@@@Z=005683c0
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
#include "shared/fly_locomotion.hpp"
#include "shared/fast_math.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
extern double const unknown_fly_land_speed_7a10f8;
// @ref ?unknown_fly_land_speed_7a10f8@@3NB=007a10f8
// The pointer as Nearing_Target holds it: the query stays out of line here.
struct UnknownFlyNearPtr : UnknownComPtr<IFlyControl,&unknown_uuid_7d80a8> {
    UnknownFlyNearPtr(FootClass * const &other)
    {
        if (other) {
            HRESULT result=Query_From(other);
            if (FAILED(result) && result!=E_NOINTERFACE) {
                _com_issue_error(result);
            }
        }
    }
    bool operator!=(int null_value) const
    {
        if (null_value!=0) _com_issue_error((long)0x80004003);
        return Pointer!=0;
    }
    bool operator==(int null_value) const
    {
        if (null_value!=0) _com_issue_error((long)0x80004003);
        return Pointer==0;
    }
};
inline UnknownFacingDir Fly_Direction_XY_004be720(CoordStruct const &from,CoordStruct const &to)
{
    UnknownFacingDir dir;
    if (from.Equal_XY_004bfb60(to)) dir.Raw=0;
    dir=UnknownFacingDir((unsigned short)(int)((Fast_Atan2(double(from.Y)-to.Y,double(to.X)-from.X)
        -unknown_facing_origin_79b630)*unknown_facing_scale_79b628));
    return dir;
}
inline UnknownFacingDir Fly_Facing_Diff_004be720(UnknownFacingDir const &a,UnknownFacingDir const &b)
{
    return UnknownFacingDir((unsigned short)(a.Raw-b.Raw));
}
inline bool Fly_Is_Complete_Turn(UnknownFacingDir const &self,UnknownFacingDir const &towards,UnknownFacingDir const &by)
{
    UnknownFacingDir diff(Fly_Facing_Diff_004be720(self,towards));
    if (by.Magnitude_At_Least_004bfb30(diff)) {
        return true;
    }
    return false;
}
inline int Fly_Distance_XY_004be720(CoordStruct const &from,CoordStruct const &to)
{
    return (Point2D(from.X,from.Y)-Point2D(to.X,to.Y)).Length();
}
int FlyLocomotionClass::unknown_4be720(bool stage,CoordStruct coord)
{
    LinkedTo->unknown_slot104();
    UnknownFlyNearPtr flyctrl(LinkedTo);
    if (flyctrl!=0 && LinkedTo->unknown_228!=0 && LinkedTo->unknown_254!=0 && flyctrl->Is_Strafe()) {
        stage=false;
    }
    CoordStruct aim=coord;
    ObjectClass *building=Map[Cell(coord)].unknown_4717b0();
    if (building!=0 && !LinkedTo->unknown_slot32()->HunterSeeker) {
        if (!LinkedTo->Is_Radio_Contact((TechnoClass *)building)) {
            FootClass *self=LinkedTo;
            if (self!=0 && self->Kind_Of()==2) {
                AbstractClass *dock=((AircraftClass *)self)->Select_Landing_Destination_004185b0(building);
                if (dock==0) {
                    aim=unknown_coord_865df8;
                } else {
                    aim=dock->Center_Coord();
                }
            }
        } else {
            aim=building->unknown_slot41((int)LinkedTo);
        }
    }
    LinkedTo->unknown_slot110();
    int dist=Fly_Distance_XY_004be720(LinkedTo->Center_Coord(),aim);
    if (flyctrl==0 || !flyctrl->Is_Locked()) {
        UnknownFacingDir dir=UnknownFacingDir(LinkedTo->Center_Coord(),CoordStruct(coord));
        bool turn=true;
        if (flyctrl!=0 && flyctrl->Is_Strafe()) {
            if (Fly_Distance_XY_004be720(LinkedTo->Center_Coord(),coord)<=0x300) {
                if (!Fly_Is_Complete_Turn(dir,LinkedTo->unknown_2e0.Current(),UnknownFacingDir((unsigned short)0x2000))) {
                    turn=false;
                }
            }
        }
        if (turn) {
            LinkedTo->unknown_2e0.Set_Desired(Fly_Direction_XY_004be720(LinkedTo->Center_Coord(),CoordStruct(coord)));
        }
    }
    if (dist<0x100 && stage && !LinkedTo->unknown_slot32()->HunterSeeker) {
        if (LinkedTo->unknown_228!=0 && LinkedTo->unknown_254!=0 && (flyctrl==0 || !flyctrl->Is_Strafe())) {
            if (flyctrl==0 || !flyctrl->Is_Locked()) {
                LinkedTo->unknown_2f8.Set_Desired(LinkedTo->Direction_To(LinkedTo->unknown_228));
            }
        } else {
            UnknownFacingDir land((unsigned short)0);
            if (flyctrl!=0) {
                land=UnknownFacingDir((unsigned short)(flyctrl->Landing_Direction()<<13));
            }
            if (flyctrl==0 || !flyctrl->Is_Locked()) {
                LinkedTo->unknown_2f8.Set_Desired(land);
            }
        }
    } else {
        if (flyctrl==0 || !flyctrl->Is_Locked()) {
            LinkedTo->unknown_2f8.Set_Desired(Fly_Direction_004bddf0(LinkedTo->Center_Coord(),coord));
        }
    }
    if (unknown_5c && dist<0x300) {
        unknown_38=unknown_1c.Z-Map.Unknown_0055A280(unknown_1c);
    } else if (LinkedTo->unknown_slot32()->IsDropship) {
        if (dist>=LinkedTo->unknown_slot32()->SlowdownDistance) {
            unknown_38=LinkedTo->unknown_slot32()->Flight_Level();
        } else {
            float ratio=(float)(dist/LinkedTo->unknown_slot32()->SlowdownDistance);
            unknown_38=(int)(LinkedTo->unknown_slot32()->Flight_Level()*ratio+(1.0f-ratio)*(LinkedTo->unknown_slot32()->Flight_Level()/3));
        }
    } else {
        unknown_38=LinkedTo->unknown_slot32()->Flight_Level();
    }
    if (!LinkedTo->unknown_slot32()->HunterSeeker && unknown_4bf8f0()) {
        if (dist<0x80) {
            if (stage) {
                unknown_40=0.0;
            }
            if (!unknown_5c && unknown_48<unknown_fly_land_speed_7a10f8) {
                unknown_4bf1f0();
            }
        } else if (dist<0x200) {
            if (stage) {
                unknown_40=0.5;
            }
        } else if (dist<0x300 && stage) {
            unknown_40=0.75;
        }
    }
    if (LinkedTo->unknown_77 && !LinkedTo->House->Unknown_004F52B0()) {
        if (Map.Unknown_00568140(Object_Coord(LinkedTo)) || ((*(unsigned int *)unknown_id_source_a3d290&0x1000) && Map.Unknown_005683C0(Object_Coord(LinkedTo)))) {
            LinkedTo->unknown_slot81();
        }
    }
    return dist;
}
