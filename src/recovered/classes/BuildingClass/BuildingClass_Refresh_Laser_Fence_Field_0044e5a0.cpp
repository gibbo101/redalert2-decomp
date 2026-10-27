// Refresh laser-fence segment frames and apply damage along connected active fields.
#include "shared/building.hpp"
#include "shared/cell.hpp"
#include "shared/building_map.hpp"
#include "shared/rules.hpp"
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?Current@FacingClass@@=004b8be0
// @ref ?unknown_4717b0@CellClass@@=004717b0
// @ref ?unknown_44ddb0@BuildingClass@@=0044ddb0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
void BuildingClass::unknown_44e5a0(int force)
{
    if(Type->LaserFencePost && unknown_7d && !unknown_76) {
        int range=Type->GuardRange.Value>>8;
        if(range<=1) range=1;
        bool powered=false;
        if(unknown_slot195() && unknown_5ba && unknown_slot91()!=19 && unknown_slot91()!=18)
            powered=true;
        unsigned facing=0;
        int remaining=4;
        do {
            Cell position=AdjacentCell[facing&7]+Coord_Cell(Center_Coord());
            Cell const &offset=AdjacentCell[facing&7];
            Cell current=position;
            BuildingClass *segment=static_cast<BuildingClass *>(Map[current].unknown_4717b0());
            unsigned axis=facing&3;
            if(segment && segment->Type->LaserFence && Owner()==segment->Owner()
               && (Dir_To_8(segment->unknown_2e0.Current())&3)==axis) {
                BuildingClass *first=segment;
                BuildingClass *last=segment;
                {
                    if(!(unsigned char)force) {
                        if(powered) {
                            if(segment->unknown_4ec<8) goto next_direction;
                        } else if(segment->unknown_4ec>=8) goto next_direction;
                    }
                    BuildingClass *post=0;
                    if(powered) post=unknown_44ddb0(facing,true,-1);
                    int first_frame=12;
                    int middle_frame=12;
                    int last_frame=12;
                    if(axis==2) { first_frame=8; middle_frame=8; last_frame=8; }
                    bool connected=false;
                    if(powered && post && post->unknown_slot195() && post->unknown_5ba
                       && post->unknown_slot91()!=19 && post->unknown_slot91()!=18) {
                        connected=true;
                        switch(facing) {
                        case 0: first_frame=5; middle_frame=4; last_frame=6; break;
                        case 4: first_frame=6; middle_frame=4; last_frame=5; break;
                        case 2: first_frame=1; middle_frame=0; last_frame=2; break;
                        case 6: first_frame=2; middle_frame=0; last_frame=1; break;
                        }
                    }
                    int distance=0;
                    while(segment && distance<range) {
                        if(!segment->Type->LaserFence) break;
                        if(Owner()!=segment->Owner()
                           || (Dir_To_8(segment->unknown_2e0.Current())&3)!=axis) break;
                        last=segment;
                        if(segment==first) segment->unknown_4ec=first_frame;
                        else segment->unknown_4ec=middle_frame;
                        segment->unknown_75=true;
                        if(connected) {
                            ObjectClass *object=Map[current].OccupierPtr;
                            while(object) {
                                int kind=object->Kind_Of();
                                if(kind>0 && (kind<=2 || kind==15)) {
                                    ObjectClass *next=object->unknown_30;
                                    if(object->Strength>0)
                                        object->unknown_slot86(&object->Strength,0,Rules->unknown_c74,segment,true,1);
                                    object=next;
                                } else object=object->unknown_30;
                            }
                        }
                        ++distance;
                        Cell next=current+offset;
                        current=next;
                        segment=static_cast<BuildingClass *>(Map[current].unknown_4717b0());
                    }
                    if(connected && last) {
                        if(first==last) {
                            if(axis==2) last->unknown_4ec=3;
                            else last->unknown_4ec=7;
                        } else last->unknown_4ec=last_frame;
                        last->unknown_75=true;
                    }
                }
            }
next_direction:
            facing=(facing+2)&7;
        } while(--remaining);
    }
}
