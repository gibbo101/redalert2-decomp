// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/Renderer.hpp"
#include <fstream>

namespace ra2 {
// Fixed host scenario, not recovered map scripting or original input policy.
struct CrossingScenario {
    static constexpr Position entry{86.5,101.5},destination{92.5,101.5};
    static constexpr int lightX=92,lightY=101; // Optional host INGALITE placement.
    std::size_t scenery=0;
    explicit CrossingScenario(const GameAssets&);
    Simulation initial(const GameAssets&) const;
    void center(Renderer&) const;
};

// Native integration diagnostics only. Original fidelity is established separately
// by the hash-pinned traversal/gate/getter and presentation differential suites.
class CrossingRegression {
    const GameAssets& assets_;
    GameAssets bare_;
    Renderer baseline_;
    std::filesystem::path output_;
    std::ofstream csv_;
    int samples_=0,occluded_=0,maximum_=0,first_=-1,last_=-1;
    bool emerged_=false;
    bool lightDemo_=false;
    int minimumBrightness_=2147483647,maximumBrightness_=-2147483647-1;
public:
    CrossingRegression(const GameAssets&,const Renderer&,const std::filesystem::path& output={});
    void sample(const Simulation&,const Renderer&);
    void finish(const Simulation&,Renderer&);
};
}
