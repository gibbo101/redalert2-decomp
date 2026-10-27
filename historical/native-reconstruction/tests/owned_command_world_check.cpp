// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/OwnedUnitWorld.hpp"
#include "assets/OwnedUnitDrawingMap.hpp"
#include <bit>
#include <iostream>
#include <sstream>
#include <type_traits>
using namespace ra2;
namespace {
void require(bool v,const char* message){if(!v)throw std::runtime_error(message);}
std::string snapshot(const TerrainUnitContext& c){
    std::ostringstream out;const auto put=[&](auto... v){((out<<+v<<' '),...);};
    const auto point=[&](Coord p){put(p.x,p.y,p.z);};
    const auto state=[&](const GroundDriveProcessState& s,const UnitMarkState& mark,const UnitDiscoveryActor& d){
        const auto& m=s.movement;point(m.actor.position);point(m.head);put(m.actor.marked74,m.actor.bridge79,m.reached5a0,m.reached5a1,
            m.track,m.index,m.accumulator,m.driving,m.body.desired,m.body.start,m.body.timerStart,m.body.duration,m.body.rate);
        const auto& r=s.ramps;put(r.current,r.previous,r.start,r.padding,r.remaining,r.duration);point(s.destination);
        for(int n:s.route)put(n);put(std::bit_cast<std::uint64_t>(s.percentage),std::bit_cast<std::uint64_t>(s.instancePercentage),
            s.wasRotating,s.crossing57b,s.preparation57a,s.nextX,s.nextY,s.retryStart,s.retryPadding,s.retryRemaining);
        put(mark.onMap,mark.needsRedraw,mark.limbo,mark.special,d.field372,d.current373,d.other374,d.queuedA4,d.owner,d.mission98,d.queuedA0,d.hasTag);
    };
    const auto cell=[&](const MapCellAttributes& a){const auto& v=a.input;
        put(v.position.x,v.position.y,v.tile,v.land,v.tube,v.subTile,v.ice,v.slope,v.level,v.flags,a.overlay,a.passability,a.overlayData,a.extraHeight);};
    const auto& map=*c.map;for(const auto& v:map.cells){cell(v.attributes);put(v.field30,v.wallOwner);}cell(map.fallback);
    put(map.floor.flags,std::bit_cast<std::uint64_t>(map.floor.height),std::bit_cast<std::uint64_t>(map.floor.scale));
    for(const auto& p:map.floor.planes)for(double n:{p.x,p.y,p.offset,p.limit,p.add})put(std::bit_cast<std::uint64_t>(n));
    for(auto n:map.buffer4)put(n);for(auto n:map.buffer10)put(n);
    const auto& u=*c.unit;const auto& f=u.membership.foundation;
    put(f.objectFlag,f.unitFlag,f.fallback.x,f.fallback.y);for(auto p:f.unit)put(p.x,p.y);
    for(const auto& [id,a]:u.membership.actors){put(id);point(a.position);put(a.next,a.alternate,a.eligible,a.typeMapFlag);}
    for(const auto& [id,v]:u.membership.cells)put(id,v.point.x,v.point.y,v.head,v.alternateHead);
    for(const auto& o:u.occupation)put(o.flags,o.ground,o.elevated);
    for(const auto& v:u.visibilityCells)put(v.point.x,v.point.y,v.flags12c,v.flags140);
    put(u.visibility.heightDivisor,u.visibility.mode,u.visibility.overrideValue,u.visibility.currentHouse13d,u.occupationThreshold,
        u.houses.currentHouse,u.houses.mode,u.houses.loading,u.houses.tagContext,u.membership.services.visibilityGate,u.membership.services.notificationArgument);
    for(const auto& [id,h]:u.houses.houses)put(id,h.human134,h.control135,h.discovered13c,h.field13d,h.field5668,h.field5669);
    put(c.redraw.mapMode,c.redraw.counter,c.redraw.tactical,c.redraw.tacticalPresent);
    state(c.state,u.marking,u.discovery);
    if(c.parked){state(c.parked->state,c.parked->marking,c.parked->discovery);
        put(c.parked->turret.has_value());if(c.parked->turret){const auto& t=*c.parked->turret;
            put(t.desired,t.start,t.timerStart,t.duration,t.rate);}}
    return out.str();
}

std::string snapshot(OwnedUnitWorld& world){
    std::ostringstream s;s<<snapshot(world.context())<<world.selected()<<' ';
    for(int id:{0,1}){auto a=world.actor(id);const auto& t=a.turret;const auto& c=a.commands;
        s<<t.desired<<' '<<t.start<<' '<<t.timerStart<<' '<<t.duration<<' '<<t.rate<<' '
         <<a.wait.start<<' '<<a.wait.padding<<' '<<a.wait.remaining<<' '
         <<c.manualTurret<<c.turretTurning<<c.stopRequested<<' ';
        if(c.navigationTarget)s<<c.navigationTarget->x<<' '<<c.navigationTarget->y<<' '<<c.navigationTarget->z;
        s<<'/'<<c.pendingBodyTurn.value_or(0)<<' '<<c.pendingBodyTurn.has_value()<<';';
    }return s.str();
}
const OwnedUnitProcessesInputs inputs{5,1,0,0,8,
    std::array<OwnedUnitProcessActorInputs,2>{OwnedUnitProcessActorInputs{{19,-23},31},OwnedUnitProcessActorInputs{{-29,37},-41}}};
struct Fixture {
    std::vector<MapFinalizationCell> cells{1};std::vector<int> slots=std::vector<int>(262144,-1);
    MapCellAttributes fallback;MapFloorHeightState floor;std::array<int,16> land{};std::array<float,11> speeds{};
    ResidentCellInputs resident;Bytes b4=Bytes(64),b10=Bytes(160);
    std::shared_ptr<const DriveData> data=std::make_shared<const DriveData>();
    std::shared_ptr<const int> numeric=std::make_shared<const int>(1);
    int queries=0,stores=0,external=0;
    Fixture(){cells[0].attributes.input.position={1,1};slots[513]=0;resident.landMap=land;resident.wheelSpeeds=speeds;}
    std::unique_ptr<TerrainUnitContext> context(bool parked=true,bool turret=true){
        UnitMapSeed seed{cells,slots,fallback,floor,resident,b4,b10,2,1,104};
        GroundDriveProcessServices supplied;
        supplied.noRoute=[this]{++external;};supplied.advance.notify=[this](int){++external;};supplied.advance.postCell=[this]{++external;};
        supplied.squareRoot=[this](double n){++external;return n;};
        GroundDriveProcessState initial;initial.movement.actor.position={384,384,0};initial.movement.reached5a0=1;
        initial.movement.body.rate=1792;
        auto c=std::make_unique<TerrainUnitContext>(std::make_shared<MutableUnitMap>(seed),supplied,initial,
            [this](int,int){++stores;},[this](char,int,int,std::uint32_t){++stores;},[this](char,Coord){++queries;});
        if(parked){UnitDiscoveryActor d;d.owner=0;d.mission98=2;d.queuedA0=-1;d.queuedA4=255;
            Facing t;t.rate=1792;t.desired=t.start=30000;
            c->bindParked(initial,{},d,[this](int,int){++stores;},turret?std::optional<Facing>(t):std::nullopt);}
        return c;
    }
    OwnedUnitWorldNumerics numerics(){return {numeric,[](double n){return n;}};}
    std::unique_ptr<OwnedUnitWorld> make(){return std::make_unique<OwnedUnitWorld>(context(),data,numerics(),inputs,Facing{});}
};
}
int main(){try{
    static_assert(!std::is_move_constructible_v<OwnedUnitWorld> && !std::is_copy_constructible_v<OwnedUnitWorld>);
    Fixture f;int guards=0;
    for(int test=0;test<7;++test){
        bool refused=false;
        try{auto c=f.context(test!=0,test!=1);auto data=f.data;auto numeric=f.numerics();auto in=inputs;
            if(test==2)data.reset();if(test==3)numeric.owner.reset();if(test==4)numeric.squareRoot={};
            if(test==5)c->enableAdmission({1,0,0,true,{}});if(test==6)in.flags=4;
            OwnedUnitWorld bad(std::move(c),data,numeric,in,Facing{});
        }catch(const std::invalid_argument&){refused=true;}
        require(refused && f.queries==0 && f.stores==0 && f.external==0,"Owner guard queried or mutated inputs");++guards;
    }
    auto world=f.make();auto a0=world->actor(0),a1=world->actor(1);
    require(&a0.state==&world->context().unit->actorState(0)&&&a1.state==&world->context().unit->actorState(1)&&
        &a0.state!=&a1.state&&&a0.turret!=&a1.turret&&&a0.commands!=&a1.commands&&&a0.wait!=&a1.wait,"Owner aliases actor records");
    require(f.queries==0&&f.stores==0,"Owner constructor made a query");
    const auto initial=snapshot(*world);
    for(int id:{-2,2}){bool refused=false;try{world->select(id);}catch(const std::invalid_argument&){refused=true;}
        require(refused&&snapshot(*world)==initial,"Invalid actor changed selection");}
    for(int missing=0;missing<4;++missing){
        OwnedUnitWorldCall call;call.notify=[](int){};call.postCell=[]{ };call.noRoute=[]{ };call.failedRoute=[](int){};
        if(missing==0)call.notify={};if(missing==1)call.postCell={};if(missing==2)call.noRoute={};if(missing==3)call.failedRoute={};
        bool refused=false;try{world->process(0,6,100,7,call);}catch(const std::invalid_argument&){refused=true;}
        require(refused&&snapshot(*world)==initial&&f.queries==0&&f.stores==0,"Missing named service queried or changed the owner");
    }
    a0.wait={17,19,23};a1.wait={29,31,37};world->select(1);
    a0.commands.navigationTarget=Coord{640,384,0};a0.commands.pendingBodyTurn=16384;a0.commands.stopRequested=true;
    const auto other=a0.turret;world->turnTurret(1,8192,100);world->updateTurret(1,101);
    require(a1.commands.manualTurret&&!a0.commands.manualTurret&&a0.turret.desired==other.desired&&
        a0.turret.timerStart==other.timerStart,"Actor1 turret command touched actor0");
    auto copy=world->clone();require(snapshot(*copy)==snapshot(*world),"Clone lost logical command/wait/turret state");
    require(copy->context().map.get()!=world->context().map.get()&&copy->context().unit.get()!=world->context().unit.get(),"Clone shares mutable owners");
    const auto live=snapshot(*world);const auto q=f.queries,st=f.stores;
    {OwnedUnitDrawingMap draw(*copy->context().map,*copy->context().unit);draw.cell({-4,-5});draw.floor({384,384,0});}
    copy->actor(0).wait.remaining=91;copy->turnTurret(0,-4096,102);copy->select(0);
    auto twice=copy->clone();{OwnedUnitDrawingMap draw(*twice->context().map,*twice->context().unit);draw.cell({-7,-8});}
    require(snapshot(*world)==live&&f.queries==q&&f.stores==st&&f.external==0,"Cloned map/wait/turret has live callbacks");
    auto moved=std::move(copy);require(moved->actor(0).wait.remaining==91,"Pointer move lost actor owners");
    int notified=0,reentries=0;OwnedUnitWorldCall silent;silent.failedRoute=[](int){};silent.notify=[](int){};silent.postCell=[]{ };silent.noRoute=[]{ };
    const auto result=world->preview([&](OwnedUnitWorld& preview){
        preview.actor(0).state.wasRotating=true;
        OwnedUnitWorldCall call;call.failedRoute=[](int){};call.notify=[](int){};call.postCell=[]{ };call.noRoute=[]{ };
        call.notify=[&](int){
            ++notified;
            try{preview.process(1,6,100,7,silent);}catch(const std::logic_error&){++reentries;}
            throw std::runtime_error("notify failure");
        };
        bool caught=false;try{preview.process(0,6,100,7,call);}catch(const std::runtime_error& e){caught=std::string(e.what())=="notify failure";}
        require(caught&&notified==1&&reentries==1,"Scoped callback/Process reentry guard did not run");
        // A stale call reference would dispatch the notification again here.
        preview.context().services.advance.notify(8);require(notified==1,"Throwing callback left active services installed");
        preview.process(1,6,101,7,silent);return false;
    });
    require(result.status==OwnedUnitPreviewStatus::rejected,"Preview did not reach the supplied rejection");
    require(snapshot(*world)==live,"Rejected preview changed live owner");
    for(int mode:{0,1,2}){
        const auto r=world->preview([&](OwnedUnitWorld& p)->bool{p.actor(1).wait.start=90;p.select(0);
            if(mode==0)throw UnsupportedGroundRoute("diagnostic domain");
            if(mode==1)throw UnsupportedGroundAdmission(7);return true;});
        require(r.status==(mode==0?OwnedUnitPreviewStatus::unsupportedRoute:mode==1?OwnedUnitPreviewStatus::unsupportedAdmission:OwnedUnitPreviewStatus::accepted)&&
            (mode!=1||r.admission==7)&&snapshot(*world)==live,"Preview domain result or isolation differs");
    }
    bool fault=false;try{world->preview([](OwnedUnitWorld& p)->bool{p.actor(0).wait.start=81;throw std::runtime_error("unrelated");});}
    catch(const std::runtime_error& e){fault=std::string(e.what())=="unrelated";}
    require(fault&&snapshot(*world)==live,"Preview swallowed a fault or changed live state");
    const std::weak_ptr<const int> numeric=f.numeric;f.numeric.reset();require(!numeric.expired(),"World lost immutable numeric lifetime");
    world.reset();moved.reset();require(!numeric.expired(),"Reclone lost numeric lifetime");
    twice->actor(1).state.wasRotating=true;twice->process(1,6,102,7,silent);
    require(f.external==0,"Reclone used destroyed source services");
    twice.reset();require(numeric.expired(),"Numeric owner leaked");
    std::cout<<guards<<" no-query constructor refusals; exact actor references; separate command/turret/wait; warm clone/reclone/map/observer isolation; scoped throw/reentry restoration; preview results/fault propagation; numeric lifetime: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
