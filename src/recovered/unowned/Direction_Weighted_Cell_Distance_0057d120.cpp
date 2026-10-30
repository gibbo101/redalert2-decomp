// Free stdcall and operation name are hypotheses; original consumes24 stack bytes.
#include "shared/coord.hpp"
#include "shared/unknown_static_rect.hpp"
#include "shared/fast_math.hpp"
#include "shared/crt_memory.hpp"
extern float const unknown_zero_79a738;
// @ref ?unknown_zero_79a738@@=0079a738
// @ref _unknown_static_rect=00a70080
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
double __stdcall Direction_Weighted_Cell_Distance_0057d120(Cell const *from,Cell const *to,Rect const *area,Cell const *origin,float xWeight,float yWeight)
{
    if(*area!=unknown_static_rect) {
        int x=abs((((int)to->X-(int)to->Y)>>1)-(((int)origin->X-(int)origin->Y)>>1));
        int y=abs((((int)to->X+(int)to->Y)>>1)-(((int)origin->X+(int)origin->Y)>>1));
        if(x==0 && y==0)return unknown_zero_79a738;
        int squared=(int)((unsigned)y*(unsigned)y+(unsigned)x*(unsigned)x);
        double length=Fast_Sqrt((double)squared);
        double xDirection=(double)x/length;
        double yDirection=(double)y/length;
        int dx=(int)from->X-(int)to->X;
        int dy=(int)from->Y-(int)to->Y;
        double distance=abs(dx)>abs(dy)?abs(dx):abs(dy);
        return (xWeight*xDirection+yWeight*yDirection)*distance;
    }
    int dx=(int)from->X-(int)to->X;
    int dy=(int)from->Y-(int)to->Y;
    return Fast_Sqrt((double)(int)((unsigned)dy*(unsigned)dy+(unsigned)dx*(unsigned)dx));
}
