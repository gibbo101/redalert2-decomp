// Basic_Path004C3000: search for a legal destination and record a path.
#include "shared/foot.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/team.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_vector3.hpp"
#include "shared/crt_memory.hpp"
// @ref _unknown_geometry_k=00865f00
// @ref ?unknown_zone_table_7a1200@@3PAHA=007a1200
// @ref ??0UnknownVector3@@QAE@HHH@Z=0041b630
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
static inline int Path_Length3(UnknownVector3 vector)
{
    double x=vector.X;
    double y=vector.Y;
    double z=vector.Z;
    return (int)unknown_sqrt_4ba410(x*x+y*y+z*z);
}
static inline int Path_Distance3(CoordStruct const &a,CoordStruct const &b)
{
    return Path_Length3(UnknownVector3(a.X-b.X,a.Y-b.Y,a.Z-b.Z));
}
static inline int Path_Length2(CoordStruct const &vector)
{
    return (int)unknown_sqrt_4ba410((double)vector.X*vector.X+(double)vector.Y*vector.Y);
}
template<class T> static inline T Path_Max(T a,T b) { return a>b?a:b; }
template<class T> static inline T Path_Min(T a,T b) { return a<b?a:b; }
bool FootClass::unknown_4c3000(Cell cell,int path_offset,int avoidance)
{
    if(path_offset==0) Path[0]=-1;
    if(!unknown_slot171(CoordStruct(cell.X*256+128,cell.Y*256+128,0))) {
        Path[0]=-1;
        return false;
    }
    int distance=Path_Distance3(Center_Coord(),Cell_Center(cell));
    int close_enough=Team?Team->Unknown_006BE6A0():Rules->unknown_1380;
    int max_distance=0;
    bool train=unknown_slot32()->IsTrain;
    int move=unknown_slot101(&Map[cell],-1,-1,0,true);
    if(move==6 && distance>close_enough && !train) {
        int zone=unknown_zone_table_7a1200[unknown_slot32()->MovementZone];
        bool check=unknown_slot32()->unknown_af5 && Map[cell].unknown_47c200();
        Cell nearby=Map.Unknown_005502E0(cell,unknown_slot32()->SpeedType,
            Map.Zone(unknown_slot104(),zone,unknown_79),zone,unknown_79,Point2D(1,1),false,true,check,true,unknown_slot104(),0);
        int dest_y=cell.Y;
        int nearby_y=nearby.Y;
        int dest_x=cell.X;
        max_distance=Path_Max(abs(nearby.X-dest_x),abs(nearby_y-dest_y));
        if(nearby!=unknown_geometry_k && Path_Length2(CoordStruct(dest_x*256+128,dest_y*256+128,0)-CoordStruct(nearby.X*256+128,nearby_y*256+128,0))<distance) {
            int walk=unknown_path_estimator_8315c8.Unknown_0042AA30(nearby,cell,this,
                (Map[nearby].unknown_140&0x100)!=0,(Map[cell].unknown_140&0x100)!=0,check?0:-1);
            if(walk<=max_distance+6) {
                unknown_slot260(&Map[nearby],1);
                cell=nearby;
            }
        }
    }
    if(move==7 && !train) {
        if(Map[cell].unknown_4717b0()!=0) {
            int zone=unknown_zone_table_7a1200[unknown_slot32()->MovementZone];
            bool check=unknown_slot32()->unknown_af5 && Map[cell].unknown_47c200();
            Cell nearby=Map.Unknown_005502E0(cell,unknown_slot32()->SpeedType,
                Map.Zone(unknown_slot104(),zone,unknown_79),zone,unknown_79,Point2D(1,1),false,true,check,true,unknown_slot104(),0);
            unknown_slot260(&Map[nearby],1);
            cell=nearby;
        }
    }
    unknown_slot71(0);
    if(path_offset==0) Path[0]=-1;
    bool found=false;
    UnknownPathType saved_path;
    int work_path[2000];
    UnknownPathType *path=Unknown_004BB350(&cell,work_path,2000,0,path_offset,avoidance);
    if(path && path->Cost) {
        memcpy(&saved_path,path,sizeof(saved_path));
        found=true;
    }
    if(found) {
        unknown_slot305((int)&saved_path);
        memcpy(&Path[path_offset],work_path,Path_Min(path->Length,24-path_offset)*sizeof(Path[0]));
    }
    unknown_slot71(1);
    unknown_530=0;
    if(Kind_Of()==1 && Path[0]!=-1) {
        UnitClass *unit=static_cast<UnitClass *>(this);
        FootClass *follower=unit->unknown_5b0;
        int length=0;
        if(path) length=path->Length-2;
        Cell next_cell=cell;
        if(follower && !unit->unknown_5b8) {
            while(follower) {
                CellClass *current=&Map[next_cell];
                next_cell=current->Adjacent_Cell((work_path[length]+4)%8).MapCoords;
                AbstractClass *destination=follower->unknown_494;
                if(!destination || Coord_Cell(destination->unknown_slot19(0))!=next_cell) {
                    follower->unknown_slot116(2,false);
                    follower->unknown_slot260(&Map[next_cell],1);
                    follower->unknown_4c3000(next_cell,0,0);
                }
                follower=static_cast<UnitClass *>(follower)->unknown_5b0;
            }
        }
    }
    if(path) {
        unknown_450=unknown_slot104();
        return true;
    }
    unknown_530=(int)(Rules->unknown_13c8*900.0);
    unknown_slot291();
    CoordStruct coord=Coord;
    Cell current=Coord_Cell(coord);
    max_distance=Path_Max(abs(current.X-cell.X),abs(current.Y-cell.Y));
    if(max_distance>1 || (!unknown_79 && (Map[cell].unknown_140&0x100))) {
        if(Team) {
            Locomotor.Checked()->Lock();
            Team->Unknown_006B8FB0(this,-1,false);
            Locomotor.Checked()->Unlock();
        }
        unknown_slot260(0,1);
        unknown_slot220(0);
        if(!House->Unknown_004F52F0()) {
            unknown_slot116(11,false);
            if(unknown_game_mode_a3d298!=0) {
                Cell guard=House->Unknown_004EB270(this);
                if(guard!=unknown_geometry_k) unknown_slot260(&Map[guard],1);
            }
        } else unknown_slot116(5,false);
    }
    return false;
}
