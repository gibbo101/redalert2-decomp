// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
#include "sim/GroundDriveContext.hpp"
#include <functional>
#include <optional>
#include <string>
#include <stdexcept>
namespace ra2 {
// A host domain refusal, caught only while previewing an order. Other failures propagate.
struct UnsupportedGroundRoute : std::invalid_argument {using std::invalid_argument::invalid_argument;};
struct Position { double x=0,y=0; };
// Command/presentation adapter around the recovered, integer-coordinate drive core.
class Simulation {
    std::shared_ptr<const DriveData> data_;
    std::unique_ptr<GroundDriveContext> ground_;
    std::optional<std::uint16_t> pendingBodyTurn_;
    bool stopRequested_=false;
    void refresh();
    void groundMovement();
    void replaceGroundRoute();
public:
    Drive drive;
    Position position{}; // Read-only-by-convention presentation snapshot, in cells.
    int elevation=0;
    std::int32_t tick=0;
    bool moving=false,selected=false,paused=false;
    std::string status="LEFT CLICK THE RHINO TO SELECT";
    Simulation(Position start,int z,int rot,int speed,std::shared_ptr<const DriveData> data,bool passive=false);
    Simulation(const Simulation&);
    Simulation& operator=(const Simulation&);
    Simulation(Simulation&&) noexcept=default;
    Simulation& operator=(Simulation&&) noexcept=default;
    // Host lifetime/commands around complete ordinary Process. A copied Simulation
    // clones actor/Cell/buffer/lazy state and rebinds every context callback.
    void enableGround(std::unique_ptr<GroundDriveContext>);
    const GroundDriveProcessState* groundState() const {return ground_?&ground_->state:nullptr;}
    const GroundDriveContext* groundContext() const {return ground_.get();}
    Coord coordinates() const {return ground_?drive.position:Coord{drive.position.x,drive.position.y,elevation*104};}
    double drawElevation() const {return coordinates().z/104.0;}
    bool move(Position target,const std::function<bool(int,int,int)>& clear,bool append=false);
    void turnBody(int delta);
    void turnTurret(int delta);
    void aim(Position target);
    void stop();
    void step();
};
std::uint16_t directionTo(Position from,Position to);
}
