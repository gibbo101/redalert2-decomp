// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
#include <array>
#include <bit>
#include <functional>
#include <stdexcept>
namespace ra2 {
struct CellRedrawQueue {
    std::array<int,800> cells{}; // Logical identities, including unused capacity tails.
    std::int32_t countE0=0;
    std::uint8_t dirtyD7D=0;
};
struct CellRedrawView {
    std::int32_t loading8324EC=0,originB0=0,originB4=0;
    std::int32_t viewportX=0,viewportY=0,viewportWidth=0,viewportHeight=0;
};
struct CellRedrawFields {
    int identity;
    std::int32_t& frame5C;
    const std::uint32_t& flags12C;
    std::uint8_t& redraw138;
};
struct CellRedrawServices {
    std::function<Coord()> center475D60;
    std::function<std::int32_t(std::int32_t)> height6A2970;
    std::function<void(char,std::int32_t,std::int32_t)> store;
};
// Complete6AADD0. The two projection blocks are identical. Its height call
// receives zero, not the saved center Z. Frame is stored even when clipped out.
inline void requestCellRedraw(CellRedrawFields a,const std::int32_t& frame,
        const CellRedrawView& view,CellRedrawQueue& queue,const CellRedrawServices& s){
    const auto add=[](std::int32_t x,std::int32_t y){return std::bit_cast<std::int32_t>(std::uint32_t(x)+std::uint32_t(y));};
    const auto sub=[](std::int32_t x,std::int32_t y){return std::bit_cast<std::int32_t>(std::uint32_t(x)-std::uint32_t(y));};
    const auto mul=[](std::int32_t x,std::uint32_t y){return std::bit_cast<std::int32_t>(std::uint32_t(x)*y);};
    const auto half=[&](std::int32_t x){return sub(x,x<0?-1:0)>>1;};
    const auto emit=[&](char k,int x,int y=0){if(s.store)s.store(k,x,y);};
    if(view.loading8324EC||a.frame5C==frame||(!(a.flags12C&8u)&&!a.redraw138))return;
    a.frame5C=frame;emit('F',a.frame5C);
    if(!s.center475D60||!s.height6A2970)throw std::invalid_argument("Cell redraw projection child unbound");
    const auto p=s.center475D60();
    const auto x=add(half(mul(p.x,60)),half(mul(p.y,std::uint32_t(-60))));
    const auto y=add(half(mul(p.x,30)),half(mul(p.y,30)));
    const auto projectedX=x/256;
    const auto height=s.height6A2970(0);
    const auto projectedY=sub(sub(y/256,height),view.originB4);
    const auto screenX=sub(projectedX,view.originB0);
    if(screenX<sub(view.viewportX,30)||projectedY< -30||
       screenX>add(add(view.viewportWidth,view.viewportX),30)||
       projectedY>add(add(view.viewportHeight,view.viewportY),15))return;
    if(queue.countE0<799){
        if(queue.countE0<0)throw std::invalid_argument("Negative Cell redraw queue index");
        const auto at=queue.countE0;queue.cells.at(std::size_t(at))=a.identity;emit('Q',at,a.identity);
        queue.countE0=add(queue.countE0,1);emit('N',queue.countE0);
    }
    a.redraw138=0;emit('R',0);queue.dirtyD7D=1;emit('D',1);
}
}
