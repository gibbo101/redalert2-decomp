// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingOrdinaryDraw.hpp"
#include "render/BuildingFrameRedraw.hpp"
#include "sim/OriginalMath.hpp"
#include <bit>
#include <cmath>
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
int sub(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
int span(int value){return std::bit_cast<std::int32_t>((std::uint32_t(value)<<8)-256u);}
template<class F> const F& need(const F& f){if(!f)throw std::invalid_argument("Entered Building ordinary child unbound");return f;}
int ftol(double v){return !std::isfinite(v)||v<-0x1p63||v>=0x1p63?0:std::bit_cast<std::int32_t>(std::uint32_t(std::int64_t(v)));}
}
std::uint32_t buildingDrawCell(Coord p){return std::uint32_t(std::uint16_t(p.x/256))|(std::uint32_t(std::uint16_t(p.y/256))<<16);}
void drawBuildingOrdinary(PixelPoint& point,PixelRect& clip,const BuildingOrdinaryServices& s){
    const auto read=[&](int subject,int off,int value){if(s.read)s.read(subject,off,value);return value;};
    const auto type=[&]{return need(s.type)();};
    const auto tr=[&](int off,int value){return read(0,off,value);};
    const auto pointer=[&](int off,const void* value){if(s.pointerRead)s.pointerRead(off,value);return value;};
    const auto stage=[&]{return read(1,0x42c,need(s.stage42c)());};
    const auto mission=[&]{return need(s.mission16c)();};
    const auto damaged=[&]{const auto ratio=need(s.healthRatio5d4540)();return !(ratio>need(s.threshold1368)());};
    const auto height=[&]{return need(s.projectHeight6a2970)(need(s.height1b8)());};
    const auto light=[&](std::uint32_t cell,bool includeType){
        int v=need(s.cellLight548070)(cell);read(1,0x10a,v);
        if(includeType)v=add(v,tr(0x11fc,type().fields.offset11fc));return v;
    };
    const auto draw=[&](const void* image,int frame,int adjust,int mode,int lighting,int global,PixelPoint offset){
        need(s.draw6d1510)({image,frame,point,clip,0,256,adjust,{mode,1,lighting,global,0,offset.x,offset.y,0}});
    };
    const auto cell=need(s.cell1a0)();auto image=need(s.image68)();if(!image)return;
    if(need(s.kind2c)()==6&&!stage()&&mission()==19){
        for(int i=0;i<18;++i){auto* flag=need(s.animation454)(i);if(flag){*flag=1;if(s.animationStore)s.animationStore(i,1);}}
    }
    const auto initial=type();if(tr(0x1385,initial.fields.flag1385))return;
    auto adjust=tr(0x11d4,initial.fields.adjust11d4);PixelPoint offset{198,446};bool alternative=false;
    if(mission()==16){
        if(const auto* partner=need(s.partner636e20)(0)){
            alternative=need(s.partnerFlag80)(partner,0xb44)!=0;
            if(!alternative)alternative=need(s.partnerFlag80)(partner,0xb1a)!=0;
        }
    }
    if(mission()==24){
        const auto predicate=[&](int id){return std::uint8_t(need(s.timerPredicate)(id));};
        if(predicate(0x496a90)||predicate(0x496ab0)||predicate(0x496b30)){
            const auto fraction=need(s.timerFraction496c70)();const auto count=tr(0x137c,type().images.count137c);
            int frame;{OriginalRounding rounding;frame=ftol(fraction*double(count));}
            if(predicate(0x496ab0))frame=sub(tr(0x137c,type().images.count137c),frame);
            if(predicate(0x496b50))frame=0;
            if(predicate(0x496b30))frame=sub(tr(0x137c,type().images.count137c),1);
            const auto limit=tr(0x137c,type().images.count137c);if(frame>=limit)frame=sub(limit,1);if(frame<0)frame=0;
            image=need(s.image68)();const auto extra=damaged()?add(tr(0x137c,type().images.count137c),1):0;
            const auto lighting=light(cell,false);adjust=sub(adjust,height());
            draw(image,add(extra,frame),adjust,2,lighting,0,{});return;
        }
    }
    if(mission()==16){
        const auto t=type();const auto replacement=alternative?pointer(0x11b0,t.fields.image11b0):pointer(0x11a0,t.fields.image11a0);
        if(replacement){image=replacement;adjust=-20;}
    }
    const auto currentMission=mission();
    if(currentMission!=18&&currentMission!=19){const auto t=type();offset.x=add(198,tr(0x11e4,t.fields.offset11e4.x));offset.y=add(446,tr(0x11e8,t.fields.offset11e4.y));}
    const auto h=need(s.foundationHeight458940)();const auto w=need(s.foundationWidth458930)();
    const auto projected=projectTacticalPlanar({span(w),span(h)});
    offset.x=sub(offset.x,projected.x);offset.y=sub(offset.y,projected.y);
    auto global=need(s.global85029c)();if(need(s.foundationWidth458930)()>=8)global=0;
    if(clip.height>0){
        auto count=int(need(s.imageCount)(image));read(2,6,count);
        const auto candidate=need(s.frame43be20)();int frame;
        if(candidate<count/2)frame=need(s.frame43be20)();
        else{count=int(need(s.imageCount)(image));read(2,6,count);frame=count/2;}
        const auto lighting=light(cell,true);adjust=sub(adjust,height());
        draw(image,frame,adjust,2,lighting,global,offset);
    }
    const auto auxiliaryType=type();if(pointer(0x11cc,auxiliaryType.bounds.auxiliary11cc)&&stage()){
        const auto lighting=light(cell,true);const auto adjustment=sub(-1,height());
        const auto frame=need(s.frame43be20)();const auto live=type();
        draw(pointer(0x11cc,live.bounds.auxiliary11cc),frame,adjustment,0,lighting,0,{});
    }
    if(mission()!=16)return;
    const auto t=type();const auto overlay=alternative?pointer(0x11b8,t.fields.image11b8):pointer(0x11a8,t.fields.image11a8);
    if(!overlay)return;
    const auto frame=damaged()?1:0;const auto lighting=light(cell,true);const auto adjustment=sub(0,height());
    const auto live=type();
    draw(alternative?pointer(0x11b8,live.fields.image11b8):pointer(0x11a8,live.fields.image11a8),frame,adjustment,0,lighting,0,{});
}
}
