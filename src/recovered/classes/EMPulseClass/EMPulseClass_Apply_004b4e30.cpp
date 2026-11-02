#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/empulse_class.hpp"
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/building.hpp"
#include "shared/building_type.hpp"
#include "shared/unit.hpp"
#include "shared/unit_type.hpp"
#include "shared/aircraft.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/random.hpp"
#include "shared/unknown_vector3.hpp"
// Existing full map and shared object interfaces; no reserved headers edited.
// The source pointer is forwarded to Foot slot224 and then the existing
// TechnoClass::unknown_6d3040(TechnoClass *) (004CD4B0 evidence).
// @ref ?unknown_471660@CellClass@@=00471660
// @ref ?Map@@=008324e0
// @ref ?Has_Cell@MapClass@@=005480b0
// @ref ?unknown_44d6c0@BuildingClass@@=0044d6c0
// @ref ??0UnknownVector3@@=0041b630
// @ref ?Length@UnknownVector3@@=0041b780
// @ref ?Aircraft@@=00a40398
// @ref ?unknown_id_source_a3d290@@=00a3d290

inline CoordStruct EMPulse_Cell_Center(Cell const &cell)
{
    return CoordStruct(cell.X*256+128,cell.Y*256+128,0);
}
inline UnknownVector3 EMPulse_Offset(CoordStruct const &position, CoordStruct const &center)
{
    return UnknownVector3(position.X-center.X,position.Y-center.Y,position.Z-center.Z);
}

void EMPulseClass::Apply_004B4E30(TechnoClass *source)
{
    Cell cell;
    if (CreatedFrame + Duration > Frame) {
        int radiusSquared = Radius * Radius;
        for (int index=0; index<Aircraft.Count(); ++index) {
            AircraftClass *aircraft=Aircraft[index];
            if (aircraft->unknown_74 && !aircraft->unknown_76 && !aircraft->unknown_slot21() && aircraft->Strength>0) {
                UnknownVector3 delta;
                delta=EMPulse_Offset(aircraft->Center_Coord(),EMPulse_Cell_Center(Position));
                if (delta.Length() < Radius*256) aircraft->unknown_slot224((int)source);
            }
        }
        for (int y=-Radius; y<=Radius; ++y) {
            for (int x=-Radius; x<=Radius; ++x) {
                cell=Cell((short)(Position.X+x),(short)(Position.Y+y));
                if (cell.X>=0 && cell.X<512 && cell.Y>=0 && cell.Y<512 && Map.Has_Cell(cell)) {
                    int dx=cell.X-Position.X;
                    int dy=cell.Y-Position.Y;
                    if (dy*dy+dx*dx <= radiusSquared) {
                        CellClass *mapCell=&Map[cell];
                        BuildingClass *building=(BuildingClass *)mapCell->unknown_4717b0();
                        if (building) {
                            Cell building_cell=Coord_Cell(building->Center_Coord());
                            if (building_cell==cell && !building->Type->InvisibleInGame) {
                                building->unknown_44d6c0();
                                building->unknown_3fc=Duration;
                                if (building->Type->Radar) building->House->unknown_5669=true;
                            }
                        } else {
                            bool active=false;
                            ObjectClass *object=mapCell->unknown_471660(Point2D(0,0),false,0);
                            if (object && (object->Kind_Of()==1 || object->Kind_Of()==2)) active=object->AbstractFlags.IsFoot;
                            if (active) {
                                FootClass *foot=(FootClass *)object;
                                if (foot->Locomotor && ((foot->Kind_Of()!=1 || !((UnitClass *)foot)->Type->LargeVisceroid)
                                    || !((UnitClass *)foot)->Type->SmallVisceroid)) {
                                    foot->Locomotor.Checked()->Power_Off();
                                    if (foot->Locomotor.Checked()->Is_Moving()) foot->Locomotor.Checked()->Stop_Moving();
                                    foot->unknown_3fc=Duration;
                                    AnimClass *effect=(AnimClass *)operator new(sizeof(AnimClass));
                                    if (effect) {
                                        int delay=unknown_id_source_a3d290->Random()(0,25);
                                        effect=new(effect) AnimClass(Rules->unknown_1438,foot->Center_Coord(),delay,1,0x600,0);
                                    }
                                    if (effect) effect->Attach_To(foot);
                                }
                            }

                        }
                    }
                }
            }
        }
    }
}
