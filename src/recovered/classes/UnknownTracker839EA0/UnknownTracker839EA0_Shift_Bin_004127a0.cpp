// Clamp each shifted spatial axis. Direct macro expressions retain the
// repeated input evaluation present in the independently matched Region_Index.
#include "shared/foot.hpp"
#include "shared/rect.hpp"
#define Tracker_Min(a,b) (((a)<(b)) ? (a) : (b))
#define Tracker_Max(a,b) (((a)>(b)) ? (a) : (b))
int UnknownTracker839EA0::Shift_Bin_004127a0(int index,Point2D offset)
{
    int x=index%20;
    int y=index/20;
    return Tracker_Min(19,Tracker_Max(0,x+offset.X))
        +Tracker_Min(19,Tracker_Max(0,y+offset.Y))*20;
}
