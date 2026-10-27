// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/OwnedUnitOrders.hpp"
#include "assets/OwnedUnitDrawingMap.hpp"
#include <bit>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <limits>
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
    Fixture f;auto world=f.make();OwnedUnitOrders orders(*world,0.30000001192092896);
    auto a0=world->actor(0),a1=world->actor(1);world->select(1);
    const auto before=snapshot(*world);
    auto route=orders.directRoute(0,4,3);
    require(route&&route->destination==cellCenter(4,3)&&route->directions==std::vector<int>({3,3,2}),"Direct route is not diagonal-first");
    require(snapshot(*world)==before&&f.queries==0&&f.stores==0,"Route construction queried or changed live state");
    require(!orders.directRoute(0,1,1)&&!orders.directRoute(0,-1,1)&&!orders.directRoute(0,1024,1)&&!orders.directRoute(0,25,1),"Unsupported direct route accepted");
    require(orders.directRoute(0,24,1)->directions.size()==23,"23-Cell boundary rejected");
    a0.state.route.fill(7);a0.state.route[0]=2;a0.state.route[1]=-1;
    a0.commands.navigationTarget=cellCenter(2,1);a0.state.destination=cellCenter(2,1);
    route=orders.directRoute(0,3,2,true);
    require(route&&route->directions==std::vector<int>({2,3}),"Append copied retained tail or used the wrong anchor");
    a0.state.movement.driving=true;a0.state.movement.head=cellCenter(5,5);
    route=orders.directRoute(0,6,5);
    require(route&&route->directions==std::vector<int>({2}),"Replacement route ignored committed head");
    a0.state.movement.driving=false;
    const auto invalid=snapshot(*world);const auto queryCount=f.queries,storeCount=f.stores;
    for(int test=0;test<6;++test){bool refused=false;
        try{const std::array<int,1> good{2},bad{8};std::vector<int> longRoute(24,2);
            if(test==0)orders.order(2,cellCenter(2,1),good);
            if(test==1)orders.order(0,{},good);
            if(test==2)orders.order(0,cellCenter(2,1),std::span<const int>{});
            if(test==3)orders.order(0,cellCenter(2,1),bad);
            if(test==4)orders.order(0,cellCenter(2,1),longRoute);
            if(test==5)OwnedUnitOrders badScale(*world,std::numeric_limits<double>::infinity());
        }catch(const std::invalid_argument&){refused=true;}
        require(refused&&snapshot(*world)==invalid&&f.queries==queryCount&&f.stores==storeCount,"Invalid order queried or mutated live records");
    }
    // Alias-safe queue replacement and a distinct actor's selected/command state.
    a0.state.route[0]=2;a0.state.route[1]=3;
    orders.order(0,cellCenter(1,1),std::span<const int>(a0.state.route.data(),2));
    require(a0.state.route[0]==2&&a0.state.route[1]==3&&std::all_of(a0.state.route.begin()+2,a0.state.route.end(),[](int n){return n==-1;}),"Explicit order lost aliased directions or retained old tails");
    require(world->selected()==1&&!a1.commands.navigationTarget&&a1.state.route.front()==-1,"Explicit actor0 order routed through selection/actor1");
    a0.wait={19,23,29};a1.wait={31,37,41};
    a0.state.percentage=.8;a0.state.movement.driving=true;a0.state.movement.track=10;
    a0.state.movement.index=7;a0.state.movement.accumulator=17;
    const auto position=a0.state.movement.actor.position,head=a0.state.movement.head;
    orders.stop(0);
    require(a0.state.percentage==0.30000001192092896&&a0.state.destination==Coord{}&&a0.state.route.front()==-1&&
        a0.state.movement.driving&&a0.state.movement.track==10&&a0.state.movement.index==7&&a0.state.movement.accumulator==17&&
        a0.state.movement.actor.position==position&&a0.state.movement.head==head&&a0.wait.remaining==29&&a1.wait.remaining==41,"Stop changed committed track or shared wait records");
    a0.state.percentage=.1;orders.stop(0);require(a0.state.percentage==.1,"Stop raised a lower speed");
    const auto oldBody=a0.state.movement.body;orders.turnBody(0,65537,100);
    require(a0.commands.pendingBodyTurn==std::uint16_t(oldBody.desired+1)&&a0.state.movement.body.desired==oldBody.desired,"Moving body turn was not deferred/wrapped");
    orders.turnBody(0,-65537,101);
    const auto pending=std::uint16_t(oldBody.desired-1);
    require(a0.commands.pendingBodyTurn==pending,"Interrupted pending body turn accumulated against pending instead of actual Facing");
    orders.finishTick(0,102);require(a0.commands.pendingBodyTurn==pending,"Committed track lost its deferred turn");
    a0.state.movement.driving=false;a0.state.route[3]=7;
    orders.finishTick(0,103);
    require(!a0.commands.pendingBodyTurn&&a0.state.movement.body.desired==pending&&a0.turret.desired==oldBody.desired&&a0.state.route[3]==7,"Tick finalization changed retained tails or turret/body order");
    a1.state.movement.body.desired=65535;orders.turnBody(1,2,104);
    require(a1.state.movement.body.desired==1&&!a1.commands.pendingBodyTurn,"Idle actor1 body turn failed");
    a0.commands.pendingBodyTurn=4096;a0.commands.manualTurret=true;
    orders.order(0,cellCenter(1,1),std::array<int,1>{2});
    require(!a0.commands.pendingBodyTurn&&!a0.commands.manualTurret&&!a0.commands.stopRequested,"New move did not cancel old control policy");
    auto copy=world->clone();require(snapshot(*copy)==snapshot(*world),"Clone lost order state");
    const auto live=snapshot(*world);const auto q=f.queries,st=f.stores;
    const auto rejected=world->preview([](OwnedUnitWorld& preview){
        OwnedUnitOrders commands(preview,0.30000001192092896);
        commands.order(1,cellCenter(1,1),std::array<int,1>{4});commands.turnBody(0,-8192,105);
        commands.stop(1);commands.finishTick(0,106);preview.select(0);
        OwnedUnitDrawingMap map(*preview.context().map,*preview.context().unit);map.cell({-7,-8});map.floor({384,384,0});
        return false;
    });
    require(rejected.status==OwnedUnitPreviewStatus::rejected&&snapshot(*world)==live&&f.queries==q&&f.stores==st&&f.external==0,"Rejected command preview changed live map/actor/observer state");
    const auto bridge=world->preview([](OwnedUnitWorld& p){
        p.context().map->cells[0].attributes.input.flags|=0x100;
        OwnedUnitOrders(p,0.3).order(1,cellCenter(1,1),std::array<int,1>{4});return true;
    });
    require(bridge.status==OwnedUnitPreviewStatus::unsupportedRoute&&snapshot(*world)==live,"Unsupported bridge command escaped discarded owner");
    std::cout<<"Direct/append/committed route anchors; alias-safe all24 replacement; invalid-input isolation; independent stop/body commands; deferred turn/turret order; warm clone and rejected/bridge preview isolation: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
