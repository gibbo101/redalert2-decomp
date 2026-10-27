// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/TechnoSpriteDraw.hpp"
#include "render/Redraw.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {
template<class F> const F& need(const F& f){if(!f)throw std::invalid_argument("Entered Techno sprite child unbound");return f;}
int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
int sub(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
}
std::int32_t buildingSpriteBrightness(std::uint32_t flagsD8,std::int32_t light){
    if(!(flagsD8&2))return light;
    return light<=1500?add(light,500):sub(light,500);
}
void drawTechnoSprite(const TechnoSpriteFields& a,const BuildingSpriteRequest& r,const TechnoSpriteServices& s){
    if(!r.image)return;
    const auto read=[&](int subject,int off,int v){if(s.read)s.read(subject,off,v);return v;};
    const auto kind=[&]{return need(s.kind2c)();};
    const auto byte=[&](int off,std::uint8_t v){return read(1,off,v);};
    const auto flag5bb=[&]{return byte(0x5bb,a.flag5bb);};
    bool shadow=need(s.shadow7d88d5)()!=0;
    const auto mode=need(s.mode64)(0,0);int flags=0;
    if(r.tail[7]==0){
        switch(mode){case 1:flags=2;break;case 2:case 3:flags=4;break;
        case 4:flags=read(1,0x1bc,a.field1bc)?4:2;break;case 5:return;default:break;}
    }
    if(need(s.predicate1bc)()||need(s.predicate1c0)())flags|=4;
    const void* converter=nullptr;int brightness=r.tail[2];
    const auto initialize=[&](TechnoSpriteCell cell){need(s.initialize4790f0)(cell,{0,65536,0,1000,1000,1000});};
    if(kind()==6&&read(0,0x1386,need(s.building1386)())){
        const auto p=need(s.coordinates48)();auto cell=need(s.cell548070)(buildingDrawCell(p));
        converter=cell.converter34;
        if(!converter){initialize(cell);converter=cell.converter34;if(!converter)return;}
        brightness=read(2,0x10c,cell.terrain10c);
    }else{
        if(kind()==1&&flag5bb())converter=need(s.converterAd0608)();
        else converter=need(s.converter1cc)();
    }
    PixelPoint point=r.point;int adjust=r.adjust;
    const auto height=[&]{return need(s.project6a2970)(need(s.height1b8)());};
    switch(kind()){
    case 2:point.y=sub(point.y,height());adjust=sub(adjust,height());break;
    case 1:
        if(read(3,0xbb0,need(s.footBB0)())||read(3,0xbb1,need(s.footBB1)()))shadow=false;
        [[fallthrough]];
    case 15:
        if(!need(s.target1b0)())adjust=add(need(s.depth2c0)(),adjust);
        else {adjust=sub(adjust,height());shadow=false;}
        break;
    default:break;
    }
    if(read(0,0xb48,need(s.typeB48)()))shadow=false;
    if(!need(s.ownerPredicate3d4)(need(s.currentHouseA35db4)())){
        const auto object=need(s.objectC8)(1);
        bool terrain=need(s.objectKind2c)(object)==21;
        if(!terrain)terrain=need(s.objectKind2c)(need(s.objectC8)(1))==37;
        if(terrain){
            auto cell=need(s.cell1a4)();converter=cell.converter34;
            if(!converter){initialize(cell);converter=cell.converter34;}
            brightness=read(2,0x10c,cell.terrain10c);
        }else converter=need(s.houseConverter)(need(s.houseCC)(1));
        if(!converter)converter=need(s.houseConverter)(need(s.currentHouseA35db4)());
    }
    if(r.tail[0]!=-1)flags|=0x2000;
    if(std::uint8_t(r.tail[1]))flags|=0x4000;
    flags|=0x800;
    if(kind()==1&&flag5bb()){flags|=0x20;shadow=false;}
    flags=std::bit_cast<std::int32_t>(std::uint32_t(flags)&~std::uint32_t(r.tail[7]));
    if(kind()==1&&flag5bb()){
        auto image=need(s.image)(r.image);const auto count=need(image.count)();PixelRect bounds;
        if(std::uint32_t(r.frame)>=std::uint32_t(std::int32_t(count)))bounds=need(s.emptyFrame)();
        else {auto saved=image;saved.count=[count]{return count;};bounds=shpFrameBounds(saved,r.frame,{});}
        const auto size=need(image.dimensions)();
        bounds.x=add(sub(bounds.x,size.x/2),point.x);bounds.y=add(sub(bounds.y,size.y/2),point.y);
        const auto field=[&](int off){return need(s.infantryBoundsRead)(off);};
        PixelRect combined=bounds;const int width=field(8);
        if(width>0&&field(12)>0){
            const int x=field(0),y=field(4),h=field(12);
            if(bounds.width>0&&bounds.height>0)combined=unionDirtyBounds({x,y,width,h},bounds);
            else combined={x,y,width,h};
        }
        const std::array<int,4> values{combined.x,combined.y,combined.width,combined.height};
        for(int i=0;i<4;++i)need(s.infantryBoundsStore)(i*4,values[i]);
    }
    if(need(s.ownedHousePredicate4f52b0)()&&need(s.predicateC0)())flags=need(s.flags3d0)(flags);
    brightness=need(s.brightness3f8)(brightness);
    if(need(s.predicate32c)())brightness=need(s.status6d86f0)(brightness);
    if(std::uint32_t(mode)>4u)return;
    const auto blit=[&](int frame,int f,int z,int gradient,int light,std::array<int,4> tail,const void* auxiliary=nullptr){
        const auto* surface=need(s.surface83995c)();
        need(s.draw49eea0)({r.image,frame,point,r.clip,f,0,z,gradient,light,tail,converter,surface,auxiliary});
    };
    blit(r.frame,flags|0x600,sub(adjust,2),r.tail[0],brightness,{r.tail[3],r.tail[4],r.tail[5],r.tail[6]},r.auxiliaryImage);
    if((mode==0||mode==1)&&shadow){
        const int z=sub(-4,height());if(byte(0x37c,a.flag37c))point.y=sub(point.y,14);
        auto image=need(s.image)(r.image);const int frame=add(int(need(image.count)())/2,r.frame);
        blit(frame,(flags&~6)|0x601,z,0,1000,{});
    }
}
}
