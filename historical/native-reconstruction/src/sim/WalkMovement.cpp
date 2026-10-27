// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/WalkMovement.hpp"
#include "sim/WalkHead.hpp"
#include "sim/WalkHeadTransfer.hpp"
#include "sim/WalkCommands.hpp"
#include "sim/WalkRoute.hpp"
#include "sim/GroundMovementPlacement.hpp"
#include "sim/FootCoordinates.hpp"
#include "sim/OriginalMath.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace ra2 {
namespace {
std::uint8_t processWalkKernel(WalkMovementState& w,WalkMovementActor a,
    const WalkMovementNumerics& n,const WalkMovementServices& s,int tick,
    int bridgeHeight,Coord empty,WalkArrivalContext* arrival,int levelHeight,
    WalkQueuedContext* queued=nullptr) {
    const auto event=[&](char c,std::int64_t x=0,std::int64_t y=0,std::int64_t z=0){if(s.trace)s.trace(c,x,y,z);};
    const auto actorStore=[&](int offset,int value){event('A',offset,std::uint32_t(value));};
    const auto byte=[&](std::uint8_t& target,int offset,std::uint8_t value,char owner){target=value;event(owner,offset,value);};
    const auto coordinates=[&]{event('C');return a.ground.position;};
    const auto facingTick=[&]{return queued&&queued->route&&queued->route->clock?queued->route->clock():tick;};
    const auto cell=[](Coord p){return TerrainCellPoint{std::int16_t(p.x/256),std::int16_t(p.y/256)};};
    const auto integer=[](double value){
        if(!std::isfinite(value)||value<-2147483648.0||value>=2147483648.0)
            throw std::invalid_argument("Walk numeric result outside recovered finite domain");
        return std::int32_t(value);
    };
    byte(w.inProcessing35,0x35,1,'L');
    OriginalRounding rounding;
    if(w.head==empty) {
        if(!queued)throw std::invalid_argument("Walk needs original head/subcell selection");
        if(w.destination==empty) {
            if(a.percentage468>0) {
                event('V',0);a.percentage468=0;actorStore(0x468,0);actorStore(0x46c,0);
            }
        } else {
            auto& route=arrival->actor.route4d0;
            if(route[0]==-1) {
                if(!queued->route)throw std::invalid_argument("Walk route finding/retry requires recovery");
                auto& refill=*queued->route;auto retry=refill.retry530;
                if(&refill.target494!=&queued->actor.target494)
                    throw std::invalid_argument("Walk route and head require the same target owner");
                if(!refill.clock)throw std::invalid_argument("Walk route requires a clock owner");
                const int start=retry.start;int remaining=retry.remaining;
                if(start!=-1) {
                    const int now=refill.clock();
                    const int elapsed=signed32(std::uint32_t(now)-std::uint32_t(start));
                    remaining=elapsed>=remaining?0:signed32(std::uint32_t(remaining)-std::uint32_t(elapsed));
                }
                if(remaining) {
                    // Actual Infantry508730 only changes states3/6/17. It
                    // does not clear57A/reallyMoving/percentage or the timer.
                    event('u');
                    if(refill.state5ac==3||refill.state5ac==6||refill.state5ac==17){
                        refill.state5ac=-1;actorStore(0x5ac,-1);
                    }
                    byte(w.inProcessing35,0x35,0,'L');return w.moving34;
                }
                // FTOL77F110 consumes signed64 and the caller uses its low32,
                // including invalid conversions (indefinite64 has low0).
                const double duration=refill.interval13c8*900.;
                const int converted=signed32(!std::isfinite(duration)||duration<-0x1p63||duration>=0x1p63?
                    0u:std::uint32_t(std::int64_t(duration)));
                const int now=refill.clock(),padding=refill.temporaryPadding;
                retry.start=now;actorStore(0x530,now);
                retry.padding=padding;actorStore(0x534,padding);
                retry.remaining=converted;actorStore(0x538,converted);
                const auto destination=cell(w.destination);
                if(!refill.findRoute)throw std::invalid_argument("Walk route provider is unbound");
                if(!refill.findRoute(destination,0,0)) {
                    byte(w.reallyMoving36,0x36,0,'L');
                    throw std::invalid_argument("Walk failed route continuation requires recovery");
                }
                refill.counter53c=10;actorStore(0x53c,10);
                event('p'); // actual Infantry508AB0 ordinary post-route check
                int count=0;
                if(refill.target494) {
                    while(count<24&&route[std::size_t(count)]!=-1&&route[std::size_t(count)]!=8)++count;
                }
                if((!refill.target494||count<4)&&refill.jumpJetB44)
                    throw std::invalid_argument("Walk JumpJet post-route child requires recovery");
                // Read the queue only after route writes/counter/post-route.
            }
            const int direction=route[0];
            if(direction==8)throw std::invalid_argument("Walk special direction requires recovery");
            const auto [dx,dy]=directionOffset(direction&7);
            const auto offset=[&](Coord p){return Coord{
                signed32(std::uint32_t(p.x)+std::uint32_t(dx)*256u),
                signed32(std::uint32_t(p.y)+std::uint32_t(dy)*256u),p.z};};
            const auto candidate=offset(a.ground.position);const auto packed=cell(candidate);
            if(!queued->coordinateCell)throw std::invalid_argument("Walk preparation requires coordinate Cells");
            const auto rawCandidate=offset(a.ground.position);
            const auto bridgeCell=queued->coordinateCell(rawCandidate);
            if(((bridgeCell.flags>>8)&1u)^a.ground.bridge79)
                byte(queued->transition57b,0x57b,1,'A');
            // Actual Object current-Cell5D51E0 performs two independent raw
            // coordinate snapshots/lookups. The first result is discarded.
            const auto first=a.ground.position;queued->coordinateCell(first);
            const auto second=a.ground.position;const auto current=queued->coordinateCell(second);
            const auto bridge=a.ground.bridge79;
            const int level=int(current.level)+(bridge?4:0);
            if(!s.lookup||!queued->admission)throw std::invalid_argument("Walk preparation requires Infantry admission");
            const auto target=s.lookup(packed);
            if(queued->admission(target,direction,level,0,1)!=0)
                throw std::invalid_argument("Walk nonzero Infantry admission continuation requires recovery");
            if(prepareWalkHead(w,queued->actor,candidate,queued->inputs,queued->head)) {
                byte(w.reallyMoving36,0x36,1,'L');
                if(!arrival->actor.onMap7d) {
                    byte(w.inProcessing35,0x35,0,'L');return w.moving34;
                }
                const auto point=coordinates();const auto heading=destinationDirection(n.direction,point,w.head);
                event('T',heading);a.body.setCurrent(heading,facingTick());
                event('V',1);a.percentage468=1;actorStore(0x468,0);actorStore(0x46c,0x3ff00000);
            } else {
                event('V',0);a.percentage468=0;actorStore(0x468,0);actorStore(0x46c,0);
            }
        }
        byte(a.field57a,0x57a,0,'A');byte(w.inProcessing35,0x35,0,'L');return w.moving34;
    }
    byte(w.reallyMoving36,0x36,1,'L');
    const auto from=coordinates();
    const auto dx=signed32(std::uint32_t(from.x)-std::uint32_t(w.head.x));
    const auto dy=signed32(std::uint32_t(from.y)-std::uint32_t(w.head.y));
    if(std::abs(std::int64_t(dx))>(1<<20)||std::abs(std::int64_t(dy))>(1<<20)||!n.squareRoot)
        throw std::invalid_argument("Walk distance outside recovered domain/services");
    if(integer(n.squareRoot(double(dx)*dx+double(dy)*dy))<17) {
        if(!arrival)throw std::invalid_argument("Walk arrival/next-subcell handling requires recovery");
        auto& actor=arrival->actor;auto& service=arrival->services;
        if(!s.placement.mark)throw std::invalid_argument("Walk arrival requires Mark");
        s.placement.mark(0);
        auto& route=actor.route4d0;
        if(route[0]==-1){route[1]=-1;actorStore(0x4d4,-1);}
        for(int i=0;i<23;++i){route[i]=route[i+1];actorStore(0x4d0+4*i,route[i]);}
        route[23]=-1;actorStore(0x52c,-1);
        setFootLocation(a.ground,w.head,s.placement,actorStore);
        actor.cell450=cell(w.head);
        actorStore(0x450,signed32(std::uint32_t(std::uint16_t(actor.cell450.x))|
            (std::uint32_t(std::uint16_t(actor.cell450.y))<<16)));
        setActorRelativeHeight(a.ground,0,bridgeHeight,s.placement,actorStore);
        byte(a.field5a1,0x5a1,0,'A');
        const auto clearHead=[&]{
            w.head.x=empty.x;event('L',0x28,std::uint32_t(w.head.x));
            w.head.y=empty.y;event('L',0x2c,std::uint32_t(w.head.y));
            w.head.z=empty.z;event('L',0x30,std::uint32_t(w.head.z));
        };
        // Retain this facade's named occupation services while sharing the
        // actual head-transfer order and Object-coordinate snapshot boundaries.
        if(queued)prepareWalkHead(w,queued->actor,empty,queued->inputs,queued->head);
        else detail::transferWalkHead(w.head,a.ground.position,empty,empty,
            [&](const Coord& p){
                if(!service.release)throw std::invalid_argument("Walk arrival requires release occupation");
                service.release(p);
            },[&](Coord){clearHead();},
            [](Coord){throw std::logic_error("Empty Walk arrival selected a nonempty request");},
            [&](const Coord& p){
                if(!service.occupy)throw std::invalid_argument("Walk arrival requires claim occupation");
                service.occupy(p);
            });
        const auto percentage=[&]{event('V',0);a.percentage468=0;actorStore(0x468,0);actorStore(0x46c,0);};
        if(route[0]==-1)percentage();
        if(!service.notify)throw std::invalid_argument("Walk arrival requires notification174");
        service.notify(2);
        // These late raw bytes may be changed by notification. The original
        // early exits skip both the final Mark(1) and the57A clear.
        if(!actor.onMap7d||actor.flag76||actor.flag7a){
            byte(w.inProcessing35,0x35,0,'L');return w.moving34;
        }
        bool complete=w.destination==empty;
        if(!complete) {
            const auto secondary=[&]{
                event('P');
                if(actor.secondaryIndex574>=0)throw std::invalid_argument("Walk arrival indexed Foot coordinates require binding");
                return footSecondaryCoordinates(actor.secondaryIndex574,{},
                    {[&]{return w.head==empty?a.ground.position:w.head;},coordinates});
            };
            if(cell(secondary())==cell(w.destination)) {
                const auto point=secondary();
                auto difference=signed32(std::uint32_t(point.z)-std::uint32_t(w.destination.z));
                if(difference<0)difference=signed32(0u-std::uint32_t(difference));
                const auto threshold=signed32(std::uint32_t(levelHeight)*2u);
                complete=difference<threshold;
            }
        }
        if(complete) {
            if(!service.destination)throw std::invalid_argument("Walk arrival requires destination410");
            service.destination(0,1);percentage();clearHead();
            // Actual interface+48 is Stop_Moving71E110, not the immediate-head
            // setter. It clears destination and always resets an empty head.
            WalkCommandServices commands;commands.resetMovement=service.resetMovement;commands.trace=s.trace;
            stopWalkMovement(w,commands,empty);
            byte(w.reallyMoving36,0x36,0,'L');
        }
        s.placement.mark(1);
    }
    else if(a.immobilized3fc>0)byte(w.reallyMoving36,0x36,0,'L');
    else {
        event('V',1);a.percentage468=1;actorStore(0x468,0);actorStore(0x46c,0x3ff00000);
        if(!s.speed)throw std::invalid_argument("Walk speed service required");
        event('S');const auto speed=s.speed();
        byte(a.field5a1,0x5a1,0,'A');
        const auto point=coordinates();
        const auto heading=destinationDirection(n.direction,point,w.head);
        event('T',heading);a.body.setCurrent(heading,facingTick());
        // Actor Cell getter precedes the raw actor-position reread.
        event('Q');const auto before=cell(a.ground.position);
        const auto raw=a.ground.position;
        if(!std::isfinite(n.radiansPerFacing)||!n.sine||!n.cosine)
            throw std::invalid_argument("Walk trigonometric services required");
        const double radians=(signed16(heading)-0x3fff)*n.radiansPerFacing;
        const auto y=integer(double(raw.y)-double(n.sine(radians))*speed);
        const auto x=integer(double(n.cosine(radians))*speed+double(raw.x));
        const Coord next{x,y,raw.z};const auto after=cell(next);
        if(before!=after) {
            if(!s.placement.mark)throw std::invalid_argument("Walk crossing requires Mark");
            s.placement.mark(0);
            setFootLocation(a.ground,next,s.placement,actorStore);
            if(!s.lookup)throw std::invalid_argument("Walk crossing requires map lookup");
            const auto oldCell=s.lookup(before);const auto newCell=s.lookup(after);
            if(int(newCell.level)==int(oldCell.level)-4&&(newCell.flags&0x100u))
                byte(a.ground.bridge79,0x79,1,'A');
            if(!(newCell.flags&0x100u)&&(oldCell.flags&0x100u))
                byte(a.ground.bridge79,0x79,0,'A');
            setActorRelativeHeight(a.ground,0,bridgeHeight,s.placement,actorStore);
            s.placement.mark(1);
            if(!s.currentCell)throw std::invalid_argument("Walk crossing requires current Cell");
            const auto current=s.currentCell(a.ground.position);
            if(!s.dirty)throw std::invalid_argument("Walk crossing requires dirty Cell effect");
            s.dirty(current);
        } else {
            const auto saved=a.ground.marked74;byte(a.ground.marked74,0x74,0,'A');
            setFootLocation(a.ground,next,s.placement,actorStore);
            setActorRelativeHeight(a.ground,0,bridgeHeight,s.placement,actorStore);
            byte(a.ground.marked74,0x74,saved,'A');
        }
    }
    byte(a.field57a,0x57a,0,'A');byte(w.inProcessing35,0x35,0,'L');
    return w.moving34; // Original returns the raw Is_Moving byte, not really36.
}
}
std::uint8_t processCommittedWalk(WalkMovementState& w,WalkMovementActor a,
    const WalkMovementNumerics& n,const WalkMovementServices& s,int tick,int bridgeHeight,Coord empty){
    return processWalkKernel(w,a,n,s,tick,bridgeHeight,empty,nullptr,0);
}
std::uint8_t processSelectedWalk(WalkMovementState& w,WalkMovementActor a,
    const WalkMovementNumerics& n,const WalkMovementServices& s,WalkArrivalContext& arrival,
    int tick,int bridgeHeight,int levelHeight,Coord empty){
    return processWalkKernel(w,a,n,s,tick,bridgeHeight,empty,&arrival,levelHeight);
}
std::uint8_t processQueuedWalk(WalkMovementState& w,WalkMovementActor a,
    const WalkMovementNumerics& n,const WalkMovementServices& s,WalkArrivalContext& arrival,
    WalkQueuedContext& queued,int tick){
    if(&queued.actor.position!=&a.ground.position)
        throw std::invalid_argument("Walk preparation and movement require the same actor coordinates");
    return processWalkKernel(w,a,n,s,tick,queued.inputs.bridgeHeight,queued.inputs.empty,
        &arrival,queued.inputs.levelHeight,&queued);
}
}
