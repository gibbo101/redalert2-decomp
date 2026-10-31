#include "shared/path_estimator.hpp"
#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/adjacent_cell.hpp"
#include "shared/crt_memory.hpp"
// @ref ?Unknown_00428950@UnknownPathEstimator@@=00428950
// @ref ?Current@FacingClass@@=004b8be0
Cell __fastcall CellClass::Adjacent_Cell(Cell const &cell,int facing)
{
    return cell + AdjacentCell[facing&7];
}
void UnknownPathEstimator::Apply_Path_Collision_Avoidance_004285d0(FootClass *foot)
{
    // Four-byte view of CellClass flag word +0x140; bit18 is the predicted path mark.
    // The alias/layout spelling remains a hypothesis; original 32-bit mask is independently verified.
    struct PredictedPathFlags {
        unsigned :18;
        unsigned IsPredictedPath:1;
        unsigned :13;
    };
    if(unknown_03) {
    Cell current=foot->unknown_slot104();
    CellClass *currentCell=&Map[current];
    CellClass *next=&Map[CellClass::Adjacent_Cell(current,Dir_To_8(foot->unknown_2e0.Current()))];
    bool bridge=(next->unknown_140&0x100)!=0 &&
        (abs(currentCell->unknown_11b-next->unknown_11b)>3 || foot->unknown_79);
    FootClass *blocker=(FootClass*)(bridge?next->AltOccupierPtr:next->OccupierPtr);
    if(!blocker)blocker=(FootClass*)Unknown_00428950(next->MapCoords,next->unknown_11b+(bridge?4:0));
    bool marked=false;
    TechnoTypeClass const *type=foot->unknown_slot32();
    while(blocker) {
        if(blocker->Kind_Of()==1 || blocker->Kind_Of()==15) {
            int index=0;
            Cell position=blocker->unknown_450;
            TechnoTypeClass const *other=blocker->unknown_slot32();
            if(unknown_3c==2 || (type!=other && type->Speed>other->Speed && Map.Unknown_0055A660(position,true))) {
                if(blocker->Kind_Of()==1) {
                    if(blocker->Path[0]==-1 || blocker->Path[1]==-1) {blocker=(FootClass*)blocker->unknown_30;continue;}
                } else {
                    if(blocker->Path[0]==-1 || blocker->Path[1]==-1 || blocker->Path[2]==-1) {blocker=(FootClass*)blocker->unknown_30;continue;}
                }
                marked=true;
                while(blocker->Path[index]!=-1 && index<24) {
                    Cell nextPosition=Unknown_0042AD50(position,blocker->Path[index]);
                    position=nextPosition;
                    reinterpret_cast<PredictedPathFlags *>(&Map[position].unknown_140)->IsPredictedPath=!reinterpret_cast<PredictedPathFlags *>(&Map[position].unknown_140)->IsPredictedPath;
                    ++index;
                }
            } else {
                blocker=(FootClass*)blocker->unknown_30;
                continue;
            }
        }
        blocker=(FootClass*)blocker->unknown_30;
    }
    if(!marked && unknown_3c==1) {unknown_3c=0;return;}
    for(int x=-2;x<3;++x) {
        for(int y=-2;y<3;++y) {
            CellClass *neighbor=&Map[next->Fetch_CellID()+Cell(x,y)];
            if(neighbor->unknown_124) {
                Cell neighborPosition=neighbor->Fetch_CellID();
                if(neighborPosition!=current)reinterpret_cast<PredictedPathFlags *>(&neighbor->unknown_140)->IsPredictedPath=!reinterpret_cast<PredictedPathFlags *>(&neighbor->unknown_140)->IsPredictedPath;
            }
        }
    }
    reinterpret_cast<PredictedPathFlags *>(&next->unknown_140)->IsPredictedPath=!reinterpret_cast<PredictedPathFlags *>(&next->unknown_140)->IsPredictedPath;
    }
}
