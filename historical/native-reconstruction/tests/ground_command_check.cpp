// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/Simulation.hpp"
#include "assets/UnitMovementRestriction.hpp"
#include <algorithm>
#include <iostream>
using namespace ra2;
namespace {
void require(bool b,const char* message){if(!b)throw std::runtime_error(message);}
// Diagnostic command boundary, deliberately not an original behavior oracle.
struct CommandContext final:GroundDriveContext {
    enum Mode {Arrive,Reject,Unsupported,Fault} mode=Arrive;
    std::vector<std::array<int,24>> seen;
    CommandContext(){
        services.advance.ground.floor=[](Coord){return 0;};
        services.advance.ground.mark=[](int){};
        services.cell=[](Coord){return GroundDriveCell{};};
    }
    std::unique_ptr<GroundDriveContext> clone()const override{return std::make_unique<CommandContext>(*this);}
    bool process(const DriveData&,int,int,int,const GroundStateStore&,const GroundStateStore&)override{
        seen.push_back(state.route);
        if(state.destination==Coord{})return false;
        if(mode==Unsupported)throw UnsupportedGroundAdmission(7);
        if(mode==Fault)throw std::invalid_argument("Diagnostic unrelated fault");
        if(mode==Arrive){state.movement.actor.position=state.destination;state.route.fill(-1);}
        else state.route[0]=-1;
        state.movement.head={};state.movement.driving=false;return false;
    }
};
bool empty(const std::array<int,24>& route){return std::all_of(route.begin(),route.end(),[](int n){return n==-1;});}
}
int main(){try{
    auto data=std::make_shared<DriveData>();data->tracks[0].points={{0,0,0}};data->tracks[1].points={{0,0,0}};
    Simulation sim({10.5,10.5},0,5,6,data);auto owner=std::make_unique<CommandContext>();auto* c=owner.get();
    c->state.route[1]=6;c->state.route[2]=4;const auto tail=c->state.route;
    sim.enableGround(std::move(owner));sim.step();sim.step();
    require(sim.groundState()->route==tail&&c->seen==std::vector{tail,tail},"Idle tick erased retained route words");
    Simulation copy=sim;require(copy.groundState()->route==tail,"Copy erased retained words");
    copy.stop();require(empty(copy.groundState()->route)&&sim.groundState()->route==tail,"Copy stop mutated source queue");
    sim.turnBody(8192);require(empty(sim.groundState()->route),"Body-turn command retained queue tails");
    c->state.route=tail;sim.stop();require(empty(sim.groundState()->route),"Stop command retained queue tails");
    const auto clear=[](int,int,int){return true;};
    c->state.route=tail;require(sim.move({12.5,10.5},clear),"Diagnostic valid command refused");
    require(c->state.route[0]==2&&c->state.route[1]==2&&c->state.route[2]==-1&&c->state.route[23]==-1,"Move command did not replace complete queue");
    require(c->seen.size()==2&&sim.coordinates()==cellCenter(10,10),"Preview changed live context");
    const auto ordered=c->state.route;const auto before=sim.coordinates();const int tick=sim.tick;
    c->mode=CommandContext::Unsupported;
    require(!sim.move({13.5,10.5},clear)&&sim.status=="UNSUPPORTED MOVEMENT ADMISSION / NO DETOUR SEARCH","Unsupported admission preview disguised as success");
    require(c->state.route==ordered&&sim.coordinates()==before&&sim.tick==tick,"Refused preview changed live state");
    c->mode=CommandContext::Fault;bool fault=false;
    try{sim.move({13.5,10.5},clear);}catch(const std::invalid_argument&){fault=true;}
    require(fault,"Unrelated preview fault was swallowed");
    c->mode=CommandContext::Reject;
    require(!sim.move({13.5,10.5},clear)&&sim.status=="MOVEMENT REJECTED / NO DETOUR SEARCH","Rejected preview reported arrival or timeout");
    c->mode=CommandContext::Unsupported;bool refused=false;
    try{sim.step();}catch(const UnsupportedGroundAdmission& e){refused=e.result==7;}
    require(refused,"Live unsupported outcome continued instead of propagating");
    c->mode=CommandContext::Reject;sim.step();
    require(!sim.moving&&sim.status=="MOVEMENT REJECTED / NO DETOUR SEARCH","Live rejection reported arrival");
    require(c->state.route[0]==-1&&c->state.route[1]==2,"Rejected Process tail was lost");
    const auto rejected=c->state.route;sim.step();require(c->state.route==rejected,"Tick after rejection erased retained words");
    require(readUnitMovementRestriction(Ini("[HTNK]\nMovementZone=Destroyer\n"),"HTNK")==-1,"MovementZone confused with restriction");
    for(const auto* value:{"","None","-1","Destroyer"}){
        bool present=false;try{(void)readUnitMovementRestriction(Ini(std::string("[HTNK]\nMovementRestrictedTo=")+value+"\n"),"HTNK");}
        catch(const std::invalid_argument&){present=true;}
        require(present,"Unverified present restriction input accepted");
    }
    std::cout<<"Command queue retention/reset, copy/preview isolation, explicit rejection/refusal and missing restriction guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
