// FootClass Can_Reach004C8730: complete519body+9NOP; existing ABI retained.
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
#include "shared/adjacent_cell.hpp"
#include "shared/crt_memory.hpp"
#pragma intrinsic(abs)
int FootClass::unknown_slot102(UnknownCellClass *from,int facing,int *level,bool *ramp,UnknownCellClass *to)
{
    if(to==0) {
        to=(UnknownCellClass *)&Map[Cell(AdjacentCell[(facing-4)&7]+from->unknown_24)];
    }
    if(facing!=-1) {
        if(to==0 || from==0) return 0;
        if(*level==-1 && (to->Flags & 0x100)) {
            *level=to->unknown_11b+4;
            if(!(from->Flags & 0x200)) return 7;
        }
        int current_height;
        int height_difference;
        if(to->Flags & 0x100) {
            current_height=from->unknown_11b;
            height_difference=to->unknown_11b-current_height;
        } else {
            current_height=from->unknown_11b;
            height_difference=*level-current_height;
        }
        switch(abs(height_difference)) {
        case 0:
            if((!(from->Flags & 0x100) || !(from->Flags & 0x200) || !(to->Flags & 0x100)) && *level!=-1 && *level!=current_height) return 7;
            break;
        case 1:
            if(height_difference>0) {
                if(!from->unknown_11c) return 7;
            } else if(!to->unknown_11c) return 7;
            break;
        case 4:
            if(to->unknown_11b==current_height-4) {
                if(*level!=current_height) return 7;
                if(!(to->Flags & 0x100)) return 7;
            }
            if(current_height!=to->unknown_11b-4) return 0;
            if(!(from->Flags & 0x100)) return 7;
            if(!(from->Flags & 0x200)) return 7;
            *ramp=true;
            break;
        default: return 7;
        }
    } else {
        if(*level==-1 && (from->Flags & 0x100)) *level=from->unknown_11b+4;
    }
    return 0;
}
