// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/Drive.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <cmath>
#include <cfenv>
#include <stdexcept>

namespace ra2 {
namespace {
constexpr double TrackFraction=0x1.2492492492492p-3; // owned binary64 1/7
constexpr double ArrivalFraction=0x1.745d1745d1746p-4; // owned binary64 1/11
}
int internalSpeed(int value,int previous) {
    // Base RA2 INI conversion block 0x6D2021..0x6D2061.
    if(value==-1) return previous;
    return std::min(255,std::clamp(value,0,100)*256/100);
}
int currentSpeed(int speed,double percentage) {
    // Healthy/unpromoted, country and instance multipliers == 1. Original FTOL
    // truncates after multiplying the integer base speed by the clamped percentage.
    if(!std::isfinite(percentage)) throw std::invalid_argument("Non-finite drive percentage");
    OriginalRounding rounding;
    return int(speed*std::clamp(percentage,0.0,1.0));
}
Coord cellCenter(int x,int y,int z) { return {x*256+128,y*256+128,z}; }
std::pair<int,int> directionOffset(int d) {
    if(d<0||d>7) throw std::invalid_argument("Drive direction outside 0..7");
    constexpr std::array<std::pair<int,int>,8> offsets{{{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}}};
    return offsets[std::size_t(d)];
}
Drive::Drive(std::shared_ptr<const DriveData> data,Coord start,int rot,int speed)
    :data_(std::move(data)),position(start),baseSpeed(internalSpeed(speed)) {
    if(!data_||data_->tracks[0].points.empty()||data_->tracks[1].points.empty())
        throw std::invalid_argument("Original drive data is required");
    body.setRate(rot);turret.setRate(rot);
}
void Drive::order(Coord target,const std::vector<int>& directions) {
    if(directions.size()>23) throw std::invalid_argument("Supplied route exceeds 23 cells");
    for(int d:directions) (void)directionOffset(d);
    destination=target;hasDestination=!directions.empty()||driving;
    route.assign(directions.begin(),directions.end());manualTurret=false;
}
void Drive::stop() {
    // Original ILocomotion::Stop_Moving caps speed and clears destination; the
    // command adapter clears its supplied route. The active track finishes.
    movementScale=std::min(movementScale,data_->stopScale);
    hasDestination=false;route.clear();
}
void Drive::prepare(std::int32_t tick) {
    if(!hasDestination||route.empty()) return;
    const int d=route.front();const auto wanted=std::uint16_t(d<<13);
    if(body.current(tick)!=wanted) {body.setDesired(wanted,tick);return;}
    const auto [dx,dy]=directionOffset(d);
    head={position.x+dx*256,position.y+dy*256,position.z};
    const int next=route.size()>1?route[1]:d;
    track=d*8+next;
    if(data_->transitions.at(std::size_t(track)).rawTrack==0) track=d*9;
    if(data_->transitions.at(std::size_t(track)).flags&8) {
        const auto [nx,ny]=directionOffset(next);
        head.x+=nx*256;head.y+=ny*256;
        route.pop_front();
    }
    route.pop_front();movementScale=terrainScale;index=0;driving=true;
}
void Drive::advance(std::int32_t tick,bool suppressSpeed) {
    if(!driving||track<0) {accumulator=0;return;}
    if(!suppressSpeed) accumulator+=currentSpeed(baseSpeed,movementScale);
    auto transform=data_->transitions.at(std::size_t(track));
    const DriveTrack* rawTrack=&data_->tracks.at(std::size_t(transform.rawTrack-1));
    const int queued=route.empty()?-1:route.front();
    bool changedDirection=queued>=0 && queued!=((transform.facing+16)>>5&7);
    auto point=[&](int i) {
        auto p=rawTrack->points.at(std::size_t(i));
        if(transform.flags&1) {std::swap(p.x,p.y);p.facing=(-64-p.facing)&255;}
        if(transform.flags&2) {p.x=-p.x;p.facing=(-p.facing)&255;}
        if(transform.flags&4) {p.y=-p.y;p.facing=(-128-p.facing)&255;}
        p.x+=head.x;p.y+=head.y;return p;
    };
    // Strictly > 7, not >= 7. Residual seven remains an interpolation update.
    while(accumulator>7) {
        accumulator-=7;
        const auto& raw=rawTrack->points.at(std::size_t(index));
        if(index!=0 && raw.x==0 && raw.y==0) {
            const int distance=std::abs(head.x-position.x)+std::abs(head.y-position.y);
            // Original x87 order and its 1/11 binary64 constant. On the bounded
            // ordinary tracks this truncation is checked against original code.
            accumulator+=int((1.0-distance*ArrivalFraction)*7.0);
            position=head;head={};track=-1;index=0;driving=false;return;
        }
        const auto p=point(index);
        position={p.x,p.y,head.z};body.setCurrent(std::uint16_t(p.facing<<8),tick);
        // Original switch point and entry point are stored with the raw track.
        // For an ordinary Unit, the complete advance routine also requires Passive.
        if(changedDirection && passive && index>0 && index==rawTrack->jumpIndex) {
            const int nextTrack=(((transform.facing+16)>>5)&7)*8+queued;
            const auto nextTransform=data_->transitions.at(std::size_t(nextTrack));
            if(nextTransform.rawTrack>0) {
                const auto* nextRaw=&data_->tracks.at(std::size_t(nextTransform.rawTrack-1));
                if(nextRaw->entryIndex>0) {
                    const auto [dx,dy]=directionOffset(queued);
                    head.x+=dx*256;head.y+=dy*256;
                    track=nextTrack;transform=nextTransform;rawTrack=nextRaw;
                    index=nextRaw->entryIndex-1;changedDirection=false;route.pop_front();
                }
            }
        }
        ++index;
    }
    if(accumulator>0) {
        const auto& raw=rawTrack->points.at(std::size_t(index));
        if(index!=0 && raw.x==0 && raw.y==0) return;
        const auto p=point(index);
        // Original stores a single-precision fraction, then FTOLs each component.
        // Do not replace this with normalization, a fixed speed, or an endpoint lerp.
        const float fraction=float(accumulator*TrackFraction);
        const Coord candidate{position.x+int((p.x-position.x)*double(fraction)),
                              position.y+int((p.y-position.y)*double(fraction)),position.z};
        auto cell=[](Coord c){return std::pair{c.x/256,c.y/256};};
        const Coord next{p.x,p.y,head.z};
        // The original prevents a diagonal interpolant from briefly entering a
        // third cell at a corner. It holds at residual <=3, otherwise takes next.
        if(cell(candidate)!=cell(position) && cell(candidate)!=cell(next)) {
            if(accumulator>3) position=next;
        } else position=candidate;
    }
}
void Drive::updateTurret(std::int32_t tick) {
    // No combat target or spinning/locked weapon. An optional destination
    // supplies the original coordinate-bearing branch. Busy turrets finish first.
    if(!manualTurret && !turret.rotating(tick)) {
        const auto wanted=navigationTarget?destinationDirection(data_->directionsToTargets,position,*navigationTarget):body.current(tick);
        turret.setDesired(wanted,tick);
    }
    turretTurning=turret.rotating(tick);
}
void Drive::aimAt(Coord target,std::int32_t tick) {
    manualTurret=true;
    turret.setDesired(destinationDirection(data_->directionsToTargets,position,target),tick);
}
void Drive::processMovement(std::int32_t tick) {
    OriginalRounding rounding;
    if(driving && track>=0) {
        advance(tick,false);
        if(!driving && (hasDestination || !route.empty())) {prepare(tick);advance(tick,true);}
    } else if(body.rotating(tick)) {
        wasRotating=true;
    } else {
        wasRotating=false;
        if(hasDestination || !route.empty()) {prepare(tick);advance(tick,false);}
    }
    if(!driving && route.empty()) hasDestination=false;
}
void Drive::process(std::int32_t tick) {processMovement(tick);updateTurret(tick);}
}
