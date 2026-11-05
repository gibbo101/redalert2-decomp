#include "shared/cell.hpp"
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_vector3.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_4706c0@CellClass@@QBEHABUPoint2D@@@Z=004706c0
static CoordStruct Cell_Ground_Center_0047cc10(CellClass const &cell)
{
    Cell center_cell=cell.MapCoords;
    UnknownVector3 center(center_cell.X*256+128,center_cell.Y*256+128,0);
    center.Z=cell.unknown_4706c0(Point2D(128,128));
    CoordStruct result(center.X,center.Y,center.Z);
    return result;
}

// Remove occupants that cannot remain here, including approaching foot objects.
void CellClass::unknown_47cc10()
{
    ObjectClass *object=OccupierPtr;
    ObjectClass *next=0;
    while(object) {
        next=object->unknown_30;
        if(object->unknown_slot101(this,-1,-1,0,true)==7) {
            int damage=object->Strength;
            object->unknown_slot86(&damage,0,Rules->unknown_c74,0,true,true);
        }
        object=next;
    }
    CoordStruct center=Cell_Ground_Center_0047cc10(*this);
    for(int x=-2;x<3;++x) {
        for(int y=-2;y<3;++y) {
            CellClass *cellptr=&Map[MapCoords+Cell(x,y)];
            if(cellptr!=this) {
                object=cellptr->OccupierPtr;
                while(object) {
                    bool is_foot;
                    if(object) is_foot=object->AbstractFlags.IsFoot;
                    if(object && is_foot) {
                        FootClass *foot=(FootClass*)object;
                        if(foot->Locomotor.Checked()->Is_Moving_Here(center)
                            && foot->unknown_slot101(this,-1,-1,0,true)==7) {
                            int damage=foot->Strength;
                            foot->unknown_slot86(&damage,0,Rules->unknown_c74,0,true,true);
                        }
                    }
                    object=object->unknown_30;
                }
            }
        }
    }
}
