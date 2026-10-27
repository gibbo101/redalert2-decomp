// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/GroundDriveAdvanceResult.hpp"
#include "sim/OriginalMath.hpp"
#include <bit>
#include <cmath>
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return signed32(std::uint32_t(a)+std::uint32_t(b));}
int sub(int a,int b){return signed32(std::uint32_t(a)-std::uint32_t(b));}
int absolute(int n){return n<0?sub(0,n):n;}
std::int16_t cell(int n){return std::bit_cast<std::int16_t>(std::uint16_t(n/256));}
bool same(Coord a,Coord b){return cell(a.x)==cell(b.x)&&cell(a.y)==cell(b.y);}
void write(const GroundStateStore& w,int offset,int value){if(w)w(offset,value);}
}
static bool advanceGroundDrive(GroundDriveAdvanceState& s,const DriveData& data,
    int speed,double percentage,int tick,bool suppressSpeed,
    const GroundDriveAdvanceServices& svc,const GroundStateStore& w,int queued,
    const std::function<bool(int)>& finish){
    if(!svc.ground.floor||!svc.ground.mark||!svc.coordinateCell||!svc.wordCell||
       !svc.unmarkOccupation||!svc.notify||!svc.postCell||s.actor.bridge79)
        throw std::invalid_argument("Ordinary Advance requires empty nonbridge Cell/actor services");
    if(speed<0||speed>255||!std::isfinite(percentage))
        throw std::invalid_argument("Ordinary Advance speed outside bounded domain");
    if(queued<-1||queued>7||(queued!=-1&&!svc.rejectedSwitchAdmission))
        throw std::invalid_argument("Queued non-Passive Advance requires admission service");
    if(!s.driving||s.track==-1){s.accumulator=0;write(svc.driveStore,0x4c,0);return false;}
    if(s.track<0||s.track>=64)throw std::invalid_argument("Ordinary Advance track outside domain");
    const auto& t=data.transitions[std::size_t(s.track)];
    if(t.rawTrack<1||t.rawTrack>6)throw std::invalid_argument("Ordinary Advance has no raw track");
    const auto& raw=data.tracks[std::size_t(t.rawTrack-1)];
    auto point=[&](int index){
        if(index<0||std::size_t(index)>=raw.points.size())throw std::invalid_argument("Ordinary Advance raw index outside domain");
        auto p=raw.points[std::size_t(index)];
        if(t.flags&1){std::swap(p.x,p.y);p.facing=(-64-p.facing)&255;}
        if(t.flags&2){p.x=sub(0,p.x);p.facing=(-p.facing)&255;}
        if(t.flags&4){p.y=sub(0,p.y);p.facing=(-128-p.facing)&255;}
        return TrackPoint{add(p.x,s.head.x),add(p.y,s.head.y),p.facing};
    };
    auto terminal=[&]{
        (void)point(s.index);
        const auto& p=raw.points[std::size_t(s.index)];return s.index!=0&&p.x==0&&p.y==0;
    };
    OriginalRounding rounding;
    int remaining=add(s.accumulator,suppressSpeed?0:currentSpeed(speed,percentage));
    while(remaining>7){
        remaining=sub(remaining,7);
        if(terminal()){
            const int distance=add(absolute(sub(s.head.x,s.actor.position.x)),absolute(sub(s.head.y,s.actor.position.y)));
            remaining=add(remaining,int((1.0-double(distance)*0x1.745d1745d1746p-4)*7.0));
            s.reached5a0=1;write(w,0x5a0,1);s.reached5a1=0;write(w,0x5a1,0);
            placeDriveResidualGround(s.actor,s.head,0,svc.ground,w);
            // The original skips this clear when all three head words are
            // already zero; in that case it also retains the driving byte.
            if(s.head!=Coord{}){
                s.head.x=0;write(svc.driveStore,0x40,0);
                s.head.y=0;write(svc.driveStore,0x44,0);
                s.driving=false;write(svc.driveStore,0x63,0);
                s.head.z=0;write(svc.driveStore,0x48,0);
            }
            s.track=-1;write(svc.driveStore,0x58,-1);
            s.index=0;write(svc.driveStore,0x5c,0);
            if(finish)return finish(remaining);
            svc.notify(2);svc.postCell();s.accumulator=remaining;write(svc.driveStore,0x4c,remaining);return false;
        }
        const auto p=point(s.index);
        const Coord next{p.x,p.y,0};
        if(svc.occupationEligible&&svc.occupationEligible()){
            svc.unmarkOccupation(s.actor.position);
            s.reached5a0=0;write(w,0x5a0,0);s.reached5a1=0;write(w,0x5a1,0);
        }
        if(same(s.actor.position,next)){
            const std::uint8_t onMap=1;
            placeDriveCommittedSameCell(s.actor,next,onMap,0,svc.ground,w);
        }else{
            const auto previous=s.index?point(s.index-1):TrackPoint{s.actor.position.x,s.actor.position.y,0};
            svc.ground.mark(0);setFootLocation(s.actor,next,svc.ground,w);
            svc.wordCell(cell(previous.x),cell(previous.y));
            const void* crossed=nullptr;
            if(svc.crushing){
                if(!svc.crossingWordCell)throw std::invalid_argument("Overlay crossing lookup unbound");
                crossed=svc.crossingWordCell(cell(next.x),cell(next.y));
            }else svc.wordCell(cell(next.x),cell(next.y));
            svc.ground.mark(1);
            if(svc.crushing)markGroundDriveCrushing(crossed,*svc.crushing,w);
            const auto saved=s.actor.marked74;s.actor.marked74=0;write(w,0x74,0);
            setActorRelativeHeight(s.actor,0,0,svc.ground,w);
            s.actor.marked74=saved;write(w,0x74,saved);
        }
        s.body.setCurrent(std::uint16_t(std::uint32_t(p.facing)<<8),tick);
        if(s.index&&s.index==raw.cellIndex)svc.unmarkOccupation(s.actor.position);
        if(queued!=-1&&queued!=(((t.facing+16)>>5)&7)&&s.index>0&&s.index==raw.jumpIndex){
            const auto& next=data.transitions[std::size_t(((((p.facing+16)>>5)&7)*8)+queued)];
            if(next.rawTrack>0&&data.tracks.at(std::size_t(next.rawTrack-1)).entryIndex>0){
                const auto [dx,dy]=directionOffset(queued);
                svc.rejectedSwitchAdmission({add(s.head.x,dx*256),add(s.head.y,dy*256),s.head.z},queued);
            }
        }
        ++s.index;write(svc.driveStore,0x5c,s.index);
    }
    s.accumulator=remaining;write(svc.driveStore,0x4c,remaining);
    if(remaining<=0||terminal())return false;
    const auto p=point(s.index);const Coord old=s.actor.position;
    const Coord next{p.x,p.y,old.z};
    const auto* nextCell=svc.coordinateCell(next);
    const float fraction=float(double(remaining)*0x1.2492492492492p-3);
    const Coord interpolated{add(old.x,int(double(sub(p.x,old.x))*double(fraction))),
        add(old.y,int(double(sub(p.y,old.y))*double(fraction))),old.z};
    const auto* oldCell=svc.coordinateCell(old);
    const auto* interpolatedCell=svc.coordinateCell(interpolated);
    const Coord selected=interpolatedCell==nextCell||interpolatedCell==oldCell?interpolated:remaining>3?next:old;
    (void)svc.coordinateCell(selected);
    if(!same(s.actor.position,selected)){
        svc.ground.mark(0);setFootLocation(s.actor,selected,svc.ground,w);svc.ground.mark(1);
    }else{
        const auto saved=s.actor.marked74;s.actor.marked74=0;write(w,0x74,0);
        setFootLocation(s.actor,selected,svc.ground,w);s.actor.marked74=saved;write(w,0x74,saved);
    }
    return false;
}
void advanceOrdinaryGroundDrive(GroundDriveAdvanceState& s,const DriveData& data,
    int speed,double percentage,int tick,bool suppressSpeed,
    const GroundDriveAdvanceServices& svc,const GroundStateStore& w,int queued){
    (void)advanceGroundDrive(s,data,speed,percentage,tick,suppressSpeed,svc,w,queued,{});
}
bool advanceOrdinaryGroundDriveResult(GroundDriveAdvanceState& s,const DriveData& data,
    int speed,double percentage,int tick,bool suppressSpeed,
    const GroundDriveAdvanceServices& svc,const GroundStateStore& w,int queued,
    const std::function<bool(int)>& finish){
    if(!finish)throw std::invalid_argument("Result-bearing Advance requires its terminal continuation");
    return advanceGroundDrive(s,data,speed,percentage,tick,suppressSpeed,svc,w,queued,finish);
}
}
