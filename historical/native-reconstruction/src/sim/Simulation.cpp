// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/Simulation.hpp"
#include <cmath>
#include <numbers>
#include <stdexcept>

namespace ra2 {
std::uint16_t directionTo(Position from,Position to) {
    // Host adapter for mouse/manual aim. Original grid direction 0 is decreasing Y.
    const auto angle=std::atan2(to.x-from.x,from.y-to.y);
    return std::uint16_t(std::int64_t(std::llround(angle*65536/(2*std::numbers::pi))));
}
static Coord startingCoordinate(Position p) {
    if(!std::isfinite(p.x)||!std::isfinite(p.y)||p.x<0||p.y<0||p.x>1024||p.y>1024)
        throw std::invalid_argument("Invalid simulation start");
    // Bounded flat-plane Z=0; terrain elevation remains separate presentation data.
    return {int(std::llround(p.x*256)),int(std::llround(p.y*256)),0};
}
Simulation::Simulation(Position start,int z,int rot,int speed,std::shared_ptr<const DriveData> data,bool passive)
    :data_(data),drive(std::move(data),startingCoordinate(start),rot,speed),elevation(z) {drive.passive=passive;refresh();}
Simulation::Simulation(const Simulation& other)
    :data_(other.data_),ground_(other.ground_?other.ground_->clone():nullptr),
     pendingBodyTurn_(other.pendingBodyTurn_),stopRequested_(other.stopRequested_),
     drive(other.drive),position(other.position),elevation(other.elevation),tick(other.tick),
     moving(other.moving),selected(other.selected),paused(other.paused),status(other.status){}
Simulation& Simulation::operator=(const Simulation& other){
    if(this!=&other){Simulation copy(other);*this=std::move(copy);}return *this;
}
void Simulation::enableGround(std::unique_ptr<GroundDriveContext> context){
    if(ground_||drive.active()||drive.passive||!context)throw std::invalid_argument("Ground binding requires an idle ordinary Unit");
    auto& state=context->state;const auto& services=context->services;
    state.movement.actor.position=drive.position;state.movement.body=drive.body;
    setActorRelativeHeight(state.movement.actor,0,416,services.advance.ground);
    unlimboDriveRamp(state.ramps,[&]{(void)services.cell(state.movement.actor.position);return services.cell(state.movement.actor.position).ramp;},tick,0);
    services.advance.ground.mark(1);
    drive.position=state.movement.actor.position;ground_=std::move(context);refresh();
}
void Simulation::groundMovement(){
    auto& s=ground_->state;auto& m=s.movement;
    m.actor.position=drive.position;m.head=drive.head;m.body=drive.body;m.track=drive.track;m.index=drive.index;
    m.accumulator=drive.accumulator;m.driving=drive.driving;s.wasRotating=drive.wasRotating;s.percentage=drive.movementScale;
    s.destination=drive.hasDestination?drive.destination:Coord{};
    ground_->process(*data_,drive.baseSpeed,tick,0);
    drive.position=m.actor.position;drive.head=m.head;drive.body=m.body;drive.track=m.track;drive.index=m.index;
    drive.accumulator=m.accumulator;drive.driving=m.driving;drive.wasRotating=s.wasRotating;drive.movementScale=s.percentage;
    drive.route.clear();for(int d:s.route){if(d==-1)break;drive.route.push_back(d);}
    // Arrival/mission completion is the prototype's target-lifetime adapter.
    if(!m.driving&&drive.route.empty()){drive.hasDestination=false;s.destination={};}
}
void Simulation::replaceGroundRoute(){
    if(!ground_)return;
    // Host command boundary only. Process owns all 24 words between commands,
    // including retained entries beyond its first -1 after failed admission.
    auto& route=ground_->state.route;route.fill(-1);
    std::copy(drive.route.begin(),drive.route.end(),route.begin());
}
void Simulation::refresh() {position={drive.position.x/256.0,drive.position.y/256.0};moving=drive.active();}
bool Simulation::move(Position target,const std::function<bool(int,int,int)>& clear,bool append) {
    if(!std::isfinite(target.x)||!std::isfinite(target.y)||target.x<0||target.y<0||target.x>=1024||target.y>=1024) return false;
    const Coord anchor=drive.driving?drive.head:drive.position;
    const Coord start=append&&drive.hasDestination?drive.destination:anchor;
    Coord destination=cellCenter(int(std::floor(target.x)),int(std::floor(target.y)));
    if(ground_&&!clear(destination.x/256,destination.y/256,elevation)){status="UNSUPPORTED OR BLOCKED TERRAIN DESTINATION";return false;}
    int dx=destination.x/256-start.x/256,dy=destination.y/256-start.y/256;
    std::vector<int> route;
    if(append&&drive.hasDestination) route.assign(drive.route.begin(),drive.route.end());
    const auto distance=std::max(std::abs(dx),std::abs(dy));
    if(distance==0) {status="CHOOSE A DIFFERENT DESTINATION CELL";return false;}
    if(route.size()+std::size_t(distance)>23) {status="BOUNDED ROUTE: AT MOST 23 QUEUED CELLS";return false;}
    // Temporary direct route: diagonal steps first, then the remaining axis.
    // No detours or search. The original core selects curves from this queue.
    while(dx||dy) {
        const int sx=(dx>0)-(dx<0),sy=(dy>0)-(dy<0);
        for(int d=0;d<8;++d) if(directionOffset(d)==std::pair{sx,sy}) {route.push_back(d);break;}
        dx-=sx;dy-=sy;
    }
    Simulation preview=*this;
    if(ground_)destination.z=preview.ground_->services.advance.ground.floor(destination);
    preview.drive.order(destination,route);preview.replaceGroundRoute();preview.paused=false;preview.pendingBodyTurn_.reset();
    auto previous=preview.drive.position;
    // Bounded sampled-footprint check over the actual recovered motion, including
    // the already committed track. It is not original collision/pathfinding code.
    bool completed=false;
    for(int step=0;step<4096;++step) {
        if(step){preview.tick=signed32(std::uint32_t(tick)+std::uint32_t(step));
            if(ground_){
                try{preview.groundMovement();}
                catch(const UnsupportedGroundRoute&){status="UNSUPPORTED TERRAIN ROUTE / NO DETOUR SEARCH";return false;}
                catch(const UnsupportedGroundAdmission&){status="UNSUPPORTED MOVEMENT ADMISSION / NO DETOUR SEARCH";return false;}
            }else preview.drive.processMovement(preview.tick);}
        const auto at=preview.drive.position;
        const int samples=std::max(1,(std::max(std::abs(at.x-previous.x),std::abs(at.y-previous.y))+15)/16);
        for(int sample=0;sample<=samples;++sample) {
            const double fraction=double(sample)/samples;
            const double x=(previous.x+(at.x-previous.x)*fraction)/256.0;
            const double y=(previous.y+(at.y-previous.y)*fraction)/256.0;
            for(double ox:{-0.25,0.25}) for(double oy:{-0.25,0.25}) {
                if(!clear(int(std::floor(x+ox)),int(std::floor(y+oy)),elevation)) {
                    status="DIRECT ROUTE BLOCKED / NO DETOUR SEARCH";return false;
                }
            }
        }
        previous=at;
        if(!preview.drive.active()) {
            completed=preview.drive.position.x==destination.x&&preview.drive.position.y==destination.y;
            if(!completed){status="MOVEMENT REJECTED / NO DETOUR SEARCH";return false;}
            break;
        }
    }
    if(!completed) {status="ROUTE EXCEEDS THE BOUNDED PREVIEW";return false;}
    drive.order(destination,route);replaceGroundRoute();drive.navigationTarget=destination;
    pendingBodyTurn_.reset();stopRequested_=false;refresh();
    status=append?"WAYPOINT APPENDED / ORIGINAL TRACK CURVES":"ORIGINAL TRACK CURVES / DIRECT-ROUTE ADAPTER";
    return true;
}
void Simulation::turnBody(int delta) {
    const auto heading=std::uint16_t(drive.body.desired+delta);drive.stop();replaceGroundRoute();drive.navigationTarget.reset();stopRequested_=true;
    if(drive.driving) pendingBodyTurn_=heading;
    else drive.body.setDesired(heading,tick);
    refresh();status="BODY TURN / ACTIVE TRACK FINISHES BEFORE MANUAL TURN";
}
void Simulation::turnTurret(int delta) {
    drive.manualTurret=true;drive.turret.setDesired(std::uint16_t(drive.turret.desired+delta),tick);
    status="MANUAL TURRET OVERRIDE / NEXT MOVE RESTORES FOLLOWING";
}
void Simulation::aim(Position target) {
    if(!std::isfinite(target.x)||!std::isfinite(target.y)) return;
    if(target.x<0||target.y<0||target.x>1024||target.y>1024) {status="AIM WITHIN THE MAP COORDINATE BOUNDS";return;}
    drive.aimAt(startingCoordinate(target),tick);
    status="RECOVERED BEARING / MANUAL AIM CONTROL";
}
void Simulation::stop() {drive.stop();replaceGroundRoute();drive.navigationTarget.reset();stopRequested_=true;pendingBodyTurn_.reset();refresh();status=drive.driving?"STOP REQUESTED / FINISHING ACTIVE TRACK":"STOPPED";}
void Simulation::step() {
    if(paused) return;tick=signed32(std::uint32_t(tick)+1);
    const bool wasMoving=moving;const auto target=drive.navigationTarget;
    if(ground_)groundMovement();else drive.processMovement(tick);
    // The prototype owns this coordinate target, not a full mission/actor object.
    // Clear it on arrival before the original turret update sees a zero vector.
    if(!drive.active()) drive.navigationTarget.reset();
    drive.updateTurret(tick);
    if(!drive.driving && pendingBodyTurn_) {drive.body.setDesired(*pendingBodyTurn_,tick);pendingBodyTurn_.reset();}
    refresh();if(wasMoving&&!moving){
        if(stopRequested_)status="STOPPED / ACTIVE TRACK FINISHED";
        else if(target&&(drive.position.x!=target->x||drive.position.y!=target->y))status="MOVEMENT REJECTED / NO DETOUR SEARCH";
        else status="ARRIVED / ORIGINAL TRACK MOVEMENT";
    }
}
}
