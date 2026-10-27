// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OccupiedCellPassability.hpp"
#include <stdexcept>
namespace ra2 {
void updateOccupiedCellPassability(int& destination,const MapCellInput& cell,bool permitted,
    const MapOverlayType* overlay,std::span<const float> speeds,const OccupiedCellPassabilityWorld& world){
    const auto write=[&](int v){destination=v;if(world.store)world.store(v);};
    const int base=overlayCellPassability(cell,permitted,overlay,speeds);
    if(base!=0||(overlay&&overlay->rubble)){write(base);return;}
    int id=world.head;std::size_t visits=0;
    while(id!=-1){
        if(++visits>world.actors.size())throw std::invalid_argument("Cyclic occupied Cell list outside native domain");
        const auto& a=world.actors.at(id);
        if(a.kind!=1&&a.kind!=6&&a.kind!=15&&a.kind!=36)throw std::invalid_argument("Unverified passability occupant kind");
        if(world.kindQuery)world.kindQuery(id,a.kind);
        if(a.kind==6){
            if(a.type135a){if(a.house142){write(6);return;}}
            else if(a.type1359&&a.mission!=12&&a.mission!=8)write(6);
            // This branch deliberately continues; a later final zero can
            // overwrite the intermediate six. There is no accumulated maximum.
        }else if(a.kind==36){
            write((world.theater==1?a.terrain27c:a.terrain278)==7?2:5);return;
        }
        id=a.next;
    }
    write(0);
}
}
