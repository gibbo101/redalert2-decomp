// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellAttributes.hpp"
#include "assets/TileSweep.hpp"
#include "render/RadarTerrain.hpp"
#include "render/RadarProjection.hpp"
namespace ra2 {
struct CellRadarColorServices {
    std::function<bool(std::int32_t,std::uint8_t)> resident471760;
    std::function<int(int)> primary;
    std::function<TileSweepType&(int)> type;
    std::function<void(int)> load52B560;
    std::function<int(const MapCellInput&,int,int)> variant4767A0;
    std::function<std::uint8_t(int)> overlay279;
    std::function<const Data*(int)> overlayAlternate26C;
    std::function<RadarRGB(int,std::uint32_t)> overlay5DD000;
    std::function<int(int)> resource5DC0B0;
    std::function<float()> theaterScale;
    std::function<void(RadarRGB&,unsigned,unsigned,std::uint32_t)> store;
};
// Complete4712C0 policy on borrowed Cell/type/image owners. Named services keep
// unrecovered leaf effects explicit; no original object-layout mirror is used.
inline void cellRadarColors(const MapCellAttributes& cell,const std::int32_t& clearTile,
        RadarRGB& first,RadarRGB& second,const CellRadarColorServices& s){
    const auto need=[](bool ok){if(!ok)throw std::invalid_argument("Cell radar color owner/service/domain");};
    const auto output=[&](RadarRGB color){
        for(auto* out:{&first,&second}){
            (*out)[0]=color[0];(*out)[1]=color[1];
            if(s.store)s.store(*out,0,2,std::uint32_t(color[0])|(std::uint32_t(color[1])<<8));
            (*out)[2]=color[2];if(s.store)s.store(*out,2,1,color[2]);
        }
    };
    need(bool(s.resident471760));if(s.resident471760(36,0)){output({200,200,160});return;}
    if(cell.input.flags&0x100){need(bool(s.overlay5DD000));output(s.overlay5DD000(24,0));return;}
    need(bool(s.primary)&&bool(s.type));
    const auto tile=cell.input.tile;int node=s.primary(tile==65535?clearTile:tile);
    auto* type=&s.type(node);
    const auto overlay=cell.overlay;
    if(overlay!=-1){
        need(bool(s.overlay279));
        if(!s.overlay279(overlay)){
            need(bool(s.overlay5DD000));
            const auto data=(overlay>=74&&overlay<=99)||(overlay>=205&&overlay<=230)?1u:std::uint32_t(cell.overlayData);
            output(s.overlay5DD000(overlay,data));return;
        }
        need(bool(s.overlayAlternate26C));const auto* image=s.overlayAlternate26C(overlay);
        if(image){
            const auto count=std::int32_t(std::bit_cast<std::int16_t>(image->u16(6)));
            const auto data=std::uint32_t(cell.overlayData);
            if(data<std::uint32_t(count)){
                const auto at=std::size_t(data)*24+20;output({image->u8(at),image->u8(at+1),image->u8(at+2)});
            }else output({0,0,0});
            return;
        }
        need(bool(s.resource5DC0B0));if(s.resource5DC0B0(overlay)!=-1){output({170,170,130});return;}
    }
    const auto image=[&](int id)->const Data*{
        auto& t=s.type(id);
        if(!t.image&&t.lazy){need(bool(s.load52B560));s.load52B560(id);}
        return t.image?&*t.image:nullptr;
    };
    const auto forced=[&](int id,int sub){
        const auto* data=image(id);if(!data)return false;
        const auto n=std::int64_t(data->i32(0))*data->i32(4);need(n>0&&n<=16384&&sub>=0);
        const auto ref=data->u32(16+std::size_t(sub%n)*4);
        return ref&&(data->u32(ref+0x24)&4)!=0;
    };
    std::int32_t chosen=0;
    if(cell.input.tile==65535){need(bool(s.variant4767A0));chosen=s.variant4767A0(cell.input,clearTile,type->variants);}
    else if(type->variants>1){
        if(forced(node,cell.input.subTile))chosen=std::int32_t((cell.input.flags>>13)&1);
        else{need(bool(s.variant4767A0));chosen=s.variant4767A0(cell.input,cell.input.tile,type->variants);}
    }
    //529520 reduces only results above variants-1, then follows exactly that
    // many links. Negative walks/divide errors are unsafe original domains.
    if(chosen>fillSub(type->variants,1)){need(type->variants!=0&&!(chosen==INT32_MIN&&type->variants==-1));chosen%=type->variants;}
    need(chosen>=0&&chosen<=65536);
    for(auto left=chosen;left;--left){node=type->next;need(node>=0);type=&s.type(node);}
    const auto* data=image(node);need(data!=nullptr);
    const auto ref=data->u32(16+std::size_t(cell.input.subTile)*4);
    if(!ref){output({60,60,60});return;}
    RadarRGB color{data->u8(ref+0x2b),data->u8(ref+0x2c),data->u8(ref+0x2d)};
    need(bool(s.theaterScale));const auto scale=s.theaterScale();
    // Complete63CDF0 numeric child under the explicit original FP profile.
    OriginalRounding rounding;
    for(auto& c:color){
        volatile double value=double(c)*double(scale);
        // x87 unordered comparisons take the upper-clamp path, including NaN.
        if(!(value<=255))value=255;else if(value<0)value=0;
        c=std::uint8_t(radarProjectionInteger(value));c=std::uint8_t(c>>1);
    }
    output(color);
}
}
