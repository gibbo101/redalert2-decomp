// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/UnitMark.hpp"
#include <stdexcept>
namespace ra2 {
namespace {
template<class F>const F& require(const F& f){
    if(!f)throw std::invalid_argument("Reached missing Unit Mark service");return f;
}
void redraw(FootMarkView a,const UnitMarkServices& s,const UnitMarkStore& store,
            const UnitMarkRedraw& entered) {
    if(entered)entered();
    if(a.needsRedraw)return;
    a.needsRedraw=1;if(store)store(0x75,1);
    require(s.redrawMap)();
}
}
bool markFootObject(FootMarkView a,int mode,const UnitMarkServices& s,
                    const UnitMarkStore& store,const UnitMarkRedraw& entered) {
    if(a.limbo)return false;
    if(mode==2) {
        if(a.needsRedraw||!a.onMap)return false;
        redraw(a,s,store,entered);return true;
    }
    // Actual Unit kind 1 passes the original techno-cast dispatch. These query
    // results are unused, but omitting their calls changes the original protocol.
    require(s.imageValue)();require(s.owner)();require(s.coordinates)();
    if((mode==1||mode==3)&&!a.onMap) {
        a.onMap=1;if(store)store(0x74,1);
        redraw(a,s,store,entered);return true;
    }
    if(mode==0&&a.onMap){a.onMap=0;if(store)store(0x74,0);return true;}
    return false;
}
bool markFootTechno(FootMarkView a,int mode,const UnitMarkServices& s,
                    const UnitMarkStore& store,const UnitMarkRedraw& entered) {
    if(!markFootObject(a,mode,s,store,entered))return false;
    if(a.special)require(s.specialEvent)(13);
    return true;
}
bool markFoot(FootMarkView a,int mode,const UnitMarkServices& s,
                  const UnitMarkStore& store,const UnitMarkRedraw& entered) {
    if(mode==2)return true;
    if(!markFootTechno(a,mode,s,store,entered))return false;
    if(require(s.layer)()==2) {
        const auto point=require(s.coordinates)();
        if(mode==0)require(s.remove)(point);
        else if(mode==1||mode==3)require(s.insert)(point);
    }
    return true;
}
bool markUnitObject(UnitMarkState& a,int mode,const UnitMarkServices& s,
    const UnitMarkStore& store,const UnitMarkRedraw& entered){
    return markFootObject({a.onMap,a.needsRedraw,a.limbo,a.special},mode,s,store,entered);
}
bool markUnitTechno(UnitMarkState& a,int mode,const UnitMarkServices& s,
    const UnitMarkStore& store,const UnitMarkRedraw& entered){
    return markFootTechno({a.onMap,a.needsRedraw,a.limbo,a.special},mode,s,store,entered);
}
bool markUnitFoot(UnitMarkState& a,int mode,const UnitMarkServices& s,
    const UnitMarkStore& store,const UnitMarkRedraw& entered){
    return markFoot({a.onMap,a.needsRedraw,a.limbo,a.special},mode,s,store,entered);
}
}
