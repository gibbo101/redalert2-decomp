// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitDrawCaller.hpp"
#include "render/UnitTypeVisibility.hpp"
#include "sim/OriginalMath.hpp"
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return signed32(std::uint32_t(a)+std::uint32_t(b));}
int sub(int a,int b){return signed32(std::uint32_t(a)-std::uint32_t(b));}
void emit(const UnitDrawTrace& t,char k,int v){if(t)t(k,v);}
}
bool registerUnitScreen(UnitScreenRegistry& registry,int actor,PixelPoint p,PixelPoint origin,
                        int width,int height,const UnitDrawTrace& trace){
    if(registry.count<0||registry.count>500)throw std::invalid_argument("Invalid Unit screen registry count");
    if(registry.count==500||p.x<-32||p.x>add(width,32)||p.y<-32||p.y>add(height,32))return false;
    auto& entry=registry.entries[std::size_t(registry.count)];
    entry.actor=actor;emit(trace,'r',actor);
    entry.point.x=add(p.x,origin.x);emit(trace,'x',entry.point.x);
    entry.point.y=add(p.y,origin.y);emit(trace,'y',entry.point.y);
    ++registry.count;emit(trace,'n',registry.count);return true;
}
void drawOrdinaryUnitCaller(UnitDrawResource& resource,const OrdinaryUnitDrawInputs& actor,
                           PixelPoint point,PixelRect bounds,const OrdinaryUnitDrawServices& s,
                           const UnitDrawTrace& trace){
    if(actor.type.harvester||actor.alternate.harvester||actor.bridge||actor.flagHouse!=-1)
        throw std::invalid_argument("Unsupported ordinary Unit DrawIt profile");
    if(!(resource.flags&1)){
        resource.flags|=1;emit(trace,'i',resource.flags);
        resource.shape=s.loadShape();emit(trace,'h',signed32(resource.shape));
    }
    point.y=sub(point.y,actor.screenOffset);const auto footPoint=point;
    if(actor.addFourteen)point.y=add(point.y,14);
    const auto cell=unitLightCell(actor.coordinates.x,actor.coordinates.y);
    emit(trace,'C',cell.x);emit(trace,'C',cell.y);
    if(s.layer()==5)return;
    s.registerScreen(actor.actor,point);
    // Actual Object height helper calls ground before coordinate cell lookup.
    (void)sub(actor.coordinates.z,s.groundHeight(actor.coordinates));
    if(s.coordinateCell(actor.coordinates).flags&0x100)
        throw std::invalid_argument("Alternate Unit cell lighting is unrecovered");
    const auto first=s.lightCell(cell);
    const bool predicate=(first.flags&0x10000)?s.brightnessPredicate()!=0:false;
    const auto second=s.lightCell(cell);
    // Flags come from the first lookup; ambient comes from the second lookup.
    const int brightness=ordinaryUnitBrightness(second.ambient,actor.extraLight,first.flags,predicate);
    const bool original=s.originalTypeVisible()!=0;
    if(!original)s.alternateType();
    const auto& type=original?actor.type:actor.alternate;
    if(actor.secondaryIndex==-1&&(!type.voxel||type.voxelModel))
        s.draw(type.voxel!=0,point,bounds,brightness);
    // The original restores +0x5AC even without a transient type change.
    emit(trace,'T',0);
    s.footDecoration(footPoint,bounds);
    if(unitDrawTimerHasRemainder(actor.timerStart,actor.timerDuration,actor.currentFrame))s.timerDecoration();
}
}
