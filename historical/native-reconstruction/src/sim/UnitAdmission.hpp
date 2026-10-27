// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MovementGate.hpp"
#include <optional>
#include "sim/Drive.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <bit>
#include <stdexcept>
namespace ra2 {
struct UnitAdmissionCell {
    std::int16_t registry=-1;
    std::int8_t level=0;
    std::uint8_t ramp=0;
    std::uint32_t flags=0,occupation=0,elevatedOccupation=0;
    int owner=-1,elevatedOwner=-1,land=0,elevatedHead=-1;
};
struct UnitAdmissionRegistry {TerrainCellPoint point;int direction=0;};
struct UnitAdmissionObject {
    std::uint8_t flags=5,crushable=0,crusher=0,train=0,building1350=0;
    int state1b8=0,target=-1,destination=-1;
    bool weapon=false,projectile275=false;
    int targetIdentity()const{return target;}
};
// Initial records and associations are supplied. Gate records own canonical
// coordinates, primary lists, kind/Next/House/mission/animation values. The
// additional Cell/object records use those same logical identities.
struct UnitAdmissionWorld {
    MovementGateWorld gates;
    std::map<int,UnitAdmissionCell> cells;
    std::map<int,UnitAdmissionObject> objects;
    std::vector<std::optional<UnitAdmissionRegistry>> registry;
    std::array<std::uint32_t,12> speedBits{};
    std::array<TerrainCellPoint,8> directions{};
    // Read-only query and selected output-store observer: kind, subject, a, b.
    std::function<void(char,int,int,int)> trace;
};
// Borrow stable fields from the selected Cell/type, House and selected weapon.
// Lookup returns null only for overlay -1. Registry/initial associations remain
// supplied; callbacks must not manufacture admission results or mutate owners.
struct UnitAdmissionOverlayView {
    const std::uint8_t& flag27a;const std::uint8_t& wall;const std::uint8_t& crushable;
    const int& armor;const int& owner;
};
struct UnitAdmissionOverlayHouseView {const std::uint8_t& human134;const std::uint8_t& control135;};
struct UnitAdmissionOverlayWeaponView {const std::uint8_t& flag144;const std::uint8_t& flag146;};
struct UnitAdmissionOverlayServices {
    std::function<std::optional<UnitAdmissionOverlayView>(int)> cell;
    std::function<UnitAdmissionOverlayHouseView(int)> house;
    std::function<UnitAdmissionOverlayWeaponView(int)> weapon;
    const int& overrideA3d298;
};
// Complete Foot elevation/ramp decision. A null previous Cell requests the
// opposite-neighbor lookup, including when direction is -1. Output bytes are
// retained unless the original writes them. Cells share one fallback identity.
int unitTerrainAdmission(int target,int direction,int& level,std::uint8_t& elevated,
    int previous,UnitAdmissionWorld&);
// Complete Unit admission in the overlay-free, UnitType+B94 restriction -1, loading=1,
// unpromoted/count704=0 profile. Stable stationary Unit and ordinary/gate Building
// residents, no team/passengers/special Building type flags, actual Drive leaves.
// Numeric return codes are deliberately unnamed. Moving/combat/overlay branches
// are outside this entry's supported domain, not fabricated success callbacks.
int ordinaryUnitAdmission(int mover,int target,int direction,int level,int previous,
    std::uint8_t consultLocomotor,UnitAdmissionWorld&);
// Same admission kernel with actual overlay/House/weapon decisions. This does
// not perform crushing, destruction, destination assignment or movement.
int overlayUnitAdmission(int mover,int target,int direction,int level,int previous,
    std::uint8_t consultLocomotor,UnitAdmissionWorld&,const UnitAdmissionOverlayServices&);
// Shared inputs for the stationary and moving policy; these are supplied views.
struct UnitAdmissionMotionActor {
    Coord position,destination,head;
    Facing body;
    std::uint8_t eligibility5a0=1;
    int queueHead=-1,track=0,index=0;
    std::uint8_t shortTrack=0;
};
struct UnitAdmissionMotionWorld {
    std::map<int,UnitAdmissionMotionActor> actors;
    const DriveData* data=nullptr;
    // Bind the recovered original table sqrt; no host std::sqrt substitution.
    std::function<double(double)> squareRoot;
};

namespace admission_detail {
bool isMoving(const UnitAdmissionMotionActor&);
bool switchPending(const UnitAdmissionMotionActor&,const DriveData&);
int directionBin(std::uint16_t);
}

namespace unit_admission_policy {
template<class Actor>
bool isMoving(const Actor& a){
    return a.destination!=Coord{}||(a.head!=Coord{}&&
        (a.head.x!=a.position.x||a.head.y!=a.position.y));
}
template<class Actor>
bool switchPending(const Actor& a,const DriveData& data){
    if(a.queueHead< -1||a.queueHead>8)return false;
    if(a.track<0||a.track>=64)throw std::invalid_argument("Moving admission requires an ordinary transition record");
    const auto& transition=data.transitions[std::size_t(a.track)];
    const int selected=a.shortTrack?transition.shortTrack:transition.rawTrack;
    if(a.queueHead==8||a.queueHead==-1)return false;
    const int direction=admission_detail::directionBin(std::uint16_t(std::uint32_t(transition.facing)<<8));
    if(direction==a.queueHead)return false;
    // The stock descriptor zero has a zero jump field, so cannot pass the
    // original nonzero-index check. No extracted descriptor table is embedded.
    if(!selected)return false;
    if(selected<1||selected>6)throw std::invalid_argument("Moving admission special descriptor is not recovered");
    if(data.tracks[std::size_t(selected-1)].jumpIndex!=a.index||a.index==0)return false;
    const auto candidate=data.transitions[std::size_t(a.queueHead+direction*8)].rawTrack;
    if(!candidate)return false;
    if(candidate<1||candidate>6)throw std::invalid_argument("Moving admission special candidate is not recovered");
    return data.tracks[std::size_t(candidate-1)].entryIndex!=0;
}

template<class World>
void event(World& w,char k,int id=0,int a=0,int b=0){if(w.trace)w.trace(k,id,a,b);}
inline int sub(int a,int b){return signed32(std::uint32_t(a)-std::uint32_t(b));}
template<class World,class Motion>
std::optional<int> movingResident(int mover,int resident,int& result,
    World& w,const Motion& motion){
    const auto& own=motion.actors.at(mover);const auto& other=motion.actors.at(resident);
    const auto& data=*motion.data;OriginalRounding rounding;
    const auto current=[&](int id,const auto& a){
        const auto heading=a.body.current(w.gates.tick);event(w,'J',id,heading);return heading;
    };
    const int ownDirection=admission_detail::directionBin(current(mover,own));
    const int oppositeDirection=admission_detail::directionBin(std::uint16_t(current(resident,other)+0x7fff));
    const auto bearing=destinationDirection(data.directionsToTargets,own.position,other.position);
    event(w,'B',0,bearing);
    if(ownDirection==oppositeDirection){
        event(w,'Q',resident);event(w,'Q',mover);
        const double x=sub(own.position.x,other.position.x),y=sub(own.position.y,other.position.y),z=sub(own.position.z,other.position.z);
        // Preserve the actual x87 product/add order and signed wrapped deltas.
        const double squared=(x*x+z*z)+y*y;
        const int distance=signed32(std::uint32_t(std::int64_t(motion.squareRoot(squared))));event(w,'Z',0,distance);
        if(distance<=511&&admission_detail::directionBin(bearing)==ownDirection)return 7;
    }
    if(other.eligibility5a0){
        // Actual Unit kind query occurs only after the live eligibility byte.
        event(w,'K',resident,w.gates.objects.at(resident).kind);
        result=std::max(result,2);
    }else{
        event(w,'Y',resident);
        const bool pending=switchPending(other,data);event(w,'y',resident,pending);
        if(pending)result=std::max(result,2);
    }
    return std::nullopt;
}
inline int absolute(int n){return n<0?signed32(0u-std::uint32_t(n)):n;}
inline std::int16_t word(int n){return std::bit_cast<std::int16_t>(std::uint16_t(n));}
template<class World>
int lookup(TerrainCellPoint p,World& w){
    event(w,'L',p.x,p.y);const int index=int(p.y)*512+int(p.x);
    const int id=index>=0&&index<262144?w.gates.slots[std::size_t(index)]:-1;
    if(id!=-1){
        if(!w.cells.contains(id)||!w.gates.cells.contains(id))throw std::invalid_argument("Noncanonical admission slot");
        return id;
    }
    w.gates.storeFallbackPoint(p);event(w,'F',p.x,p.y);
    return w.gates.fallbackCell;
}
inline int opposite(int direction){return int((std::uint32_t(direction)-4u)&7u);}
template<class World>
int neighbor(int target,int d,World& w){
    event(w,'N',target,d);if(std::uint32_t(d)>=8)return target;
    const auto& point=w.gates.cells.at(target).point;
    const TerrainCellPoint p{point.x,point.y};const auto offset=w.directions[std::size_t(d)];
    return lookup({word(int(p.x)+offset.x),word(int(p.y)+offset.y)},w);
}
template<class World>
int registry(int cell,World& w){
    const int index=w.cells.at(cell).registry;
    const int result=index>=0&&std::size_t(index)<w.registry.size()&&w.registry[std::size_t(index)]?index:-1;
    event(w,'r',cell,result);return result;
}
template<class World>
int kind(int id,World& w){const int k=w.gates.objects.at(id).kind;event(w,'K',id,k);return k;}
template<class World>
int mission(int id,World& w){event(w,'M',id);return unitDiscoveryMission(w.gates.objects.at(id).mission);}
template<class World>
bool house(int left,int right,World& w){
    event(w,'h',left,right);if(right==-1)return false;
    if(left==right)return true;
    const auto& l=w.gates.houses.at(left);const auto& r=w.gates.houses.at(right);
    if(l.index==r.index)return true;
    return r.index!=-1&&(l.allies&(std::uint32_t(1)<<(std::uint32_t(r.index)&31u)))!=0;
}
template<class World>
bool indexAlly(int left,int right,World& w){
    event(w,'i',left,right);const auto& l=w.gates.houses.at(left);
    if(l.index==right)return true;
    return right!=-1&&(l.allies&(std::uint32_t(1)<<(std::uint32_t(right)&31u)))!=0;
}
template<class World>
void type(int id,World& w){event(w,'T',id);event(w,'t',id);}
template<class World>
bool slot(int id,World& w){
    event(w,'w',id,0);event(w,'v',id,2);type(id,w);event(w,'p',id,0);
    return w.objects.at(id).weapon;
}
template<class World>
bool canFire(int id,World& w){
    event(w,'C',id);event(w,'s',id);type(id,w);event(w,'c',id);
    return slot(id,w);
}
template<class World>
bool ability(int id,World& w){
    event(w,'b',id,17);event(w,'v',id,1);event(w,'v',id,2);return false;
}
template<class World,class Motion>
void validate(int mover,int target,int previous,const World& w,const Motion* motion){
    if(w.gates.slots.size()!=262144||!w.cells.contains(w.gates.fallbackCell)||
       !w.cells.contains(target)||(previous!=-1&&!w.cells.contains(previous))||
       !w.objects.contains(mover)||w.gates.objects.at(mover).kind!=1||w.registry.size()>32768)
        throw std::invalid_argument("Unit admission map/actor outside domain");
    for(const auto& [id,c]:w.cells){
        if(!w.gates.cells.contains(id)||c.land<0||c.land>=12)
            throw std::invalid_argument("Unit admission Cell outside domain");
    }
    for(const auto& [id,a]:w.gates.objects){
        if((a.kind!=1&&a.kind!=6)||!w.objects.contains(id)||!w.gates.houses.contains(a.owner)||
           (a.next!=-1&&!w.gates.objects.contains(a.next))||
           (!motion&&id!=mover&&w.objects.at(id).targetIdentity()!=-1))
            throw std::invalid_argument("Unit admission resident outside stationary profile");
    }
    if(motion){
        if(!motion->data||!motion->squareRoot||motion->actors.size()!=w.gates.objects.size())
            throw std::invalid_argument("Moving admission requires explicit actor and numeric associations");
        for(const auto& [id,a]:w.gates.objects)
            if(a.kind!=1||!motion->actors.contains(id))
                throw std::invalid_argument("Moving admission requires ordinary Unit identities");
    }
}
template<class World>
int unitTerrainAdmission(int target,int direction,int& level,std::uint8_t& elevated,int previous,World& w){
    if(w.gates.slots.size()!=262144||!w.cells.contains(target)||!w.gates.cells.contains(target)||
       !w.cells.contains(w.gates.fallbackCell)||!w.gates.cells.contains(w.gates.fallbackCell)||
       (previous!=-1&&!w.cells.contains(previous)))
        throw std::invalid_argument("Unit terrain admission map outside domain");
    event(w,'H',target,direction,previous);
    if(previous==-1){
        const auto& point=w.gates.cells.at(target).point;
        const TerrainCellPoint p{point.x,point.y};const auto o=w.directions[std::size_t(opposite(direction))];
        previous=lookup({word(int(p.x)+o.x),word(int(p.y)+o.y)},w);
    }
    const auto& t=w.cells.at(target);const auto& p=w.cells.at(previous);
    const auto setLevel=[&](int n){level=n;event(w,'W',0,4,n);};
    if(direction==-1){if(level==-1&&(t.flags&0x100))setLevel(int(t.level)+4);return 0;}
    if(level==-1&&(p.flags&0x100)){
        setLevel(int(p.level)+4);if(!(t.flags&0x200))return 7;
    }
    const bool bridge=(p.flags&0x100)!=0;
    const int delta=sub(bridge?int(p.level):level,int(t.level));
    switch(absolute(delta)){
    case 0:
        if(!((t.flags&0x100)&&(t.flags&0x200)&&bridge)&&level!=-1&&level!=int(t.level))return 7;
        return 0;
    case 1:return (delta>0?t.ramp:p.ramp)?0:7;
    case 4:
        if(int(p.level)==int(t.level)-4&&(level!=int(t.level)||!bridge))return 7;
        if(int(t.level)==int(p.level)-4){
            if(!(t.flags&0x100)||!(t.flags&0x200))return 7;
            elevated=1;event(w,'W',1,1,1);
        }
        return 0;
    default:return 7;
    }
}
template<class World,class Motion=UnitAdmissionMotionWorld>
int unitAdmission(int mover,int target,int direction,int level,int previous,std::uint8_t consult,World& w,const Motion* motion=nullptr,
    const UnitAdmissionOverlayServices* overlays=nullptr){
    validate(mover,target,previous,w,motion);
    auto& a=w.objects.at(mover);const auto& actor=w.gates.objects.at(mover);const auto& t=w.cells.at(target);
    std::uint8_t elevated=std::uint8_t((t.flags&0x100)&&(level==-1||absolute(sub(level,t.level))>1));
    std::uint8_t occupation=std::uint8_t(t.occupation);bool bit5=(t.occupation&32)!=0;int owner=t.owner;
    int r=registry(target,w);
    if(direction==8){
        if(r!=-1){const auto p=w.registry[std::size_t(r)]->point;if(p.x||p.y)return 0;}
        return 7;
    }
    const auto blocked=[&](int id,int d){if(id==-1)return false;const int n=absolute(sub(d,w.registry[std::size_t(id)]->direction));return n>2&&n<6&&direction!=-1;};
    if(blocked(r,direction))return 7;
    const int reverse=opposite(direction);r=registry(neighbor(target,reverse,w),w);
    if(blocked(r,reverse))return 7;
    if(unitTerrainAdmission(target,direction,level,elevated,previous,w)==7)return 7;
    if(level!=-1&&(t.flags&0x100)&&level==int(t.level)+4){occupation=std::uint8_t(t.elevatedOccupation);bit5=(t.elevatedOccupation&32)!=0;owner=t.elevatedOwner;}
    event(w,'l',mover,consult);if(consult)event(w,'d',mover); // Actual Drive +1C returns zero.
    int result=0;
    if(overlays){
        if(!overlays->cell)throw std::invalid_argument("Overlay admission requires actual Cell/type lookup");
        if(const auto overlay=overlays->cell(target)){
            const auto& o=*overlay;
            if(o.flag27a){
                if(!overlays->house)throw std::invalid_argument("Overlay admission requires actual House fields");
                event(w,'u',actor.owner);const auto h=overlays->house(actor.owner);
                // 4F52F0 preserves raw human134 when the global is nonzero.
                const auto controlled=overlays->overrideA3d298?h.human134:std::uint8_t(h.human134||h.control135);
                if(!controlled&&!overlays->overrideA3d298)return 7;
            }
            if(o.wall){
                if(o.crushable&&(a.crusher||ability(mover,w))){
                    if(indexAlly(actor.owner,o.owner,w))result=std::max(result,4);
                }else{
                    if(!canFire(mover,w))return 7;
                    (void)slot(mover,w); // Actual second selected-weapon query.
                    if(!overlays->weapon)throw std::invalid_argument("Overlay admission requires actual weapon fields");
                    const auto weapon=overlays->weapon(mover);
                    if(!weapon.flag144&&(!weapon.flag146||o.armor!=6))return 7;
                    result=std::max(result,indexAlly(actor.owner,o.owner,w)?4:5);
                }
            }
        }
    }
    int resident=elevated?t.elevatedHead:w.gates.cells.at(target).head;
    std::size_t visits=0;
    while(resident!=-1){
        if(++visits>w.gates.objects.size())throw std::invalid_argument("Cyclic admission resident list");
        const auto& obj=w.gates.objects.at(resident);const auto& other=w.objects.at(resident);
        if(resident==mover){bit5=false;occupation&=0xdf;resident=obj.next;continue;}
        event(w,'P',mover,(other.flags&1)?resident:-1); // Actual empty passenger vector.
        if(kind(resident,w)==6&&obj.gate){
            if(!movement_gate_policy::movementGateTraversable(resident,w.gates)){
                if(house(obj.owner,actor.owner,w))result=std::max(result,3);
                else{if(!canFire(mover,w))return 7;result=std::max(result,5);}
            }
            resident=obj.next;continue;
        }
        if(mission(mover,w)==7&&resident==a.targetIdentity()&&kind(resident,w)==1)return 0;
        if(mission(mover,w)==11&&a.destination==resident)return 7;
        bool active=false;
        if(other.flags&4){
            if(motion){
                const auto& moving=motion->actors.at(resident);
                active=other.targetIdentity()!=-1;
                if(!active){event(w,'f',resident);active=moving.body.rotating(w.gates.tick);}
                if(!active){event(w,'m',resident);active=isMoving(moving);}
            }else{event(w,'f',resident);event(w,'m',resident);} // Legacy settled Facing/Drive.
        }
        if(movement_gate_policy::movementGateAllied(actor.owner,resident,w.gates)){
            if(active){
                if(const auto exit=movingResident(mover,resident,result,w,*motion))return *exit;
                resident=obj.next;continue;
            }
            if(kind(resident,w)==6)return 7;result=std::max(result,6);
        }else{
            event(w,'X',resident);(void)kind(resident,w); // Actual cast returns self for kinds1/6.
            if(other.state1b8==2)result=std::max(result,1);
            else{
                if(a.crusher||ability(mover,w)){
                    event(w,'t',resident);
                    if(other.crushable){
                        (void)movement_gate_policy::movementGateAllied(actor.owner,resident,w.gates);
                        throw std::invalid_argument("Crushing resident branch requires occupied-Unit join");
                    }
                }
                if(!slot(mover,w)&&!a.train)return 7;
                if(kind(resident,w)==6&&other.building1350)return 7;
                result=std::max(result,5);
            }
        }
        resident=obj.next;
    }
    const auto bits=w.speedBits[std::size_t(t.land)]&0x7fffffff;
    if(!elevated&&(bits==0||bits>0x7f800000))return 7; // x87 zero or unordered comparison.
    if(result)return result;
    if(!(occupation&0x3f))return 0;
    if(bit5)return 2;
    if(owner!=-1&&indexAlly(actor.owner,owner,w))return 2;
    if(a.crusher||ability(mover,w))return 0;
    if(a.train)return 5;
    if(!slot(mover,w))return 7;
    (void)slot(mover,w);
    return a.projectile275?5:7;
}
}
}
