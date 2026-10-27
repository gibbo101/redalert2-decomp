// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "platform/TerrainScenario.hpp"
#include <fstream>
namespace ra2 {
// Fixed native integration scenarios. These assertions do not prove original frames.
class TerrainRegression {
    const GameAssets& assets_;
    std::filesystem::path output_;
    std::ofstream csv_;
    int tilted_=0,lag_=0,positive_=0,negative_=0,minimum_=2147483647,maximum_=-2147483647;
    void stable(const Simulation&,Renderer&);
public:
    static constexpr Position rampEntry{65.5,26.5},rampExit{69.5,26.5},cliffEntry{51.5,72.5};
    static constexpr Position blockedEntry{73.5,41.5},blockedExit{74.5,41.5};
    TerrainRegression(const GameAssets&,const std::filesystem::path& output={});
    void ramp(const Simulation&,Renderer&);
    void finishRamp(const Simulation&,Renderer&);
    void cliff(const Simulation&,Renderer&);
};
}
