// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MovementGate.hpp"
namespace ra2 {
bool movementGateAllied(int house,int object,MovementGateWorld& w){return movement_gate_policy::movementGateAllied(house,object,w);}
bool makeMovementGateTraversable(int object,MovementGateWorld& w){return movement_gate_policy::makeMovementGateTraversable(object,w);}
bool movementGateTraversable(int object,MovementGateWorld& w){return movement_gate_policy::movementGateTraversable(object,w);}
bool checkMovementGates(int mover,TerrainCellPoint point,MovementGateWorld& w){return movement_gate_policy::checkMovementGates(mover,point,w);}
}
