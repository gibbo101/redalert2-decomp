// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FootDepth.hpp"
#include "sim/Drive.hpp"
#include <algorithm>
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {
int product(int a,int b){return signed32(std::uint32_t(a)*std::uint32_t(b));}
UnitLightCell neighbor(UnitLightCell p,int direction){
    const auto [x,y]=directionOffset(direction);
    return {std::bit_cast<std::int16_t>(std::uint16_t(unsigned(std::uint16_t(p.x))+unsigned(x))),
            std::bit_cast<std::int16_t>(std::uint16_t(unsigned(std::uint16_t(p.y))+unsigned(y)))};
}
void enter(const FootDepthWorld& w,int i){if(w.trace)w.trace(i);}
const FootDepthCell& required(const FootDepthCell* c){
    if(!c)throw std::invalid_argument("Foot depth requires a current cell");return *c;
}
}
UnitLightCell footDepthCoordinates(int x,int y){
    return {std::bit_cast<std::int16_t>(std::uint16_t(x/256)),
            std::bit_cast<std::int16_t>(std::uint16_t(y/256))};
}
int footDepthAdjustment(bool has,const FootDepthServices& s){
    const int loco=has?s.locomotorDepth():0;
    auto t=s.type();const int a=product(t.b60,s.predicate0());
    t=s.type();const int b=product(t.b64,s.predicate1());
    t=s.type();const int c=product(t.b5c,s.predicate2());
    const int d=s.predicate3()!=0?s.type().b68:0;
    const int maximum=std::max({a,b,c,d});
    const int base=s.baseDepth();
    return signed32(std::uint32_t(base)+std::uint32_t(maximum)+std::uint32_t(loco));
}
int footDepthGradient(bool has,const FootDepthServices& s){return has?s.locomotorGradient():2;}
bool footDepthCellPredicate(const FootDepthCell& c,int count){
    return c.field116>=0&&c.field116<count&&c.fieldEC==10;
}
bool footDepthFlag(const FootDepthWorld& w,bool mask400){
    enter(w,mask400?4:3);const auto p=w.coordinates();const auto center=w.cell(p);
    if(!center||w.bridge)return false;
    const auto a=w.cell(neighbor(p,4)),b=w.cell(neighbor(p,0)),
               c=w.cell(neighbor(p,2)),d=w.cell(neighbor(p,6));
    const std::uint32_t mask=mask400?0x400:0x100;
    return (center->flags&mask)||(a&&(a->flags&mask)&&(a->flags&0x800))||
           (d&&(d->flags&mask)&&!(d->flags&0x800))||
           (c&&(c->flags&mask)&&!(c->flags&0x800))||
           (b&&(b->flags&mask)&&(b->flags&0x800));
}
int footDepthPredicate0(const FootDepthWorld& w){
    enter(w,0);const auto p=w.coordinates();if(!w.cell(p))return 0;
    if(!footDepthFlag(w)&&!footDepthFlag(w,true))return 0;
    const auto a=w.cell(neighbor(p,4)),b=w.cell(neighbor(p,2)),c=w.cell(neighbor(p,3));
    if(!a||!b||!c)return 0;
    auto included=[&](int tile){
        if(tile==65535||tile==255)return false;
        const int value=signed32(std::uint32_t(tile)-std::uint32_t(w.tileBase)+1u);
        return value>=7&&value<=16;
    };
    return int(included(a->tile)||included(b->tile))+int(included(c->tile));
}
int footDepthPredicate1(const FootDepthWorld& w){
    enter(w,1);const auto p=w.coordinates();if(w.bridge)return 0;
    const auto a=w.cell(neighbor(p,0)),b=w.cell(neighbor(p,6)),center=w.cell(p);
    if(!a||!b)return 0;
    auto candidate=w.invalid;
    if(w.cellPredicate(required(center)))candidate=center->position;
    else if(w.cellPredicate(*a))candidate=a->position;
    else if(w.cellPredicate(*b))candidate=b->position;
    if(candidate==w.invalid)return 0;
    const auto c=w.cell(neighbor(candidate,0)),d=w.cell(neighbor(candidate,6));
    if(!c||!d)return 0;
    const auto e=w.cell(neighbor(c->position,0)),f=w.cell(neighbor(d->position,6));
    if(!e||!f)return 0;
    return int(w.cellPredicate(*f)||w.cellPredicate(*e));
}
int footDepthPredicate2(const FootDepthWorld& w){
    enter(w,2);const auto p=w.coordinates();const auto center=w.cell(p);
    if(w.bridge)return 0;
    const auto a=w.cell(neighbor(w.coordinates(),3));if(!a)return 0;
    const int first=int(a->level)-int(required(center).level)>=4?2:0;
    const auto b=w.cell(neighbor(a->position,3));
    if(b&&int(b->level)-int(center->level)>=4)return 1;
    return first;
}
}
