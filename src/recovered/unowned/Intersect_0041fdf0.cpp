// Clip a draw rectangle to bounds and adjust optional source offsets.
#include "shared/rect.hpp"

Rect __fastcall Intersect(Rect const &bounds,Rect const &draw,int *x,int *y)
{
    Rect bad(0,0,0,0);
    Rect result=draw;
    if(!bounds.Is_Valid() || !draw.Is_Valid()) return bad;
    if(result.X<bounds.X) { result.Width-=bounds.X-result.X; result.X=bounds.X; }
    if(result.Width<1) return bad;
    if(result.Y<bounds.Y) { result.Height-=bounds.Y-result.Y; result.Y=bounds.Y; }
    if(result.Height<1) return bad;
    if(result.X+result.Width>bounds.X+bounds.Width) result.Width-=(result.X+result.Width)-(bounds.X+bounds.Width);
    if(result.Width<1) return bad;
    if(result.Y+result.Height>bounds.Y+bounds.Height) result.Height-=(result.Y+result.Height)-(bounds.Y+bounds.Height);
    if(result.Height<1) return bad;
    if(x) *x-=result.X-draw.X;
    if(y) *y-=result.Y-draw.Y;
    return result;
}
