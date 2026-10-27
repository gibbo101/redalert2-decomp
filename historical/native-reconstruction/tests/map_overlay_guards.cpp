// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapCellAttributes.hpp"
#include <stdexcept>
using namespace ra2;
template<class F>void refused(F f){bool caught=false;try{f();}catch(const std::invalid_argument&){caught=true;}if(!caught)throw std::runtime_error("Unsafe overlay input accepted");}
int main(){
    if(classifyMapOverlay(-1,nullptr,{})!=-1)throw std::runtime_error("Absent overlay touched bindings");
    refused([&]{classifyMapOverlay(0,nullptr,{});});
    MapOverlayType type;refused([&]{classifyMapOverlay(-2,&type,{});});
    MapCellInput cell;cell.land=-1;type.land=-1;
    if(overlayCellPassability(cell,false,&type,{})!=7)throw std::runtime_error("Permission lost priority");
    refused([&]{overlayCellPassability(cell,true,&type,{});});
    type.flag1FD=2;
    if(overlayCellPassability(cell,true,&type,{})!=1)throw std::runtime_error("Overlay gate lost priority");
    std::uint8_t data=71;MapResourceServices s;
    if(updateMapResource({},-1,data,s)!=0||data!=71)throw std::runtime_error("Absent resource changed data");
    refused([&]{updateMapResource({},0,data,s);});
    s.classify=[](int){return 0;};
    refused([&]{updateMapResource({},0,data,s);});
    std::array<MapResourceType,1> types{};s.types=types;types[0].numFrames=0;
    refused([&]{updateMapResource({},0,data,s);});
    types[0].numFrames=-1;refused([&]{updateMapResource({},0,data,s);});
    types[0].numFrames=1;refused([&]{updateMapResource({},0,data,s);});
    s.neighborOverlay=[](auto){return -1;};s.classify=[](int n){return n==-1?-1:0;};
    refused([&]{updateMapResource({},0,data,s);});
    if(data!=71)throw std::runtime_error("Refused resource fixture stored data");
    std::array<std::uint8_t,4>b4{};std::array<std::uint8_t,10>b10{};MapCellAttributes c;MapAttributeServices a;
    c.overlay=1;a.overlays=std::span(&type,1);
    refused([&]{recalculateMapCellAttributes(c,-1,b4,b10,a);});
    c.overlay=-2;refused([&]{recalculateMapCellAttributes(c,-1,b4,b10,a);});
}
