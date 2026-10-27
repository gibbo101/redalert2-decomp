// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TerrainOccupation.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
TerrainCellPoint terrainCellPoint(Coord p) {
    // Divide before word truncation. Negative fractions do not round down.
    return {std::bit_cast<std::int16_t>(std::uint16_t(p.x/256)),
            std::bit_cast<std::int16_t>(std::uint16_t(p.y/256))};
}
TerrainOccupationChange terrainOccupation(Coord p,int theater,TerrainOccupationType type,
                                          std::uint32_t flags,bool mark) {
    TerrainOccupationChange result{terrainCellPoint(p),flags,{}};
    const auto mask=theater==1?type.snow:type.temperate;
    for(unsigned bit=0;bit<3;++bit)if(mask&(1u<<bit)) {
        const auto cellBit=1u<<(bit+2);
        result.flags=mark?result.flags|cellBit:result.flags&~cellBit;
        result.writes.push_back(std::uint8_t(result.flags));
    }
    return result;
}
TerrainMarkDecision terrainMark(TerrainMarkState& s,std::int32_t mode) {
    if(s.limbo)return {};
    bool redraw=false;
    if(mode==2) {
        if(s.needsRedraw||!s.onMap)return {};
        redraw=true;
    } else if((mode==1||mode==3)&&!s.onMap) {s.onMap=1;redraw=true;}
    else if(mode==0&&s.onMap)s.onMap=0;
    else return {};
    if(redraw&&!s.needsRedraw)s.needsRedraw=1;
    return {true,redraw,true,mode==0?TerrainMapAction::Remove:
        (mode==1||mode==3)?TerrainMapAction::Insert:TerrainMapAction::None};
}
static void emit(const std::function<void(TerrainOccupationEvent)>& trace,char kind,int id,std::int64_t value) {
    if(trace)trace({kind,id,value});
}
void TerrainOccupationWorld::cellInsert(int id,TerrainCellPoint point,bool alternate,
                                        const std::function<void(TerrainOccupationEvent)>& trace) {
    auto& actor=members.at(id);auto& cell=cells.at(point);auto& head=alternate?cell.alternateHead:cell.head;
    // Ordinary Terrain prepends. Preserve the original head->next guard, which
    // differs from a general duplicate search or a head==actor check.
    if(head==-1||members.at(head).next!=id) {
        actor.next=head;emit(trace,'N',id,head);head=id;emit(trace,'H',alternate,id);
    }
    emit(trace,'V',id,0); // Supplied visibility service boundary, before occupation.
    const auto changed=terrainOccupation(actor.position,theater,actor.type,cells.at(terrainCellPoint(actor.position)).flags,true);
    emit(trace,'L',changed.cell.x,changed.cell.y);
    auto& target=cells.at(changed.cell);
    for(auto value:changed.writes){emit(trace,'W',0,value);target.flags=(target.flags&0xffffff00u)|value;}
}
void TerrainOccupationWorld::cellRemove(int id,TerrainCellPoint point,bool alternate,
                                        const std::function<void(TerrainOccupationEvent)>& trace) {
    auto& actor=members.at(id);auto& cell=cells.at(point);auto& head=alternate?cell.alternateHead:cell.head;
    bool found=false;
    if(head==id) {head=actor.next;emit(trace,'H',alternate,head);found=true;}
    else {
        int before=head;std::size_t visits=0;
        while(before!=-1) {
            if(++visits>members.size())throw std::invalid_argument("Cyclic terrain membership outside valid profile");
            auto& item=members.at(before);
            if(item.next==id){item.next=actor.next;emit(trace,'N',before,item.next);found=true;break;}
            before=item.next;
        }
    }
    if(found){actor.next=-1;emit(trace,'N',id,-1);}
    // The original unmarks even when absent from this cell's list; no refcounts.
    const auto changed=terrainOccupation(actor.position,theater,actor.type,cells.at(terrainCellPoint(actor.position)).flags,false);
    emit(trace,'L',changed.cell.x,changed.cell.y);
    auto& target=cells.at(changed.cell);
    for(auto value:changed.writes){emit(trace,'W',0,value);target.flags=(target.flags&0xffffff00u)|value;}
}
bool TerrainOccupationWorld::mark(int id,std::int32_t mode,
                                 const std::function<void(TerrainOccupationEvent)>& trace) {
    auto& actor=members.at(id);const auto previous=actor.state.onMap,previousRedraw=actor.state.needsRedraw;
    const auto decision=terrainMark(actor.state,mode);
    if(previous!=actor.state.onMap)emit(trace,'M',id,actor.state.onMap);
    if(previousRedraw!=actor.state.needsRedraw){emit(trace,'B',id,1);emit(trace,'R',id,0);}
    if(decision.coordinates)emit(trace,'C',id,0);
    const auto point=terrainCellPoint(actor.position);
    if(decision.action==TerrainMapAction::Insert) {cellInsert(id,point,false,trace);emit(trace,'D',point.x,point.y);}
    if(decision.action==TerrainMapAction::Remove) {cellRemove(id,point,false,trace);emit(trace,'D',point.x,point.y);}
    return decision.accepted;
}
}
