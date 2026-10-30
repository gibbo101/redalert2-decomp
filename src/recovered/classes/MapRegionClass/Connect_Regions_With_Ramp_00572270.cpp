#include "shared/map_region.hpp"
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
// @ref ?unknown_005729f0@MapRegionClass@@=005729f0
// @ref ?unknown_00573040@MapRegionClass@@=00573040
// @ref ?unknown_00573680@MapRegionClass@@=00573680
// @ref ?unknown_00573d40@MapRegionClass@@=00573d40
// @ref ?unknown_00574930@MapRegionClass@@=00574930
// @ref ?unknown_00574e50@MapRegionClass@@=00574e50
// @ref ?unknown_005753f0@MapRegionClass@@=005753f0
bool MapRegionClass::Connect_Regions_With_Ramp_00572270(Cell const &cell,int region,float density)
{
    bool valid=true;
    unsigned mask=Build_Neighbor_Region_Mask_005728d0(cell,valid,region,density);
    if(!valid)return false;
    bool result=false;
    if(mask==255)return false;
    {
    Cell first,second;
    if((mask&0x82)==0x82 && (mask&0x38)==0) {
        first.X=cell.X-1;first.Y=cell.Y-5;
        second.X=cell.X+5;second.Y=cell.Y+1;
        if(mask&0x40)++first.Y;
        if(mask&4)--second.X;
        result=unknown_005753f0(first,second,region);
        if(result)goto fallback;
    }
    if((mask&10)==10 && (mask&0x11)==0) {
        first.X=cell.X+5;first.Y=cell.Y-1;
        second.X=cell.X-1;second.Y=cell.Y+5;
        if(mask&0x10)--second.Y;
        if(mask&1)--first.X;
        result=unknown_00574e50(first,second,region);
        if(result)goto fallback;
    }
    if((mask&0x28)==0x28 && (mask&0x83)==0) {
        first.X=cell.X+1;first.Y=cell.Y+5;
        second.X=cell.X-5;second.Y=cell.Y-1;
        if(mask&0x40)--second.X;
        if(mask&4)--first.Y;
        result=unknown_00574930(first,second,region);
        if(result)goto fallback;
    }
    if((mask&0xa0)==0xa0 && (mask&0xe)==0) {
        first.X=cell.X-5;first.Y=cell.Y+1;
        second.X=cell.X+1;second.Y=cell.Y-5;
        if(mask&1)++second.Y;
        if(mask&0x10)++first.X;
        result=unknown_00574930(first,second,region);
        if(result)goto fallback;
    }
    if((mask&0x70)==0 && (mask&0x88)!=0) {
        first.X=cell.X-1;first.Y=cell.Y-4;
        second.X=first.X;second.Y=cell.Y+4;
        if(mask&0x80) {++first.Y;++second.Y;}
        if(mask&8) {--second.Y;--first.Y;}
        first.X+=(short)Map_Random_Range_005797a0(0,1);
        second.X+=(short)Map_Random_Range_005797a0(0,1);
        result=unknown_00573d40(first,second,region);
        if(result)goto fallback;
    }
    if((mask&7)==0 && (mask&0x88)!=0) {
        first.X=cell.X+1;first.Y=cell.Y+4;
        second.X=first.X;second.Y=cell.Y-4;
        if(mask&0x80) {++second.Y;++first.Y;}
        if(mask&8) {--first.Y;--second.Y;}
        first.X+=(short)Map_Random_Range_005797a0(0,1)-1;
        second.X+=(short)Map_Random_Range_005797a0(0,1)-1;
        result=unknown_00573040(first,second,region);
        if(result)goto fallback;
    }
    if((mask&0xc1)==0 && (mask&0x22)!=0) {
        first.X=cell.X+4;first.Y=cell.Y-1;
        second.X=cell.X-4;second.Y=first.Y;
        if(mask&0x20) {++second.X;++first.X;}
        if(mask&2) {--first.X;--second.X;}
        first.Y+=(short)Map_Random_Range_005797a0(0,1);
        second.Y+=(short)Map_Random_Range_005797a0(0,1);
        result=unknown_00573680(first,second,region);
        if(result)goto fallback;
    }
    if((mask&0x1c)==0 && (mask&0x22)!=0) {
        first.X=cell.X-4;first.Y=cell.Y+1;
        second.X=cell.X+4;second.Y=first.Y;
        if(mask&0x20) {++first.X;++second.X;}
        if(mask&2) {--second.X;--first.X;}
        first.Y+=(short)Map_Random_Range_005797a0(0,1)-1;
        second.Y+=(short)Map_Random_Range_005797a0(0,1)-1;
        result=unknown_005729f0(first,second,region);
    }
    }
fallback:
    if(density>0.5f && !result) {
        Cell first,second;
        if((mask&8)==0) {
            first.X=cell.X-4;first.Y=cell.Y+1;
            second.X=cell.X+4;second.Y=cell.Y+1;
            result=unknown_005729f0(first,second,region);
            if(result)return result;
        }
        if((mask&2)==0) {
            first.X=cell.X+1;first.Y=cell.Y+4;
            second.X=cell.X+1;second.Y=cell.Y-4;
            result=unknown_00573040(first,second,region);
            if(result)return result;
        }
        if((mask&8)==0) {
            first.X=cell.X+4;first.Y=cell.Y-1;
            second.X=cell.X-4;second.Y=cell.Y-1;
            result=unknown_00573680(first,second,region);
            if(result)return result;
        }
        if((mask&32)==0) {
            first.X=cell.X-1;first.Y=cell.Y-4;
            second.X=cell.X-1;second.Y=cell.Y+4;
            result=unknown_00573d40(first,second,region);
            if(result)return result;
        }
    }
    return result;
}
