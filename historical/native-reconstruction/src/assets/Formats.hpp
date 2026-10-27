// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Bytes.hpp"
#include <array>
#include <map>
#include <string_view>
#include <vector>

namespace ra2 {
using Section = std::map<std::string,std::string>;
// Original GetBool value boundary, with the CRT in its locale-zero mode.
// Only the first decoded byte is consumed; unrecognized values retain fallback.
std::uint8_t iniBooleanValue(std::string_view value,std::uint8_t fallback);
class Ini {
    std::map<std::string,Section> sections_;
public:
    explicit Ini(const std::string& text);
    bool hasSection(const std::string& name) const;
    const Section& section(const std::string& name) const;
    std::string get(const std::string& section,const std::string& key,const std::string& fallback="") const;
    int integer(const std::string& section,const std::string& key,int fallback=0) const;
    double number(const std::string& section,const std::string& key,double fallback=0) const;
    std::uint8_t boolean(const std::string& section,const std::string& key,std::uint8_t fallback=0) const;
};
std::vector<int> integers(const std::string& text);
Bytes decodeBase64(const std::string& text);
Bytes unpackMap(const Bytes& packed);
struct Color { std::uint8_t r=0,g=0,b=0,a=255; };
using Palette = std::array<Color,256>;
struct HsvColor {std::uint8_t hue=0,saturation=0,value=0;};
Palette readPalette(const Data& data);
struct TileImage {
    int width=0,height=0,x=0,y=0;
    std::uint8_t terrain=0,ramp=0;
    Bytes pixels,depth,coverage,basePixels,baseDepth,extraPixels,extraDepth;
    std::uint32_t flags=0; // Resident subtile flags at +24hex, retained from input.
};
std::vector<TileImage> readTmp(const Data& data);
struct MapCell { int x=0,y=0; std::uint32_t tile=0; std::uint8_t sub=0,z=0; };
struct MapData {
    int width=0,height=0;
    std::vector<int> local;
    std::vector<MapCell> cells;
    std::map<int,std::pair<int,int>> waypoints;
    std::array<double,3> tint{1,1,1};
    double ambient=1,ground=0,level=0;
};
MapData readMap(const Ini& ini);
struct Vec3 { float x=0,y=0,z=0; };
using Matrix = std::array<float,12>;
struct Voxel { std::uint8_t x=0,y=0,z=0,color=0,normal=0; };
struct VoxelSection {
    std::string name;
    float scale=1;
    Vec3 min,max;
    std::array<int,3> size{};
    int normalType=0;
    Matrix base{};
    std::vector<Voxel> voxels;
    std::vector<Bytes> spans; // Validated original runs, retained for forward/reverse raster traversal.
};
struct VoxelModel { std::vector<VoxelSection> sections; };
struct Animation {
    int frames=0;
    std::vector<std::string> names;
    std::vector<Matrix> transforms;
    const Matrix& at(int frame,std::size_t section) const;
};
VoxelModel readVxl(const Data& data);
Animation readHva(const Data& data);
}
