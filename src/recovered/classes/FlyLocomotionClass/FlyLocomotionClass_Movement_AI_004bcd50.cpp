// @ref ??0?$TPoint3D@H@@QAE@HHH@Z=0041b630
// @ref ?unknown_4bf8f0@FlyLocomotionClass@@QAE_NXZ=004bf8f0
// @ref ?Unknown_00413600@UnknownTracker839EA0@@QAEXPAVTechnoClass@@VCell@@1@Z=00413600
// @ref ?Unknown_00413310@UnknownTracker839EA0@@QAEXPAVTechnoClass@@@Z=00413310
// @ref ?Unknown_00547F30@MapClass@@QAE?AVCell@@ABV2@@Z=00547f30
// @ref ?unknown_6d7e20@TechnoClass@@QAEHH@Z=006d7e20
#include "shared/fly_locomotion.hpp"
#include "shared/fast_math.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/techno_type.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/bullet.hpp"
extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;
extern double const unknown_move_angle_scale_79b620;
// The helipad test's views (TibSun BuildingClass::Class, BuildingTypeClass::IsHelipad).
struct UnknownFlyBuildingType {
    char unknown_000[0x1365];
    bool Helipad;                       // +0x1365
};
struct UnknownFlyBuilding {
    char unknown_000[0x418];
    UnknownFlyBuildingType *Type;       // +0x418
};
// The smart pointer built from the linked unit: the query is the row 0x004BFC20.
struct UnknownFlyControlPtr : UnknownComPtr<IFlyControl,&unknown_uuid_7d80a8> {
    UnknownFlyControlPtr(FootClass * const &other)
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
};
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
inline int Fly_Land_004bcd50(CellClass const &cell)
{
    return cell.unknown_ec;
}
inline int Fly_Distance_004bcd50(CoordStruct const &from,CoordStruct const &to)
{
    CoordStruct difference=from-to;
    double x=difference.X;
    double y=difference.Y;
    return (int)Fast_Sqrt(x*x+y*y);
}
inline UnknownFacingDir Fly_Direction_004bcd50(CoordStruct const &from,CoordStruct const &to)
{
    return UnknownFacingDir((unsigned short)(int)((Fast_Atan2(double(from.Y)-to.Y,double(to.X)-from.X)
        -unknown_facing_origin_79b630)*unknown_facing_scale_79b628));
}
inline double Fly_As_Radian_004bcd50(UnknownFacingDir const &dir)
{
    return ((short)dir.Raw-0x3fff)*unknown_move_angle_scale_79b620;
}
inline CoordStruct Fly_Move_Coord_004bcd50(CoordStruct const &start,UnknownFacingDir const &dir,int distance)
{
    double radians=Fly_As_Radian_004bcd50(dir);
    return CoordStruct((int)(double(start.X)+Fast_Cos(radians)*double(distance)),
        (int)(double(start.Y)-Fast_Sin(radians)*double(distance)),start.Z);
}
void FlyLocomotionClass::unknown_4bcd50()
{
    Cell here=LinkedTo->unknown_slot104();
    if (here!=LinkedTo->unknown_458 && Is_Moving_Now()) {
        unknown_tracker_839ea0.Unknown_00413600(LinkedTo,LinkedTo->unknown_458,here);
    }
    if (LinkedTo->unknown_slot91()==7 && unknown_5c) {
        unknown_5c=false;
    }
    CoordStruct coord;
    if ((!Is_Powered() || LinkedTo->Strength==0) && LinkedTo->unknown_slot108()!=0) {
        if (LinkedTo->Strength==0) {
            unknown_58+=1;
        } else {
            unknown_58+=3;
        }
        coord=Object_Coord(LinkedTo);
        CoordStruct oldcoord=coord;
        coord.Z-=unknown_58;
        Map.Unknown_0055A280(coord);
        Map[coord];
        if (Map.Unknown_0054AAB0(Cell(coord))) {
            Map.Remove(LinkedTo);
            LinkedTo->unknown_slot71(0);
            LinkedTo->unknown_slot103(coord);
            LinkedTo->unknown_slot71(1);
            Map.Submit(LinkedTo);
        }
        if (LinkedTo->unknown_slot108()<=0) {
            unknown_tracker_839ea0.Unknown_00413310(LinkedTo);
            LinkedTo->unknown_slot109(0);
            int damage=LinkedTo->Strength;
            if (damage==0) {
                Cell cell=Cell(coord);
                LinkedTo->unknown_6d7e20(0);
                int sound;
                if (Map[cell].unknown_ec!=2) {
                    sound=LinkedTo->unknown_slot32()->ImpactLandSound;
                    if (sound==-1) sound=Rules->ImpactLandSound;
                } else {
                    sound=LinkedTo->unknown_slot32()->ImpactWaterSound;
                    if (sound==-1) sound=Rules->ImpactWaterSound;
                }
                if (sound!=-1) {
                    Voc_Play_At(sound,Object_Coord(LinkedTo),0);
                }
                LinkedTo->unknown_slot60();
                return;
            }
            LinkedTo->unknown_slot86(&LinkedTo->Strength,0,Rules->unknown_c74,0,true,1);
            Cell cell=Cell(coord);
            new AnimClass(Select_Damage_Anim(damage,Rules->unknown_c74,Fly_Land_004bcd50(Map[cell]),&oldcoord),coord,0,1,0x2600,Unknown_0047FCC0(coord));
            Unknown_0047F600(coord,damage,Rules->unknown_c74,0,0);
            Unknown_0047E2C0(coord,damage,0,Rules->unknown_c74,1);
            return;
        }
    } else {
        if (LinkedTo->Strength>0 && LinkedTo->unknown_494!=0 && LinkedTo->unknown_slot91()==5 && LinkedTo->MissionQueue==-1 && !unknown_18) {
            LinkedTo->unknown_slot116(2,false);
        }
    }
    if (!Is_Moving()) {
        return;
    }
    TechnoTypeClass *ttype=LinkedTo->unknown_slot32();
    bool is_dropship=ttype->IsDropship;
    bool is_hunter_seeker=ttype->HunterSeeker;
    LinkedTo->unknown_slot71(0);
    coord=Object_Coord(LinkedTo);
    Physics_004bdc20(coord,LinkedTo->unknown_2e0.Current());
    if (!Map.Unknown_0054AAB0(Cell(coord)) && LinkedTo->unknown_slot282()) {
        Cell cell=Cell(coord);
        Cell edge=Map.Unknown_00547F30(cell);
        if (edge.X<Map.unknown_128/2) {
            coord.X+=128;
        } else {
            coord.X-=128;
        }
        if (Map.Unknown_0054AAB0(Cell(coord))) {
            LinkedTo->unknown_slot103(coord);
        } else {
            coord=Coord_Scatter(coord,64,false);
            if (Map.Unknown_0054AAB0(Cell(coord))) {
                LinkedTo->unknown_slot103(coord);
            }
        }
    } else {
        LinkedTo->unknown_slot103(coord);
    }
    int bridge_height=0;
    int current_height=LinkedTo->unknown_slot108();
    if (!LinkedTo->unknown_79 && current_height>=unknown_geometry_j && (Loco_Cell(Object_Coord(LinkedTo))->Flags&0x100)) {
        current_height-=unknown_geometry_j;
        bridge_height=unknown_geometry_j;
    }
    CoordStruct dest=unknown_1c;
    int dist=Fly_Distance_004bcd50(dest,Object_Coord(LinkedTo));
    if (current_height<unknown_38 && LinkedTo->Strength>0) {
        bool is_loaded=false;
        UnknownFlyControlPtr flyctrl(LinkedTo);
        if (flyctrl!=0) {
            is_loaded=flyctrl->Is_Loaded()!=0;
        }
        if (is_dropship) {
            int climb=unknown_38-current_height;
            if (climb>16) climb=16;
            LinkedTo->unknown_slot109(bridge_height+current_height+climb);
        } else if (is_hunter_seeker) {
            if (unknown_50) {
                int climb=unknown_38-current_height;
                climb=MIN(Rules->HunterSeekerEmergeSpeed,climb);
                LinkedTo->unknown_slot109(bridge_height+current_height+climb);
            } else {
                int climb=unknown_38-current_height;
                climb=MIN(Rules->HunterSeekerAscentSpeed,climb);
                LinkedTo->unknown_slot109(bridge_height+current_height+climb);
            }
        } else {
            int climb=unknown_38-current_height;
            climb=MIN(is_loaded?10:20,climb);
            LinkedTo->unknown_slot109(bridge_height+current_height+climb);
        }
        LinkedTo->unknown_79=false;
    }
    if (current_height>unknown_38 || LinkedTo->Strength==0) {
        int descent=current_height-unknown_38;
        if (is_dropship) {
            if (unknown_51) {
                int limit=descent/20+10;
                descent=MIN(MIN(limit,48),descent);
            } else if (unknown_38==LinkedTo->unknown_slot32()->Flight_Level()) {
                if (current_height>16) descent=16;
                else descent=current_height;
            } else {
                if (current_height>6) descent=6;
                else descent=current_height;
            }
        } else if (is_hunter_seeker) {
            descent=MIN(Rules->HunterSeekerDescentSpeed,current_height);
        } else {
            if (descent/20<descent) {
                descent/=20;
            }
            if (descent>=50) {
                descent=50;
            } else if (descent<=20) {
                descent=20;
            }
        }
        current_height-=descent;
        if (LinkedTo->Strength==0 && current_height<=1) {
            current_height=1;
        } else if (current_height<0) {
            current_height=0;
        }
        if (current_height==0 && bridge_height>0) {
            LinkedTo->unknown_79=true;
            bridge_height=0;
        }
        LinkedTo->unknown_slot109(bridge_height+current_height);
        if (LinkedTo->Strength>0 && unknown_1c!=unknown_coord_865df8) {
            if (LinkedTo->unknown_slot91()!=7 || LinkedTo->unknown_494==0
                || LinkedTo->unknown_494->Kind_Of()!=6
                || !((UnknownFlyBuilding *)LinkedTo->unknown_494)->Type->Helipad) {
                Cell target=Cell(unknown_1c);
                CoordStruct center(target.X*256+128,target.Y*256+128,0);
                CoordStruct current=Object_Coord(LinkedTo);
                LinkedTo->unknown_slot103(Fly_Move_Coord_004bcd50(current,Fly_Direction_004bcd50(current,center),5));
            }
        }
    }
    if (LinkedTo->Strength>0 && unknown_4bf3c0() && unknown_1c!=unknown_coord_865df8) {
        UnknownFlyControlPtr flyctrl(LinkedTo);
        if (!unknown_4bf8f0()) {
            unknown_40=1.0;
        } else if (LinkedTo->unknown_slot32()->HunterSeeker) {
            if (!unknown_50 && LinkedTo->unknown_228!=0) {
                unknown_40=1.0;
            } else {
                unknown_40=0.0;
            }
        } else {
            double speed=(double)dist/(double)ttype->SlowdownDistance;
            if (1.0<speed) {
                speed=1.0;
            }
            unknown_40=speed;
            if (unknown_40<0.1) {
                if (dist>85) {
                    unknown_40=0.1;
                } else {
                    unknown_40=0.0;
                    unknown_48*=0.5;
                }
            }
            if ((double)dist<unknown_48) {
                unknown_48=(double)dist;
            }
            if (unknown_40==0.0 && unknown_48==0.0 && dist>0) {
                unknown_48=0.05;
            }
        }
    }
    if (is_dropship && LinkedTo->Strength>0 && unknown_48>0.0 && !unknown_50) {
        int slowdown=ttype->SlowdownDistance;
        if (dist<slowdown) {
            double factor=1.0-((double)dist-((double)slowdown*0.6))/((double)slowdown*0.4);
            LinkedTo->unknown_240=MIN(LinkedTo->unknown_slot32()->PitchAngle,factor*LinkedTo->unknown_slot32()->PitchAngle);
        }
    }
    if (!unknown_5c && LinkedTo->Strength>0 && !unknown_51 && !unknown_50) {
        if (Cell(unknown_1c)==LinkedTo->unknown_slot104() && unknown_40==0.0 && (LinkedTo->unknown_228==0 || LinkedTo->unknown_254==0)) {
            unknown_4bf1f0();
        }
    }
    if (LinkedTo->Strength>0) {
        if (unknown_48<unknown_40) {
            unknown_48=MIN(unknown_48+0.1,unknown_40);
        } else if (unknown_48>unknown_40) {
            unknown_48=MAX(unknown_48-0.1,unknown_40);
        }
    }
    LinkedTo->unknown_slot71(1);
}
