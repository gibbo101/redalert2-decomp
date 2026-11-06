// @ref ??0?$TPoint3D@H@@QAE@HHH@Z=0041b630
// @ref ??0Cell@@QAE@HH@Z=0042ad30
// int __fastcall Unknown_00660b60(ObjectClass *object, Cell &center, int distance) (0x00660B60)
// Places an object near a cell, scanning eight directions at increasing radii.
// Clip_Move/Clip_Scatter are file-local operation-boundary hypotheses from the reference twin.
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/cell_class.hpp"
#include "shared/object.hpp"
#include "shared/dir_type.hpp"

static Cell const Placement_Clip_Move(Cell const &center,FacingType direction,int distance)
{
    int x=center.X;
    int y=center.Y;
    int left=Map.unknown_120;
    int right=left+Map.unknown_128-1;
    int top=Map.unknown_124;
    int bottom=top+Map.unknown_12c-1;
    switch(direction) {
    case 0: y-=distance; break;
    case 1: x+=distance; y-=distance; break;
    case 2: x+=distance; break;
    case 3: x+=distance; y+=distance; break;
    case 4: y+=distance; break;
    case 5: x-=distance; y+=distance; break;
    case 6: x-=distance; break;
    case 7: x-=distance; y-=distance; break;
    }
    if(x>right) x=right;
    if(x<left) x=left;
    if(y>bottom) y=bottom;
    if(y<top) y=top;
    return Cell(x,y);
}
static Cell const Placement_Clip_Scatter(Cell const &center,int radius)
{
    int x=center.X;
    int y=center.Y;
    int left=Map.unknown_120;
    int right=left+Map.unknown_128-1;
    int top=Map.unknown_124;
    int bottom=top+Map.unknown_12c-1;
    int xdistance=Random_Pick(0,radius);
    if(Random_Pick(0,99)<50) {
        x+=xdistance;
        if(x>right) x=right;
    } else {
        x-=xdistance;
        if(x<left) x=left;
    }
    int ydistance=Random_Pick(0,radius);
    if(Random_Pick(0,99)<50) {
        y+=ydistance;
        if(y>bottom) y=bottom;
    } else {
        y-=ydistance;
        if(y<top) y=top;
    }
    return Cell(x,y);
}
int __fastcall Unknown_00660b60(ObjectClass *object,Cell &center,int distance)
{
    if(Map.Unknown_0054AAB0(center)) {
        ObjectClass *occupant=Map[center].unknown_471660(Point2D(0,0),false,0);
        if(!occupant || (occupant->Kind_Of()==15 && object->Kind_Of()==15)) {
            if(object->unknown_slot53(&UnknownCoord434820(center,Map.Unknown_0055A280(UnknownCoord434820(center))),0)) return 1;
        }
    }
    int pass;
    FacingType count;
    int skip;
    ObjectClass *occupant;
    Cell target;
    int range=distance;
    FacingType direction;
    for(;range<32;++range) {
        direction=Random_Pick(FACING_N,FACING_NW);
        for(pass=0;pass<2;++pass) {
            for(count=FACING_N;count<=FACING_NW;count=FacingType(count+1)) {
                skip=0;
                target=Placement_Clip_Move(center,direction,range);
                if(pass>0) target=Placement_Clip_Scatter(target,1);
                if(target.X==center.X && target.Y==center.Y) skip=1;
                if(!skip) {
                    occupant=Map[target].unknown_471660(Point2D(0,0),false,0);
                    if(!occupant || (occupant->Kind_Of()==15 && object->Kind_Of()==15)) {
                        if(object->unknown_slot53(&UnknownCoord434820(target,Map.Unknown_0055A280(UnknownCoord434820(target))),0)) return 1;
                    }
                }
                direction=FacingType(direction+1);
                if(direction>FACING_NW) direction=FACING_N;
            }
        }
    }
    return 0;
}
