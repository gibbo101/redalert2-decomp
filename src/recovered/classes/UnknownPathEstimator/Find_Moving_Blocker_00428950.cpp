#include "shared/path_estimator.hpp"
#include "shared/foot.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/crt_memory.hpp"
extern int unknown_path_level_scale_84e800;
// @ref ?unknown_path_level_scale_84e800@@=0084e800
ObjectClass *UnknownPathEstimator::Unknown_00428950(Cell const &cell,int level)
{
    CoordStruct destination=Cell_Coord(cell);
    destination.Z=level*unknown_path_level_scale_84e800;
    for(int y=-2;y<3;++y) {
        for(int x=-2;x<3;++x) {
            CellClass &neighbor=Map[Cell(x,y)+cell];
            bool alternate=(neighbor.unknown_140&0x100)!=0 && abs(neighbor.unknown_11b-level)>2;
            FootClass *object=(FootClass*)(alternate?neighbor.AltOccupierPtr:neighbor.OccupierPtr);
            while(object) {
                bool isFoot;
                if(object!=0)isFoot=object->AbstractFlags.IsFoot;
                if(object!=0 && isFoot) {
                    if(object->Locomotor.Checked()->Is_Moving_Here(destination))return object;
                }
                object=(FootClass*)object->unknown_30;
            }
        }
    }
    return 0;
}
