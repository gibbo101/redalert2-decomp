// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/PreparedUnitAdmission.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
PreparedUnitAdmission::PreparedUnitAdmission(PreparedMembershipMap map,PreparedUnitMembership& member,
    GroundDriveProcessState& state,const GroundDriveProcessServices& services,
    PreparedUnitAdmissionInputs inputs,const PreparedUnitMembership::Query& query,const Decision& decision)
    :map_(map),member_(member),state_(state),inputs_(inputs),query_(query),decision_(decision){
    const auto shared=member_.world();
    if(map_.slots.size()!=262144||map_.cells.size()+1!=member_.occupation.size()||
       shared.cells.data()!=map_.resident.world.cells.data()||shared.fallback!=&map_.fallback.input)
        throw std::invalid_argument("Prepared admission requires canonical membership Cells");
    world_.gates.slots=map_.slots;world_.gates.fallbackCell=int(map_.cells.size());
    world_.gates.houses[0]={inputs.houseIndex,inputs.houseAllies};
    world_.gates.objects[0].owner=0;world_.objects[0].crusher=inputs.crusher;
    world_.directions={TerrainCellPoint{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
    for(unsigned i=0;i<12;++i)world_.speedBits[i]=std::bit_cast<std::uint32_t>(services.trackSpeed[i]);
    world_.gates.fallbackStore=[this](TerrainCellPoint p){fallback(p);};
    world_.trace=[this](char kind,int a,int b,int){
        if(kind=='L'&&query_)query_('W',{a,b,0});
        if(kind=='F')fallback({std::int16_t(a),std::int16_t(b)});
    };
    refresh(0);
}
void PreparedUnitAdmission::event(char kind,int a,int b,int c)const{if(decision_)decision_(kind,a,b,c);}
void PreparedUnitAdmission::fallback(TerrainCellPoint p){
    // This updates the map, membership and visibility views before returning to
    // the original decision. Do not defer it to the end of a Process tick.
    member_.world().fallbackStore({p.x,p.y});
}
void PreparedUnitAdmission::refresh(int tick){
    if(member_.membership.actors.size()!=(inputs_.parkedResident?2u:1u)||!member_.membership.actors.contains(0)||
       member_.discovery.owner!=0||member_.discovery.hasTag||member_.houses.loading!=1||
       state_.movement.actor.bridge79)
        throw std::invalid_argument("Prepared admission requires explicitly bound loaded nonbridge Units and House 0");
    world_.gates.tick=tick;
    for(const auto& [id,member]:member_.membership.actors){
        if(id!=0&&(!inputs_.parkedResident||id!=1))
            throw std::invalid_argument("Prepared admission actor identity outside joined profile");
        const auto& discovery=member_.actorDiscovery(id);
        const auto& drive=member_.actorState(id).movement;
        if(discovery.owner!=0||discovery.hasTag||drive.actor.bridge79||member.alternate||
           (member.next!=-1&&!member_.membership.actors.contains(member.next))||
           (id==1&&(drive.driving||drive.head!=Coord{}||drive.track!=-1||drive.body.rotating(tick))))
            throw std::invalid_argument("Prepared admission resident is not a stationary allied Unit");
        auto& actor=world_.gates.objects[id];actor.owner=0;actor.mission=discovery;actor.next=member.next;
        world_.objects[id].flags=5;
    }
    for(std::size_t i=0;i<=map_.cells.size();++i){
        const auto& c=i==map_.cells.size()?map_.fallback:*map_.cells[i];
        const auto& m=member_.cellMembership(i);
        const auto valid=[&](int id){return id==-1||member_.membership.actors.contains(id);};
        if(!valid(m.head)||!valid(m.alternateHead))
            throw std::invalid_argument("Prepared admission stationary residents are not joined");
        auto& gate=world_.gates.cells[int(i)];gate.point={c.input.position.x,c.input.position.y};gate.head=m.head;
        auto& a=world_.cells[int(i)];a.level=c.input.level;a.ramp=c.input.slope;a.flags=c.input.flags;
        a.land=c.input.land;a.elevatedHead=m.alternateHead;
        a.occupation=member_.occupation[i].ground;a.elevatedOccupation=member_.occupation[i].elevated;
    }
}
int PreparedUnitAdmission::identity(const MapCellInput& c)const{
    if(&c==&map_.fallback.input)return int(map_.cells.size());
    const int slot=int(c.position.y)*512+int(c.position.x);
    if(slot<0||slot>=262144)throw std::invalid_argument("Prepared admission Cell outside table");
    const int id=map_.slots[std::size_t(slot)];
    if(id<0||std::size_t(id)>=map_.cells.size()||&map_.cells[std::size_t(id)]->input!=&c)
        throw std::invalid_argument("Prepared admission Cell identity is not canonical");
    return id;
}
bool PreparedUnitAdmission::gates(std::int16_t x,std::int16_t y,int tick){
    refresh(tick);event('G',x,y);const bool result=checkMovementGates(0,{x,y},world_.gates);
    event('g',result);return result;
}
int PreparedUnitAdmission::admit(const GroundDriveCell& c,int direction,int level,int tick){
    if(!c.identity)throw std::invalid_argument("Prepared admission retained a null Cell");
    refresh(tick);const int id=identity(*static_cast<const MapCellInput*>(c.identity));event('D',id,direction,level);
    const int result=ordinaryUnitAdmission(0,id,direction,level,-1,1,world_);event('d',result);return result;
}
void PreparedUnitAdmission::next(std::int16_t x,std::int16_t y){
    refresh(world_.gates.tick);event('N',x,y);
    ordinaryUnitNextCell(0,{state_.movement.actor.position,state_.movement.actor.bridge79},{x,y},1,world_);
}
GroundDriveProcessServices PreparedUnitAdmission::bind(GroundDriveProcessServices services){
    services.reserve={};services.admit={};
    // Binding is held by the stable owner. The returned callback is never copied
    // into another simulation; the clone constructs a new admission owner.
    services.markNext=[this](auto x,auto y){next(x,y);};
    return services;
}
bool PreparedUnitAdmission::process(const DriveData& data,int speed,int tick,int padding,
    const GroundDriveProcessServices& services,const GroundStateStore& actorStore,
    const GroundStateStore& rampStore,const GroundStateStore& driveStore){
    GroundDriveAdmissionServices admission;
    admission.check=[this,tick](const auto& c,int direction,int level){return admit(c,direction,level,tick);};
    admission.driveStore=driveStore;
    if(inputs_.parkedResident)return processResidentOrdinaryGroundDrive(state_,data,speed,tick,padding,services,
        [this,tick](auto x,auto y){return gates(x,y,tick);},admission,inputs_.residentRetry,actorStore,rampStore);
    return processAdmittedOrdinaryGroundDrive(state_,data,speed,tick,padding,services,
        [this,tick](auto x,auto y){return gates(x,y,tick);},admission,actorStore,rampStore);
}
}
