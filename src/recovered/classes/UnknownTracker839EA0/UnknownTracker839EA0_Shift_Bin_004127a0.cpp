// Shift a bin index by an offset, clamping each axis to the 20 by 20 grid
// (the column and row locals are clamped in place).
#include "shared/foot.hpp"
#include "shared/rect.hpp"
#define Tracker_Min(a,b) (((a)<(b)) ? (a) : (b))
#define Tracker_Max(a,b) (((a)>(b)) ? (a) : (b))
int UnknownTracker839EA0::Shift_Bin_004127a0(int index,Point2D offset)
{
    int x=index%20;
    int y=index/20;
    x=Tracker_Min(19,Tracker_Max(0,x+offset.X));
    y=Tracker_Min(19,Tracker_Max(0,y+offset.Y));
    return x+y*20;
}
