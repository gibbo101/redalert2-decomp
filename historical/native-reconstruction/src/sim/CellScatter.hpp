// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
#include <functional>
#include <map>
#include <stdexcept>
#include <vector>

namespace ra2 {
struct CellScatterMember {
    int kind=1,next=-1,type=-1,owner=-1;
    double veterancy=0;
};
struct CellScatterType {std::uint8_t veteranAbility3=0,eliteAbility3=0;};
struct CellScatterHeads {int primary=-1,elevated=-1;};
// Initial records and their associations are supplied, not constructors.
// The two unnamed rule/House values retain their measured byte/dword offsets.
struct CellScatterWorld {
    std::map<int,CellScatterMember> members;
    std::map<int,CellScatterType> types;
    std::map<int,int> house194;
    std::map<int,CellScatterHeads> cells;
    std::uint8_t rules1431=0;
    int rules10b4=0;
    // Read-only consumer observer: operation, subject, value.
    std::function<void(char,int,int)> trace;
};
struct CellScatterServices {
    // Original vector growth and heap disposal remain named services. The low
    // byte of grow's return controls success; capacity grows in steps of ten.
    std::function<std::uint32_t(int)> grow;
    std::function<void(int)> release;
    // Actual member +15C dispatch remains a service, NOT a recovered Unit
    // Scatter implementation or a successful no-op suitable for live Advance6.
    std::function<void(int,const Coord&,std::uint8_t,std::uint8_t)> scatter;
};

namespace cell_scatter_detail {
inline void event(auto& w,char op,int id=0,int value=0){if(w.trace)w.trace(op,id,value);}
inline bool techno(int id,auto& w){
    event(w,'X',id);const int kind=w.members.at(id).kind;event(w,'K',id,kind);
    // Exact base cast table: other kinds return null, including Terrain36.
    return kind==1||kind==2||kind==6||kind==15;
}
inline bool veteran(int id,auto& w){event(w,'V',id);const double n=w.members.at(id).veterancy;return n>=1.0&&n<2.0;}
inline bool elite(int id,auto& w){event(w,'E',id);return w.members.at(id).veterancy>=2.0;}
inline bool ability3(int id,auto& w){
    event(w,'B',id,3);
    if(!veteran(id,w)&&!elite(id,w))return false;
    event(w,'T',id);const int type=w.members.at(id).type;event(w,'t',id,type);
    const auto& t=w.types.at(type);
    if(veteran(id,w)&&t.veteranAbility3)return true;
    return elite(id,w)&&(t.veteranAbility3||t.eliteAbility3);
}
}

// Complete Cell member snapshot/dispatch policy in the successful host-storage
// domain, including explicit supplied guest growth failures. Member movement,
// mission/pathfinder effects and allocation internals are not recovered here.
// This helper is unwired; the existing Advance6/scatter refusals stay intact.
inline void scatterCellResidents(int cell,const Coord& at,std::uint8_t ignoreMission,
    std::uint8_t ignoreDestination,std::uint8_t elevated,
    auto& w,const CellScatterServices& services){
    using namespace cell_scatter_detail;
    if(!services.grow||!services.release||!services.scatter||!w.cells.contains(cell))
        throw std::invalid_argument("Cell scatter requires explicit Cell and services");
    const auto head=[&]{const auto& c=w.cells.at(cell);const int id=elevated?c.elevated:c.primary;event(w,'H',cell,elevated?1:0);return id;};
    const auto next=[&](int id){const int n=w.members.at(id).next;event(w,'N',id,n);return n;};
    bool hasElite=false;int id=head();std::size_t visits=0;
    if(!ignoreDestination){
        while(id!=-1){
            if(++visits>w.members.size())throw std::invalid_argument("Cyclic Cell scatter list");
            if(techno(id,w)&&elite(id,w)){hasElite=true;break;}
            id=next(id);
        }
    }
    // Reload the selected head after the prepass, then retain a separate
    // snapshot before any Scatter callback can change live Cell/Next values.
    id=head();visits=0;int capacity=0;std::vector<int> snapshot;
    while(id!=-1){
        if(++visits>w.members.size())throw std::invalid_argument("Cyclic Cell scatter list");
        bool room=int(snapshot.size())<capacity;
        if(!room){
            const int requested=capacity+10;
            if(std::uint8_t(services.grow(requested))){snapshot.reserve(std::size_t(requested));capacity=requested;room=true;}
        }
        if(room){const int index=int(snapshot.size());snapshot.push_back(id);event(w,'W',index,id);}
        id=next(id);
    }
    for(int member:snapshot){
        const bool isTechno=techno(member,w);
        if(!hasElite&&!ignoreDestination&&!w.rules1431){
            if(!isTechno)continue;
            if(!ability3(member,w)&&w.house194.at(w.members.at(member).owner)<w.rules10b4)continue;
        }
        services.scatter(member,at,ignoreMission,ignoreDestination);
    }
    if(capacity)services.release(capacity);
}
}
