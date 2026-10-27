// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
namespace ra2 {
// Supplied display tick only. Actor poses/targets are borrowed from the scene;
// no platform owner, Simulation, mirrored Drive or cached pose lives here.
struct OwnedUnitDrawFrame {int tick=0;};
}
