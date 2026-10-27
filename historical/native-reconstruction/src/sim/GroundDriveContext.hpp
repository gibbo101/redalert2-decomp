// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/GroundDriveProcess.hpp"
#include <memory>
namespace ra2 {
// Host ownership for one ordinary Unit. Clone is the prototype's isolated route
// preview, not an original-game operation. The state address stays stable when
// a Simulation is moved; cloned services must refer only to the clone's state.
struct GroundDriveContext {
    GroundDriveProcessState state;
    GroundDriveProcessServices services;
    virtual bool process(const DriveData& data,int speed,int tick,int padding,
        const GroundStateStore& actorStore={},const GroundStateStore& rampStore={}){
        return processOrdinaryGroundDrive(state,data,speed,tick,padding,services,actorStore,rampStore);
    }
    virtual std::unique_ptr<GroundDriveContext> clone() const=0;
    virtual ~GroundDriveContext()=default;
};
}
