// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Facing.hpp"
#include "sim/Targeting.hpp"
#include <optional>
#include <array>
#include <cstdint>
#include <deque>
#include <memory>
#include <vector>

namespace ra2 {
// Original world coordinates: signed integer leptons, 256 per cell.
struct Coord {
    std::int32_t x=0,y=0,z=0;
    bool operator==(const Coord&) const = default;
};
struct TrackPoint { std::int32_t x=0,y=0,facing=0; };
struct DriveTrack {
    std::vector<TrackPoint> points;
    int jumpIndex=-1,entryIndex=0,cellIndex=-1;
};
struct TrackTransform { int rawTrack=0,flags=0,facing=0,shortTrack=0; };
// Filled from the hash-checked owned executable, never compiled-in extracted tables.
struct DriveData {
    std::array<DriveTrack,6> tracks;
    std::array<TrackTransform,64> transitions;
    double stopScale=0.0;
    DirectionData directionsToTargets;
};
int internalSpeed(int iniSpeed,int previous=0);
int currentSpeed(int baseSpeed,double percentage);
Coord cellCenter(int x,int y,int z=0);
std::pair<int,int> directionOffset(int direction);

// Bounded recovery: flat-ground ordinary drive tracks and a supplied direction
// queue. No pathfinder, combat, towing or short/special tracks. See CURVES.md.
class Drive {
    std::shared_ptr<const DriveData> data_;
    void prepare(std::int32_t tick);
    void advance(std::int32_t tick,bool suppressSpeed);
public:
    Coord position{},head{},destination{};
    std::optional<Coord> navigationTarget;
    Facing body,turret;
    std::deque<int> route;
    int baseSpeed=0,track=-1,index=0,accumulator=0;
    double terrainScale=1.0,movementScale=1.0;
    bool driving=false,hasDestination=false,wasRotating=false;
    bool passive=false; // Original UnitType Passive guard, not a smoother-turn option.
    bool turretTurning=false,manualTurret=false;
    Drive(std::shared_ptr<const DriveData> data,Coord start,int rot,int speed);
    void order(Coord target,const std::vector<int>& directions);
    void stop();
    void processMovement(std::int32_t tick);
    void process(std::int32_t tick);
    void updateTurret(std::int32_t tick);
    void aimAt(Coord target,std::int32_t tick);
    bool active() const { return driving || (hasDestination && !route.empty()); }
};
}
