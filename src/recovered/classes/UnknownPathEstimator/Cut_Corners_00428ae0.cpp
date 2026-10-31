#include "shared/path_estimator.hpp"
// @ref ?Unknown_00428CF0@UnknownPathEstimator@@=00428cf0
#include "shared/adjacent_cell.hpp"
void UnknownPathEstimator::Unknown_00428AE0(UnknownPathType *path,FootClass *foot)
{
    int maximum=path->Length;
    --maximum;
    unsigned secondDirection=(unsigned)-1;
    int *heights=path->Height;
    int *moves=path->Command;
    Cell source=path->Start;
    int firstStart=0,secondStart=0;
    bool corner=false;
    int firstLength=0,secondLength=0;
    Cell start=source;
    Cell cursor=source;
    unsigned firstDirection=(unsigned)-1;
    while(firstStart+firstLength<maximum) {
        if(secondStart+secondLength>=maximum)break;
        if(!corner) {
            unsigned direction=moves[firstStart+firstLength];
            unsigned turn=(direction-firstDirection)&7;
            if(direction==firstDirection)++firstLength;
            else if((turn==2 || turn==6) && firstDirection!=-1 && firstDirection!=8 && direction!=8) {
                corner=true;secondDirection=direction;secondLength=1;
                secondStart=firstStart+firstLength;
            } else {
                firstStart+=firstLength;firstLength=1;
                firstDirection=(direction&1)?direction:-1;
                start=cursor;
            }
            cursor=Unknown_0042AD50(cursor,direction);
        } else {
            if(moves[secondStart+secondLength]==secondDirection)++secondLength;
            else {
                firstStart+=Unknown_00428CF0(foot,moves+firstStart,heights+firstStart,firstLength,secondLength,start);
                firstLength=1;corner=false;
                cursor=start+AdjacentCell[moves[firstStart]&7];
                firstDirection=moves[firstStart];
            }
        }
    }
    if(corner)Unknown_00428CF0(foot,moves+firstStart,heights+firstStart,firstLength,secondLength,start);
}
